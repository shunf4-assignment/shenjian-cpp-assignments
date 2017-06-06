/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include "11-b1-time.h"
#include "11-b1-date.h"

class DateTime : protected Date, protected Time
{
public:
	DateTime(int y, int M, int d, int h = 0, int m = 0, int s = 0);
	DateTime();
	
	void set(int y, int M, int d, int h, int m, int s );
	void get(int& y, int& M, int& d, int& h, int& m, int& s) const;
	void show() const;
	DateTime(long long seconds);
	operator long long() const ;
	//operator int() = delete;
	friend DateTime operator+ (const DateTime &d, long long offset);
	friend DateTime operator- (const DateTime &d, long long offset);
	friend long long operator- (const DateTime &d1, const DateTime &d2);
	friend ostream & operator<< (ostream &out, const DateTime &d);
	friend ostream & operator<< (ostream &out, const DateTime &d);
	friend istream & operator >> (istream &in, DateTime &d);
	friend DateTime operator++(DateTime &d, int);
	friend DateTime & operator++(DateTime &d);
	friend DateTime operator--(DateTime &d, int);
	friend DateTime & operator--(DateTime &d);
	
	bool operator> (const DateTime &d) const
	{
		return long long(*this) > long long(d);
	}
	bool operator< (const DateTime &d) const
	{
		return long long(*this) < long long(d);
	}
	bool operator>= (const DateTime &d) const
	{
		return long long(*this) >= long long(d);
	}
	bool operator<= (const DateTime &d) const
	{
		return long long(*this) <= long long(d);
	}
	bool operator== (const DateTime &d) const
	{
		return long long(*this) == long long(d);
	}
	bool operator!= (const DateTime &d) const
	{
		return long long(*this) != long long(d);
	}
};

ostream & operator<<(ostream &out, const DateTime &d);

istream & operator >> (istream &in, DateTime &d);

DateTime operator++(DateTime &d, int);

DateTime & operator++(DateTime &d);

DateTime operator--(DateTime &d, int);

DateTime & operator--(DateTime &d);