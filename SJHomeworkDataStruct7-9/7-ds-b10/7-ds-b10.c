/*1652270 计算机2班 冯舜*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define STAT_OK 0
#define STAT_ERR 1
#define STAT_INFEASIBLE -1
#define STAT_OVERFLOW -2

typedef int Status;

typedef struct
{
	double coef;
	int expn;
} TermData;

struct TermPrototype
{
	TermData data;
	struct TermPrototype *next;
};
typedef struct TermPrototype Term, LNode, *TermP, *Polynomial;

Status InitPoly(Polynomial *P)
{
	*P = (TermP)malloc(sizeof(Term));
	if (*P == NULL)
		exit(STAT_OVERFLOW);
	(*P)->next = NULL;
	return STAT_OK;
}

Status ClearPoly(Polynomial *P)
{
	TermP q, p;
	p = (*P)->next;

	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}

	(*P)->next = NULL;
	return STAT_OK;
}

Status DestroyPoly(Polynomial *P)
{
	ClearPoly(P);
	free(*P);
	P = NULL;
	return STAT_OK;
}

Status isPolyEmpty(Polynomial *P)
{
	if ((*P)->next == NULL)
		return TRUE;
	else
		return FALSE;
}

int PolyTermNum(Polynomial *P)
{
	TermP p = (*P)->next;
	int len = 0;

	while (p)
	{
		p = p->next;
		len++;
	}
	return len;
}

Status GetTerm(Polynomial P, int i, TermData *objTerm)
{
	TermP p = P->next;
	int pos = 1;
	while (p && pos < i)
	{
		p = p->next;
		pos++;
	}
	if (!p || pos > i)
		return STAT_ERR;

	objTerm->coef = p->data.coef;
	objTerm->expn = p->data.expn;

	return STAT_OK;
}

TermP searchForPriorOfToBeInsert(Polynomial P, TermData objTerm)
{
	TermP p = P;
	while (p->next && objTerm.expn > p->next->data.expn)
	{
		p = p->next;
	}
	return p;
}

Status InsertTerm(Polynomial P, TermData objTerm)
{
	
	TermP prevTerm = searchForPriorOfToBeInsert(P, objTerm);
	if (prevTerm->next != NULL && prevTerm->next->data.expn == objTerm.expn)
	{
		//combine
		prevTerm->next->data.coef += objTerm.coef;
		if (fabs(prevTerm->next->data.coef) < 1e-6)
		{
			//delete this term
			TermP q;
			q = prevTerm->next;
			prevTerm->next = q->next;
			free(q);
		}
	}
	else
	{
		TermP newTerm = (TermP)malloc(sizeof(Term));
		if (!newTerm)
			exit(STAT_OVERFLOW);
		memcpy(&(newTerm->data), &objTerm, sizeof(objTerm));
		newTerm->next = prevTerm->next;
		prevTerm->next = newTerm;
	}
	return STAT_OK;
}

Status DeleteTerm(Polynomial P, int i)
{
	TermP prevTerm = P, tmpTerm;
	int pos = 1;
	while (prevTerm->next && pos < i)
	{
		prevTerm = prevTerm->next;
		pos++;
	}

	if (prevTerm->next == NULL || pos > i)
		return STAT_ERR;

	tmpTerm = prevTerm->next;
	prevTerm->next = tmpTerm->next;
	free(tmpTerm);

	return STAT_OK;
}

Status DeleteTermByP(Polynomial P, TermP prevTerm)
{
	TermP tmpTerm;

	tmpTerm = prevTerm->next;
	prevTerm->next = tmpTerm->next;
	free(tmpTerm);

	return STAT_OK;
}

Status SimplifyPoly(Polynomial A)
{
	if (A->next == NULL)
		return STAT_OK;
	TermP currTermFixedPrev = A;
	TermP currTermMovablePrev = currTermFixedPrev->next, tmpTerm;
	while (currTermMovablePrev->next)
	{

		if (currTermMovablePrev->next->data.expn != currTermFixedPrev->next->data.expn)
		{
			currTermFixedPrev = currTermMovablePrev;
			currTermMovablePrev = currTermMovablePrev->next;
		}
		else
		{
			currTermFixedPrev->next->data.coef += currTermMovablePrev->next->data.coef;
			tmpTerm = currTermMovablePrev->next;
			currTermMovablePrev->next = currTermMovablePrev->next->next;
			free(tmpTerm);
		}
	}
	currTermMovablePrev = A;
	while (currTermMovablePrev->next)
	{
		if (fabs(currTermMovablePrev->next->data.coef - 0) < 1e-6)
		{
			tmpTerm = currTermMovablePrev->next;
			currTermMovablePrev->next = tmpTerm->next;
			free(tmpTerm);
		}
		else
			currTermMovablePrev = currTermMovablePrev->next;
	}
	return STAT_OK;
}

Status OppositePoly(Polynomial A)
{
	TermP currTermPrev = A;

	while (currTermPrev->next)
	{
		currTermPrev->next->data.coef = -(currTermPrev->next->data.coef);
		currTermPrev = currTermPrev->next;
	}

	return STAT_OK;
}

Status AddPoly(Polynomial A, Polynomial B)
{
	TermP currPrevA = A;
	TermP ac = A->next, bc = B->next;

	while (ac && bc)
	{
		if (ac->data.expn < bc->data.expn)
		{
			currPrevA->next = ac;
			currPrevA = ac;
			ac = ac->next;
		}
		else
		{
			currPrevA->next = bc;
			currPrevA = bc;
			bc = bc->next;
		}
	}
	if (ac)
	{
		currPrevA->next = ac;
	}
	else
	{
		currPrevA->next = bc;
	}
	SimplifyPoly(A);
	free(B);
	return STAT_OK;
}

Status SubstractPoly(Polynomial A, Polynomial B)
{
	OppositePoly(B);
	AddPoly(A, B);
	return STAT_OK;
}

Status PrintPoly(Polynomial P, int printEmpty)
{
	if (P->next == NULL)
	{
		if (printEmpty)
			printf("空\n");
		return STAT_OK;
	}
	printf("%.3lgx^%d", P->next->data.coef, P->next->data.expn);
	P = P->next;
	while (P->next)
	{
		printf(" + %.3lgx^%d", P->next->data.coef, P->next->data.expn);
		P = P->next;
	}
	printf("\n");
	return STAT_OK;
}

void testAdd(Polynomial P)
{
	Polynomial B;
	InitPoly(&B);
	TermData t;
	for (int i = 0; i < 30; i++)
	{
		t.expn = rand() % 100 - 50;
		t.coef = rand() * 40. / 32768;
		InsertTerm(B, t);
	}
	printf("建立了随机多项式 B ：\n");
	PrintPoly(B, TRUE);
	printf("\n");
	PrintPoly(P, TRUE);
	printf(" + \n");
	PrintPoly(B, TRUE);
	printf(" = \n");
	AddPoly(P, B);
	PrintPoly(P, TRUE);
	system("pause");

}

void testSub(Polynomial P)
{
	Polynomial B;
	InitPoly(&B);
	TermData t;
	for (int i = 0; i < 30; i++)
	{
		t.expn = rand() % 100 - 50;
		t.coef = rand() * 40. / 32768;
		InsertTerm(B, t);
	}
	printf("建立了随机多项式 B ：\n");
	PrintPoly(B, TRUE);
	printf("\n");
	PrintPoly(P, TRUE);
	printf(" - \n");
	PrintPoly(B, TRUE);
	printf(" = \n");
	SubstractPoly(P, B);
	PrintPoly(P, TRUE);
	system("pause");
}

int main()
{
	Polynomial P;
	TermData currTerm;
	char opt;
	int wantExit = 0;
	int succNum;
	InitPoly(&P);
	srand((unsigned)(time(0)));

	/*
	FILE *f;
	fopen_s(&f, "Text.txt", "r");
	freopen_s(&f, "Text.txt", "r", stdin);
	*/

	printf("现在开始建立多项式。连续交替输入每一项的系数（实数型）和指数（整形）。当检测到非数字输入时（非法输入），将结束建立多项式。\n");
	printf("请现在开始输入，以空格和回车作为分隔符：\n");
	do
	{
		succNum = scanf_s("%lg %d", &(currTerm.coef), &(currTerm.expn));
		if(succNum == 2)
			InsertTerm(P, currTerm);
	} while (succNum == 2);

	scanf_s("%*[^\n]%*c");

	while (wantExit == 0)
	{
		system("cls");
		printf("\n现在的多项式：\n");
		PrintPoly(P, TRUE);
		printf("多项式有 %d 项。\n", PolyTermNum(&P));
		printf("\n");
		printf("菜单\na. 加多项式测试\nb. 减多项式测试\nq. 退出\n\n请选择：");
		scanf_s("%c", &opt, 1);
		switch (opt)
		{
			case 'a':
				testAdd(P);
				break;
			case 'b':
				testSub(P);
				break;
			case 'q':
				wantExit = 1;
				break;
			default:
				break;
		}
	}
	ClearPoly(&P);
	printf("清除多项式后，多项式有 %d 项。\n", PolyTermNum(&P));
	DestroyPoly(&P);
	printf("已经摧毁多项式。\n");
	return 0;
}