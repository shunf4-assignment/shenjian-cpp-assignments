/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include <iostream>
using namespace std;

class Time
{
private:
	int hour;
	int minute;
	int second;
protected:
	int plusSeconds(int seconds);
public:
	Time();
	Time(int h, int m, int d);
	bool set(int h, int m, int d);
	void get(int &h, int &m, int &d) const;
	void show() const;
	Time(int seconds);
	operator int() const;
	friend ostream & operator<< (ostream &out, const Time &t);
	friend istream & operator >> (istream &in, Time &t);
	friend Time operator++(Time &t, int);
	friend Time & operator++(Time &t);
	friend Time operator--(Time &t, int);
	friend Time & operator--(Time &t);
	//Time operator+(const Time &t) = delete;
};