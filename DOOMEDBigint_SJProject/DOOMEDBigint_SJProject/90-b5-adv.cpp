/* 1652270 �����2�� ��˴ */
/* DOOMEDBigint_SJProject 90-b5.cpp */
#include "90-b5-adv.h"

#define max(a, b) (a > b)?a:b		//�궨�壬ȡ�����д���
#define min(a, b) (a < b)?a:b		//�궨�壬ȡ������С��
#define sgn(a) (a?((a>0)*2-1):0)	//�궨�壬a ���� b ����ȡ��
#define ceilQuot(a, b) ((a + (b - 1))/b )	//�궨�壬a ���� b ����ȡ��

/*
 *	bigint::init(unsigned buflen_, bool negative)
 *		���� buflen_ �� int �Ŀռ���Ϊ�� bigint ���ݵĴ洢����
 *		ͬʱΪ�� bigint �趨���ţ�+/-����
 *		��ע�⣺buflen_ �ڴ���ǰ�Ѿ���������ǰ������Ĵ�С�������û���˷ѿռ䣡����
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
*		���޲ι���� bigint ��ֵΪ������ 0��
*/
bigint::bigint()
{
	init(0, 0);
}

/*
*	bigint::bigint(int i)
*		�� int ��ת������Ϊ bigint��
*/
bigint::bigint(int i)
{
	//��ȡ i ��λ���󣬳��� 4������ȡ����Ϊ���ݴ洢�� int *buf �ĳ��ȡ�
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
*		�� buflen_ �� int �����ݴ洢�����ȹ��� bigint����
*		������������Ϊ negative��
*/
bigint::bigint(unsigned buflen_, bool negative_)
{
	init(buflen_, negative_);
}

/*
*	bigint::bigint(const bigint &b)
*		���ƹ��캯����
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
*		���������֣����еĻ�����ǰ�÷��ţ����ַ���ת��Ϊ
*		bigint��
*/
bigint::bigint(const string &s)
{
	//strNumBegin: ���ֵ����λ���ַ�����λ�á�
	auto strNumBegin = s.begin();
	//strNumEnd: ���ֵ����λ���ַ�����λ�á�
	auto strNumEnd = s.end();
	bool negative_ = false;
	if (*strNumBegin == '-' || *strNumBegin == '+')
	{
		//�з���λ
		negative_ = *strNumBegin == '-';
		strNumBegin++;
	}
	//strNumBegin ��Ҫָ���һ������ 0 ��λ
	while (strNumBegin != s.end() && (*strNumBegin == '0'))
		strNumBegin++;

	if (strNumBegin >= strNumEnd)
	{
		//��Ч������ 0�����ַ����ƺ���Ч��
		init(0, 0);
		return;
	}
	//numLen : ��Ч�����ֳ���
	unsigned numLen = strNumEnd - strNumBegin;
	//��� ceil(numLen / 4) �� int �ĳ��ȳ�ʼ��
	init(ceilQuot(numLen, 4), negative_);
	auto p = strNumEnd - 1;
	//currNumSeg : ��ǰҪ��������������λ�� int
	int currNumSeg = 0;
	//��ǰ��λȨ����1,10,100��1000
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

	//�����Ȳ�Ϊ 4 �ı����������ʣ�� 1~3 λ�����λû������ buf����ʱ����
	if (numLen % 4 != 0)
	{
		pushBack(currNumSeg);
	}
}

/*
*	bigint::pushBack(int d)
*		���� bigint �ڲ��� writepos �����±꣬�����ݴ洢��������һ��������
*		�����������0�Ļ������� bigint ��Ч���� len��
*		����ԭ buf �� A0A1A2A3 A4A5A6A7 ******** ��writepos == 2��len == 2��
*		pushBack(0) ��
*		�� buf �� A0A1A2A3 A4A5A6A7 00000000 ******** ��writepos == 3��len == 2��
*		pushBack(0xB1B2B3B4) ��
*		�� buf �� A0A1A2A3 A4A5A6A7 00000000 B1B2B3B4 ******** ��writepos == 4��len == 4��
*/
void bigint::pushBack(int d)
{
	buf[writepos++] = d;
	if (d != 0)
		len = writepos;
}

/*
 *	void bigint::prune()
 *		�Ը� bigint ���������������������λ�� 0 ����������� len ��Ա��ֵ���ͽ� -0 תΪ +0��
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
*		���ڵ��Ե�bigint���
*		�ӵ�λ����λ���
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
*		�Ա� bigint �� b �ġ�����ֵ�����д�С�Ƚ�
*		*this > b : ���� CompVal::greater
*		*this < b : ���� CompVal::less
*		*this == b: ���� CompVal::equal
*/
CompVal bigint::compAbs(const bigint & b) const
{
	int* aPointer,* bPointer;

	//�ȱȽϳ��ȣ�����С�ı�С
	if (len < b.len)
		return CompVal::less;
	else if (len > b.len)
		return CompVal::greater;
	else if (len == 0)
		//��������£�ֻ�п�����������Ϊ 0
		return CompVal::equal;
	else
	{
		/*
		*  aPointer : �Ա� bigint �� buf ����ָ�룬�ɸ�λ���λ�ƶ�
		*  bPointer : �� b �� buf����ָ��
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
 *		�� *this ���� a �� b �ĺ͡�
 *		ע�⣺����������� *this ��ԭ�����ݡ�
 */
void bigint::equalsAdd(const bigint &a, const bigint &b)
{
	//��ձ� bigint ������
	this->bigint::~bigint();
	//sumLen : a �� b �ĳ��ȸ����ߡ�
	unsigned sumLen = max(a.len, b.len);

	//gtrint : ָ�� a �� b �еĸ����ߡ�
	const bigint *gtrint;
	//lesint : ָ�� a �� b �еĸ�С�ߡ�
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
		//carry : �Ƿ��λ��
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

		//��������ʣ��λ����
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
		//carry���Ƿ��λ
		bool carry = 0;

		int gtrCurDigit;
		for (; unsigned(lesP - lesint->buf) < lesint->len; lesP++, gtrP++)
		{
			//��λ��Ӧ��ӣ����Ͻ�λ������10000������������һλ��λ
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

		//����λ��ʣ��λ����
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
	//����
	prune();
}

/*
* void bigint::equalsMul(const bigint &a, const bigint &b)
*		�� *this ���� a �� b �Ļ���
*		ע�⣺����������� *this ��ԭ�����ݡ�
*/
void bigint::equalsMul(const bigint &a, const bigint &b)
{
	//�Ƚ�ԭ�������
	this->bigint::~bigint();
	//����λ�����������
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

	
	//���� bigint ���λ��Ϊ UINT32_MAX - 1������
	//������� 10000 * 10000 * (UINT32_MAX - 1)��Ӧ���� __int64

	//thisDigitSum : �˻������λӦ����ʲô��
	unsigned __int64 thisDigitSum;
	//carrier : ��λ
	unsigned __int64 carrier = 0;

	unsigned minLen;
	unsigned adigit;
	unsigned bdigit;
	

	//�� digitSum �� 0 ~ mulLen - 1 ����
	//digitSum ����������λ��֮�ͣ���� adigit = 0 λ�͵� bdigit = 3 λ��ˣ���Ӧ���� digitSum = 3 λ��
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
	//�˵������λʱ������� 9999 * 9999���ʽ�λ���ᳬ�� UINT32_MAX
	if(carrier)
		pushBack(unsigned(carrier));
	prune();
}

/*
* void bigint::equalsDiv(const bigint &a, const bigint &b, bigint &remainder)
*		�� *this ���� a �� b ���̣������������remainder��
*		ע�⣺����������� *this ��ԭ�����ݡ�
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

