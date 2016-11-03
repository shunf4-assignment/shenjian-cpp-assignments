/* 1652270 �����2�� ��˴ */
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
		cout << "������������ �� �գ��ո������";
		cin >> y >> m >> d;

		if (!(cin.rdstate() != ios_base::failbit))
		{
			cout << "����Ƿ������������롣" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		valid = true;
		if (y < 1900 || y > 2100)
		{
			cout << "��ݷǷ�������������" << endl;
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
				dayForThisMonth -= !leapYear;  //ʹ���µ�����������29��28
			}
			else
			{
				cout << "�·ݷǷ������������롣" << endl;
				valid = false;
			}
		}
		if (valid)
		{
			if (d > 0 && d <= dayForThisMonth)
				break;
			else
			{
				cout << "���ڷǷ������������롣" << endl;
				valid = false;
			}
		}
	}
	week = zeller(y, m, d);
	cout << y << " �� " << m << " �� " << d << " ���ǣ�";
	//cout << week;
	switch (week)
	{
		case(0):
			cout << "������";
			break;
		case(1):
			cout << "����һ";
			break;
		case(2):
			cout << "���ڶ�";
			break;
		case(3):
			cout << "������";
			break;
		case(4):
			cout << "������";
			break;
		case(5):
			cout << "������";
			break;
		case(6):
			cout << "������";
			break;
	}
	cout << "��" << endl;
	//goto REINPUT;

	return 0;
}