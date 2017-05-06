/*1652270 �����2�� ��˴*/
#include <stdio.h>
#include <stdlib.h>		//malloc/realloc����
#include <io.h>

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

int line_count;

/* ��ʼ�����Ա� */
Status InitList(LinkList *L)
{
	*L = NULL;  //ͷָ��ֱ�Ӹ�NULL
	return OK;
}

/* ɾ�����Ա� */
Status DestroyList(LinkList *L)
{
	LinkList q, p = *L; //ָ����Ԫ

						/* �������������ͷ� */
	while (p) {    //������Ϊ�գ���ѭ����ִ��
		q = p->next; //ץס�������һ�����
		free(p);
		p = q;
	}

	*L = NULL;	//ͷָ����NULL
	return OK;
}

/* ������Ա���DestroyList��ȫ��ͬ�� */
Status ClearList(LinkList *L)
{
	LinkList q, p = *L; //ָ����Ԫ

						/* �������������ͷ� */
	while (p) {
		q = p->next; //ץס�������һ�����
		free(p);
		p = q;
	}

	*L = NULL;	//ͷָ����NULL
	return OK;
}

/* �ж��Ƿ�Ϊ�ձ� */
Status ListEmpty(LinkList L)
{
	/* �ж�ͷָ�뼴�� */
	if (L == NULL)
		return TRUE;
	else
		return FALSE;
}

/* ���ĳ��� */
int ListLength(LinkList L)
{
	LinkList   p = L; //ָ����Ԫ���
	int      len = 0;

	/* ѭ�������������м��� */
	while (p) {
		p = p->next;
		len++;
	}

	return len;
}

/* ȡ����Ԫ�� */
Status GetElem(LinkList L, int i, ElemType *e)
{
	LinkList   p = L; //ָ����Ԫ���
	int      pos = 1; //��ʼλ��Ϊ1

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
	LinkList   p = L;	//��Ԫ���
	int      pos = 1;	//��ʼλ��

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
	LinkList p = L; //ָ����Ԫ���

	if (p == NULL)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �ӵ�2����㿪ʼѭ����������(����Ƚ���ȣ���֤��ǰ��) */
	while (p->next && p->next->data != cur_e)
		p = p->next;

	if (p->next == NULL) //δ�ҵ�
		return ERROR;

	*pre_e = p->data;
	return OK;
}

/* ���ҷ���ָ��������Ԫ�صĺ��Ԫ�� */
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e)
{
	LinkList p = L;  //��Ԫ���

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
	LinkList s, p = *L;	//pָ����Ԫ���(����ΪNULL)
	int      pos = 1;  //��Ϊp��ָ����Ԫ������ʼλ����1

					   /* ����½���Ϊ��Ԫ������Ҫ�ı�L��ֵ������λ�ò�����L���� */
	if (i != 1) {
		/* Ѱ�ҵ�i-1����� */
		while (p && pos<i - 1) {
			p = p->next;
			pos++;
		}

		if (p == NULL || pos>i - 1)  //iֵ�Ƿ��򷵻�
			return ERROR;
	}

	s = (LinkList)malloc(sizeof(LNode));
	if (s == NULL)
		return LOVERFLOW;

	s->data = e; 	//�½��������ֵ
	if (i != 1) {
		//����λ�÷���Ԫ����ʱpָ���i-1�����
		s->next = p->next;	//�½���next��p->next
		p->next = s;		//��i-1����next���½��
	}
	else {
		//����λ������Ԫ
		s->next = p;	//��ʱp����L������L=NULL�������
		*L = s;		//ͷָ��ָ���½��
	}

	return OK;
}

/* ɾ��ָ��λ�õ�Ԫ�أ�������ɾ��Ԫ�ص�ֵ����e�з��� */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	LinkList q = NULL, p = *L;	//pָ����Ԫ���(����ΪNULL)
	int      pos = 1;	//��Ϊp��ָ����Ԫ������ʼλ����1

	if (p == NULL)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* ���ɾ���Ĳ�����Ԫ������ҵ�i����� */
	if (i != 1) {
		/* Ѱ�ҵ�i����㣨p->next�ǵ�i����㣩 */
		while (p->next && pos<i - 1) {
			p = p->next;
			pos++;
		}

		if (p->next == NULL || pos>i - 1)	//iֵ�Ƿ��򷵻�
			return ERROR;

		q = p->next;       //qָ���i�����
		p->next = q->next; //��i-1������next��ָ���i+1��
	}
	else { //Ҫɾ��������Ԫ
		q = p;
		*L = q->next;	//���ֻ��һ����㣬��q->nextΪNULL
	}

	*e = q->data;      //ȡ��i������ֵ
	free(q);           //�ͷŵ�i�����

	return OK;
}

/* �������Ա� */
Status ListTraverse(LinkList L, Status(*visit)(ElemType e))
{
	extern int line_count;	//��main�ж���Ĵ�ӡ���м����������㷨�޹أ�
	LinkList p = L;		//ָ����Ԫ

	line_count = 0;		//�������ָ���ʼֵ�����㷨�޹أ�
	while (p && (*visit)(p->data) == TRUE)
		p = p->next;

	if (p)
		return ERROR;

	printf("\n");//����ӡһ�����У�ֻ��Ϊ�˺ÿ������㷨�޹�
	return OK;
}

void union_L_without_head(LinkList *La, LinkList *Lb)
{
	LinkList p, q, r;
	for (q = *Lb; q; q = q->next)
	{
		for (p = *La; p; p = p->next)
		{
			if (p->data == q->data)
				break;
		}
		if (!p)
		{
			r = (LinkList)malloc(sizeof(LNode));
			if (!r)
				exit(LOVERFLOW);
			r->data = q->data;
			r->next = *La;
			*La = r;
		}
	}
}

#define INSERT_NUM		115		//��ʼ������е�Ԫ������
#define MAX_NUM_PER_LINE 	10		//ÿ����������Ԫ�ظ���

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
	const int data_LA[] = { 8, 4, 2, 1, 5 };
	const int data_LB[] = { 10, 100};
	LinkList LA, LB;
	InitList(&LA);
	InitList(&LB);
	if (1)
	{
		for (int i = 0; i < sizeof(data_LA) / sizeof(data_LA[0]); i++)
		{
			ListInsert(&LA, 1, data_LA[i]);
		}
	}
	
	for (int i = 0; i < sizeof(data_LB) / sizeof(data_LB[0]); i++)
	{
		ListInsert(&LB, 1, data_LB[i]);
	}
	printf("LA �����ݣ�\n");
	ListTraverse(LA, MyVisit);
	printf("\nLB �����ݣ�\n");
	ListTraverse(LB, MyVisit);
	printf("\n\n�ϲ���LA �����ݣ�\n");
	union_L_without_head(&LA, &LB);
	ListTraverse(LA, MyVisit);
	return 0;
}
