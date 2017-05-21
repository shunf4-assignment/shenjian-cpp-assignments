/* 1652270 计算机2班 冯舜 */
/* FRENZYQRCode_SJProject - 90-b4-myself.cpp */
#include "90-b4.h"

void xorBuff(unsigned char * buf, int length, const int normal)
{
	for (int i = 0; i < length; i++)
	{
		buf[i] ^= (normal >> (length - i - 1)) & 1;
	}
}

void generatorPoly(int n, GFPoly &resultPoly)
{
	const unsigned char initialChar[] = { 1 };
	unsigned char multiplierChar[] = { 0, 0 };
	resultPoly.clear();
	resultPoly.createPoly(initialChar, 1, false);
	GFPoly multiplier;
	for (int i = 0; i < n; i++)
	{
		multiplier.clear();
		multiplier.createPoly(multiplierChar, len(multiplierChar), true);
		resultPoly.multiply(multiplier, resultPoly);
		multiplierChar[1]++;
	}
}

void generateRSCode(const unsigned char * inputbuf, int inputbuflen, int RSCodeLength, unsigned char *outputbuf)
{
	GFPoly g;
	GFPoly m(inputbuf, inputbuflen, false);
	GFPoly f;

	generatorPoly(RSCodeLength, g);
	f.copyFrom(&m);
	f.multiply_x(RSCodeLength);
	f.modby(g, f);
	//f.print(true, false, true);
	f.outputInBuffer(outputbuf, RSCodeLength);
}

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
	simplify();
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
			printf("空\n");
		return;
	}
	printf(printExpn ? "α^%d x^%d" :"%dx^%d", printExpn ? terms->next->data.ce : gfilog[terms->next->data.ce], terms->next->data.expn);
	auto P = terms->next;
	while (P->next)
	{
		printf(printExpn ? " + α^%d x^%d" : " + %dx^%d", printExpn ? P->next->data.ce : gfilog[P->next->data.ce], P->next->data.expn);
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
/*
void GFPoly::outputInBuffer(unsigned char * const buf)
{
	unsigned char * pb = buf;
	TermP p = terms->next;
	unsigned int lastExpn = p->data.expn;
	unsigned int expn;
	while (p)
	{
		expn = p->data.expn;
		for (int zeroNum = 0; zeroNum < int(lastExpn - expn - 1); zeroNum++)
			*(pb++) = 0;
		*(pb++) = p->data.ce == INT_MAX ? 0 : gfilog[p->data.ce];
		p = p->next;
		lastExpn = expn;
	}
	for (; expn > 0; expn--)
	{
		*(pb++) = 0;
	}
}
*/
void GFPoly::outputInBuffer(unsigned char * const buf, int length)
{
	unsigned char * pb = buf;
	TermP p = terms->next;
	if (!p)
	{
		for (int i = 0; i < int(length); i++)
		{
			*(pb++) = 0;
		}
		return;
	}
	unsigned int lastExpn = p->data.expn;
	unsigned int expn;
	expn = p->data.expn;
	for (int i = 0; i < int(length - expn - 1); i++)
	{
		*(pb++) = 0;
	}
	while (p)
	{
		expn = p->data.expn;
		for (int zeroNum = 0; zeroNum < int(lastExpn - expn - 1); zeroNum++)
			*(pb++) = 0;
		*(pb++) = p->data.ce == INT_MAX ? 0 : gfilog[p->data.ce];
		p = p->next;
		lastExpn = expn;
	}
	for (; expn > 0; expn--)
	{
		*(pb++) = 0;
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
	cout << "Binary bytes: " << endl;
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
	cout << endl;
	cout << "Dec bytes: " << endl;

	for (p = space; unsigned int(p - space) < currLen / 8; p++)
	{
		tmp = *p;
		cout << (unsigned int)tmp;
		cout << ' ';
	}

	if (currBit != 0)
	{
		tmp = *p;
		cout << "(" << (unsigned int)(tmp) << ")";
	}
	cout << endl;
	if (verbose)
	{
		cout << endl;
		cout << "capacity: " << this->capacity << endl;
		cout << "currByte: " << this->currByte << endl;
		cout << "currBit: " << this->currBit << endl;
		cout << "currLen: " << this->currLen << endl;
	}
	cout << endl;


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

Blocks::Blocks(int g1n, int g1c, int g2n, int g2c) : g1n(g1n), g1c(g1c), g2n(g2n), g2c(g2c)
{
	group[0] = new(nothrow) unsigned char[g1n * g1c];
	if (group[0] == NULL)
		exit(SOVF);
	if (g2n)
	{
		group[1] = new(nothrow) unsigned char[g2n * g2c];
		if (group[1] == NULL)
			exit(SOVF);
	}
	else
	{
		group[1] = nullptr;
	}
	groupNextWrite = 0;
	codewordNextWrite = 0;
}

Blocks::Blocks(int version, int ECLevel, bool isECCBlock)
{
	if (isECCBlock)
	{
		this->Blocks::Blocks(errBlocks[version - 1][ECLevel][TABLE_GROUP1BLOCK], errBlocks[version - 1][ECLevel][TABLE_ECCPERBLOCK], errBlocks[version - 1][ECLevel][TABLE_GROUP2BLOCK], errBlocks[version - 1][ECLevel][TABLE_ECCPERBLOCK]);
	}
	else
	{
		this->Blocks::Blocks(errBlocks[version - 1][ECLevel][TABLE_GROUP1BLOCK], errBlocks[version - 1][ECLevel][TABLE_GROUP1BLOCKCW], errBlocks[version - 1][ECLevel][TABLE_GROUP2BLOCK], errBlocks[version - 1][ECLevel][TABLE_GROUP2BLOCKCW]);
	}
}

Blocks::~Blocks()
{
	if (group[0])
		delete[]group[0];
	if (group[1])
		delete[]group[1];
}

void Blocks::input(const unsigned char * buf, unsigned int n)
{
	unsigned int writeOnce = 0;
	if (groupNextWrite == 2)
		return;
	if (groupNextWrite == 0)
	{
		writeOnce = g1c * g1n - codewordNextWrite;
		writeOnce > n && (writeOnce = n);
		memcpy_s((group[0] + codewordNextWrite), (g1c * g1n - codewordNextWrite) * sizeof(unsigned char), buf, writeOnce * sizeof(unsigned char));
		n -= writeOnce;
		codewordNextWrite += writeOnce;
		if (codewordNextWrite >= g1n *g1c)
		{
			codewordNextWrite = 0;
			groupNextWrite = 1;
		}
		buf += writeOnce;
	}
	
	if (n > 0 && groupNextWrite == 1 && group[1] != nullptr)
	{
		writeOnce = n;
		memcpy_s((group[1] + codewordNextWrite), (g2c * g2n - codewordNextWrite) * sizeof(unsigned char), buf, writeOnce * sizeof(unsigned char));
		n -= writeOnce;
		codewordNextWrite += writeOnce;
		if (codewordNextWrite >= g2n * g2c)
		{
			codewordNextWrite = 0;
			groupNextWrite = 2;
		}
	}
}

void Blocks::display()
{
	unsigned char *p;
	p = group[0];
	for (unsigned int i = 0u; i < g1n; i++)
	{
		cout << "Group 1 Block " << i + 1 << "(" << g1c << ")" << endl;
		for (unsigned int j = 0u; j < g1c; j++)
		{
			cout << unsigned int(*p) << " ";
			p++;
		}
		cout << endl;
	}
	p = group[1];
	for (unsigned int i = 0u; i < g2n; i++)
	{
		cout << "Group 2 Block " << i + 1 << "(" << g2c << ")" << endl;
		for (unsigned int j = 0u; j < g2c; j++)
		{
			cout << unsigned int(*p) << " ";
			p++;
		}
		cout << endl;
	}
}

void Blocks::input(const unsigned char * buf)
{
	input(buf, g1n * g1c + g2n * g2c);
}

unsigned char * Blocks::output(unsigned char * buf) const
{
	unsigned char *p = buf;
	unsigned int maxIndex = max(g1c, g2c);
	for (unsigned int i = 0; i < maxIndex; i++)
	{
		if (i < g1c)
		{
			for (unsigned int j = 0; j < g1n; j++)
			{
				*p++ = group[0][j * g1c + i];
			}
		}
		if (i < g2c)
		{
			for (unsigned int j = 0; j < g2n; j++)
			{
				*p++ = group[1][j * g2c + i];
			}
		}
	}
	return p;
}

void Blocks::makeRSCodeTo(Blocks & rsb) const
{
	unsigned char * in = group[0];
	unsigned char * out = rsb.group[0];
	for (unsigned int i = 0; i < g1n; i++)
	{
		generateRSCode(in, g1c, rsb.g1c, out);
		in += g1c;
		out += rsb.g1c;
	}
	in = group[1];
	out = rsb.group[1];
	for (unsigned int i = 0; i < g2n; i++)
	{
		generateRSCode(in, g2c, rsb.g2c, out);
		in += g2c;
		out += rsb.g2c;
	}
}

unsigned int Blocks::length()
{
	return g1c * g1n + g2c * g2n;
}

void Pattern::init(int version_)
{
	version = version_;
	sidelen = ((version - 1) * 4) + 21;
	matrix = new(nothrow) int[sidelen * sidelen];
	if (nullptr == matrix)
		exit(SOVF);
	memset(matrix, 0, sidelen * sidelen * sizeof(int));
}

void Pattern::placeOneFinder(int y, int x)
{
	int xb = x, yb = y;
	for (int i = 0; i < 7; i++)
	{
		set(yb, xb++, 1, true);
	}
	yb++, xb = x;
	for (int i = 0; i < 7; i++)
	{
		set(yb, xb, xb - x == 0 || xb - x == 6, true);
		xb++;
	}
	yb++, xb = x;
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 7; i++)
		{
			set(yb, xb, xb - x != 1 && xb - x != 5, true);
			xb++;
		}
		yb++, xb = x;
	}
	for (int i = 0; i < 7; i++)
	{
		set(yb, xb, xb - x == 0 || xb - x == 6, true);
		xb++;
	}
	yb++, xb = x;
	for (int i = 0; i < 7; i++)
	{
		set(yb, xb++, 1, true);
	}
}

void Pattern::placeOneAlign(int y, int x)
{
	int xb = x, yb = y;
	for (int i = 0; i < 5; i++)
	{
		set(yb, xb++, 1, true);
	}
	yb++, xb = x;
	for (int i = 0; i < 5; i++)
	{
		set(yb, xb, xb - x == 0 || xb - x == 4, true);
		xb++;
	}
	yb++, xb = x;
	for (int i = 0; i < 5; i++)
	{
		set(yb, xb, !(i % 2), true);
		xb++;
	}
	yb++, xb = x;
	for (int i = 0; i < 5; i++)
	{
		set(yb, xb, xb - x == 0 || xb - x == 4, true);
		xb++;
	}
	yb++, xb = x;
	for (int i = 0; i < 5; i++)
	{
		set(yb, xb++, 1, true);
	}
}

void Pattern::makeAlign()
{
	const unsigned int *p0 = alignPlacement[version - 1];
	int testValid = 0;
	for (const unsigned int *p = p0; p - p0 < 7 && *p != 0u; p++)
	{
		for (const unsigned int *q = p0; q - p0 < 7 && *q != 0u; q++)
		{
			testValid = 0;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					testValid += get(*q + j, *p + i) & MODULE_RESERVED;
				}
			}
			if (testValid == 0)
			{
				placeOneAlign(*q -2 , *p -2 );
			}
		}
	}
}

