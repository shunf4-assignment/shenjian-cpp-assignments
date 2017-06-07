/* 1652270 计算机2班 冯舜 */
/* DOOMEDBigint_SJProject 90-b5.cpp */
#include "90-b5-adv.h"

#define max(a, b) (a > b)?a:b		//宏定义，取两者中大者
#define min(a, b) (a < b)?a:b		//宏定义，取两者中小者
#define sgn(a) (a?((a>0)*2-1):0)	//宏定义，a 除以 b 向上取整
#define ceilQuot(a, b) ((a + (b - 1))/b )	//宏定义，a 除以 b 向上取整

/*
 *	bigint::init(unsigned buflen_, bool negative)
 *		申请 buflen_ 个 int 的空间作为该 bigint 数据的存储区，
 *		同时为该 bigint 设定符号（+/-）。
 *		【注意：buflen_ 在传参前已经计算过，是按需分配的大小！！因此没有浪费空间！！】
 */
void bigint::init(unsigned buflen_, bool negative_)
{
	buf = buflen_ ? (new int[buflen_]) : nullptr;
	/*if (buflen_ && buf == nullptr)
	{
		///exit(STAT_OVERFLOW);
	}*/
	memset(buf, 0, buflen_ * sizeof(int));
	len = 0;
	buflen = buflen_;
	negative = negative_;
	writepos = 0;
}

/*
*	bigint::bigint()
*		给无参构造的 bigint 赋值为正数的 0。
*/
bigint::bigint()
{
	init(0, 0);
}

/*
*	bigint::bigint(int i)
*		将 int 型转换构造为 bigint。
*/
bigint::bigint(int i)
{
	//获取 i 的位数后，除以 4，向上取整作为数据存储区 int *buf 的长度。
	init(unsigned(ceilQuot(getHowManyDigits(i), 4)), i < 0);
	unsigned i_ = abs(i);
	while (i_ > 0)
	{
		pushBack(i_ % 10000);
		i_ = i_ / 10000;
	}
}

bigint::bigint(unsigned i_)
{
	init(unsigned(ceilQuot(getHowManyDigits(i_), 4)), 0);
	while (i_ > 0)
	{
		pushBack(i_ % 10000);
		i_ = i_ / 10000;
	}
}

bigint::bigint(__int64 i)
{
	init(unsigned(ceilQuot(getHowManyDigits(i), 4)), i < 0);
	__int64 i_ = _abs64(i);
	while (i_ > 0)
	{
		pushBack(i_ % 10000);
		i_ = i_ / 10000;
	}
}

bigint::bigint(unsigned __int64 i_)
{
	init(unsigned((getHowManyDigits(i_) + 3) / 4), 0);
	while (i_ > 0)
	{
		pushBack(i_ % 10000);
		i_ = i_ / 10000;
	}
}

/*
*	bigint::bigint(unsigned buflen_, bool negative_)
*		以 buflen_ 个 int 的数据存储区长度构造 bigint，并
*		将正负性设置为 negative。
*/
bigint::bigint(unsigned buflen_, bool negative_)
{
	init(buflen_, negative_);
}

/*
*	bigint::bigint(const bigint &b)
*		复制构造函数。
*/
bigint::bigint(const bigint & b)
{
	init(b.len, b.negative);
	buflen = len = b.len;
	writepos = b.writepos;
	memcpy_s(buf, buflen * sizeof(int), b.buf, b.len * sizeof(int));
}

