/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#pragma once
#include <iostream>
#include <cmath>
using namespace std;

#define SOK 0
#define SERR 1
#define SOVF -2  //Overflow
#define BEXT 1 //Bytes Length Extending
#define ERRLVL_L 0
#define ERRLVL_M 1
#define ERRLVL_Q 2
#define ERRLVL_H 3
#define MODE_NUM 0
#define MODE_ALPHA 1
#define MODE_BYTE 2
#define MODE_KANJI 3
#define TABLE_TOTALCODEWORD 0
#define TABLE_ECCPERBLOCK 1
#define TABLE_GROUP1BLOCK 2
#define TABLE_GROUP1BLOCKCW 3
#define TABLE_GROUP2BLOCK 4
#define TABLE_GROUP2BLOCKCW 5



extern const int gflog[];
extern const int gfilog[];
extern const unsigned int alphanumericMap[];
extern const unsigned int capabilityTable[40][4][4];
extern const unsigned int modeIndicator[];
extern const unsigned int countIndicator[40][4];
extern const unsigned int errBlocks[40][4][6];
extern const unsigned int padBytes[];

class GFPoly
{
private:
	typedef struct
	{
		unsigned ce;	//the exponent of the coefficient of this term, like 2^7 -> 7
		int expn;
	} Term2, TermData;	//Term in GF(2^8) expressed in 2^ce * x ^ expn (generator 2)

	struct TermPrototype
	{
		Term2 data;
		struct TermPrototype *next;
	};
	typedef struct TermPrototype Term, *TermP;
	void init();
	void dividedbyImplementor(GFPoly & divisor, GFPoly * quotientContainer, GFPoly * remainderContainer);

	TermP terms;
	TermP termstail;
public:
	GFPoly();
	//GFPoly(const GFPoly& origin);
	void copyFrom(GFPoly * const origin);
	GFPoly(const unsigned char * codewords, int cwlen, bool isOriginAlphaMode);
	void createPoly(const unsigned char * codewords, int cwlen, bool isOriginAlphaMode);
	~GFPoly();
	void sequentialInsert(unsigned char cw, int expn, bool);
	void sequentialInsert(TermData t);
	void clear();
	void multiply_x(int);	//multiply x^n
	void addAndClear(GFPoly &B);
	void dividedby(GFPoly &divisor, GFPoly &quotientContainer, GFPoly &remainderContainer);
	void dividedby(GFPoly &divisor, GFPoly &quotientContainer);
	void modby(GFPoly &divisor, GFPoly &remainderContainer);
	void outputInBuffer(unsigned char * buf);
	void multiply(GFPoly &B, GFPoly &result);
	void multiply(TermData, GFPoly &result);
	void multiply(int ce, GFPoly & r);
	void simplify();
	void print(bool printEmpty, bool printExpn, bool newline = true);
};

class Bits
{
private:
	unsigned char * space;
	unsigned int currByte;
	unsigned int currBit;
	unsigned int currLen;
	unsigned int capacity;
	static unsigned int createMask(int blockLen, int maskLen);
	void expandForMoreUnits(unsigned int unit);
public:
	Bits();
	Bits(int length);
	~Bits();
	void writeInBytes(const unsigned int * buf, unsigned int lenOfBlock, unsigned int len);
	//void writeInChar(const char * buf);
	//void writeInChar(const char * buf, int len);
	void print(bool verbose = true) const;
	unsigned int getBitLen();
	unsigned int getBitRemainder();
	unsigned int getByteLen();
	const unsigned char * getCharBuf();
};

class Blocks
{
private:
	unsigned char * block[2];
public:
	Blocks(int g1n, int g1c, int g2n, int g2c);
	Blocks(int version, int ECLevel, bool isECCBlock);
	~Blocks();
	void input(const unsigned char * buf);
	void input(const unsigned char * buf, unsigned int n);

};