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
#define LOVERFLOW	-2

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
		exit(LOVERFLOW);

	(*L)->next = NULL;
	return OK;
}

/* 删除线性表 */
Status DestroyList(LinkList *L)
{
	LinkList q, p = *L; //指向首元

						/* 整个链表(含头结点)依次释放 */
	while (p) {    //若链表为空，则循环不执行
		q = p->next; //抓住链表的下一个结点
		free(p);
		p = q;
	}

	*L = NULL;	//头指针置NULL
	return OK;
}

/* 清除线性表（保留头结点） */
Status ClearList(LinkList *L)
{
	LinkList q, p = (*L)->next;

	/* 从首元结点开始依次释放 */
	while (p) {
		q = p->next;   //抓住链表的下一个结点
		free(p);
		p = q;
	}

	(*L)->next = NULL; //头结点的next域置NULL
	return OK;
}

/* 判断是否为空表 */
Status ListEmpty(LinkList L)
{
	/* 判断头结点的next域即可 */
	if (L->next == NULL)
		return TRUE;
	else
		return FALSE;
}

/* 求表的长度 */
int ListLength(LinkList L)
{
#if 1
	LinkList p = L->next; //指向首元结点
	int len = 0;

	/* 循环整个链表，进行计数 */
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

/* 取表中元素 */
Status GetElem(LinkList L, int i, ElemType *e)
{
	LinkList p = L->next;	//指向首元结点
	int    pos = 1;		//初始位置为1

						/* 链表不为NULL 且 未到第i个元素 */
	while (p != NULL && pos<i) {
		p = p->next;
		pos++;
	}

	if (!p || pos>i)
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
	while (p && (*compare)(e, p->data) == FALSE) {
		p = p->next;
		pos++;
	}

	return p ? pos : 0;
}

/* 查找符合指定条件的元素的前驱元素 */
Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e)
{
#if 1
	LinkList p = L->next;	//指向首元结点

	if (p == NULL)	//空表直接返回
		return ERROR;

	/* 从第2个结点开始循环整个链表(如果比较相等，保证有前驱) */
	while (p->next && p->next->data != cur_e)
		p = p->next;

	if (p->next == NULL) //未找到
		return ERROR;

	*pre_e = p->data;
	return OK;
#else
	LinkList p = L; //指向头结点

					/* 循环整个链表并比较值是否相等 */
	while (p->next && p->next->data != cur_e)
		p = p->next;

	if (p->next == NULL || p == L) //未找到或首元结点或空表
		return ERROR;
	*pre_e = p->data;
	return OK;
#endif
}

/* 查找符合指定条件的元素的后继元素 */
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e)
{
	LinkList p = L->next;  //首元结点

	if (p == NULL)	//空表直接返回
		return ERROR;

	/* 有后继结点且当前结点值不等时继续 */
	while (p->next && p->data != cur_e)
		p = p->next;

	if (p->next == NULL)
		return ERROR;

	*next_e = p->next->data;
	return OK;
}

/* 在指定位置前插入一个新元素 */
Status ListInsert(LinkList *L, int i, ElemType e)
{
	LinkList s, p = *L;	//p指向头结点
	int      pos = 0;

	/* 寻找第i-1个结点 */
	while (p && pos<i - 1) {
		p = p->next;
		pos++;
	}

	if (p == NULL || pos>i - 1)  //i值非法则返回
		return ERROR;

	//执行到此表示找到指定位置，p指向第i-1个结点

	s = (LinkList)malloc(sizeof(LNode));
	if (s == NULL)
		return LOVERFLOW;

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
	while (p->next && pos<i - 1) {
		p = p->next;
		pos++;
	}

	if (p->next == NULL || pos>i - 1)	//i值非法则返回
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
	extern int line_count; //在main中定义的打印换行计数器（与算法无关）
	LinkList p = L->next;

	line_count = 0;		//计数器恢复初始值（与算法无关）
	while (p && (*visit)(p->data) == TRUE)
		p = p->next;

	if (p)
		return ERROR;

	printf("\n");//最后打印一个换行，只是为了好看，与算法无关
	return OK;
}

#define INSERT_NUM		115		//初始插入表中的元素数量
#define MAX_NUM_PER_LINE 	10		//每行最多输出的元素个数

int line_count = 0;   //打印链表时的计数器

void difference(LinkList *La, LinkList *Lb)
{//删除Lb中所有内容，将La修改为原La与Lb的对称差
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

	/* 每输出MAX_NUM_PER_LINE个，打印一个换行 */
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

	printf("LA 中内容：\n");
	ListTraverse(LA, MyVisit);
	printf("\nLB 中内容：\n");
	ListTraverse(LB, MyVisit);
	printf("\n\n求对称差后，LA 中内容：\n");
	difference(&LA, &LB);
	ListTraverse(LA, MyVisit);
	printf("\n\n求对称差后，LB 中内容：\n");
	ListTraverse(LB, MyVisit);
	printf("\n");
	return 0;
}