/*
*	bigint::bigint(const string &s)
*		将含有数字（若有的话，和前置符号）的字符串转换为
*		bigint。
*/
bigint::bigint(const string &s)
{
	//strNumBegin: 数字的最高位在字符串的位置。
	auto strNumBegin = s.begin();
	//strNumEnd: 数字的最低位在字符串的位置。
	auto strNumEnd = s.end();
	bool negative_ = false;
	if (*strNumBegin == '-' || *strNumBegin == '+')
	{
		//有符号位
		negative_ = *strNumBegin == '-';
		strNumBegin++;
	}
	//strNumBegin 需要指向第一个不是 0 的位
	while (strNumBegin != s.end() && (*strNumBegin == '0'))
		strNumBegin++;

	if (strNumBegin >= strNumEnd)
	{
		//有效长度是 0，该字符串似乎无效？
		init(0, 0);
		return;
	}
	//numLen : 有效的数字长度
	unsigned numLen = strNumEnd - strNumBegin;
	//针对 ceil(numLen / 4) 个 int 的长度初始化
	init(ceilQuot(numLen, 4), negative_);
	auto p = strNumEnd - 1;
	//currNumSeg : 当前要填入数据区的四位数 int
	int currNumSeg = 0;
	//当前的位权，从1,10,100到1000
	int currBase = 1;
	while (p >= strNumBegin)
	{
		currNumSeg = currNumSeg + currBase * (*p - '0');
		currBase *= 10;
		if ((strNumEnd - p) % 4 == 0)
		{
			pushBack(currNumSeg);
			currNumSeg = 0;
			currBase = 1;
		}
		if (p == strNumBegin)
			break;
		else
			p--;
	}

	//若长度不为 4 的倍数，则最后还剩下 1~3 位的最高位没有填入 buf，此时填入
	if (numLen % 4 != 0)
	{
		pushBack(currNumSeg);
	}
}

/*
*	bigint::pushBack(int d)
*		根据 bigint 内部的 writepos 整数下标，向数据存储区内填入一个整数。
*		填入的整数非0的话，更新 bigint 有效长度 len。
*		例：原 buf ： A0A1A2A3 A4A5A6A7 ******** ，writepos == 2，len == 2。
*		pushBack(0) 后，
*		现 buf ： A0A1A2A3 A4A5A6A7 00000000 ******** ，writepos == 3，len == 2。
*		pushBack(0xB1B2B3B4) 后，
*		现 buf ： A0A1A2A3 A4A5A6A7 00000000 B1B2B3B4 ******** ，writepos == 4，len == 4。
*/
void bigint::pushBack(int d)
{
	buf[writepos++] = d;
	if (d != 0)
		len = writepos;
}

/*
 *	void bigint::prune()
 *		对该 bigint 进行修整，包括处理最高位是 0 的情况（减少 len 成员的值）和将 -0 转为 +0。
 */
void bigint::prune()
{
	while (len > 0 && buf[len - 1] == 0)
		len--;
	if (len == 0)
		negative = false;
}

/*
*	void bigint::print() const
*		用于调试的bigint输出
*		从低位到高位输出
*/
void bigint::print() const
{
	if (negative)
		cout << "-";
	for (unsigned i = 0; i < len; i++)
	{
		cout << buf[i] << " ";
	}
}

/*
*	CompVal bigint::compAbs(const bigint &b)
*		对本 bigint 与 b 的【绝对值】进行大小比较
*		*this > b : 返回 CompVal::greater
*		*this < b : 返回 CompVal::less
*		*this == b: 返回 CompVal::equal
*/
CompVal bigint::compAbs(const bigint & b) const
{
	int* aPointer,* bPointer;

	//先比较长度，长度小的必小
	if (len < b.len)
		return CompVal::less;
	else if (len > b.len)
		return CompVal::greater;
	else if (len == 0)
		//这种情况下，只有可能是两方都为 0
		return CompVal::equal;
	else
	{
		/*
		*  aPointer : 对本 bigint 在 buf 区的指针，由高位向低位移动
		*  bPointer : 对 b 在 buf区的指针
		*/
		for (bPointer = b.buf + b.len - 1, aPointer = buf + len - 1; bPointer >= b.buf; bPointer--, aPointer--)
		{
			if (*bPointer < *aPointer)
			{
				return CompVal::greater;
			}
			else if (*aPointer < *bPointer)
			{
				return CompVal::less;
			}
		}
		return CompVal::equal;
	}
}

/*
 * void bigint::equalsAdd(const bigint &a, const bigint &b)
 *		令 *this 等于 a 和 b 的和。
 *		注意：本方法将清除 *this 的原有数据。
 */
