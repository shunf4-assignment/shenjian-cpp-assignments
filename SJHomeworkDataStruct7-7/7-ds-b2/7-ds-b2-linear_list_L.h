/* 1652270 计算机2班 冯舜 */
#pragma once

//#define ELEMTYPE_IS_INT
//#define ELEMTYPE_IS_DOUBLE
//#define ELEMTYPE_IS_CHAR_ARRAY
//#define ELEMTYPE_IS_CHAR_P
#define ELEMTYPE_IS_STRUCT_STUDENT
//#define ELEMTYPE_IS_STRUCT_STUDENT_P

/* P.10 的预定义常量和类型 */
#define TRUE		1
#define FALSE		0
#define OK		1
#define ERROR		0
#define INFEASIBLE	-1
#define LOVERFLOW	-2

typedef int Status;

/* P.28 形式定义 */
#ifdef ELEMTYPE_IS_DOUBLE
typedef double ElemType;
#elif defined (ELEMTYPE_IS_CHAR_ARRAY)
typedef char ElemType[10];
#elif defined (ELEMTYPE_IS_CHAR_P)
typedef char* ElemType;
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT)
typedef struct student {
	int   num;
	char  name[10];
	char  sex;
	float score;
	char  addr[30];
} ElemType;
#elif defined (ELEMTYPE_IS_STRUCT_STUDENT_P)
typedef struct student {
	int   num;
	char  name[10];
	char  sex;
	float score;
	char  addr[30];
} ET, *ElemType;
#else
typedef int ElemType;
#endif

typedef struct LNode {
	ElemType      data;	//存放数据
	struct LNode *next;	//存放直接后继的指针
} LNode, *LinkList;

/* P.19-20的抽象数据类型定义转换为实际的C语言 */
Status	InitList(LinkList *L);
Status DestroyList(LinkList *L, Status(*sub_free)(LinkList *L));
Status ClearList(LinkList *L, Status(*sub_free)(LinkList *L));
Status	ListEmpty(LinkList L);
int	ListLength(LinkList L);
Status	GetElem(LinkList L, int i, ElemType *e, Status(*assign)(ElemType *dst, ElemType src));
int	LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType e1, ElemType e2));
Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e, Status(*compare)(ElemType e1, ElemType e2), Status(*assign)(ElemType *dst, ElemType src));
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e, Status(*compare)(ElemType e1, ElemType e2), Status(*assign)(ElemType *dst, ElemType src));
Status ListInsert(LinkList *L, int i, ElemType e, Status(*assign)(ElemType *dst, ElemType src), Status(*allocnode)(LinkList *p, ElemType e));
Status ListDelete(LinkList *L, int i, ElemType *e, Status(*assign)(ElemType *dst, ElemType src), Status(*freenode)(ElemType p));
Status	ListTraverse(LinkList L, Status(*visit)(ElemType e));

