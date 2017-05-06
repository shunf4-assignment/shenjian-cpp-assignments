/*1652270 计算机2班 冯舜*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>		//malloc/realloc函数
#include <io.h>		//exit函数

#define ELEMTYPE_IS_STRUCT_STUDENT

/* P.10 的预定义常量和类型 */
#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define LOVERFLOW	-2

typedef int Status;

/* P.28 形式定义 */

#if defined (ELEMTYPE_IS_STRUCT_STUDENT)
typedef struct student {
	int   num;
	char  name[10];
	char  sex;
	float score;
	char  addr[30];
} ElemType;
//#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
#else
typedef struct student {
	int   num;
	char  name[10];
	char  sex;
	float score;
	char  addr[30];
} ET, *ElemType;
#endif

typedef struct DuLNode {
	ElemType        data;	//存放数据
	struct DuLNode *prior;	//存放直接前驱的指针
	struct DuLNode *next;	//存放直接后继的指针
} DuLNode, *DuLinkList;

/* P.19-20的抽象数据类型定义转换为实际的C语言 */
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
Status	ListTraverse(DuLinkList L, Status(*visit)(ElemType e));

/* 初始化线性表 */
Status InitList(DuLinkList *L)
{
	/* 申请头结点空间，赋值给头指针 */
	*L = (DuLNode *)malloc(sizeof(DuLNode));
	if (*L == NULL)
		exit(LOVERFLOW);

	(*L)->prior = *L;
	(*L)->next = *L;
	return OK;
}

/* 删除线性表 */
Status DestroyList(DuLinkList *L, Status(*sub_free)(DuLinkList *L))
{
	DuLinkList q, p = *L; //指向首元
	/* 按需释放空间 */
	(*sub_free)(L);
						  /* 整个链表(含头结点)依次释放(同单链表，不考虑prior指针，只用next) */
	do {    //若链表为空，则循环不执行
		q = p->next; //抓住链表的下一个结点
		free(p);
		p = q;
	} while (p != (*L));

	*L = NULL;	//头指针置NULL
	return OK;
}

/* 清除线性表（保留头结点） */
Status ClearList(DuLinkList *L, Status(*sub_free)(DuLinkList *L))
{
	DuLinkList q, p = (*L)->next;
	(*sub_free)(L);
	/* 从首元结点开始依次释放(同单链表，不考虑prior指针，只用next) */
	while (p != (*L)) {
		q = p->next;   //抓住链表的下一个结点
		free(p);
		p = q;
	}

	(*L)->prior = *L; //头结点的prior域置NULL
	(*L)->next = *L; //头结点的next域置NULL
	return OK;
}

/* 判断是否为空表 */
Status ListEmpty(DuLinkList L)
{
	/* 判断头结点的next域即可(同单链表) */
	if (L->next == L)
		return TRUE;
	else
		return FALSE;
}

/* 求表的长度 */
int ListLength(DuLinkList L)
{
	DuLinkList p = L->next; //指向首元结点
	int len = 0;

	/* 循环整个链表，进行计数(同单链表) */
	while (p != L) {
		p = p->next;
		len++;
	}

	return len;
}

/* 取表中元素 */
Status GetElem(DuLinkList L, int i, ElemType *e, Status (*assign)(ElemType *e, ElemType a))
{
	DuLinkList p = L->next;	//指向首元结点
	int    pos = 1;		//初始位置为1

						/* 链表不为NULL 且 未到第i个元素(同单链表) */
	while (p != L && pos<i) {
		p = p->next;
		pos++;
	}

	if (p == L || pos>i)
		return ERROR;
	
	//*e = p->data;
	return assign(e, p->data);
}

/* 查找符合指定条件的元素 */
int LocateElem(DuLinkList L, ElemType e, Status(*compare)(ElemType e1, ElemType e2))
{
	DuLinkList p = L->next;	//首元结点
	int    pos = 1;		//初始位置

						/* 循环整个链表(同单链表)  */
	while (p != L && (*compare)(e, p->data) == FALSE) {
		p = p->next;
		pos++;
	}

	return (p != L) ? pos : 0;
}

/* 查找符合指定条件的元素的前驱元素 */
Status PriorElem(DuLinkList L, ElemType cur_e, ElemType *pre_e, Status(*compare)(ElemType e1, ElemType e2), Status(*assign)(ElemType *e, ElemType a))
{
	DuLinkList p = L->next;	//指向首元结点

	if (p == L)	//空表直接返回
		return ERROR;

	/* 从第2个结点开始循环整个链表(如果比较相等，保证有前驱)(同单链表) */
	while (p->next != L && compare(p->next->data, cur_e) == FALSE)
		p = p->next;

	if (p->next == L) //未找到
		return ERROR;

	return assign(pre_e, p->data);
	//return OK;
}