void Pattern::makeFinderAndSeparator()
{
	int tmp;
	placeOneFinder(0, 0);
	for (int i = 0; i < 8; i++)
		set(7, i, 0, true);
	for (int i = 0; i < 8; i++)
		set(i, 7, 0, true);
	placeOneFinder(0, sidelen - 7);
	tmp = sidelen - 8;
	for (int i = 0; i < 8; i++)
		set(i, tmp, 0, true);
	for (int i = 0; i < 8; i++)
		set(7, sidelen - i - 1, 0, true);
	placeOneFinder(sidelen - 7, 0);
	for (int i = 0; i < 8; i++)
		set(tmp, i, 0, true);
	for (int i = 0; i < 8; i++)
		set(sidelen - 1 - i, 7, 0, true);
}

Pattern::Pattern(int version_)
 {
	init(version_);
	makeFinderAndSeparator();
	makeAlign();
	makeTiming();
	reserveFormat();
	if(version > 6)
		reserveVersion();
}

void Pattern::makeTiming()
{
	for (int i = 8; i < sidelen - 8; i++)
	{
		set(6, i, !(i % 2), true);
		set(i, 6, !(i % 2), true);
	}
}

Pattern::~Pattern()
{
	delete[]matrix;
}

void Pattern::print(bool color)
{
	int X, Y, currY;
	getxy(hOut, X, Y);
	currY = Y;
	for (int *p = matrix; p - matrix < sidelen * sidelen; p++)
	{
		if (*p & MODULE_SET || !color)
		{
			if (*p & MODULE_FUNCTION && color)
			{
				if (*p & MODULE_DARK)
					setcolor(hOut, QRCOLOR_FUNC1, QRCOLOR_FUNC1);
				else
					setcolor(hOut, QRCOLOR_FUNC0, QRCOLOR_FUNC0);
			}
			else
			{
				if (*p & MODULE_DARK)
					setcolor(hOut, QRCOLOR_1, QRCOLOR_0);
				else
					setcolor(hOut, QRCOLOR_0, QRCOLOR_0);
			}
			
		}
		else if(*p & MODULE_RESERVED)
			setcolor(hOut, QRCOLOR_RESERVED, QRCOLOR_RESERVED);
		else
			setcolor(hOut, QRCOLOR_ERR, QRCOLOR_ERR);
		cout << "  ";
		if ((p - matrix) % sidelen == sidelen - 1)
			gotoxy(hOut, X, ++currY);
	}
	setcolor(hOut, QRCOLOR_TEXTBG, QRCOLOR_TEXTFG);
}

