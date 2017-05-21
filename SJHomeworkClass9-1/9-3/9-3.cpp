/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

class Date
{
public:
	Date(int, int, int);
	/*Date(int, int);
	Date(int);
	Date();*/
	void display();
private:
	int month;
	int day;
	int year;
};

Date::Date(int m = 2005, int d = 1, int y = 1) :month(m), day(d), year(y)
{

}
/*
Date::Date(int m, int d) : month(m), day(d)
{
	year = 2005;
}

Date::Date(int m) : month(m)
{
	day = 1;
	year = 2005;
}

Date::Date()
{
	month = 1;
	day = 1;
	year = 2005;
}
*/
void Date::display()
{
	cout << month << "/" << day << "/" << year << endl;
}

int main()
{
	Date d1(10, 13, 2005);
	Date d2(12, 30);
	Date d3(10);
	Date d4;

	d1.display();
	d2.display();
	d3.display();
	d4.display();

	return 0;
}
/*
将重复的3个构造函数的声明与实现删除即可。
*/