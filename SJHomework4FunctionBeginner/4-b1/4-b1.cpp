/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

int zeller(int year, int month, int day)
{
	int c, w;
	(month < 3) && (year = year - 1, month = month + 12);
	c = year / 100, year = year % 100;
	w = year + year / 4 + c / 4 - 2 * c + 13 * (month + 1) / 5 + day - 1;
	return ((w % 7 + 7) % 7);
}


int main()
{
	int y, m, d, valid, dayForThisMonth, week;
	bool leapYear;

//REINPUT:
	valid = false;
	while (!valid) {
		cout << "请依次输入年 月 日，空格隔开：";
		cin >> y >> m >> d;

		if (!(cin.rdstate() != ios_base::failbit))
		{
			cout << "输入非法，请重新输入。" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		valid = true;
		if (y < 1900 || y > 2100)
		{
			cout << "年份非法，请重新输入" << endl;
			valid = false;
		}
		else
		{
			leapYear = ((y % 400 == 0) || (y % 100 != 0 && y % 4 == 0));
			dayForThisMonth = 30;
			if (m > 7 && m <= 12)
			{
				dayForThisMonth += ((m + 1) % 2);
			}
			else if (m >= 1 && m <= 7 && m != 2)
			{
				dayForThisMonth += (m % 2);
			}
			else if (m == 2)
			{
				dayForThisMonth -= 1;
				dayForThisMonth -= !leapYear;  //使该月的日子数等于29或28
			}
			else
			{
				cout << "月份非法，请重新输入。" << endl;
				valid = false;
			}
		}
		if (valid)
		{
			if (d > 0 && d <= dayForThisMonth)
				break;
			else
			{
				cout << "日期非法，请重新输入。" << endl;
				valid = false;
			}
		}
	}
	week = zeller(y, m, d);
	cout << y << " 年 " << m << " 月 " << d << " 日是：";
	//cout << week;
	switch (week)
	{
		case(0):
			cout << "星期日";
			break;
		case(1):
			cout << "星期一";
			break;
		case(2):
			cout << "星期二";
			break;
		case(3):
			cout << "星期三";
			break;
		case(4):
			cout << "星期四";
			break;
		case(5):
			cout << "星期五";
			break;
		case(6):
			cout << "星期六";
			break;
	}
	cout << "。" << endl;
	//goto REINPUT;

	return 0;
}