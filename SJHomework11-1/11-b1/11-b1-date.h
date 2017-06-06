/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

/* 补全Date类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class Date {
private:
	int year;
	int month;
	int day;
public:
	/* 根据需要定义所需的成员函数、友元函数等 */
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

/* 如果有其它全局函数需要声明，写于此处 */
ostream & operator<<(ostream &out, const Date &d);

istream & operator >> (istream &in, Date &d);

Date operator++(Date &d, int);

Date & operator++(Date &d);

Date operator--(Date &d, int);

Date & operator--(Date &d);

/* 如果有需要的宏定义、只读全局变量等，写于此处 */

const int dayOfMonth[] = { 0, 31, 28, 31,30,31,30,31,31,30,31,30,31 };

bool _isLeapYear(int year);