void Pattern::reserveFormat()
{
	for (int i = 0; i < 9; i++)
	{
		reserve(8, i, true);
		reserve(i, 8, true);
	}
	for (int i = 0; i < 8; i++)
	{
		reserve(8, sidelen - i - 1, true);
		reserve(sidelen - i - 1, 8, true);
	}
	set(sidelen - 7 - 1, 8, 1, true);
}

void Pattern::reserveVersion()
{
	for (int i = sidelen - 11; i < sidelen - 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			reserve(i, j, true);
			reserve(j, i, true);
		}
	}
}

void Pattern::fillInCodewords(const unsigned char * buf, unsigned int buflen)
{
	int currCol = sidelen - 1;
	int currLin = sidelen - 1;
	const unsigned char *cp = buf;
	int currBit = 0;
	bool evenBit = true;
	bool evenCol = true;
	bool bitNotEnough = false;
	while (currCol >= 1)
	{
		while (true)
		{
			if ((get(currLin, currCol - !evenBit) & MODULE_RESERVED) == false)
			{
				break;
			}
			!evenBit && (evenCol ? (currLin--) : (currLin++));
			evenBit = !evenBit;
			if (currLin < 0 || currLin >= sidelen)
				break;
		}
		while (true)
		{
			if ((get(currLin, currCol - !evenBit) & MODULE_RESERVED) == false)
			{
				if (bitNotEnough)
				{
					set(currLin, currCol - !evenBit, 0, false);
				}
				else
				{
					set(currLin, currCol - !evenBit, (*cp >> (7 - currBit)) & 1, false);
					currBit++;
					if (currBit == 8)
					{
						currBit = 0, cp++;
						if (unsigned int(cp - buf) >= buflen)
						{
							bitNotEnough = true;
						}
					}
				}
			}
			else
			{

			}
			!evenBit && (evenCol ? (currLin--) : (currLin++));
			evenBit = !evenBit;
			if (currLin < 0 || currLin >= sidelen)
				break;
			
		}
		/*if (bitNotEnough)
			break;*/
		currCol--;
		if (currCol == 6)
			currCol--;
		currCol--;
		if (currCol == 6)
			currCol--;
		currLin = evenCol ? 0 : (sidelen - 1);

		evenCol = !evenCol;
		evenBit = true;
	}
}

