/*1652270 �����2�� ��˴*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
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

//#if defined (ELEMTYPE_IS_STRUCT_STUDENT)
//typedef struct student {
//	int   num;
//	char  name[10];
//	char  sex;
//	float score;
//	char  addr[30];
//} ElemType;
////#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
//#else
//typedef struct student {
//	int   num;
//	char  name[10];
//	char  sex;
//	float score;
//	char  addr[30];
//} ET, *ElemType;
//#endif

typedef int ElemType;

typedef struct DuLNode {
	ElemType        data;	//�������
	struct DuLNode *prior;	//���ֱ��ǰ����ָ��
	struct DuLNode *next;	//���ֱ�Ӻ�̵�ָ��
} DuLNode, *DuLinkList;

/* P.19-20�ĳ����������Ͷ���ת��Ϊʵ�ʵ�C���� */
Status	InitList(DuLinkList *L);
Status	DestroyList(DuLinkList *L, Status(*sub_free)(DuLinkList *L));
Status	ClearList(DuLinkList *L, Status(*sub_free)(DuLinkList *L));
Status	ListEmpty(DuLinkList L);
int	ListLength(DuLinkList L);
Status	GetElem(DuLinkList L, int i, ElemType *e, Status(*assign)(ElemType *e, ElemType a));
int	LocateElem(DuLinkList L, ElemType e, Status(*compare)(ElemType e1, ElemType e2));
Status	PriorElem(DuLinkList L, ElemType cur_e, ElemType *pre_e, Status(*compare)(ElemType e1, ElemType e2), Status(*assign)(ElemType *e, ElemType a));
Status	NextElem(DuLinkList L, ElemType cur_e, ElemType *next_e, Status(*compare)(ElemType e1, ElemType e2), Status(*assign)(ElemType *e, ElemType a));
Status	ListInsert(DuLinkList *L, int i, ElemType e, Status(*assign)(ElemType *e, ElemType a), Status(*allocnode)(DuLinkList *p, ElemType e));
Status	ListDelete(DuLinkList *L, int i, ElemType *e, Status(*assign)(ElemType *e, ElemType a), Status(*specfree)(ElemType p));
Status	ListTraverse(DuLinkList L, Status(*visit)(ElemType e), int reverse);

/* ��ʼ�����Ա� */
Status InitList(DuLinkList *L)
{
	/* ����ͷ���ռ䣬��ֵ��ͷָ�� */
	*L = (DuLNode *)malloc(sizeof(DuLNode));
	if (*L == NULL)
		exit(LOVERFLOW);

	(*L)->prior = *L;
	(*L)->next = *L;
	return OK;
}

/* ɾ�����Ա� */
Status DestroyList(DuLinkList *L, Status(*sub_free)(DuLinkList *L))
{
	DuLinkList q, p = *L; //ָ����Ԫ
						  /* �����ͷſռ� */
	(*sub_free)(L);
	/* ��������(��ͷ���)�����ͷ�(ͬ������������priorָ�룬ֻ��next) */
	do {    //������Ϊ�գ���ѭ����ִ��
		q = p->next; //ץס�������һ�����
		free(p);
		p = q;
	} while (p != (*L));

	*L = NULL;	//ͷָ����NULL
	return OK;
}

/* ������Ա�����ͷ��㣩 */
Status ClearList(DuLinkList *L, Status(*sub_free)(DuLinkList *L))
{
	DuLinkList q, p = (*L)->next;
	(*sub_free)(L);
	/* ����Ԫ��㿪ʼ�����ͷ�(ͬ������������priorָ�룬ֻ��next) */
	while (p != (*L)) {
		q = p->next;   //ץס�������һ�����
		free(p);
		p = q;
	}

	(*L)->prior = *L; //ͷ����prior����NULL
	(*L)->next = *L; //ͷ����next����NULL
	return OK;
}

/* �ж��Ƿ�Ϊ�ձ� */
Status ListEmpty(DuLinkList L)
{
	/* �ж�ͷ����next�򼴿�(ͬ������) */
	if (L->next == L)
		return TRUE;
	else
		return FALSE;
}

/* ���ĳ��� */
int ListLength(DuLinkList L)
{
	DuLinkList p = L->next; //ָ����Ԫ���
	int len = 0;

	/* ѭ�������������м���(ͬ������) */
	while (p != L) {
		p = p->next;
		len++;
	}

	return len;
}

/* ȡ����Ԫ�� */
Status GetElem(DuLinkList L, int i, ElemType *e, Status(*assign)(ElemType *e, ElemType a))
{
	DuLinkList p = L->next;	//ָ����Ԫ���
	int    pos = 1;		//��ʼλ��Ϊ1

						/* ����ΪNULL �� δ����i��Ԫ��(ͬ������) */
	while (p != L && pos<i) {
		p = p->next;
		pos++;
	}

	if (p == L || pos>i)
		return ERROR;

	//*e = p->data;
	return assign(e, p->data);
}

