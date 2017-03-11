/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

bool leapYear(int year)
{
	return (year % 100 != 0 && year % 4 == 0) || (year % 400 == 0);
}

bool dayInLimit(int m, int d, int dayThisMonth[])
{
	
	return (d <= dayThisMonth[m - 1]) && (d > 0);
}

int dayNoThisYear(int m, int d, int dayThisMonth[])
{
	int dayNoLastMonthEnd = 0;
	for (int i = 0; i < m - 1; i++)
	{
		dayNoLastMonthEnd += dayThisMonth[i];
	}
	return dayNoLastMonthEnd + d;
}



int main()
{
	//REINPUT:

	int y,m,d;
	int dayThisMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	bool valid;

	do
	{
		valid = true;
		cout << "�������������գ��ÿո��������2014 2 14��\n�����룺";
		cin >> y >> m >> d;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (m > 12 || m < 1)
		{
			valid = false;
			cout << "�·�Χ����������������롣" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (leapYear(y))
			dayThisMonth[1] = 29;

		if (!dayInLimit(m, d, dayThisMonth))
		{
			valid = false;
			cout << "�շ�Χ����������������롣" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

	} while (!valid);

	cout << "����������ĵ� " << dayNoThisYear(m,d,dayThisMonth) << " �졣" << endl;
	cout << endl;
	//goto REINPUT;
	return 0;
}