Pattern::Pattern(const Pattern & p2)
{
	init(p2.version);
	memcpy_s(matrix, sidelen * sidelen * sizeof(int), p2.matrix, sidelen * sidelen * sizeof(int));
}

Pattern::Pattern(const Pattern & p2, int maskNum)
{
	this->Pattern::Pattern(p2);
	if(maskNum >= 0)
		mask(maskNum);
}

void Pattern::mask(int maskNum)
{
	for (int j = 0; j < sidelen; j++)
		for (int i = 0; i < sidelen; i++)
		{
			if(!isFunction(j, i))
				switch (maskNum)
				{
					case 0:
						matrix[i + j * sidelen] ^= ((j + i) % 2 == 0);
						break;
					case 1:
						matrix[i + j * sidelen] ^= ((j) % 2 == 0);
						break;
					case 2:
						matrix[i + j * sidelen] ^= ((i) % 3 == 0);
						break;
					case 3:
						matrix[i + j * sidelen] ^= ((j + i) % 3 == 0);
						break;
					case 4:
						matrix[i + j * sidelen] ^= ((j / 2 + i / 3) % 2 == 0);
						break;
					case 5:
						matrix[i + j * sidelen] ^= ((j * i) % 2 + (j * i) % 3 == 0);
						break;
					case 6:
						matrix[i + j * sidelen] ^= (((j * i) % 2 + (j * i) % 3) % 2 == 0);
						break;
					case 7:
						matrix[i + j * sidelen] ^= (((j + i) % 2 + (j * i) % 3) % 2 == 0);
						break;
					default:
						return;
				}
		}
}

unsigned int Pattern::calcPenalty()
{
	unsigned score = 0;
	score += evalConsec();
	score += evalSimiBlock();
	score += evalFinderLike();
	score += evalRatio();
	return score;
}