/* ���ҷ���ָ��������Ԫ�� */
int LocateElem(DuLinkList L, ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
	DuLinkList p = L->next;	//��Ԫ���
	int    pos = 1;		//��ʼλ��

						/* ѭ����������(ͬ������)  */
	while (p != L && (*compare)(e, p->data) == FALSE) {
		p = p->next;
		pos++;
	}

	return (p != L) ? pos : 0;
}

/* ���ҷ���ָ��������Ԫ�ص�ǰ��Ԫ�� */
Status PriorElem(DuLinkList L, ElemType cur_e, ElemType *pre_e, Status(*compare)(ElemType e1, ElemType e2), Status(*assign)(ElemType *e, ElemType a))
{
	DuLinkList p = L->next;	//ָ����Ԫ���

	if (p == L)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �ӵ�2����㿪ʼѭ����������(����Ƚ���ȣ���֤��ǰ��)(ͬ������) */
	while (p->next != L && compare(p->next->data, cur_e) == FALSE)
		p = p->next;

	if (p->next == L) //δ�ҵ�
		return ERROR;

	return assign(pre_e, p->data);
	//return OK;
}

/* ���ҷ���ָ��������Ԫ�صĺ��Ԫ�� */
Status NextElem(DuLinkList L, ElemType cur_e, ElemType *next_e, Status(*compare)(ElemType e1, ElemType e2), Status(*assign)(ElemType *e, ElemType a))
{
	DuLinkList p = L->next;  //��Ԫ���

	if (p == L)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �к�̽���ҵ�ǰ���ֵ����ʱ����(ͬ������) */
	while (p->next != L && compare(p->data, cur_e) == FALSE)
		p = p->next;

	if (p->next == L)
		return ERROR;

	//*next_e = p->next->data;
	return assign(next_e, p->next->data);
}

/* ��ָ��λ��ǰ����һ����Ԫ�� */
Status ListInsert(DuLinkList *L, int i, ElemType e, Status(*assign)(ElemType *e, ElemType a), Status(*allocnode)(DuLinkList *p, ElemType e))
{
#if 0
	DuLinkList s, p = *L;	//pָ��ͷ���
	int      pos = 1;

	/* Ѱ�ҵ�i�����(i�����Ǳ�+1) */
	while (p->next && pos<i - 1) {
		p = p->next;
		pos++;
	}

	if (p->next == NULL || pos>i - 1)  //iֵ�Ƿ��򷵻�
		return ERROR;

	//ִ�е��˱�ʾ�ҵ�ָ��λ�ã�pָ���i-1�����

	s = (DuLinkList)malloc(sizeof(DuLNode));
	if (s == NULL)
		return LOVERFLOW;

	if (pos == i - 1) {
	}
	else {
		/* ע�⣬p������NULL */
		s->data = e; 	//�½��������ֵ
		s->prior = p->prior;
		p->prior->next = s;
		s->next = p;	//�½���next�ǵ�i��
		p->prior = s;	//��i-1����next���½��
	}
#else
	DuLinkList s, p = *L;	//pָ��ͷ���
	Status error;
	int      pos = 0;

	/* Ѱ�ҵ�i-1����� */
	if (i == 1)
		;
	else
	{
		do {
			p = p->next;
			pos++;
		} while (p != (*L) && pos < i - 1);

		if (p == (*L) || pos>i)  //iֵ�Ƿ��򷵻�
			return ERROR;
	}

	//ִ�е��˱�ʾ�ҵ�ָ��λ�ã�pָ���i-1�����
	/*s = (DuLinkList)malloc(sizeof(DuLNode));
	if (s == NULL)
	return LOVERFLOW;*/
	if ((*allocnode)(&s, e) == LOVERFLOW)
		return LOVERFLOW;

	if ((error = assign(&(s->data), e)) != OK)
		return error; 	//�½��������ֵ
	s->next = p->next;  //�½���next�ǵ�i�����(��ʹp->next��*LҲû����)
	p->next->prior = s; //��i������prior��s
	s->prior = p;       //s��ǰ����p
	p->next = s;        //p�ĺ����s
#endif

	return OK;
}

