/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

/* ��ȫDate��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
class Date {
private:
	int year;
	int month;
	int day;
public:
	/* ������Ҫ��������ĳ�Ա��������Ԫ������ */
	Date();
	Date(int y, int m, int d);
	bool set(int y, int m, int d);
	void get(int &y, int &m, int &d) const;
	void show() const;
	Date(int days);
	 operator int() const;
	bool isLeapYear() const;
	friend ostream & operator<< (ostream &out, const Date &d);
	friend istream & operator >> (istream &in, Date &d);
	friend Date operator++(Date &d, int);
	friend Date & operator++(Date &d);
	friend Date operator--(Date &d, int);
	friend Date & operator--(Date &d);
	//Date operator+(const Date &d) = delete;
};

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
ostream & operator<<(ostream &out, const Date &d);

istream & operator >> (istream &in, Date &d);

Date operator++(Date &d, int);

Date & operator++(Date &d);

Date operator--(Date &d, int);

Date & operator--(Date &d);

/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */

const int dayOfMonth[] = { 0, 31, 28, 31,30,31,30,31,31,30,31,30,31 };

bool _isLeapYear(int year);