/* 查找符合指定条件的元素的后继元素 */
Status NextElem(DuLinkList L, ElemType cur_e, ElemType *next_e, Status(*compare)(ElemType e1, ElemType e2), Status(*assign)(ElemType *e, ElemType a))
{
	DuLinkList p = L->next;  //首元结点

	if (p == L)	//空表直接返回
		return ERROR;

	/* 有后继结点且当前结点值不等时继续(同单链表) */
	while (p->next != L && compare(p->data , cur_e) == FALSE)
		p = p->next;

	if (p->next == L)
		return ERROR;

	//*next_e = p->next->data;
	return assign(next_e, p->next->data);
}

/* 在指定位置前插入一个新元素 */
Status ListInsert(DuLinkList *L, int i, ElemType e, Status(*assign)(ElemType *e, ElemType a), Status(*allocnode)(DuLinkList *p, ElemType e))
{
#if 0
	DuLinkList s, p = *L;	//p指向头结点
	int      pos = 1;

	/* 寻找第i个结点(i可能是表长+1) */
	while (p->next && pos<i - 1) {
		p = p->next;
		pos++;
	}

	if (p->next == NULL || pos>i - 1)  //i值非法则返回
		return ERROR;

	//执行到此表示找到指定位置，p指向第i-1个结点

	s = (DuLinkList)malloc(sizeof(DuLNode));
	if (s == NULL)
		return LOVERFLOW;

	if (pos == i - 1) {
	}
	else {
		/* 注意，p可能是NULL */
		s->data = e; 	//新结点数据域赋值
		s->prior = p->prior;
		p->prior->next = s;
		s->next = p;	//新结点的next是第i个
		p->prior = s;	//第i-1个的next是新结点
	}
#else
	DuLinkList s, p = *L;	//p指向头结点
	Status error;
	int      pos = 0;

	/* 寻找第i-1个结点 */
	if (i == 1)
		;
	else
	{
		do {
			p = p->next;
			pos++;
		} while (p != (*L) && pos < i - 1);

		if (p == (*L) || pos>i)  //i值非法则返回
			return ERROR;
	}

	//执行到此表示找到指定位置，p指向第i-1个结点
	/*s = (DuLinkList)malloc(sizeof(DuLNode));
	if (s == NULL)
		return LOVERFLOW;*/
	if ((*allocnode)(&s, e) == LOVERFLOW)
		return LOVERFLOW;

	if((error = assign(&(s->data), e)) != OK)
		return error; 	//新结点数据域赋值
	s->next = p->next;  //新结点的next是第i个结点(即使p->next是*L也没问题)
	p->next->prior = s; //第i个结点的prior是s
	s->prior = p;       //s的前驱是p
	p->next = s;        //p的后继是s
#endif

	return OK;
}

/* 删除指定位置的元素，并将被删除元素的值放入e中返回 */
Status ListDelete(DuLinkList *L, int i, ElemType *e, Status(*assign)(ElemType *e, ElemType a), Status(*specfree)(ElemType p))
{
#if 1
	DuLinkList p = *L;	//p指向头结点
	Status error;
	int      pos = 0;

	/* 寻找第i个结点（p是第i个结点） */
	do {
		p = p->next;
		pos++;
	} while (p != (*L) && pos < i);

	if (p == (*L) || pos>i)	//i值非法则返回
		return ERROR;

	//执行到此表示找到了第i个结点，此时p指向第i个结点

	if ((error = assign(e, p->data)) != OK)
		return error; 	//新结点数据域赋值
	//e = p->data;      //取第i个结点的值
	p->prior->next = p->next;
	//if (p->next) //要加判断条件
	p->next->prior = p->prior;
	(*specfree)(p->data);
	free(p);           //释放第i个结点
#else
	DuLinkList q, p = *L;	//p指向头结点
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
	p->next = q->next; //第i-1个结点的next域指向第i+1个(即使NULL也没错)
	if (q->next)
		q->next->prior = p;

	*e = q->data;      //取第i个结点的值
	free(q);           //释放第i个结点
#endif

	return OK;
}

