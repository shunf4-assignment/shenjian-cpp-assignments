/* 1652270 计算机2班 冯舜 */
/* DOOMEDBigint_SJProject 90-b5.h */
#pragma once
#include <string>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

#define STAT_OVERFLOW -1

enum CompVal { less = -1, equal = 0, greater = 1 };

class bigint
{
private:
	bool negative;	//to indicate if this bigint is negative
	int * buf;	//to store digits in bigint as groups of 4 (0-9999)
	unsigned buflen;//the actual length of buffer
	unsigned writepos;//the position when writing digits to the bigint(an index of buf)
	unsigned len;	//the length of bigint buffer, not counting 0s / the most significant digit
	void init(unsigned len, bool negative_);
	void prune();
public:
	bigint(const string &s);
	bigint();
	bigint(const bigint &b);	//constructor by bigint
	bigint(__int64 i);
	bigint(unsigned __int64 i);
	bigint(int i);	//constructor by int
	bigint(unsigned i);	//constructor by unsigned
	bigint(unsigned buflen_, bool negative_);
	void pushBack(int d);	//push an unsigned number to the buffer
	void print() const;		//print this bigint
	bigint &operator=(const string &s);
	bigint &operator=(const bigint &b);
	bigint operator-() const;
	bigint operator+() const
	{
		return *this;
	}
	const bigint operator++(int);
	bigint & operator++();
	const bigint operator--(int);
	bigint & operator--();
	friend bigint operator+(const bigint &a, const bigint &b);
	friend bigint & operator+=(bigint &a, const bigint &b);
	friend bigint operator-(const bigint &a, const bigint &b);
	friend bigint & operator-=(bigint &a, const bigint &b);
	friend bigint operator*(const bigint &a, const bigint &b);
	friend bigint & operator*=(bigint &a, const bigint &b);
	friend bigint operator/(const bigint &a, const bigint &b);
	friend bigint & operator/=(bigint &a, const bigint &b);
	friend bigint operator%(const bigint &a, const bigint &b);
	friend bigint & operator%=(bigint &a, const bigint &b);
	friend bool operator<(const bigint &a, const bigint &b) ;
	friend bool operator<=(const bigint &a, const bigint &b) ;
	friend bool operator>(const bigint &a, const bigint &b) ;
	friend bool operator>=(const bigint &a, const bigint &b) ;
	friend bool operator==(const bigint &a, const bigint &b) ;
	friend bool operator!=(const bigint &a, const bigint &b) ;
	friend ostream & operator<<(ostream &out, const bigint &b);
	friend istream & operator>>(istream &in, bigint &b);
	void equalsAdd(const bigint &a, const bigint &b);
	void equalsMul(const bigint &a, const bigint &b);
	void equalsDiv(const bigint &a, const bigint &b, bigint &remainder);
	CompVal bigint::compAbs(const bigint & b) const;
	~bigint();

	bool is_badalloc()
	{
		return (buf == nullptr);  //int *buf是数据存储区的指针
	}
};


template <typename I>
unsigned getHowManyDigits(I i)
{
	if (i == 0)
		return 0;
	unsigned result = 0;
	while (result++, (i /= 10))
		;
	return result;
}