unsigned int Pattern::evalConsec()
{
	int lastSec = -1;
	int currSec = -1;
	int repeat = 0;
	unsigned score = 0;
	for (int j = 0; j < sidelen; j++)
	{
		for (int i = 0; i < sidelen; i++)
		{
			currSec = get(j, i);
			if (currSec == lastSec)
			{
				repeat++;
			}
			else
			{
				repeat = 1;
			}
			if (repeat > 5)
				score++;
			else if (repeat == 5)
				score += 3;
			lastSec = currSec;
		}
		repeat = 1;
		lastSec = -1;
	}
	for (int i = 0; i < sidelen; i++)
	{
		for (int j = 0; j < sidelen; j++)
		{
			currSec = get(j, i) & 1;
			if (currSec == lastSec)
			{
				repeat++;
			}
			else
			{
				repeat = 1;
			}
			if (repeat > 5)
				score++;
			else if (repeat == 5)
				score += 3;
			lastSec = currSec;
		}
		repeat = 1;
		lastSec = -1;
	}
	return score;
}

unsigned int Pattern::evalSimiBlock()
{
	int currSec = -1;
	unsigned score = 0;
	for (int j = 0; j < sidelen - 1; j++)
	{
		for (int i = 0; i < sidelen - 1; i++)
		{
			currSec = (get(j, i) & 1) + (get(j + 1, i) & 1) + (get(j, i + 1) & 1) + (get(j + 1, i + 1) & 1);
			if (currSec == 4 || currSec == 0)
				score += 3;
		}
	}
	return score;
}

unsigned int Pattern::evalFinderLike()
{
	int currSec = -1;
	unsigned score = 0;
	for (int j = 0; j < sidelen; j++)
	{
		for (int i = 0; i < sidelen - 10; i++)
		{
			currSec = 0;
			for (int k = 0; k < 11; k++)
			{
				currSec |= (get(j, i + k) & 1);
				currSec <<= 1;
			}
			if (currSec == 93 || currSec == 1488)
				score += 40;
		}
	}
	for (int j = 0; j < sidelen - 10; j++)
	{
		for (int i = 0; i < sidelen; i++)
		{
			currSec = 0;
			for (int k = 0; k < 11; k++)
			{
				currSec |= (get(j + k, i) & 1);
				currSec <<= 1;
			}
			if (currSec == 93 || currSec == 1488)
				score += 40;
		}
	}
	return score;
	return 0;
}

unsigned int Pattern::evalRatio()
{
	int totalNum = sidelen *sidelen;
	int darkNum = 0;
	for (int j = 0; j < sidelen; j++)
	{
		for (int i = 0; i < sidelen; i++)
		{
			darkNum += (get(j, i) & 1);
		}
	}
	int ratio = darkNum * 100 / totalNum;
	int diff1, diff2;
	ratio = ratio / 5 * 5;
	diff1 = abs(ratio - 50) / 5;
	diff2 = abs(ratio + 5 - 50) / 5;
	return min(diff1, diff2) * 10;
}

int Pattern::chooseBestSaveIn(Pattern & source, bool debug)
{
	Pattern maskedPats[8] = { {*this, 0},{ *this, 1 },{ *this, 2},{ *this, 3},{ *this, 4},{ *this, 5},{ *this, 6},{ *this, 7} };
	unsigned int minIndex = UINT_MAX;
	unsigned int minScore = UINT_MAX;
	unsigned int score;
	source.~Pattern();
	if (debug)
	{
		cout << "各掩模的惩罚分数如下："<< endl;
	}
	for (int i = 0; i < 8; i++)
	{
		score = maskedPats[i].calcPenalty();
		if (debug)
		{
			cout << i << ": " << score << endl;
		}
		if (score < minScore)
		{
			minIndex = i;
			minScore = score;
		}
	}
	if (minScore == UINT_MAX)
	{
		source.init(1);
		return -1;
	}
	source.Pattern::Pattern(maskedPats[minIndex]);
	return minIndex;
}

