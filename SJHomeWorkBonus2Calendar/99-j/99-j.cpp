/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

#define row 4
#define prespace 3
#define space 2
#define halftitle (space + 2)*7 / 2 - 2
#define gap 3
#define column 3

int zeller(int year, int month, int day)
{
	int c, w;
	(month < 3) && (year = year - 1, month = month + 12);
	c = year / 100, year = year % 100;
	w = year + year / 4 + c / 4 - 2 * c + 13 * (month + 1) / 5 + day - 1;
	return ((w % 7 + 7) % 7);
}

void setColor(HANDLE h, bool red, bool green, bool blue, bool inten)
{
	SetConsoleTextAttribute(h, (FOREGROUND_RED * red) | (FOREGROUND_BLUE * blue) | (FOREGROUND_GREEN * green) | (FOREGROUND_INTENSITY * inten));
}

void calendarForWholeYear(int year)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int monthDay[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	monthDay[2] += (year % 400 == 0) || (year % 400 != 0 && year % 4 == 0);
	char weekday[] = "一二三四五六日";
	for (int q = 0; q < row; q++)
	{
		cout << endl << setw(prespace) << "";
		for (int m = 0; m < 3; m++)
		{//输出X月
			cout << setw(halftitle + (m > 0)*(halftitle + gap)) << "" << setw(2);
			setColor(h, 1, 0, 1, 1); 
			cout << q * 3 + m + 1;
			setColor(h, 1, 1, 1, 1);
			cout << " 月";
		}
		cout << endl << setw(prespace) << "";
		for (int m = 0; m < 3; m++)
		{//输出星期头
			for (int w = 0; w < 7; w++)
			{
				if (w == 5)
					setColor(h, 1, 1, 0, 1);
				if (w == 6)
					setColor(h, 1, 0, 0, 1);
				if (w == 0)
					setColor(h, 1, 1, 1, 0);
				cout << setw(space) << "" << weekday[w * 2] << weekday[w * 2 + 1];
			}
			cout << setw(gap) << "";
			setColor(h, 1, 1, 1, 0);
		}
		
		int currDay[3] = {2 - zeller(year, q * 3 + 1, 1) ,2 - zeller(year, q * 3 + 2, 1) ,2 - zeller(year, q * 3 + 3, 1) };
		for (int i = 0; i < 6 * 7 * column; i++)
		{
			if (i % (7 * 3) == 0)
			{
				cout << endl;
				cout << setw(prespace) << "";
			}
			if (i % (7 * 3) % 7 == 0 && i % (7 * 3) != 0 )
				cout << setw(gap) << "";
			cout << setw(space) << "";
			cout << setw(2);
			if (i % (7 * 3) % 7 == 5)
				setColor(h, 1, 1, 0, 1);
			if (i % (7 * 3) % 7 == 6)
				setColor(h, 1, 0, 0, 1);
			if (i % (7 * 3) % 7 == 0)
				setColor(h, 1, 1, 1, 0);
			if (currDay[i % (7 * 3) / 7] > 0 && currDay[i % (7 * 3) / 7] <= monthDay[i % (7 * 3) / 7 + 1 + q * 3])
			{
				cout << currDay[i % (7 * 3) / 7];
			}
			else
			{
				cout << "";
			}
			currDay[i % (7 * 3) / 7] += 1;
		}
	}
	cout << endl;
}

int main()
{
	int y;
	bool valid;

	system("mode con cols=140 lines=37");

	//REINPUT:
	valid = false;
	while (!valid) {
		cout << "请输入年份：";
		cin >> y;
		valid = true;

		if (!(cin.rdstate() != ios_base::failbit))
		{
			cout << "输入非法，请重新输入。" << endl;
			cin.clear();
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			valid = false;
			continue;
		}

		if (y < 1900 || y > 2100)
		{
			cout << "年份非法，请重新输入" << endl;
			cin.clear();
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			valid = false;
			continue;
		}

	}
	cout << y << " 年 年历" << endl;
	//calendar(dayForThisMonth, week, dayForLastMonth);
	calendarForWholeYear(y);
	//goto REINPUT;

	return 0;
}