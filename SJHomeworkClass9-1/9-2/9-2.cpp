/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

class Date
{
public:
	Date(int, int, int);
	Date(int, int);
	Date(int);
	Date();
	void display();
private:
	int month;
	int day;
	int year;
};

Date::Date(int m, int d, int y) :month(m), day(d), year(y)
{

}

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
程序输出：
4 个已经建立的Date对象的内容，是四个日期：
10/13/2005
12/30/2005
10/1/2005
1/1/2005
之后程序结束。
*/