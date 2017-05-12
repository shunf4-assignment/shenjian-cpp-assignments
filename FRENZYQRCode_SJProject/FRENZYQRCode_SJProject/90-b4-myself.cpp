/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include "90-b4.h"

void GFPoly::init()
{
	terms = new(nothrow) Term;  //head
	if (terms == NULL)
		exit(SOVF);
	terms->next = NULL;
	termstail = terms;
}

GFPoly::GFPoly()
{
	this->init();
}

GFPoly::GFPoly(const unsigned char * codewords, int cwlen, bool isOriginAlphaMode)
{
	this->init();
	createPoly(codewords, cwlen, isOriginAlphaMode);
}

void GFPoly::createPoly(const unsigned char * codewords, int cwlen, bool isOriginAlphaMode)
{
	for (int i = 0, e = cwlen - 1; i < cwlen; i++, e--)
	{
		sequentialInsert(codewords[i], e, isOriginAlphaMode);
	}
}

void GFPoly::clear()
{
	TermP q, p;
	p = terms->next;

	while (p)
	{
		q = p->next;
		delete p;
		p = q;
	}

	terms->next = NULL;
	termstail = terms;
}

GFPoly::~GFPoly()
{
	clear();
	delete terms;
}

void GFPoly::sequentialInsert(unsigned char rawCoef, int expn, bool isCoefAlphaMode)
{
	TermP newTerm = new(nothrow) Term;
	if (!newTerm)
		exit(SOVF);
	newTerm->data.ce = isCoefAlphaMode ? rawCoef : gflog[rawCoef];
	newTerm->data.expn = expn;
	newTerm->next = NULL;
	termstail->next = newTerm;
	termstail = newTerm;
}

void GFPoly::sequentialInsert(TermData t)
{
	TermP newTerm = new(nothrow) Term;
	if (!newTerm)
		exit(SOVF);
	memcpy_s(&(newTerm->data), sizeof(TermData), &t, sizeof(TermData));
	newTerm->next = NULL;
	termstail->next = newTerm;
	termstail = newTerm;
}

void GFPoly::multiply_x(int n)
{
	TermP p = terms->next;
	while (p)
	{
		p->data.expn += n;
		p = p->next;
	}
}

void GFPoly::simplify()
{
	if (terms->next == NULL)
		return;
	TermP currTermFixedPrev = terms;
	TermP currTermMovablePrev = currTermFixedPrev->next, tmpTerm;
	while (currTermMovablePrev->next)
	{

		if (currTermMovablePrev->next->data.expn != currTermFixedPrev->next->data.expn)
		{
			currTermFixedPrev = currTermMovablePrev;
			currTermMovablePrev = currTermMovablePrev->next;
		}
		else
		{
			currTermFixedPrev->next->data.ce = gflog[gfilog[currTermFixedPrev->next->data.ce] ^ gfilog[currTermMovablePrev->next->data.ce]];
			tmpTerm = currTermMovablePrev->next;
			currTermMovablePrev->next = currTermMovablePrev->next->next;
			delete(tmpTerm);
		}
	}

	currTermMovablePrev = terms;
	while (currTermMovablePrev->next)
	{
		if (currTermMovablePrev->next->data.ce == INT_MAX)
		{
			tmpTerm = currTermMovablePrev->next;
			currTermMovablePrev->next = tmpTerm->next;
			delete(tmpTerm);
		}
		else
			currTermMovablePrev = currTermMovablePrev->next;
	}

	termstail = currTermMovablePrev;
}

void GFPoly::addAndClear(GFPoly &B)
{
	TermP currPrev = terms;
	TermP ac = terms->next, bc = B.terms->next;
	while (ac && bc)
	{
		if (ac->data.expn > bc->data.expn)
		{
			currPrev->next = ac;
			currPrev = ac;
			ac = ac->next;
		}
		else
		{
			currPrev->next = bc;
			currPrev = bc;
			bc = bc->next;
		}
	}
	if (ac)
	{
		currPrev->next = ac;
	}
	else
	{
		currPrev->next = bc;
		termstail = B.termstail;
	}
	simplify();
	B.terms->next = NULL;
}