/* 遍历线性表 */
Status ListTraverse(DuLinkList L, Status(*visit)(ElemType e))
{
	extern int line_count; //在main中定义的打印换行计数器（与算法无关）
	DuLinkList p = L->next;
	line_count = 0;		//计数器恢复初始值（与算法无关）

#if 1
	while (p != L && (*visit)(p->data) == TRUE) //同单链表
		p = p->next;

	if (p != L)
		return ERROR;

	//printf("\n");//最后打印一个换行，只是为了好看，与算法无关
#else
						/* 逆序输出 */
	while (p->next) //同单链表
		p = p->next;

	/* 执行到此，p指向最后一个结点 */
	while (p && p->prior && (*visit)(p->data) == TRUE) //同单链表
		p = p->prior;

	printf("\n");//最后打印一个换行，只是为了好看，与算法无关
#endif

	return OK;
}

/*获取第i个位置的结点指针*/
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

#define INSERT_NUM		115		//初始插入表中的元素数量
#define MAX_NUM_PER_LINE 	10		//每行最多输出的元素个数

int line_count = 0;   //打印链表时的计数器

Status MyCompare(ElemType e1, ElemType e2)
{
#if defined (ELEMTYPE_IS_STRUCT_STUDENT)
	if (e1.num == e2.num)
#else
	if (e1->num == e2->num)
#endif
		return TRUE;
	return FALSE;
}

Status MyVisit(ElemType e)
{
#if defined (ELEMTYPE_IS_STRUCT_STUDENT)
	printf("%d-%s-%c-%f-%s->", e.num, e.name, e.sex, e.score, e.addr);
#else
	printf("%d-%s-%c-%f-%s->", e->num, e->name, e->sex, e->score, e->addr);
#endif
	/* 每输出MAX_NUM_PER_LINE个，打印一个换行 */
	if ((++line_count) % MAX_NUM_PER_LINE == 0)
		printf("\n");

	return OK;
}

Status MySubFree(DuLinkList *L)
{
	/* 两种指针类型需要释放二级空间，其它什么也不做 */
#if ! defined (ELEMTYPE_IS_STRUCT_STUDENT)
	DuLinkList p = (*L)->next;

	while (p != *L)
	{
		free(p->data);
		p = p->next;
	}

#endif
	return OK;
}

/* 赋值 */
Status MyAssign(ElemType *dst, ElemType src)
{
#if defined (ELEMTYPE_IS_STRUCT_STUDENT)
	memcpy(dst, &src, sizeof(ElemType));
#else
	memcpy(*dst, src, sizeof(ET));
#endif

	return OK;
}

Status MyAlloc(DuLinkList *p, ElemType e)
{
	*p = (DuLinkList)malloc(sizeof(DuLNode));
	if ((*p) == NULL)
		return LOVERFLOW;
#if  ! defined (ELEMTYPE_IS_STRUCT_STUDENT)
	(*p)->data = (ElemType)malloc(sizeof(ET));
	if ((*p)->data == NULL)
		return LOVERFLOW;
#endif
	
	return OK;
}

Status MyFree(ElemType p)
{
#if  ! defined (ELEMTYPE_IS_STRUCT_STUDENT)
	free(p);
#endif

	return OK;
}

