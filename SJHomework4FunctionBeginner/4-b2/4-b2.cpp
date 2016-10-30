/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <iomanip>
using namespace std;

int zeller(int year, int month, int day)
{
	int c, w;
	(month < 3) && (year = year - 1, month = month + 12);
	c = year / 100, year = year % 100;
	w = year + year / 4 + c / 4 - 2 * c + 13 * (month + 1) / 5 + day - 1;
	return ((w % 7 + 7) % 7);
}

void calendar(int dayForThisMonth, int dayOfFirstDay, int dayForLastMonth = -1)
{
	int dayLoop, weekLoop;
	dayLoop = 1 - dayOfFirstDay;
	weekLoop = 0;
	cout << " 周日  周一  周二  周三  周四  周五  周六 ";
	while (dayLoop <= dayForThisMonth + (6 - (dayOfFirstDay + dayForThisMonth - 1) % 7))
	{
		if (weekLoop != 0)
			cout << "  ";
		else
			cout << endl << " ";

		if (dayLoop > 0 && dayLoop <= dayForThisMonth)
		{
			cout << setw(3) << dayLoop;
			cout << " ";
		}
		else
		{
			if (dayForLastMonth == -1)
				cout << "    ";
			else
			{
				if(dayLoop <= 0)
					cout << "(" << setw(2) << dayForLastMonth + dayLoop << ")";
				else
					cout << "(" << setw(2) << dayLoop - dayForThisMonth << ")";
			}
		}
		dayLoop++;
		weekLoop = (++weekLoop) % 7;
	}
	cout << endl;
}



int main()
{
	int y, m, valid, dayForThisMonth, dayForLastMonth, week;
	bool leapYear;

//REINPUT:
	valid = false;
	while (!valid) {
		cout << "请依次输入年 月，空格隔开：";
		cin >> y >> m;
		valid = true;

		if (!(cin.rdstate() != ios_base::failbit))
		{
			cout << "输入非法，请重新输入。" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			valid = false;
			continue;
		}

		if (y < 1900 || y > 2100)
		{
			cout << "年份非法，请重新输入" << endl;
			valid = false;
		}
		else
		{
			leapYear = ((y % 400 == 0) || (y % 100 != 0 && y % 4 == 0));
			dayForThisMonth = 30;
			dayForLastMonth = 30;
			if (m > 7 && m <= 12)
			{
				dayForThisMonth += ((m + 1) % 2);
				dayForLastMonth += (m % 2) + (m == 8);
			}
			else if (m >= 1 && m <= 7 && m != 2)
			{
				dayForThisMonth += (m % 2);
				dayForLastMonth += ((m + 1) % 2) + (m == 1) - (m == 3) * (1 + !leapYear);
			}
			else if (m == 2)
			{
				dayForThisMonth -= 1;
				dayForThisMonth -= !leapYear;  //使该月的日子数等于29或28
				dayForLastMonth += 1;
			}
			else
			{
				cout << "月份非法，请重新输入。" << endl;
				valid = false;
			}
		}
	}

	week = zeller(y, m, 1);
	cout << y << " 年 " << m << " 月 月历" << endl;
	calendar(dayForThisMonth, week, dayForLastMonth);
	//goto REINPUT;

	return 0;
}