void GFPoly::multiply(GFPoly &B, GFPoly &resultPoly)
{
	GFPoly tmpPoly;
	GFPoly A_;
	GFPoly B_;
	A_.copyFrom(this);
	B_.copyFrom(&B);
	TermP p = B_.terms->next;

	resultPoly.clear();

	while (p)
	{
		A_.multiply(p->data, tmpPoly);
		resultPoly.addAndClear(tmpPoly);
		p = p->next;
	}
}

void GFPoly::multiply(TermData t, GFPoly &r)
{
	if(&r != this)
		r.copyFrom(this);

	TermP p = r.terms->next;
	while (p)
	{
		p->data.ce += t.ce;
		p->data.ce %= 255;
		p->data.expn += t.expn;
		p = p->next;
	}
}

void GFPoly::multiply(int ce, GFPoly &r)
{
	if (&r != this)
		r.copyFrom(this);

	TermP p = r.terms->next;
	while (p)
	{
		p->data.ce += ce;
		p->data.ce %= 255;
		p = p->next;
	}
}

//inline GFPoly::GFPoly(const GFPoly & origin)
//{
//	this->init();
//	TermP p = origin.terms->next;
//	while (p)
//	{
//		sequentialInsert(p->data);
//		p = p->next;
//	}
//}

void GFPoly::copyFrom(GFPoly * const origin)
{
	clear();
	TermP p = origin->terms->next;
	while (p)
	{
		sequentialInsert(p->data);
		p = p->next;
	}
}

void GFPoly::print(bool printEmpty, bool printExpn, bool newline)
{
	if (terms->next == NULL)
	{
		if (printEmpty)
			printf("¿Õ\n");
		return;
	}
	printf(printExpn ? "¦Á^%d x^%d" :"%dx^%d", printExpn ? terms->next->data.ce : gfilog[terms->next->data.ce], terms->next->data.expn);
	auto P = terms->next;
	while (P->next)
	{
		printf(printExpn ? " + ¦Á^%d x^%d" : " + %dx^%d", printExpn ? P->next->data.ce : gfilog[P->next->data.ce], P->next->data.expn);
		P = P->next;
	}
	if (newline)
		cout << endl;
}

void GFPoly::dividedbyImplementor(GFPoly &divisor, GFPoly *quotientContainerP, GFPoly *remainderContainerP)
{
	int diffExpn, diffCoefE;
	GFPoly tmpRemainder, tmpQuotient, tmpDivisorMulti;
	TermData tmpTerm;
	if (!remainderContainerP)
	{
		remainderContainerP = &tmpRemainder;
	}
	if (!quotientContainerP)
	{
		quotientContainerP = &tmpQuotient;
	}
	if (remainderContainerP != this)
		remainderContainerP->copyFrom(this);
	if (divisor.terms->next == NULL)
		return;
	while (remainderContainerP->terms->next)
	{
		diffExpn = remainderContainerP->terms->next->data.expn - divisor.terms->next->data.expn;
		diffCoefE = remainderContainerP->terms->next->data.ce - divisor.terms->next->data.ce;
		if (diffExpn < 0)
			break;
		tmpDivisorMulti.copyFrom(&divisor);
		//cout << "Divisor "; tmpDivisorMulti.print(true, false, false);
		
		tmpTerm.ce = diffCoefE;
		tmpTerm.expn = diffExpn;
		//cout << " * " << gfilog[tmpTerm.ce] << "x^" << tmpTerm.expn << endl;
		tmpDivisorMulti.multiply(tmpTerm, tmpDivisorMulti);
		remainderContainerP->addAndClear(tmpDivisorMulti);
		//cout << "Remainder : ";
		//remainderContainerP->print(true, false, true);
	}
	
}

void GFPoly::dividedby(GFPoly &divisor, GFPoly &quotientContainer, GFPoly &remainderContainer)
{
	dividedbyImplementor(divisor, &quotientContainer, &remainderContainer);
}

void GFPoly::dividedby(GFPoly &divisor, GFPoly &quotientContainer)
{
	dividedbyImplementor(divisor, &quotientContainer, NULL);
}

void GFPoly::modby(GFPoly &divisor, GFPoly &remainderContainer)
{
	dividedbyImplementor(divisor, NULL, &remainderContainer);
}

