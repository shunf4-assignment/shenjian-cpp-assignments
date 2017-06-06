/* 1652270 ¼ÆËã»ú2°à ·ëË´ */

#include "11-b1-datetime.h"

template <typename T1, typename T2>
T1 positiveRemainder(T1 dividend, T2 divisor)
{
	T1 remainder = dividend % divisor;
	if (remainder < 0)
		remainder += divisor;
	return remainder;
}

DateTime::DateTime() : Date(), Time()
{
}

DateTime::DateTime(int y, int M, int d, int h, int m, int s) : Date(y, M, d), Time(h, m, s)
{
}

void DateTime::set(int y, int M, int d, int h, int m, int s) 
{
	bool suc;
	suc = Date::set(y, M, d);
	suc &= Time::set(h, m, s);
	if (!suc)
	{
		this->Date::Date();
		this->Time::Time();
	}
}

void DateTime::get(int& y, int& M, int& d, int& h, int& m, int& s) const
{
	Date::get(y, M, d);
	Time::get(h, m, s);
}

void DateTime::show() const
{
	cout << *this << endl;
}

DateTime::DateTime(long long seconds)
{
	seconds = positiveRemainder(seconds, 6311433600i64);
	this->Date::Date(int(seconds / 86400) + 1);
	this->Time::Time(int(seconds % 86400));
}

DateTime::operator long long() const
{
	long long result = 0;
	result += long long(Date::operator int() - 1) * 86400;
	result += long long(Time::operator int());
	return result;
}

ostream& operator<< (ostream &out, const DateTime &d)
{
	out << Date::Date(d) << " " << Time::Time(d);
	return out;
}

istream& operator >> (istream &in, DateTime &d)
{
	Date & d_date = d;
	Time & d_time = d;
	in >> d_date >> d_time;
	if (!in.good())
	{
		d.Time::Time();
		d.Date::Date();
	}
	return in;
}

//DateTime++
DateTime operator++(DateTime &d, int)
{
	int overflow = 0;
	DateTime backup = d;
	overflow = d.plusSeconds(1);
	d.Date::operator=(Date(d) + overflow);
	return backup;
}

//++DateTime
DateTime & operator++(DateTime &d)
{
	int overflow = 0;
	overflow = d.plusSeconds(1);
	d.Date::operator=(Date(d) + overflow);
	return d;
}

//DateTime--
DateTime operator--(DateTime &d, int)
{
	int overflow = 0;
	DateTime backup = d;
	overflow = d.plusSeconds(-1);
	d.Date::operator=(Date(d) + overflow);
	return backup;
}

//--DateTime
DateTime & operator--(DateTime &d)
{
	int overflow = 0;
	overflow = d.plusSeconds(-1);
	d.Date::operator=(Date(d) + overflow);
	return d;
}

DateTime operator+(const DateTime & d, long long offset)
{
	return DateTime(long long(d) + offset);
}

DateTime operator-(const DateTime & d, long long offset)
{
	return DateTime(long long(d) - offset);
}

long long operator-(const DateTime & d1, const DateTime & d2)
{
	return (long long(d1) - long long (d2));
}