void bigint::equalsAdd(const bigint &a, const bigint &b)
{
	//清空本 bigint 的内容
	this->bigint::~bigint();
	//sumLen : a 和 b 的长度更大者。
	unsigned sumLen = max(a.len, b.len);

	//gtrint : 指向 a 和 b 中的更大者。
	const bigint *gtrint;
	//lesint : 指向 a 和 b 中的更小者。
	const bigint *lesint;
	CompVal comp = a.compAbs(b);

	if (CompVal::greater == comp)
	{
		gtrint = &a;
		lesint = &b;
	}
	else
	{
		gtrint = &b;
		lesint = &a;
	}

	const int *lesP = lesint->buf;
	const int *gtrP = gtrint->buf;

	if (a.negative ^ b.negative)
	{
		//actually Substraction
		init(sumLen, 0);
		if (gtrint->negative)
		{
			//in this case the result is negative
			negative = 1;
		}

		//start Substraction
		//carry : 是否进位。
		bool carry = 0;
		int gtrCurDigit;
		for (; unsigned(lesP - lesint->buf) < lesint->len; lesP++, gtrP++)
		{
			gtrCurDigit = *gtrP;
			if (carry)
			{
				gtrCurDigit--;
				carry = 0;
			}
			gtrCurDigit -= *lesP;
			if (gtrCurDigit < 0)
			{
				carry = 1;
				gtrCurDigit += 10000;
			}
			pushBack(gtrCurDigit);
		}

		//将大数的剩余位推入
		for (; unsigned(gtrP - gtrint->buf) < gtrint->len; gtrP++)
		{
			gtrCurDigit = *gtrP;
			if (carry)
			{
				gtrCurDigit--;
				carry = 0;
			}
			if (gtrCurDigit < 0)
			{
				carry = 1;
				gtrCurDigit += 10000;
			}
			pushBack(gtrCurDigit);
		}
	}
	else
	{
		//actually Addition
		sumLen++;
		init(sumLen, a.negative);

		//start Addition
		//carry：是否进位
		bool carry = 0;

		int gtrCurDigit;
		for (; unsigned(lesP - lesint->buf) < lesint->len; lesP++, gtrP++)
		{
			//逐位对应相加，加上进位；大于10000则消除并在下一位进位
			gtrCurDigit = *gtrP + *lesP;
			if (carry)
			{
				gtrCurDigit++;
				carry = 0;
			}

			if (gtrCurDigit >= 10000)
			{
				carry = 1;
				gtrCurDigit -= 10000;
			}
			pushBack(gtrCurDigit);
		}

		//将多位的剩余位补上
		for (; unsigned(gtrP - gtrint->buf) < gtrint->len; gtrP++)
		{
			gtrCurDigit = *gtrP;
			if (carry)
			{
				gtrCurDigit++;
				carry = 0;
			}
			if (gtrCurDigit >= 10000)
			{
				carry = 1;
				gtrCurDigit -= 10000;
			}
			pushBack(gtrCurDigit);
		}

		if (carry)
			pushBack(1);
	}
	//裁整
	prune();
}

/*
* void bigint::equalsMul(const bigint &a, const bigint &b)
*		令 *this 等于 a 和 b 的积。
*		注意：本方法将清除 *this 的原有数据。
*/
void bigint::equalsMul(const bigint &a, const bigint &b)
{
	//先将原数据清除
	this->bigint::~bigint();
	//积的位数是两者相加
	unsigned mulLen = a.len + b.len;

	if (a.negative ^ b.negative)
	{
		//result is negative
		init(mulLen, 1);
	}
	else
	{
		init(mulLen, 0);
	}

	
	//由于 bigint 最大位数为 UINT32_MAX - 1，所以
	//最大容量 10000 * 10000 * (UINT32_MAX - 1)，应该用 __int64

	//thisDigitSum : 乘积的这个位应该是什么数
	unsigned __int64 thisDigitSum;
	//carrier : 进位
	unsigned __int64 carrier = 0;

	unsigned minLen;
	unsigned adigit;
	unsigned bdigit;
	

	//按 digitSum 从 0 ~ mulLen - 1 遍历
	//digitSum 是两因数的位数之和，如第 adigit = 0 位和第 bdigit = 3 位相乘，对应积的 digitSum = 3 位。
	for (unsigned digitsum = 0; digitsum < mulLen - 1; digitsum++)
	{
		thisDigitSum = carrier;
		minLen = min(a.len, digitsum + 1);
		for (adigit = 0; adigit < minLen; adigit++)
		{
			bdigit = digitsum - adigit;
			if (bdigit >= 0 && bdigit < b.len)
			{
				thisDigitSum += a.buf[adigit] * b.buf[bdigit];
			}
		}
		
		carrier = thisDigitSum / 10000;
		thisDigitSum = thisDigitSum % 10000;
		pushBack(unsigned(thisDigitSum));
	}
	//乘到积最高位时，最大是 9999 * 9999，故进位不会超过 UINT32_MAX
	if(carrier)
		pushBack(unsigned(carrier));
	prune();
}