void GFPoly::outputInBuffer(unsigned char * const buf)
{
	unsigned char * pb = buf;
	TermP p = terms->next;
	while (p)
	{
		*(pb++) = gfilog[p->data.ce];
		p = p->next;
	}
}

Bits::Bits()
{
	space = (unsigned char *)malloc(sizeof(unsigned char) * BEXT);
	if (space == NULL)
		exit(SOVF);
	currByte = 0;
	space[currByte] = 0;
	currBit = 0;
	currLen = 0;
	capacity = BEXT * 8;
}

Bits::Bits(int length)
{
	space = (unsigned char *)malloc(sizeof(unsigned char) * length);
	if (space == NULL)
		exit(SOVF);
	currByte = 0;
	space[currByte] = 0;
	currBit = 0;
	currLen = 0;
	capacity = length * 8;
}

Bits::~Bits()
{
	free(space);
}

unsigned int Bits::createMask(int blockLen, int maskLen)
{
	unsigned int mask = 0;
	for (int i = 0; i < maskLen; i++)
	{
		mask |= 1 << (blockLen - i - 1);
	}
	return mask;
}

void Bits::expandForMoreUnits(unsigned int unit)
{
	space = (unsigned char *)realloc(space, capacity / 8 + unit * BEXT);
	if (space == NULL)
		exit(SOVF);
	capacity += unit * BEXT * 8;
	if (this->currBit == 0)
		space[currByte] = 0;
}

void Bits::writeInBytes(const unsigned int * buf, unsigned int lenOfBlock, unsigned int len)
{
	
	if (capacity - currLen < lenOfBlock * len)
	{
		int extNeeded = ((lenOfBlock * len - (capacity - currLen)) / 8 + !!((lenOfBlock * len - (capacity - currLen)) % 8));
		extNeeded = extNeeded / BEXT + !!(extNeeded % BEXT);
		expandForMoreUnits(extNeeded);
	}


	const unsigned int * srcByte = buf;
	int srcBit = 0;
	int thisBit;
	
	while (true)
	{
		thisBit = (*srcByte >> (lenOfBlock - srcBit - 1)) & 1;
		//cout << thisBit << endl;
		//getchar();

		space[currByte] |= thisBit << (8 - currBit - 1);
		//print(false);
		//cout << endl;
		currLen++;
		currBit++;
		if (currBit == 8)
		{
			currBit = 0;
			currByte++;
			if(currLen < capacity)
				space[currByte] = 0;
		}
		
		srcBit += 1;
		if (srcBit == lenOfBlock)
		{
			srcBit = 0;
			srcByte++;
			if (unsigned int(srcByte - buf) >= len)
				break;
		}
	}
}

void Bits::print(bool verbose) const
{
	unsigned char tmp, mask;
	const unsigned char * p;
	for (p = space; unsigned int(p - space) < currLen / 8; p++)
	{
		tmp = *p;
		mask = 1u << 7;
		for (int i = 0; i < 8; i++)
		{
			cout << (mask & tmp ? '1' : '0');
			mask >>= 1;
		}
		cout << ' ';
	}
	if (currBit != 0)
	{
		tmp = *p;
		mask = 1u << 7;
		for (unsigned int i = 0; i < currBit; i++)
		{
			cout << (mask & tmp ? '1' : '0');
			mask >>= 1;
		}
		cout << ' ';
	}
	if (verbose)
	{
		cout << endl;
		cout << "capacity: " << this->capacity << endl;
		cout << "currByte: " << this->currByte << endl;
		cout << "currBit: " << this->currBit << endl;
		cout << "currLen: " << this->currLen << endl;
	}
	

}

unsigned int Bits::getBitLen()
{
	return currBit + currByte * 8;
}
unsigned int Bits::getBitRemainder()
{
	return currBit;
}
unsigned int Bits::getByteLen()
{
	return currByte;
}
const unsigned char * Bits::getCharBuf()
{
	return space;
}

Blocks::Blocks(int g1n, int g1c, int g2n, int g2c)
{
	block[0] = new(nothrow) unsigned char[g1n * g1c];
	if (block[0] == NULL)
		exit(SOVF);
	if (g2n)
	{
		block[1] = new(nothrow) unsigned char[g2n * g2c];
		if (block[1] == NULL)
			exit(SOVF);
	}
	else
	{
		block[1] == NULL;
	}
}