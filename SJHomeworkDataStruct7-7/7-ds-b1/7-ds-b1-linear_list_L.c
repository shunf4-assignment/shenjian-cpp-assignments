/* 1652270 �����2�� ��˴ */
#include <stdio.h>
#include <stdlib.h>		//malloc/realloc����
//#include <unistd.h>		//exit����
#ifndef _UNISTD_H
#define _UNISTD_H 
#include <io.h> 
#include <process.h> 
#endif /* _UNISTD_H */
#include "7-ds-b1-linear_list_L.h"	//��ʽ����

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
Status DestroyList(LinkList *L, Status (*sub_free)(LinkList *L))
{
	LinkList q, p = *L; //ָ����Ԫ
	/* �����ͷſռ� */
	(*sub_free)(L);

	/* ��������(��ͷ���)�����ͷ� */
	while (p) {    //������Ϊ�գ���ѭ����ִ��

		q = p->next; //ץס��������һ�����
		free(p);
		p = q;
	}

	*L = NULL;	//ͷָ����NULL
	return OK;
}

/* ������Ա�������ͷ��㣩 */
Status ClearList(LinkList *L, Status(*sub_free)(LinkList *L))
{
	LinkList q, p = (*L)->next;
	/* �����ͷſռ� */
	(*sub_free)(L);

	/* ����Ԫ��㿪ʼ�����ͷ� */
	while (p) {
		q = p->next;   //ץס��������һ�����
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

/* ����ĳ��� */
int ListLength(LinkList L)
{
#if 1
	LinkList p = L->next; //ָ����Ԫ���
	int len = 0;

	/* ѭ���������������м��� */
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
Status GetElem(LinkList L, int i, ElemType *e, Status(*assign)(ElemType *dst, ElemType src))
{
	LinkList p = L->next;	//ָ����Ԫ���
	int    pos = 1;		//��ʼλ��Ϊ1

						/* ������ΪNULL �� δ����i��Ԫ�� */
	while (p != NULL && pos<i) {
		p = p->next;
		pos++;
	}

	if (!p || pos>i)
		return ERROR;

	if((*assign)(e, p->data) == ERROR)
		return ERROR;
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
Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e, Status(*compare)(ElemType e1, ElemType e2), Status(*assign)(ElemType *dst, ElemType src))
{
#if 1
	LinkList p = L->next;	//ָ����Ԫ���

	if (p == NULL)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �ӵ�2����㿪ʼѭ����������(����Ƚ���ȣ���֤��ǰ��) */
	while (p->next && !(*compare)(p->next->data, cur_e))
		p = p->next;

	if (p->next == NULL) //δ�ҵ�
		return ERROR;

	if((*assign)(pre_e, p->data) == ERROR)
		return ERROR;
	return OK;
#else
	LinkList p = L; //ָ��ͷ���

					/* ѭ�������������Ƚ�ֵ�Ƿ���� */
	while (p->next && p->next->data != cur_e)
		p = p->next;

	if (p->next == NULL || p == L) //δ�ҵ�����Ԫ����ձ�
		return ERROR;
	*pre_e = p->data;
	return OK;
#endif
}

/* ���ҷ���ָ��������Ԫ�صĺ��Ԫ�� */
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e, Status(*compare)(ElemType e1, ElemType e2), Status(*assign)(ElemType *dst, ElemType src))
{
	LinkList p = L->next;  //��Ԫ���

	if (p == NULL)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �к�̽���ҵ�ǰ���ֵ����ʱ���� */
	while (p->next && !(*compare)(p->data, cur_e) )
		p = p->next;

	if (p->next == NULL)
		return ERROR;

	if ((*assign)(next_e, p->next->data) == ERROR)
		return ERROR;
	return OK;
}

/* ��ָ��λ��ǰ����һ����Ԫ�� */
Status ListInsert(LinkList *L, int i, ElemType e, Status(*assign)(ElemType *dst, ElemType src), Status(*allocnode)(LinkList *p, ElemType e))
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

	//s = (LinkList)malloc(sizeof(LNode));
	if ((*allocnode)(&s, e) == LOVERFLOW)
		return LOVERFLOW;

	if ((*assign)(&(s->data), e) == ERROR)
		return ERROR; 	//�½��������ֵ
	s->next = p->next;	//�½���next�ǵ�i��
	p->next = s;	//��i-1����next���½��

	return OK;
}

/* ɾ��ָ��λ�õ�Ԫ�أ�������ɾ��Ԫ�ص�ֵ����e�з��� */
Status ListDelete(LinkList *L, int i, ElemType *e, Status(*assign)(ElemType *dst, ElemType src), Status(*subfree)(ElemType p))
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

	if ((*assign)(e, q->data) == ERROR)
		return ERROR;	//ȡ��i������ֵ
	(*subfree)(q->data);
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

	//printf("\n");//����ӡһ�����У�ֻ��Ϊ�˺ÿ������㷨�޹�
	return OK;
}