void Pattern::formatStr(int errCorrLevel, int maskPat, bool debug)
{
	int fiveBit;
	const unsigned char formatGen[] = { 1,0,1,0,0,1,1,0,1,1,1 };
	unsigned char formatBits[5], resultRSCode[15];
	fiveBit = ((errLevelEquivalent[errCorrLevel] & 3) << 3) | (maskPat & 7);

	if (debug)
	{
		cout << "Format 格式字符串的原数据：";
	}
	for (int i = 0; i < 5; i++)
	{
		formatBits[i] = (fiveBit >> (4 - i)) & 1;
		if (debug)
			cout << int(formatBits[i]);
	}
	GFPoly formatBitPoly(formatBits, 5, false);
	formatBitPoly.multiply_x(10);
	GFPoly formatGenPoly(formatGen, len(formatGen), false);

	if (debug)
	{
		cout << endl << "生成了原数据和纠错码生成码对应的两个多项式：" << endl;
		cout << "原数据多项式：" << endl;
		formatBitPoly.print(true, false, true);
		cout << "纠错码多项式：" << endl;
		formatGenPoly.print(true, false, true);
	}
	formatBitPoly.modby(formatGenPoly, formatBitPoly);
	if (debug)
	{
		cout << endl << "两个多项式取模成功。" << endl;
		cout << "取模后多项式：" << endl;
		formatBitPoly.print(true, false, true);
	}
	memcpy_s(resultRSCode, sizeof(unsigned char) * 15, formatBits, sizeof(unsigned char) * 5);
	formatBitPoly.outputInBuffer(resultRSCode + 5, 10);

	if (debug)
	{
		cout << endl << "最终的格式信息（15 个 bit）：" << endl;
		for (int i = 0; i < 15; i++)
		{
			cout << int(resultRSCode[i]);
		}
		cout << endl;
	}

	xorBuff(resultRSCode, 15, 21522);

	if (debug)
	{
		cout << "101010000010010（21522） XOR 后 格式信息（ 15 个字节）：" << endl;
		for (int i = 0; i < 15; i++)
		{
			cout << int(resultRSCode[i]);
		}
		cout << endl;
	}

	for (int i = 0; i < 6; i++)
	{
		set(i, 8, resultRSCode[14 - i], true);
	}
	set(7, 8, resultRSCode[8], true);
	set(8, 8, resultRSCode[7], true);
	set(8, 7, resultRSCode[6], true);
	for (int i = 9; i < 15; i++)
	{
		set(8, 14 - i, resultRSCode[14 - i], true);
	}
	for (int i = 0; i < 8; i++)
	{
		set(8, sidelen - 1 - i, resultRSCode[14 - i], true);
	}
	for (int i = 8; i < 15; i++)
	{
		set(sidelen - 1 - (14 - i), 8, resultRSCode[14 - i], true);
	}

	if (debug)
	{
		cout << "按照格式填入了 二维码 Pattern 的 Format 区域。" << endl;
	}
}

void Pattern::versionStr(bool debug)
{
	if (version < 7)
	{
		if (debug)
		{
			cout << "版本小于 7，不生成 version string。" << endl;
		}
		return;
	}
	const unsigned char versionGen[] = { 1,1,1,1,1,0,0,1,0,0,1,0,1};
	unsigned char versionBits[6], resultRSCode[18];
	if (debug)
	{
		cout << "Version 格式字符串的原数据：";
	}
	for (int i = 0; i < 6; i++)
	{
		versionBits[i] = (version >> (5 - i)) & 1;
		if (debug)
			cout << int(versionBits[i]);
	}
	GFPoly versionBitPoly(versionBits, 6, false);
	versionBitPoly.multiply_x(12);
	GFPoly versionGenPoly(versionGen, len(versionGen), false);

	if (debug)
	{
		cout << endl << "生成了原数据和纠错码生成码对应的两个多项式：" << endl;
		cout << "原数据多项式：" << endl;
		versionBitPoly.print(true, false, true);
		cout << "纠错码多项式：" << endl;
		versionGenPoly.print(true, false, true);
	}

	versionBitPoly.modby(versionGenPoly, versionBitPoly);
	if (debug)
	{
		cout << endl << "两个多项式取模成功。" << endl;
		cout << "取模后多项式：" << endl;
		versionBitPoly.print(true, false, true);
	}
	memcpy_s(resultRSCode, sizeof(unsigned char) * 18, versionBits, sizeof(unsigned char) * 6);
	versionBitPoly.outputInBuffer(resultRSCode + 6, 12);

	if (debug)
	{
		cout << endl << "最终的格式信息（18 个 bit）：" << endl;
		for (int i = 0; i < 18; i++)
		{
			cout << int(resultRSCode[i]);
		}
		cout << endl;
	}

	for (int i = sidelen - 11; i < sidelen - 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			set(j, i, resultRSCode[17 - (3 * j + i - sidelen + 11)], true);
			set(i, j, resultRSCode[17 - (3 * j + i - sidelen + 11)], true);
		}
	}
	if (debug)
	{
		cout << "按照格式填入了 二维码 Pattern 的 Version 区域。" << endl;
	}
}

