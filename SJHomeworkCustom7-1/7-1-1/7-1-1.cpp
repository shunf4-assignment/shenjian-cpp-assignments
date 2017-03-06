/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

struct Date
{
	int year;
	int month;
	int day;
};

int main()
{
	//REINPUT:

	Date d;
	int dayThisMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	bool valid;
	int dayNoLastMonthEnd = 0;

	do
	{
		valid = true;
		cout << "依次输入年月日，用空格隔开，如2014 2 14。\n请输入：";
		cin >> d.year >> d.month >> d.day;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (d.month > 12 || d.month < 1)
		{
			valid = false;
			cout << "月范围输入错误，请重新输入。" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if ((d.year % 100 != 0 && d.year % 4 == 0) || (d.year % 400 == 0))
			dayThisMonth[1] = 29;

		if (!((d.day <= dayThisMonth[d.month - 1]) && (d.day > 0)))
		{
			valid = false;
			cout << "日范围输入错误，请重新输入。" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

	} while (!valid);

	for (int i = 0; i < d.month - 1; i++)
	{
		dayNoLastMonthEnd += dayThisMonth[i];
	}

	dayNoLastMonthEnd += d.day;

	cout << "这天是这年的第 " << dayNoLastMonthEnd << " 天。" << endl;
	cout << endl;
	//goto REINPUT;
	return 0;
}
