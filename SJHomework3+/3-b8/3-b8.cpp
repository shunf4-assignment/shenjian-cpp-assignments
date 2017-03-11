#include <iostream>
using namespace std;

int main()
{
	int y, m, d;
	int dayNumOfThisMonth, dayNumFromNewYearDayToEndOfMonth, dayNumFromNewYearDayToToday;
	bool leapYear, inputValid;

	cout << "�������������գ��ÿո��������2014 2 14��\n�����룺";
	cin >> y >> m >> d;
	inputValid = true;

	if ((m > 12 || m < 1) || (d < 0 || d > 31))
		inputValid = false;
	else
	{
		leapYear = (y % 400 == 0 || y % 4 == 0 && y % 100 != 0);
		dayNumOfThisMonth = m % 2 + 30 + (m > 7)*(((m + 1) % 2) * 2 - 1);
		dayNumOfThisMonth = (m == 2) ? ((leapYear) ? (29) : (28)) : (dayNumOfThisMonth);

		if (d > dayNumOfThisMonth)
			inputValid = false;
	}

	if (inputValid) {
		dayNumFromNewYearDayToEndOfMonth = (int)(30.5 * (m - 1) + 0.5 * ((m - 1) % 2)) + ((m - 1) >= 2)*(-1 + -1 * !leapYear) + ((m - 1) >= 8) * (((m - 1) - 7) % 2);
		dayNumFromNewYearDayToToday = dayNumFromNewYearDayToEndOfMonth + d;
		cout << "����������ĵ� " << dayNumFromNewYearDayToToday << " �졣" << endl;
	}
	else
		cout << "�����������" << endl;

	cout << "�������н�����" << endl;
	return 0;
}