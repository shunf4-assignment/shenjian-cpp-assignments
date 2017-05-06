/*1652270 �����2�� ��˴*/
#include <stdio.h>
#include <stdlib.h>		//malloc/realloc����
#include <io.h>		//exit����

/* P.10 ��Ԥ���峣�������� */
#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define LOVERFLOW	-2

typedef int Status;

/* P.28 ��ʽ���� */
typedef int ElemType;	//�ɸ�����Ҫ�޸�Ԫ�ص�����

typedef struct LNode {
	ElemType      data;	//�������
	struct LNode *next;	//���ֱ�Ӻ�̵�ָ��
} LNode, *LinkList;

/* P.19-20�ĳ����������Ͷ���ת��Ϊʵ�ʵ�C���� */
Status	InitList(LinkList *L);
Status	DestroyList(LinkList *L);
Status	ClearList(LinkList *L);
Status	ListEmpty(LinkList L);
int	ListLength(LinkList L);
Status	GetElem(LinkList L, int i, ElemType *e);
int	LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType e1, ElemType e2));
Status	PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e);
Status	NextElem(LinkList L, ElemType cur_e, ElemType *next_e);
Status	ListInsert(LinkList *L, int i, ElemType e);
Status	ListDelete(LinkList *L, int i, ElemType *e);
Status	ListTraverse(LinkList L, Status(*visit)(ElemType e));

/* ��ʼ�����Ա� */
Status InitList(LinkList *L)
{
	/* ����ͷ���ռ䣬��ֵ��ͷָ�� */
	*L = (LNode *)malloc(sizeof(LNode));
	if (*L == NULL)
		exit(LOVERFLOW);

	(*L)->next = NULL;
	return OK;
}

/* ɾ�����Ա� */
Status DestroyList(LinkList *L)
{
	LinkList q, p = *L; //ָ����Ԫ

						/* ��������(��ͷ���)�����ͷ� */
	while (p) {    //������Ϊ�գ���ѭ����ִ��
		q = p->next; //ץס�������һ�����
		free(p);
		p = q;
	}

	*L = NULL;	//ͷָ����NULL
	return OK;
}

/* ������Ա�����ͷ��㣩 */
Status ClearList(LinkList *L)
{
	LinkList q, p = (*L)->next;

	/* ����Ԫ��㿪ʼ�����ͷ� */
	while (p) {
		q = p->next;   //ץס�������һ�����
		free(p);
		p = q;
	}

	(*L)->next = NULL; //ͷ����next����NULL
	return OK;
}

/* �ж��Ƿ�Ϊ�ձ� */
Status ListEmpty(LinkList L)
{
	/* �ж�ͷ����next�򼴿� */
	if (L->next == NULL)
		return TRUE;
	else
		return FALSE;
}

/* ���ĳ��� */
int ListLength(LinkList L)
{
#if 1
	LinkList p = L->next; //ָ����Ԫ���
	int len = 0;

	/* ѭ�������������м��� */
	while (p) {
		p = p->next;
		len++;
	}

	return len;
#else
	int len = 0;

	LinkList p = L;
	while ((p = p->next) != NULL)
		len++;

	return len;
#endif
}

/* ȡ����Ԫ�� */
Status GetElem(LinkList L, int i, ElemType *e)
{
	LinkList p = L->next;	//ָ����Ԫ���
	int    pos = 1;		//��ʼλ��Ϊ1

						/* ����ΪNULL �� δ����i��Ԫ�� */
	while (p != NULL && pos<i) {
		p = p->next;
		pos++;
	}

	if (!p || pos>i)
		return ERROR;

	*e = p->data;
	return OK;
}

/* ���ҷ���ָ��������Ԫ�� */
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
	LinkList p = L->next;	//��Ԫ���
	int    pos = 1;		//��ʼλ��

						/* ѭ����������  */
	while (p && (*compare)(e, p->data) == FALSE) {
		p = p->next;
		pos++;
	}

	return p ? pos : 0;
}

/* ���ҷ���ָ��������Ԫ�ص�ǰ��Ԫ�� */
Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e)
{
#if 1
	LinkList p = L->next;	//ָ����Ԫ���

	if (p == NULL)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �ӵ�2����㿪ʼѭ����������(����Ƚ���ȣ���֤��ǰ��) */
	while (p->next && p->next->data != cur_e)
		p = p->next;

	if (p->next == NULL) //δ�ҵ�
		return ERROR;

	*pre_e = p->data;
	return OK;
#else
	LinkList p = L; //ָ��ͷ���

					/* ѭ�����������Ƚ�ֵ�Ƿ���� */
	while (p->next && p->next->data != cur_e)
		p = p->next;

	if (p->next == NULL || p == L) //δ�ҵ�����Ԫ����ձ�
		return ERROR;
	*pre_e = p->data;
	return OK;
#endif
}

/* ���ҷ���ָ��������Ԫ�صĺ��Ԫ�� */
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e)
{
	LinkList p = L->next;  //��Ԫ���

	if (p == NULL)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �к�̽���ҵ�ǰ���ֵ����ʱ���� */
	while (p->next && p->data != cur_e)
		p = p->next;

	if (p->next == NULL)
		return ERROR;

	*next_e = p->next->data;
	return OK;
}

