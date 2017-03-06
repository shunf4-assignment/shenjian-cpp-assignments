/* 1652270 �����2�� ��˴ */
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
		cout << "�������������գ��ÿո��������2014 2 14��\n�����룺";
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
			cout << "�·�Χ����������������롣" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if ((d.year % 100 != 0 && d.year % 4 == 0) || (d.year % 400 == 0))
			dayThisMonth[1] = 29;

		if (!((d.day <= dayThisMonth[d.month - 1]) && (d.day > 0)))
		{
			valid = false;
			cout << "�շ�Χ����������������롣" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

	} while (!valid);

	for (int i = 0; i < d.month - 1; i++)
	{
		dayNoLastMonthEnd += dayThisMonth[i];
	}

	dayNoLastMonthEnd += d.day;

	cout << "����������ĵ� " << dayNoLastMonthEnd << " �졣" << endl;
	cout << endl;
	//goto REINPUT;
	return 0;
}
