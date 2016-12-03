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

void calendarForWholeYear(int year)
{
	int dayPoint[6][3] = { {0} ,{ 0 } ,{ 0 } ,{ 0 } ,{ 0 } ,{ 0 }};
	int day[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (year % 400 == 0 || year % 100 != 0 && year % 4 == 0)
		day[1] = 29;
	for (int q = 0; q <= 3; q++)
	{
		
		for (int m = 0; m < 3; m++)
		{
			dayPoint[0][m] = 1 - zeller(year, q * 3 + m + 1, 1);
			for (int i = 1; i < 6; i++)
				dayPoint[i][m] = dayPoint[i-1][m] + 7;
		}
		for (int m = 0; m < 3; m++)
		{
			if (!m)
				cout << "  ";
			cout << "                 " << setw(2) << q * 3 + m + 1 << " 月                        ";
		}
		cout << endl;
		for (int m = 0; m < 3; m++)
		{
			if (m)
				cout << "    ";
			else
				cout << "  ";
			cout << " 周日  周一  周二  周三  周四  周五  周六 ";
		}
		cout << endl;
		for (int k = 0; k < 6; k++)
		{
			for (int m = 0; m < 3; m++)
			{
				for (int i = 0; i < 7; i++)
				{
					cout << "    ";
					if (dayPoint[k][m] < 1 || dayPoint[k][m] > day[q * 3 + m ])
						cout << "  ";
					else
						cout << setw(2) << dayPoint[k][m];
					dayPoint[k][m] += 1;
				}
				cout << "    ";
			}
			cout << endl;
		}
	}
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
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			valid = false;
			continue;
		}

		if (y < 1900 || y > 2100)
		{
			cout << "年份非法，请重新输入" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
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
