/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#pragma once
#include "7-ds-b12-double1.h"
#include "7-ds-b12-student.h"

#define STAT_OK 0
#define STAT_ERR 1
#define STAT_INFEASIBLE -2
#define STAT_OVERFLOW -1

using Status = int;


template <typename ElemType>
class LNode
{
protected:
	ElemType data;
	LNode *next;
public:
	template<typename ElemType2>
	friend class LinkList;
	LNode();
	//~LNode();
	LNode(const ElemType &data_);
	LNode(const ElemType &data_, LNode<ElemType> *next_);
	void setNext(LNode *next_);
	LNode& operator+(unsigned i);
};

template <typename ElemType>
class LinkList
{
protected:
	LNode<ElemType> head;
public:
	LinkList();
	~LinkList();
	Status clear();
	bool isEmpty();
	unsigned length();
	ElemType & operator[](unsigned i);
	Status get(ElemType &dst, unsigned index);
	int locate(ElemType curElem);
	Status prior(ElemType &dst, ElemType curElem);
	Status next(ElemType &dst, ElemType curElem);
	Status insert(ElemType newElem, unsigned index);
	Status pop(ElemType &dst, unsigned index);
	Status traverse(Status (*visit)(ElemType, bool firstInvoke));
};

template<typename ElemType, typename ElemTypeConst>
void elemCopy(ElemType &dst, const ElemTypeConst &src)
{
	dst = ElemType(src);
}

template<typename ElemType>
bool isElemEqual(const ElemType &e1, const ElemType &e2)
{
	return (e1 == e2);
}

template<typename ElemType>
void elemFree(ElemType *&pointer)
{
	if (nullptr != pointer)
	{
		delete pointer;
	}
	pointer = nullptr;
}

