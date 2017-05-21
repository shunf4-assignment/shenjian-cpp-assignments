/* 1652270 计算机2班 冯舜 */
/* FRENZYQRCode_SJProject - 90-b4.h */
#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include "cmd_console_tools.h"
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
#define MODULE_RESERVED 2
#define MODULE_SET 4
#define MODULE_DARK 1
#define MODULE_SWITCH 1
#define MODULE_FUNCTION 8
#define QRCOLOR_TEXTBG COLOR_BLACK
#define QRCOLOR_TEXTFG COLOR_WHITE
#define QRCOLOR_1 COLOR_BLACK
#define QRCOLOR_0 COLOR_HWHITE
#define QRCOLOR_FUNC1 COLOR_RED
#define QRCOLOR_FUNC0 COLOR_HPINK
#define QRCOLOR_RESERVED COLOR_BLUE
#define QRCOLOR_ERR COLOR_HRED
#define QRCOLOR_PADDING COLOR_WHITE


const int errLevelEquivalent[] = {1,0,3,2};
extern const int gflog[];
extern const int gfilog[];
extern const unsigned int alphanumericMap[];
extern const unsigned int capabilityTable[40][4][4];
extern const unsigned int modeIndicator[];
extern const unsigned int countIndicator[40][4];
extern const unsigned int errBlocks[40][4][6];
extern const unsigned int padBytes[];
extern const unsigned int alignPlacement[40][7];

const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
const HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄


template <typename T>
int len(T &tgt)
{
	return sizeof(tgt) / sizeof(tgt[0]);
}


void Gb2312ToUtf8(const char *pcGb2312, char * strUtf8, rsize_t strUtf8Len);

unsigned validCharNum(const unsigned char *str, int mode, bool UTF8, bool debug);

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
	void outputInBuffer(unsigned char * buf, int length);
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
	unsigned char * group[2];
	unsigned int g1n, g1c, g2n, g2c;
	unsigned int groupNextWrite;
	unsigned int codewordNextWrite;
public:
	Blocks(int g1n, int g1c, int g2n, int g2c);
	Blocks(int version, int ECLevel, bool isECCBlock);
	~Blocks();
	void input(const unsigned char * buf);
	void input(const unsigned char * buf, unsigned int n);
	unsigned char * output(unsigned char *buf) const;
	void display();
	void makeRSCodeTo(Blocks &rsb) const;
	unsigned int length();
};

class Pattern
{
private:
	int * matrix;
	int sidelen;
	int version;
	int mode;
	inline int get(int y, int x)
	{
		return matrix[y * sidelen + x];
	}
	inline void set(int y, int x, int what, bool func)
	{
		matrix[y * sidelen + x] = what | MODULE_SET | MODULE_RESERVED | (func ? MODULE_FUNCTION : 0);
	}
	inline void unset(int y, int x, int what)
	{
		matrix[y * sidelen + x] &= ~(MODULE_RESERVED | MODULE_SET);
	}
	inline void reserve(int y, int x, bool func)
	{
		matrix[y * sidelen + x] |= MODULE_RESERVED | (func ? MODULE_FUNCTION : 0);
	}
	inline bool isReserved(int y, int x)
	{
		return !!(matrix[y * sidelen + x] & MODULE_RESERVED);
	}
	inline bool isFunction(int y, int x)
	{
		return !!(matrix[y * sidelen + x] & MODULE_FUNCTION);
	}
	void init(int version);
	void placeOneFinder(int y, int x);
	void placeOneAlign(int y, int x);
public:
	unsigned int evalConsec();
	unsigned int evalSimiBlock();
	unsigned int evalFinderLike();
	unsigned int evalRatio();
public:
	//Pattern(int version, int mode);
	Pattern(int version);
	Pattern(const Pattern &p2);
	Pattern(const Pattern &p2, int maskNum);
	void makeAlign();
	void makeFinderAndSeparator();
	~Pattern();
	void print(bool color = false);
	void makeTiming();
	void reserveFormat();
	void reserveVersion();
	void fillInCodewords(const unsigned char * buf, unsigned int buflen);
	void mask(int maskNum);
	unsigned int calcPenalty();
	int chooseBestSaveIn(Pattern &source, bool debug = false);
	void formatStr(int errCorr, int maskPat, bool debug = false);
	void versionStr(bool debug = false);
	int getSidelen()
	{
		return sidelen;
	}
};

class QRCode
{
private:
	unsigned char *dataBuf;
	int version;
	int errLevel;
	int mode;
	bool UTF8;
	int paddingWidth;
	bool debug;
	bool UTF8BOM;
public:
	QRCode(bool debug = false):paddingWidth(4), debug(debug), dataBuf(nullptr)
	{}
	void inputData();
	void printQR();
	~QRCode()
	{
		if(dataBuf != nullptr)
			delete[]dataBuf;
	}
};