/* ɾ��ָ��λ�õ�Ԫ�أ�������ɾ��Ԫ�ص�ֵ����e�з��� */
Status ListDelete(DuLinkList *L, int i, ElemType *e, Status(*assign)(ElemType *e, ElemType a), Status(*specfree)(ElemType p))
{
#if 1
	DuLinkList p = *L;	//pָ��ͷ���
	Status error;
	int      pos = 0;

	/* Ѱ�ҵ�i����㣨p�ǵ�i����㣩 */
	do {
		p = p->next;
		pos++;
	} while (p != (*L) && pos < i);

	if (p == (*L) || pos>i)	//iֵ�Ƿ��򷵻�
		return ERROR;

	//ִ�е��˱�ʾ�ҵ��˵�i����㣬��ʱpָ���i�����

	if ((error = assign(e, p->data)) != OK)
		return error; 	//�½��������ֵ
						//e = p->data;      //ȡ��i������ֵ
	p->prior->next = p->next;
	//if (p->next) //Ҫ���ж�����
	p->next->prior = p->prior;
	(*specfree)(p->data);
	free(p);           //�ͷŵ�i�����
#else
	DuLinkList q, p = *L;	//pָ��ͷ���
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
	p->next = q->next; //��i-1������next��ָ���i+1��(��ʹNULLҲû��)
	if (q->next)
		q->next->prior = p;

	*e = q->data;      //ȡ��i������ֵ
	free(q);           //�ͷŵ�i�����
#endif

	return OK;
}

/* �������Ա� */
Status ListTraverse(DuLinkList L, Status(*visit)(ElemType e), int reverse)
{
	DuLinkList p = L->next;

	if (!reverse)
	{

		while (p != L && (*visit)(p->data) == TRUE) //ͬ������
			p = p->next;

		if (p != L)
			return ERROR;

		//printf("\n");//����ӡһ�����У�ֻ��Ϊ�˺ÿ������㷨�޹�
	}
	else
	{
		/* ������� */
		while (p->next) //ͬ������
			p = p->next;

		/* ִ�е��ˣ�pָ�����һ����� */
		while (p && p->prior && (*visit)(p->data) == TRUE) //ͬ������
			p = p->prior;

		printf("\n");//����ӡһ�����У�ֻ��Ϊ�˺ÿ������㷨�޹�
	}

	return OK;
}

/*��ȡ��i��λ�õĽ��ָ��*/
DuLinkList GetElemP_Dul(DuLinkList L, int i)
{
	DuLinkList p = L->next;
	int pos = 1;

	while (p != L && pos < i)
	{
		p = p->next;
		pos++;
	}

	if (p == L)
		return NULL;

	return p;
}

#define INSERT_NUM		115		//��ʼ������е�Ԫ������
#define MAX_NUM_PER_LINE 	10		//ÿ����������Ԫ�ظ���

int line_count = 0;   //��ӡ����ʱ�ļ�����

Status MyCompare(ElemType e1, ElemType e2)
{
	if(e1 == e2)
		return TRUE;
	return FALSE;
}


Status MySubFree(DuLinkList *L)
{
	return OK;
}

/* ��ֵ */
Status MyAssign(ElemType *dst, ElemType src)
{
	*dst = src;

	return OK;
}

Status MyAlloc(DuLinkList *p, ElemType e)
{
	*p = (DuLinkList)malloc(sizeof(DuLNode));
	if ((*p) == NULL)
		return LOVERFLOW;

	return OK;
}

Status MyFree(ElemType p)
{

	return OK;
}

/* β�� */
Status ListAppend(DuLinkList *L, ElemType e, Status(*assign)(ElemType *e, ElemType a), Status(*allocnode)(DuLinkList *p, ElemType e))
{
	Status error;
	DuLinkList s, p = *L;	//pָ��ͷ���

						/* Ѱ��ĩ��� */
	p = (*L)->prior;

	//ִ�е��˱�ʾ�ҵ�ָ��λ�ã�pָ���i-1�����

	if ((*allocnode)(&s, e) == LOVERFLOW)
		return LOVERFLOW;

	if ((error = assign(&(s->data), e)) != OK)
		return error; 	//�½��������ֵ
	s->next = p->next;  //�½���next�ǵ�i�����(��ʹp->next��*LҲû����)
	p->next->prior = s; //��i������prior��s
	s->prior = p;       //s��ǰ����p
	p->next = s;        //p�ĺ����s

	return OK;
}


void createList(DuLinkList *l, int n)
{
	int count = 0;
	InitList(l);

	for (count = 0; count < n; count++)
	{
		ListInsert(l, 1, count + 1, MyAssign, MyAlloc);
	}
}

void eliminate(DuLinkList *l, int n, int m, int k)
{
	DuLinkList p, q;
	int count;
	p = (*l)->prior;

	for (count = 0; count < k - 1; count++)
	{
		p = p->prior;
		if (p == *l)
			p = p->prior;
	}

	while (!ListEmpty(*l))
	{
		for (count = 0; count < m - 1; count++)
		{
			p = p->prior;
			if (p == *l)
				p = p->prior;
		}
		printf_s("%d ����\n", p->data);
		q = p;
		q->prior->next = q->next;
		q->next->prior = q->prior;
		p = q->prior;
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

	DuLinkList l;
	createList(&l, n);
	eliminate(&l, n, m, k);
	DestroyList(&l, MySubFree);

	return 0;
}