int main()
{
#if defined (ELEMTYPE_IS_STRUCT_STUDENT)
	/* 这两种数据类型需要预置数据 */
	ElemType e[] = { { 1001, "张三", 'M', 76.5, "上海市杨浦区" },
	{ 1002, "李四", 'F', 87, "上海市普陀区" },
	{ 1003, "王五", 'M', 80, "浙江省杭州市" },
	{ 1004, "赵六", 'M', 54, "浙江省绍兴市" },
	{ 1005, "牛七", 'F', 85, "江苏省南京市" },
	{ 1006, "马八", 'M', 60, "江苏省苏州市" } };
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
	/* 这两种数据类型需要预置数据 */
	ET       e[] = { { 1001, "张三", 'M', 76.5, "上海市杨浦区" },
	{ 1002, "李四", 'F', 87, "上海市普陀区" },
	{ 1003, "王五", 'M', 80, "浙江省杭州市" },
	{ 1004, "赵六", 'M', 54, "浙江省绍兴市" },
	{ 1005, "牛七", 'F', 85, "江苏省南京市" },
	{ 1006, "马八", 'M', 60, "江苏省苏州市" } };
#endif
	DuLinkList L;
	ElemType e1;
	int      i, pos;

	InitList(&L);

#if defined (ELEMTYPE_IS_STRUCT_STUDENT)
	printf("插入 %d 个元素：\n", sizeof(e) / sizeof(e[0]));
	for (i = 0; i< sizeof(e) / sizeof(e[0]) ; i++)
		ListInsert(&L, ListLength(L) + 1, *(e + i), MyAssign, MyAlloc);
#else
	printf("插入 %d 个元素：\n", sizeof(e) / sizeof(e[0]));
	for (i = 0; i< sizeof(e) / sizeof(e[0]); i++)
		ListInsert(&L, ListLength(L) + 1, (e + i), MyAssign, MyAlloc);
#endif
	printf("插入后的线性表如下：\n");
	ListTraverse(L, MyVisit);//此处传入MyVisit函数名

	printf("\n表长=%d\n\n", ListLength(L));


	for (int o = 0; o < 3; o++)
	{
		printf("\n第 %d 次插入元素\n", o + 1);
#if defined (ELEMTYPE_IS_STRUCT_STUDENT)
		printf("\n\n请输入要插入元素的值(学号 姓名 性别 成绩 地址)：\n");
		scanf("%d %s %c %f %s", &e1.num, e1.name, &e1.sex, &e1.score, e1.addr);
#else
		printf("\n请输入要插入元素的值(学号 姓名 性别 成绩 地址)：\n");
		scanf("%d %s %c %f %s", &e1->num, e1->name, &e1->sex, &e1->score, e1->addr);
#endif
		//printf("请输入要插入元素的位序：\n");
		//scanf("%d", &pos);
		printf("\n");
		switch (o)
		{
			case 0:
				pos = 1;
				printf("该元素将在首元之前插入。\n");
				break;
			case 1:
				pos = 3;
				printf("该元素将在第 3 个结点之前插入。\n");
				break;
			case 2:
				pos = ListLength(L) + 1;
				printf("该元素将在最末结点后插入。\n");
				break;
		}
		if (ListInsert(&L, pos, e1, MyAssign, MyAlloc) == OK) {
#if defined (ELEMTYPE_IS_STRUCT_STUDENT)
			printf("在%d前插入元素=\"%d.%s.%c.%f.%s\"成功\n", pos, e1.num, e1.name, e1.sex, e1.score, e1.addr);
#else
			printf("在%d前插入元素=\"%d.%s.%c.%f.%s\"成功\n", pos, e1->num, e1->name, e1->sex, e1->score, e1->addr);
#endif
			printf("新表为：\n");
			ListTraverse(L, MyVisit);
		}
		else
#if defined (ELEMTYPE_IS_STRUCT_STUDENT)
			printf("在%d前插入元素=\"%d.%s.%c.%f.%s\"失败\n", pos, e1.num, e1.name, e1.sex, e1.score, e1.addr);
#else
			printf("在%d前插入元素=\"%d.%s.%c.%f.%s\"失败\n", pos, e1->num, e1->name, e1->sex, e1->score, e1->addr);
#endif
	}


/*
	printf("\n请输入要删除元素的位序：\n");
	scanf("%d", &pos);
	if (ListDelete(&L, pos, &e1, MyAssign, MyFree) == OK) {
#ifdef ELEMTYPE_IS_DOUBLE
		printf("删除第%d元素=%5.1f成功\n", pos, e1);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
		printf("删除第%d元素=%s成功\n", pos, e1);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
		printf("删除第%d元素=\"%d.%s.%c.%f.%s\"成功\n", pos, e1.num, e1.name, e1.sex, e1.score, e1.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
		printf("删除第%d元素=\"%d.%s.%c.%f.%s\"成功\n", pos, e1->num, e1->name, e1->sex, e1->score, e1->addr);
#else	//缺省当做int处理
		printf("删除第%d元素=%d成功\n", pos, e1);
#endif
		printf("新表为：\n");
		ListTraverse(L, MyVisit);
	}
	else
#ifdef ELEMTYPE_IS_DOUBLE
		printf("删除第%d元素=%5.1f失败\n", pos, e1);
#elif defined (ELEMTYPE_IS_CHAR_ARRAY) || defined (ELEMTYPE_IS_CHAR_P)
		printf("删除第%d元素=%s失败\n", pos, e1);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
		printf("删除第%d元素=\"%d.%s.%c.%f.%s\"失败\n", pos, e1.num, e1.name, e1.sex, e1.score, e1.addr);
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
		printf("删除第%d元素=\"%d.%s.%c.%f.%s\"失败\n", pos, e1->num, e1->name, e1->sex, e1->score, e1->addr);
#else	//缺省当做int处理
		printf("删除第%d元素=%d失败\n", pos, e1);
#endif
*/
	printf("\n清空表：\n");
	ClearList(&L, MySubFree);
	printf("空表=%s\n", (ListEmpty(L) == TRUE) ? "TRUE" : "FALSE");
	printf("表长=%d\n", ListLength(L));

	DestroyList(&L, MySubFree);

	return 0;
}