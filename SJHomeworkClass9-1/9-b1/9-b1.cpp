/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

class Days {
private:
	int year;
	int month;
	int day;
	int is_leap_year();  //判断是否闰年，是：返回1  /   否：返回0
public:
	int calc_days();     //计算是当年的第几天
						 /* 下面可以补充其它需要的类成员函数的定义，数量不限 */
	Days(int y, int m, int d);
	bool valid();
};

/* 此处给出类成员函数的体外实现 */
Days::Days(int y, int m, int d) : year(y), month(m), day(d)
{

}

int Days::is_leap_year()
{
	return (year % 100 != 0 && year % 4 == 0) || (year % 400 == 0);
}

bool Days::valid()
{
	static int dayThisMonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month > 12 || month < 1)
	{
		return false;
	}
	dayThisMonth[2] = 28 + is_leap_year();
	if (!((day <= dayThisMonth[month]) && (day > 0)))
		return false;
	return true;
}

int Days::calc_days()
{
	static int dayThisMonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (!valid())
		return -1;
	int dayNoLastMonthEnd = 0;
	dayThisMonth[2] = 28 + is_leap_year();

	for (int i = 1; i <= month - 1; i++)
	{
		dayNoLastMonthEnd += dayThisMonth[i];
	}

	dayNoLastMonthEnd += day;
	return dayNoLastMonthEnd;
}



/* main函数不准动 */
int main()
{
	if (1) {
		Days d1(2012, 3, 18);
		cout << "应该输出78， 实际是：" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 12, 31);
		cout << "应该输出365，实际是：" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2012, 12, 31);
		cout << "应该输出366，实际是：" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 2, 29);
		cout << "应该输出-1， 实际是：" << d1.calc_days() << endl;
	}

	return 0;
}