/*
* void bigint::equalsDiv(const bigint &a, const bigint &b, bigint &remainder)
*		令 *this 等于 a 和 b 的商，并将结果存入remainder。
*		注意：本方法将清除 *this 的原有数据。
*/
void bigint::equalsDiv(const bigint &a, const bigint &b, bigint &remainder)
{
	this->bigint::~bigint();
	CompVal compAB = a.compAbs(b);
	if ( CompVal::less == compAB)
	{
		remainder = a;
		*this = 0;
	}
	else if (CompVal::equal == compAB)
	{
		remainder = 0;
		*this = 1;
	}
	else
	{
		remainder = a;
		bigint b_ = b;
		remainder.negative = b_.negative = 0;
		unsigned divLen = a.len - b.len + 1;
		init(divLen, 0);

		len = divLen;
		unsigned dividendDigit;

		if (0 == b_.len)
		{
			buf[0] = b_.len / b_.len;
		}
		else
			for (dividendDigit = remainder.len - b_.len; dividendDigit + 1 != 0; dividendDigit--)
			{
				if (remainder < b_)
					break;
				//try to estimate this digit of the quotient
				unsigned approxDividend = remainder.buf[dividendDigit + b_.len - 1];
				if (remainder.len > dividendDigit + b_.len)
					approxDividend += remainder.buf[dividendDigit + b_.len] * 10000;
				unsigned approxDivisor = b_.buf[b_.len - 1];
				unsigned approxQuot = approxDividend / approxDivisor;
				/////cout << approxDividend << " / " << approxDivisor << " = " << approxQuot << endl;
				bigint tryMultiply;
				do
				{
					bigint approxQuotAsFactor(dividendDigit + 1, 0);//approxQuot times base^dividendDigit to make product with divisor b_ which later substracts from remainder
					approxQuotAsFactor.buf[dividendDigit] = approxQuot;
					approxQuotAsFactor.len = dividendDigit + 1;
					/////cout << "AsAFactor: " << approxQuotAsFactor << endl;

					tryMultiply.equalsMul(approxQuotAsFactor, b_);
					/////cout << "TryMultiply " << tryMultiply << endl;

					if (tryMultiply > remainder)
					{
						approxQuot--;
						/////cout << "Decrease by 1" << endl;
						/////cout << "approxQuot " << approxQuot << endl;
						continue;
					}
					else
					{
						break;
					}
				} while (1);
				/////cout << remainder << " - ";
				remainder -= tryMultiply;
				/////cout << tryMultiply << " = " ;

				buf[dividendDigit] = approxQuot;
				remainder.prune();
				/////cout << remainder << endl;
			}
	}
	if (a.negative ^ b.negative)
		negative = true;
	if (a.negative)
		remainder.negative = true;

	prune();

}


bigint bigint::operator-() const
{
	bigint result(*this);
	result.negative ^= 1;
	return result;
}

bigint operator+(const bigint &a, const bigint & b)
{
	bigint result;
	result.equalsAdd(a, b);
	return result;
}

bigint & operator+=(bigint &a, const bigint & b)
{
	a = a + b;
	return a;
}

bigint operator-(const bigint &a, const bigint & b)
{
	return a + -b;
}

bigint & operator-=( bigint &a, const bigint & b)
{
	a = a - b;
	return a;
}


bigint operator*(const bigint &a, const bigint & b)
{
	bigint result;
	result.equalsMul(a, b);
	return result;
}

bigint & operator*=(bigint &a, const bigint & b)
{
	a = a * b;
	return a;
}