unsigned validCharNum(const unsigned char *str, int mode, bool UTF8, bool debug)
{
	unsigned count = 0;
	unsigned mappedNum;
	if(mode == MODE_ALPHA)
		for (const unsigned char *p = str; *p; p++)
		{
			mappedNum = 0;
			if (*p < 'z')
				mappedNum = alphanumericMap[*p];
			else
				continue;
			if (mappedNum)
				count++;
		}
	if(mode == MODE_NUM)
		for (const unsigned char *p = str; *p; p++)
		{
			if (*p >= '0' && *p <= '9')
				count++;
		}
	if (mode == MODE_BYTE)
	{
		count = strlen((const char *)(str)) + (UTF8 ? 3: 0);
	}
		
	return count;
}

void writeInValidChar(Bits &b, const unsigned char *str, int mode, bool UTF8, bool debug)
{
	if (mode == MODE_ALPHA)
	{
		unsigned mappedNum, lastMapped;
		unsigned numToInsert;
		bool even = 0;
		for (const unsigned char *p = str; *p; p++)
		{
			mappedNum = 0;
			if (*p < 'z')
				mappedNum = alphanumericMap[*p];
			else
				continue;
			if (mappedNum)
			{
				if (even)
				{
					numToInsert = lastMapped * 45 + mappedNum;
					b.writeInBytes(&numToInsert, 11, 1);
				}
				even = !even;
				lastMapped = mappedNum;
			}
		}
		if (even)
		{//if left a single letter/digit
			b.writeInBytes(&mappedNum, 6, 1);
		}
	}

	if (mode == MODE_NUM)
	{
		int mod3 = 0;
		unsigned threebitgroup = 0;
		for (const unsigned char *p = str; *p; p++)
		{
			if (*p >= '0' && *p <= '9')
			{
				threebitgroup = threebitgroup * 10 + *p - '0';
			}
			mod3++;
			if (mod3 % 3 == 0)
			{
				mod3 = 0;
				b.writeInBytes(&threebitgroup, 10, 1);
				threebitgroup = 0;
			}
		}
		if (mod3 == 1)
		{
			b.writeInBytes(&threebitgroup, 4, 1);
		}
		if (mod3 == 2)
		{
			b.writeInBytes(&threebitgroup, 7, 1);
		}
	}
		
	if (mode == MODE_BYTE)
	{
		unsigned int currChar;
		if (UTF8)
		{
			//write BOM
			const unsigned int BOM[] = { 0xEF, 0xBB, 0xBF };
			b.writeInBytes(BOM, 8, 3);
		}
		for (const unsigned char *p = str; *p; p++)
		{
			currChar = *p;
			b.writeInBytes(&currChar, 8, 1);
		}
	}
}

void fillUpBits(Bits &b, unsigned codewordlen, bool debug)
{
	unsigned empty;
	unsigned zero = 0;
	unsigned remain, bytesToBeFilled;
	empty = codewordlen * 8 - b.getBitLen();
	if (empty >= 4)
	{
		b.writeInBytes(&zero, 4, 1);
	}
	else
	{
		b.writeInBytes(&zero, empty, 1);
	}

	if (remain = b.getBitRemainder())
	{
		b.writeInBytes(&zero, 8 - remain, 1);
	}
	bytesToBeFilled = codewordlen - b.getByteLen();
	for (unsigned i = 0; i < bytesToBeFilled; i++)
	{
		b.writeInBytes(padBytes + i % 2, 8, 1);	//fill in padbytes
	}
}

void drawPadding(int paddingWidth, unsigned int sidelen, bool debug)
{
	int tmpX, tmpY;
	gotoxy(hOut, 0, 0);
	setcolor(hOut, QRCOLOR_PADDING, QRCOLOR_PADDING);
	for (int i = 0; i < paddingWidth; i++)
	{
		cout << setw((sidelen + paddingWidth * 2) * 2) << "";
		cout << endl;
	}
	getxy(hOut, tmpX, tmpY);
	for (unsigned i = 0; i < sidelen; i++)
	{
		cout << setw(paddingWidth * 2) << "";
		gotoxy(hOut, (paddingWidth + sidelen) * 2, tmpY + i);
		cout << setw(paddingWidth * 2) << "";
		cout << endl;
	}
	for (int i = 0; i < paddingWidth; i++)
	{
		cout << setw((sidelen + paddingWidth * 2) * 2) << "";
		cout << endl;
	}
}

