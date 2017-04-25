/* 1652270 �����2�� ��˴ */
#include <stdio.h>
#include <stdlib.h>		//malloc/realloc����
//#include <unistd.h>		//exit����
#ifndef _UNISTD_H
#define _UNISTD_H 
#include <io.h> 
#include <process.h> 
#endif /* _UNISTD_H */
#include "7-ds-b2-linear_list_L.h"	//��ʽ����

/* ��ʼ�����Ա� */
Status InitList(LinkList *L)
{
	*L = NULL;  //ͷָ��ֱ�Ӹ�NULL
	return OK;
}

/* ɾ�����Ա� */
Status DestroyList(LinkList *L, Status(*sub_free)(LinkList *L))
{
	LinkList q, p = *L; //ָ����Ԫ

	/* �����ͷſռ� */
	(*sub_free)(L);
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
Status ClearList(LinkList *L, Status(*sub_free)(LinkList *L))
{
	LinkList q, p = *L; //ָ����Ԫ
	/* �����ͷſռ� */
	(*sub_free)(L);
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
Status GetElem(LinkList L, int i, ElemType *e, Status(*assign)(ElemType *dst, ElemType src))
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

	if ((*assign)(e, p->data) == ERROR)
		return ERROR;
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
Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e, Status(*compare)(ElemType e1, ElemType e2), Status(*assign)(ElemType *dst, ElemType src))
{
	LinkList p = L; //ָ����Ԫ���

	if (p == NULL)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �ӵ�2����㿪ʼѭ����������(����Ƚ���ȣ���֤��ǰ��) */
	while (p->next && !(*compare)(p->next->data, cur_e))
		p = p->next;

	if (p->next == NULL) //δ�ҵ�
		return ERROR;

	if ((*assign)(pre_e, p->data) == ERROR)
		return ERROR;
	return OK;
}

/* ���ҷ���ָ��������Ԫ�صĺ��Ԫ�� */
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e, Status(*compare)(ElemType e1, ElemType e2), Status(*assign)(ElemType *dst, ElemType src))
{
	LinkList p = L;  //��Ԫ���

	if (p == NULL)	//�ձ�ֱ�ӷ���
		return ERROR;

	/* �к�̽���ҵ�ǰ���ֵ����ʱ���� */
	while (p->next && !(*compare)(p->data, cur_e))
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

	//s = (LinkList)malloc(sizeof(LNode));
	if ((*allocnode)(&s, e) == LOVERFLOW)
		return LOVERFLOW;

	if ((*assign)(&(s->data), e) == ERROR)
		return ERROR; 	//�½��������ֵ
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
Status ListDelete(LinkList *L, int i, ElemType *e, Status(*assign)(ElemType *dst, ElemType src), Status(*subfree)(ElemType p))
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

	if ((*assign)(e, q->data) == ERROR)
		return ERROR;	//ȡ��i������ֵ
	(*subfree)(q->data);
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

	//printf("\n");//����ӡһ�����У�ֻ��Ϊ�˺ÿ������㷨�޹�
	return OK;
}
