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
#define OVERFLOW	-2

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
		exit(OVERFLOW);

	(*L)->next = (*L);	//ͷ����nextָ���Լ�
	return OK;
}

/* ɾ�����Ա� */
Status DestroyList(LinkList *L)
{
	LinkList q, p = *L; //ָ����Ԫ

	/* ��������(��ͷ���)�����ͷ�
	   ������whileѭ�� */
	do {
		q = p->next; //ץס�������һ����㣬���ձ���qֱ��ΪNULL
		free(p);
		p = q;
	} while (p != (*L));   //������Ϊ�գ���ѭ����ִ��

	(*L) = NULL;	//ͷ����next��NULL
	return OK;
}

/* ������Ա�����ͷ��㣩 */
Status ClearList(LinkList *L)
{
	LinkList q, p = (*L)->next;  //pָ����Ԫ

	/* ����Ԫ��㿪ʼ�����ͷ�(����ձ���while��ִ��) */
	while (p != (*L)) {
		q = p->next;   //ץס�������һ�����
		free(p);
		p = q;
	}

	(*L)->next = (*L); //ͷ����next����L
	return OK;
}

/* �ж��Ƿ�Ϊ�ձ� */
Status ListEmpty(LinkList L)
{
	/* �ж�ͷ����next�򼴿� */
	if (L->next == L)
		return TRUE;
	else
		return FALSE;
}

/* ���ĳ��� */
int ListLength(LinkList L)
{
	LinkList p = L->next; //ָ����Ԫ���
	int len = 0;

	/* ѭ�������������м��� */
	while (p != L) {
		p = p->next;
		len++;
	}

	return len;
}

/* ȡ����Ԫ�� */
Status GetElem(LinkList L, int i, ElemType *e)
{
	LinkList p = L->next;	//ָ����Ԫ���
	int    pos = 1;		//��ʼλ��Ϊ1

	/* ����ΪNULL �� δ����i��Ԫ�� */
	while (p != L && pos < i) {
		p = p->next;
		pos++;
	}

	if (p == L || pos > i)
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
	while (p != L && (*compare)(e, p->data) == FALSE) {
		p = p->next;
		pos++;
	}

	return (p != L) ? pos : 0;
}

/* ���ҷ���ָ��������Ԫ�ص�ǰ��Ԫ�� */
Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e)
{
	LinkList p = L->next;	//ָ����Ԫ���

	if (p == L)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �ӵ�2����㿪ʼѭ����������(����Ƚ���ȣ���֤��ǰ��) */
	while (p->next != L && p->next->data != cur_e)
		p = p->next;

	if (p->next == L) //δ�ҵ�
		return ERROR;

	*pre_e = p->data;
	return OK;
}

/* ���ҷ���ָ��������Ԫ�صĺ��Ԫ�� */
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e)
{
	LinkList p = L->next;  //��Ԫ���

	if (p == L)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �к�̽���ҵ�ǰ���ֵ����ʱ���� */
	while (p->next != L && p->data != cur_e)
		p = p->next;

	if (p->next == L)
		return ERROR;

	*next_e = p->next->data;
	return OK;
}

/* ��ָ��λ��ǰ����һ����Ԫ�� */
Status ListInsert(LinkList *L, int i, ElemType e)
{
	LinkList s, p = *L;	//pָ��ͷ���
	int      pos = 0;

	if (i == 1)
		;
	else
	{
		/* Ѱ�ҵ�i-1����� */
		do {
			p = p->next;
			pos++;
		} while (p != (*L) && pos < i - 1);

		if (p == (*L) || pos > i - 1)  //iֵ�Ƿ��򷵻�
			return ERROR;
	}


	//ִ�е��˱�ʾ�ҵ�ָ��λ�ã�pָ���i-1�����
	s = (LinkList)malloc(sizeof(LNode));
	if (s == NULL)
		return OVERFLOW;

	s->data = e; 	//�½��������ֵ
	s->next = p->next;	//�½���next�ǵ�i��
	p->next = s;	//��i-1����next���½��

	return OK;
}

/* β�� */
Status ListAppend(LinkList *L, ElemType e)
{
	LinkList s, p = *L;	//pָ��ͷ���

	/* Ѱ��ĩ��� */
	while (p->next != (*L))
	{
		p = p->next;
	}

	//ִ�е��˱�ʾ�ҵ�ָ��λ�ã�pָ��ĩ���
	s = (LinkList)malloc(sizeof(LNode));
	if (s == NULL)
		return OVERFLOW;

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
	while (p->next != (*L) && pos < i - 1) {
		p = p->next;
		pos++;
	}

	if (p->next == (*L) || pos > i - 1)	//iֵ�Ƿ��򷵻�
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
	LinkList p = L->next;

	while (p != L && (*visit)(p->data) == TRUE)
		p = p->next;

	if (p != L)
		return ERROR;

	printf("\n");//����ӡһ�����У�ֻ��Ϊ�˺ÿ������㷨�޹�
	return OK;
}

#define INSERT_NUM		115		//��ʼ������е�Ԫ������
#define MAX_NUM_PER_LINE 	10		//ÿ����������Ԫ�ظ���

void createList(LinkList *l, int n)
{
	int count = 0;
	InitList(l);

	for (count = 0; count < n; count++)
	{
		ListAppend(l, count + 1);
	}
}

void eliminate(LinkList *l, int n, int m, int k)
{
	LinkList p, q;
	int count;
	p = *l;
	
	for (count = 0; count < k - 1; count++)
	{
		p = p->next;
		if (p->next == *l)
			p = p->next;
	}

	while (!ListEmpty(*l))
	{
		for (count = 0; count < m - 1; count++)
		{
			p = p->next;
			if (p->next == *l)
				p = p->next;
		}
		printf_s("%d ����\n", p->next->data);
		q = p->next;
		p->next = p->next->next;
		free(q);
	}
}

int main()
{
	int n, m, k, succNum;
	do
	{
		printf_s("����������n��m��k��ֵ���ո������");
		succNum = scanf_s("%d %d %d", &n, &m, &k);
		rewind(stdin);

	} while (succNum != 3);

	LinkList l;
	createList(&l, n);
	eliminate(&l, n, m, k);
	DestroyList(&l);
	
	return 0;
}