void QRCode::printQR()
{
	const static char ecletter[] = "LMQH";
	Bits bitsbuf;
	
	unsigned int codewordlen = errBlocks[version - 1][errLevel][TABLE_TOTALCODEWORD];
	unsigned int rslen = errBlocks[version - 1][errLevel][TABLE_ECCPERBLOCK];
	bool even = 0;
	unsigned int tmp;
	unsigned dataLen, lenOfAllCW;
	unsigned char * allCW, *cwP;
	int maskPat;
	int fontSize;
	if (debug)
	{
		cout << "开始转换，QR 版本 " << version << "，纠错等级 " << ecletter[errLevel] << "，码元应该有 " << codewordlen << " 个字节，每块的纠错码应该有 " << rslen << " 个字节。" << endl << "要编码的数据全文：" << endl;
		cout << dataBuf << endl;
	}
		
	bitsbuf.writeInBytes(&(modeIndicator[mode]), 4, 1);
	if (debug)
	{
		cout << "写入了 modeIndicator " << modeIndicator[mode] << endl;
		bitsbuf.print(false);
	}
	dataLen = validCharNum(dataBuf, mode, UTF8, debug);
	if (debug)
	{
		cout << "由于可能存在不能表达的字符，实际的数据长度 " << dataLen << "，原数据长度 " << strlen((const char *)dataBuf) << endl;
	}
	bitsbuf.writeInBytes(&dataLen, (countIndicator[version - 1][mode]), 1);
	if (debug)
	{
		cout << "以 " << (countIndicator[version - 1][mode]) << " bits 长度输入了实际数据长度。" << endl;
		bitsbuf.print(false);
	}
	writeInValidChar(bitsbuf, dataBuf, mode, UTF8,debug);
	if (debug)
	{
		cout << "写入了数据码元。" << endl;
		bitsbuf.print(false);
	}
	fillUpBits(bitsbuf, codewordlen,debug);
	if (debug)
	{
		cout << "填充了数据码元。" << endl;
		bitsbuf.print(false);
		cout << "现在数据码元长度为 " << bitsbuf.getByteLen() << "。" << endl;
	}

	Blocks codewordBlock(version, errLevel, false);
	codewordBlock.input(bitsbuf.getCharBuf());
	if (debug)
	{
		cout << "创建数据组和数据块成功。" << endl;
		cout << "现在各块中的内容：" << endl;
		codewordBlock.display();
		cout << endl;
	}
	Blocks eccBlock(version, errLevel, true);
	codewordBlock.makeRSCodeTo(eccBlock);
	if (debug)
	{
		cout << "各个组块的纠错码创建成功。" << endl;
		cout << "现在各块中的纠错码：" << endl;
		eccBlock.display();
		cout << endl;
	}
	

	lenOfAllCW = codewordlen + eccBlock.length();
	if (debug)
	{
		cout << "现在开始整合数据码元和纠错码。总长度：" << lenOfAllCW << " = " << codewordBlock.length() + eccBlock.length() << " = " << codewordlen + rslen * (errBlocks[version - 1][errLevel][TABLE_GROUP1BLOCK] + errBlocks[version - 1][errLevel][TABLE_GROUP2BLOCK]) << endl;
	}
	allCW = new(nothrow) unsigned char[lenOfAllCW];
	if (allCW == nullptr)
	{
		exit(SOVF);
	}
	cwP = allCW;
	cwP = codewordBlock.output(cwP);
	eccBlock.output(cwP);
	if (debug)
	{
		cout << "整合成功。最终整合后的字节流如下：" << endl;
		for (unsigned char *p = allCW; unsigned(p - allCW) < lenOfAllCW; p++)
		{
			cout << int(*p) << " ";
		}
		cout << endl;
	}
	
	Pattern pat(version);
	pat.fillInCodewords(allCW, lenOfAllCW);
	Pattern pat2(1);
	maskPat = pat.chooseBestSaveIn(pat2, debug);

	if (debug)
	{
		cout << "选用了掩码编号：" << maskPat << endl;
	}

	pat2.formatStr(errLevel, maskPat, debug);
	pat2.versionStr(debug);

	cout << "生成完毕，按任意键显示二维码，再按一次任意键退出。";
	system("pause>nul");

	if (version < 3)
		fontSize = 16;
	else if (version >= 3 && version < 16)
		fontSize = 8;
	else if (version >= 16 && version < 27)
		fontSize = 5;
	else
		fontSize = 1;
	tmp = pat2.getSidelen();

	setfontsize(hOut, L"新宋体", fontSize);
	system("cls");
	setconsoleborder(hOut, (tmp + paddingWidth * 2 + 10) * 2, tmp + paddingWidth * 2 + 10);

	drawPadding(paddingWidth, tmp, debug);
	gotoxy(hOut, paddingWidth * 2, paddingWidth);

	pat2.print();
	gotoxy(hOut,  0, (paddingWidth * 2 + tmp));

	delete[]allCW;
	return;
}