bigint operator/(const bigint &a, const bigint & b)
{
	bigint result, remain;
	result.equalsDiv(a, b, remain);
	return result;
}

bigint & operator/=(bigint &a, const bigint & b)
{
	a = a / b;
	return a;
}

bigint operator%(const bigint &a, const bigint & b)
{
	bigint result, remain;
	result.equalsDiv(a, b, remain);
	return remain;
}

bigint & operator%=(bigint &a, const bigint & b)
{
	a = a % b;
	return a;
}

const bigint bigint::operator++(int)
{
	bigint result = *this;
	*this += 1;
	return result;
}
bigint & bigint::operator++()
{
	*this += 1;
	return *this;
}

const bigint bigint::operator--(int)
{
	bigint result = *this;
	*this -= 1;
	return result;
}
bigint & bigint::operator--()
{
	*this -= 1;
	return *this;
}

bool operator<(const bigint &a, const bigint & b)
{
	if (a.negative && b.negative == false)
		return true;
	if (b.negative && a.negative == false)
		return false;
	CompVal comp = a.compAbs(b);
	if (comp == CompVal::equal)
		return false;
	return (comp == CompVal::less) ^ a.negative;
}

bool operator<=(const bigint &a, const bigint & b)
{
	if (a.negative && b.negative == false)
		return true;
	if (b.negative && a.negative == false)
		return false;
	CompVal comp = a.compAbs(b);
	if (comp == CompVal::equal)
		return true;
	return (comp == CompVal::less) ^ a.negative;
}

bool operator>(const bigint &a, const bigint & b)
{
	return !(a <= b);
}

bool operator>=(const bigint &a, const bigint & b)
{
	return !(a < b);
}

bool operator==(const bigint &a, const bigint & b)
{
	if (a.negative ^ b.negative)
		return false;
	CompVal comp = a.compAbs(b);
	return (comp == CompVal::equal);
}

bool operator!=(const bigint &a, const bigint & b)
{
	return !(a == b);
}


bigint::~bigint()
{
	if (buf)
		delete[]buf;
}

ostream & operator<<(ostream &out, const bigint &b)
{
	if (b.negative)
		out << '-';
	const int *bufTail = b.buf + b.len;
	const int *bufP = bufTail;
	char fill = out.fill();

	out << setfill('0');
	if (bufP == b.buf)
	{
		out << '0';
	}
	else
	{
		bufP--, bufTail--;
		for (; bufP + 1 != b.buf; bufP--)
		{
			if (bufP != bufTail)
				out << setw(4);
			out << *bufP;
			//out << ' ';
		}
	}
		
	out << setfill(fill);

	return out;
}

istream & operator>>(istream &in, bigint &b)
{
	char sign;
	bool validNum = false;
	bool negative = false;
	string result = "";
	b.~bigint();
	
	in >> sign;
	if (sign == '-')
	{
		negative = true;
	}
	else if (sign == '+')
	{
		negative = false;
	}
	else if (sign >= '0' && sign <= '9')
	{
		in.putback(sign);
	}
	else
	{
		//invalid
		in.putback(sign);
		in.setstate(in.rdstate() | ios::ios_base::failbit);
		return in;
	}

	char readChr;
	while (true)
	{
		readChr = in.peek();
		if (!in.good())
		{
			return in;
		}
		if (!(readChr >= '0' && readChr <= '9'))
		{
			if (validNum)
			{
				break;
			}
			else
			{
				//invalid
				in.setstate(in.rdstate() | ios::ios_base::failbit);
				return in;
			}
		}
		result += readChr;
		in.get();
		if (!validNum)
			validNum = true;
	}
	b.bigint::bigint(result);
	b.negative = negative;
	return in;
	
}

bigint & bigint::operator=(const string & s)
{
	this->bigint::~bigint();
	this->bigint::bigint(s);
	return *this;
}

bigint & bigint::operator=(const bigint & b)
{
	if (buflen >= b.len)
	{
		negative = b.negative;
		len = b.len;
		writepos = b.writepos;
		memcpy_s(buf, buflen * sizeof(int), b.buf, b.len * sizeof(int));
	}
	else
	{
		this->bigint::~bigint();
		this->bigint::bigint(b);
	}
	return *this;
}

