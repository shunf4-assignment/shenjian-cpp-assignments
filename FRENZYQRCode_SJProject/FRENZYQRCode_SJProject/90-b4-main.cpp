/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include "90-b4.h"

template <typename T>
int len(T &tgt)
{
	return sizeof(tgt) / sizeof(tgt[0]);
}

void generatorPoly(int n, GFPoly &resultPoly)
{
	unsigned char initialChar[] = { 1 };
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
	f.outputInBuffer(outputbuf);
}


int testRSCode()
{
	unsigned char message[] = { 32,91,11,120,209,114,220,77,67,64,236,17,236,17,236,17 };
	const int rslen = 10;
	unsigned char rscode[rslen + 1] = "";
	generateRSCode(message, len(message), rslen, rscode);

	for (unsigned char *p = rscode; p - rscode < rslen; p++)
	{
		cout  << int(*p) << " ";
	}
	return 0;
}


int maintest()
{
	Bits x;
	int version = 1;
	int errLevel = ERRLVL_M;
	int mode = MODE_ALPHA;
	char *str = "HELLO WORLD";
	unsigned int mappedNum, lastMapped;
	unsigned int numToInsert;
	unsigned int len;
	unsigned int codewordlen = errBlocks[version - 1][errLevel][TABLE_TOTALCODEWORD];
	unsigned int rslen = errBlocks[version - 1][errLevel][TABLE_ECCPERBLOCK];
	bool even = 0;
	unsigned int tmp;
	x.writeInBytes(&(modeIndicator[mode]), 4, 1);
	x.print();
	len = strlen(str);
	x.writeInBytes(&len, (countIndicator[version - 1][mode]), 1);
	x.print();
	for (char *p = str; *p; p++)
	{
		mappedNum = 0;
		if(*p <= 'z')
			mappedNum = alphanumericMap[*p];
		if (mappedNum)
		{
			if (even)
			{
				numToInsert = lastMapped * 45 + mappedNum;
				x.writeInBytes(&numToInsert, 11, 1);
			}
			even = !even;
			lastMapped = mappedNum;
		}
	}
	if (even)
	{
		x.writeInBytes(&mappedNum, 6, 1);
	}
	tmp = codewordlen * 8 - x.getBitLen();
	numToInsert = 0;
	if (tmp >= 4)
	{
		x.writeInBytes(&numToInsert, 4, 1);
	}
	else
	{
		x.writeInBytes(&numToInsert, tmp, 1);
	}

	if (x.getBitRemainder())
	{
		x.writeInBytes(&numToInsert, 8 - x.getBitRemainder(), 1);
	}

	tmp = codewordlen - x.getByteLen();
	for (unsigned int i = 0; i < tmp; i++)
	{
		x.writeInBytes(padBytes + i % 2, 8, 1);
	}
	x.print();

	unsigned char * rscode = new(nothrow) unsigned char[codewordlen];

	generateRSCode(x.getCharBuf(), codewordlen, rslen, rscode);

	for (unsigned char *p = rscode; unsigned(p - rscode) < rslen; p++)
	{
		cout << int(*p) << " ";
	}
	return 0;
}

int main()
{
	//cout << alphanumericMap['z'];
	maintest();
	return 0;
}