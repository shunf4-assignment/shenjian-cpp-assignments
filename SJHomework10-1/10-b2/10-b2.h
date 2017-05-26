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
	void set(int y, int m = 0, int d = 0);
	void get(int &y, int &m, int &d);
	void show();
	Date(int days);
	operator int();
	bool isLeapYear();
	friend ostream & operator<< (ostream &out, Date &d);
	friend istream & operator>> (istream &in, Date &d);
	friend Date operator++(Date &d, int);
	friend Date & operator++(Date &d);
	friend Date operator--(Date &d, int);
	friend Date & operator--(Date &d);
};

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
ostream & operator<<(ostream &out, Date &d);

istream & operator >> (istream &in, Date &d);

Date operator++(Date &d, int);

Date & operator++(Date &d);

Date operator--(Date &d, int);

Date & operator--(Date &d);

/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */

const int dayOfMonth[] = { 0, 31, 28, 31,30,31,30,31,31,30,31,30,31 };

bool _isLeapYear(int year);