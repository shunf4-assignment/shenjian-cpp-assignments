/*1652270 计算机2班 冯舜*/
#include <stdio.h>
#include <stdlib.h>		//malloc/realloc函数
#include <io.h>		//exit函数

/* P.10 的预定义常量和类型 */
#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define OVERFLOW	-2

typedef int Status;

/* P.28 形式定义 */
typedef int ElemType;	//可根据需要修改元素的类型

typedef struct LNode {
	ElemType      data;	//存放数据
	struct LNode *next;	//存放直接后继的指针
} LNode, *LinkList;

/* P.19-20的抽象数据类型定义转换为实际的C语言 */
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

/* 初始化线性表 */
Status InitList(LinkList *L)
{
	/* 申请头结点空间，赋值给头指针 */
	*L = (LNode *)malloc(sizeof(LNode));
	if (*L == NULL)
		exit(OVERFLOW);

	(*L)->next = (*L);	//头结点的next指向自己
	return OK;
}

/* 删除线性表 */
Status DestroyList(LinkList *L)
{
	LinkList q, p = *L; //指向首元

	/* 整个链表(含头结点)依次释放
	   不能用while循环 */
	do {
		q = p->next; //抓住链表的下一个结点，若空表则q直接为NULL
		free(p);
		p = q;
	} while (p != (*L));   //若链表为空，则循环不执行

	(*L) = NULL;	//头结点的next置NULL
	return OK;
}

/* 清除线性表（保留头结点） */
Status ClearList(LinkList *L)
{
	LinkList q, p = (*L)->next;  //p指向首元

	/* 从首元结点开始依次释放(如果空表则while不执行) */
	while (p != (*L)) {
		q = p->next;   //抓住链表的下一个结点
		free(p);
		p = q;
	}

	(*L)->next = (*L); //头结点的next域置L
	return OK;
}

/* 判断是否为空表 */
Status ListEmpty(LinkList L)
{
	/* 判断头结点的next域即可 */
	if (L->next == L)
		return TRUE;
	else
		return FALSE;
}

/* 求表的长度 */
int ListLength(LinkList L)
{
	LinkList p = L->next; //指向首元结点
	int len = 0;

	/* 循环整个链表，进行计数 */
	while (p != L) {
		p = p->next;
		len++;
	}

	return len;
}

/* 取表中元素 */
Status GetElem(LinkList L, int i, ElemType *e)
{
	LinkList p = L->next;	//指向首元结点
	int    pos = 1;		//初始位置为1

	/* 链表不为NULL 且 未到第i个元素 */
	while (p != L && pos < i) {
		p = p->next;
		pos++;
	}

	if (p == L || pos > i)
		return ERROR;

	*e = p->data;
	return OK;
}

/* 查找符合指定条件的元素 */
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
	LinkList p = L->next;	//首元结点
	int    pos = 1;		//初始位置

	/* 循环整个链表  */
	while (p != L && (*compare)(e, p->data) == FALSE) {
		p = p->next;
		pos++;
	}

	return (p != L) ? pos : 0;
}

/* 查找符合指定条件的元素的前驱元素 */
Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e)
{
	LinkList p = L->next;	//指向首元结点

	if (p == L)	//空表直接返回
		return ERROR;

	/* 从第2个结点开始循环整个链表(如果比较相等，保证有前驱) */
	while (p->next != L && p->next->data != cur_e)
		p = p->next;

	if (p->next == L) //未找到
		return ERROR;

	*pre_e = p->data;
	return OK;
}

/* 查找符合指定条件的元素的后继元素 */
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e)
{
	LinkList p = L->next;  //首元结点

	if (p == L)	//空表直接返回
		return ERROR;

	/* 有后继结点且当前结点值不等时继续 */
	while (p->next != L && p->data != cur_e)
		p = p->next;

	if (p->next == L)
		return ERROR;

	*next_e = p->next->data;
	return OK;
}

/* 在指定位置前插入一个新元素 */
Status ListInsert(LinkList *L, int i, ElemType e)
{
	LinkList s, p = *L;	//p指向头结点
	int      pos = 0;

	if (i == 1)
		;
	else
	{
		/* 寻找第i-1个结点 */
		do {
			p = p->next;
			pos++;
		} while (p != (*L) && pos < i - 1);

		if (p == (*L) || pos > i - 1)  //i值非法则返回
			return ERROR;
	}


	//执行到此表示找到指定位置，p指向第i-1个结点
	s = (LinkList)malloc(sizeof(LNode));
	if (s == NULL)
		return OVERFLOW;

	s->data = e; 	//新结点数据域赋值
	s->next = p->next;	//新结点的next是第i个
	p->next = s;	//第i-1个的next是新结点

	return OK;
}

/* 尾插 */
Status ListAppend(LinkList *L, ElemType e)
{
	LinkList s, p = *L;	//p指向头结点

	/* 寻找末结点 */
	while (p->next != (*L))
	{
		p = p->next;
	}

	//执行到此表示找到指定位置，p指向末结点
	s = (LinkList)malloc(sizeof(LNode));
	if (s == NULL)
		return OVERFLOW;

	s->data = e; 	//新结点数据域赋值
	s->next = p->next;	//新结点的next是第i个
	p->next = s;	//第i-1个的next是新结点

	return OK;
}

/* 删除指定位置的元素，并将被删除元素的值放入e中返回 */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
	LinkList q, p = *L;	//p指向头结点
	int      pos = 0;

	/* 寻找第i个结点（p->next是第i个结点） */
	while (p->next != (*L) && pos < i - 1) {
		p = p->next;
		pos++;
	}

	if (p->next == (*L) || pos > i - 1)	//i值非法则返回
		return ERROR;

	//执行到此表示找到了第i个结点，此时p指向第i-1个结点

	q = p->next;       //q指向第i个结点
	p->next = q->next; //第i-1个结点的next域指向第i+1个

	*e = q->data;      //取第i个结点的值
	free(q);           //释放第i个结点

	return OK;
}

/* 遍历线性表 */
Status ListTraverse(LinkList L, Status(*visit)(ElemType e))
{
	LinkList p = L->next;

	while (p != L && (*visit)(p->data) == TRUE)
		p = p->next;

	if (p != L)
		return ERROR;

	printf("\n");//最后打印一个换行，只是为了好看，与算法无关
	return OK;
}

#define INSERT_NUM		115		//初始插入表中的元素数量
#define MAX_NUM_PER_LINE 	10		//每行最多输出的元素个数

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
		printf_s("%d 出列\n", p->next->data);
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
		printf_s("请依次输入n，m，k的值，空格隔开：");
		succNum = scanf_s("%d %d %d", &n, &m, &k);
		rewind(stdin);

	} while (succNum != 3);

	LinkList l;
	createList(&l, n);
	eliminate(&l, n, m, k);
	DestroyList(&l);
	
	return 0;
}
