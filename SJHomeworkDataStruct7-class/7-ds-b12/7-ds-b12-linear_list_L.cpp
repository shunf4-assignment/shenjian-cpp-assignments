/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include "7-ds-b12-linear_list_L.h"




template<typename ElemType>
inline LNode<ElemType>::LNode()
	: data{}, next{}
{
}

template<typename ElemType>
LNode<ElemType>::LNode(const ElemType &data_)
	: next{}
{
	elemCopy(data, data_);
}

template<typename ElemType>
LNode<ElemType>::LNode(const ElemType & data_, LNode<ElemType>* next_)
{
	elemCopy(data, data_);
	next = next_;
}

template<typename ElemType>
void LNode<ElemType>::setNext(LNode * next_)
{
	next = next_;
}

template<typename ElemType>
LNode<ElemType> & LNode<ElemType>::operator+(unsigned i)
{
	LNode<ElemType> *pNode = this;
	while (nullptr != pNode && i > 0)
	{
		i--;
		pNode = pNode->next;
	}

	if (0 != i || nullptr == pNode)
	{
		//pNode == nullptr, out of range
		throw "LNode: index out of range in operator+";
	}
	
	return (*pNode);
}

template<typename ElemType>
LinkList<ElemType>::LinkList()
	: head()
{
}

template<typename ElemType>
LinkList<ElemType>::~LinkList()
{
	clear();
}

template<typename ElemType>
Status LinkList<ElemType>::clear()
{
	LNode<ElemType> *&curr = head.next;

	LNode<ElemType> *currNext;
	while (curr)
	{
		currNext = curr->next;
		elemFree(curr);
		curr = currNext;
	}
	return STAT_OK;
}

template<typename ElemType>
bool LinkList<ElemType>::isEmpty()
{
	return (nullptr == head.next);
}

template<typename ElemType>
unsigned LinkList<ElemType>::length()
{
	unsigned length = 0;
	LNode<ElemType> *curr = head.next;
	while (curr != nullptr)
	{
		length++;
		curr = curr->next;
	}
	return length;
}

template<typename ElemType>
ElemType & LinkList<ElemType>::operator[](unsigned i)
{
	LNode<ElemType> *pNode = head.next;
	if (nullptr == pNode)
	{
		throw "LinkList : try to get Elem by index in an empty LinkList";
	}
	else
	{
		pNode = &((*pNode) + i);
	}
	return pNode->data;
}

template<typename ElemType>
Status LinkList<ElemType>::get(ElemType & dst, unsigned index)
{
	try
	{
		elemCopy(dst, (*this)[index]);
	}
	catch(const char *&errStr)
	{
		cerr << errStr << endl;
		return STAT_INFEASIBLE;
	}
	catch (std::bad_alloc &exp)
	{
		cerr << exp.what() << endl;
		return STAT_OVERFLOW;
	}
	return STAT_OK;
}

template<typename ElemType>
int LinkList<ElemType>::locate(ElemType curElem)
{
	LNode <ElemType> *pNode = head.next;
	int index = -1;
	while (nullptr != pNode)
	{
		index++;
		if (true == isElemEqual(pNode->data, curElem))
		{
			break;
		}
		pNode = pNode->next;
	}
	if (nullptr == pNode)
	{
		//not found
		return -1;
	}
	return index;
}

template<typename ElemType>
Status LinkList<ElemType>::prior(ElemType & dst, ElemType curElem)
{
	LNode<ElemType> *pPrevNode = &head;
	while (nullptr != pPrevNode->next)
	{
		if (isElemEqual(pPrevNode->next->data, curElem))
		{
			break;
		}
		pPrevNode = pPrevNode->next;
	}
	if (nullptr == pPrevNode->next || &head == pPrevNode)
	{
		return STAT_ERR;
	}
	else
	{
		elemCopy(dst, pPrevNode->data);
		return STAT_OK;
	}
}

template<typename ElemType>
Status LinkList<ElemType>::next(ElemType & dst, ElemType curElem)
{
	LNode <ElemType> *pNode = head.next;
	int index = -1;
	while (nullptr != pNode)
	{
		index++;
		if (true == isElemEqual(pNode->data, curElem))
		{
			break;
		}
		pNode = pNode->next;
	}
	if (nullptr == pNode || nullptr == pNode->next)
	{
		//not found
		return STAT_ERR;
	}
	elemCopy(dst, pNode->next->data);
	return STAT_OK;
}

template<typename ElemType>
Status LinkList<ElemType>::insert(ElemType newElem, unsigned index)
{
	LNode <ElemType> *pPrevNode = &head;
	while (nullptr != pPrevNode && nullptr != pPrevNode->next && index != 0)
	{
		index--;
		pPrevNode = pPrevNode->next;
	}
	if (index != 0)
		return STAT_INFEASIBLE;
	
	try
	{
		LNode<ElemType> *newNode = new LNode<ElemType>{ newElem, pPrevNode->next };
		pPrevNode->next = newNode;
	}
	catch (std::bad_alloc &exp)
	{
		std::cerr << exp.what() << std::endl;
		std::cerr << "LinkList : no enough memory when inserting" << std::endl;
		return STAT_OVERFLOW;
	}
	return STAT_OK;
}

template<typename ElemType>
Status LinkList<ElemType>::pop(ElemType & dst, unsigned index)
{
	LNode <ElemType> *pPrevNode = &head;
	while (nullptr != pPrevNode && nullptr != pPrevNode->next && index != 0)
	{
		index--;
		pPrevNode = pPrevNode->next;
	}
	if (index != 0)
		return STAT_INFEASIBLE;

	LNode <ElemType> *pPrevNext = pPrevNode->next;
	pPrevNode->next = pPrevNext->next;
	elemCopy(dst, pPrevNext->data);
	delete pPrevNext;

	return STAT_OK;
}

template<typename ElemType>
Status LinkList<ElemType>::traverse(Status(*visit)(ElemType, bool firstInvoke))
{
	LNode <ElemType> *pNode = head.next;
	bool firstInvoke = true;

	while (nullptr != pNode)
	{
		visit(pNode->data, firstInvoke);
		if (firstInvoke)
			firstInvoke = false;
		pNode = pNode->next;
	}
	return STAT_OK;
}