/* ��ָ��λ��ǰ����һ����Ԫ�� */
Status ListInsert(LinkList *L, int i, ElemType e)
{
	LinkList s, p = *L;	//pָ��ͷ���
	int      pos = 0;

	/* Ѱ�ҵ�i-1����� */
	while (p && pos<i - 1) {
		p = p->next;
		pos++;
	}

	if (p == NULL || pos>i - 1)  //iֵ�Ƿ��򷵻�
		return ERROR;

	//ִ�е��˱�ʾ�ҵ�ָ��λ�ã�pָ���i-1�����

	s = (LinkList)malloc(sizeof(LNode));
	if (s == NULL)
		return LOVERFLOW;

	s->data = e; 	//�½��������ֵ
	s->next = p->next;	//�½���next�ǵ�i��
	p->next = s;	//��i-1����next���½��

	return OK;
}

/* ɾ��ָ��λ�õ�Ԫ�أ�������ɾ��Ԫ�ص�ֵ����e�з��� */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	LinkList q, p = *L;	//pָ��ͷ���
	int      pos = 0;

	/* Ѱ�ҵ�i����㣨p->next�ǵ�i����㣩 */
	while (p->next && pos<i - 1) {
		p = p->next;
		pos++;
	}

	if (p->next == NULL || pos>i - 1)	//iֵ�Ƿ��򷵻�
		return ERROR;

	//ִ�е��˱�ʾ�ҵ��˵�i����㣬��ʱpָ���i-1�����

	q = p->next;       //qָ���i�����
	p->next = q->next; //��i-1������next��ָ���i+1��

	*e = q->data;      //ȡ��i������ֵ
	free(q);           //�ͷŵ�i�����

	return OK;
}

/* �������Ա� */
Status ListTraverse(LinkList L, Status(*visit)(ElemType e))
{
	extern int line_count; //��main�ж���Ĵ�ӡ���м����������㷨�޹أ�
	LinkList p = L->next;

	line_count = 0;		//�������ָ���ʼֵ�����㷨�޹أ�
	while (p && (*visit)(p->data) == TRUE)
		p = p->next;

	if (p)
		return ERROR;

	printf("\n");//����ӡһ�����У�ֻ��Ϊ�˺ÿ������㷨�޹�
	return OK;
}

#define INSERT_NUM		115		//��ʼ������е�Ԫ������
#define MAX_NUM_PER_LINE 	10		//ÿ����������Ԫ�ظ���

int line_count = 0;   //��ӡ����ʱ�ļ�����

void difference(LinkList *La, LinkList *Lb)
{//ɾ��Lb���������ݣ���La�޸�ΪԭLa��Lb�ĶԳƲ�
	LinkList Alast = *La, searchAPrev, searchBPrev;
	//LinkList newNode;
	LinkList tmpA, tmpB;
	while (Alast->next)
		Alast = Alast->next;

	searchBPrev = (*Lb);
	while (searchBPrev->next)
	{
		searchAPrev = (*La);
		while (searchAPrev != Alast && searchAPrev->next->data != searchBPrev->next->data)
		{
			searchAPrev = searchAPrev->next;
		}
		if (searchAPrev == Alast)
		{
			//newNode = (LinkList)malloc(sizeof(LNode));
			//if (!newNode)
			//{
			//	exit(LOVERFLOW);
			//}
			tmpB = searchBPrev->next;
			searchBPrev->next = tmpB->next;
			tmpA = Alast->next;
			tmpB->next = tmpA;
			Alast->next = tmpB;
		}
		else
		{
			tmpA = searchAPrev->next;
			searchAPrev->next = searchAPrev->next->next;
			if (tmpA == Alast)
			{
				Alast = searchAPrev;
			}
			free(tmpA);
			tmpB = searchBPrev->next;
			searchBPrev->next = tmpB->next;
			free(tmpB);
		}
	}
}

Status MyVisit(ElemType e)
{
	printf("%3d->", e);

	/* ÿ���MAX_NUM_PER_LINE������ӡһ������ */
	if ((++line_count) % MAX_NUM_PER_LINE == 0)
		printf("\n");

	return OK;
}

int main()
{
	const int data_LA[] = { 1,2,3,5,7,9 };
	const int data_LB[] = { 1, 3,8,9,6 };
	LinkList LA, LB;
	InitList(&LA);
	InitList(&LB);
	if (1)
	{
		for (int i = 0; i < sizeof(data_LA) / sizeof(data_LA[0]); i++)
		{
			ListInsert(&LA, 1, data_LA[sizeof(data_LA) / sizeof(data_LA[0]) - i - 1]);
		}
	}
	if (1)
	{
		for (int i = 0; i < sizeof(data_LB) / sizeof(data_LB[0]); i++)
		{
			ListInsert(&LB, 1, data_LB[sizeof(data_LB) / sizeof(data_LB[0]) - i - 1]);
		}
	}

	printf("LA �����ݣ�\n");
	ListTraverse(LA, MyVisit);
	printf("\nLB �����ݣ�\n");
	ListTraverse(LB, MyVisit);
	printf("\n\n��ԳƲ��LA �����ݣ�\n");
	difference(&LA, &LB);
	ListTraverse(LA, MyVisit);
	printf("\n\n��ԳƲ��LB �����ݣ�\n");
	ListTraverse(LB, MyVisit);
	printf("\n");
	return 0;
}
