/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <cmath>  //���ڳ���Ҫ�õ���ѧ����sqrt����Ӧ����ͷ�ļ�cmath
using namespace std;

int zeller(int year, int month, int day)
{
	int c, w;
	(month < 3) && (year = year - 1, month = month + 12);
	c = year / 100, year = year % 100;
	w = year + year / 4 + c / 4 - 2 * c + 13 * (month + 1) / 5 + day - 1;
	return (w % 7);
}


int main()
{
	int y, m, d;
	while (1) {
		cout << "������������ �� �գ��ո������";
		cin >> y >> m >> d;

		if (!(cin.rdstate() != ios_base::failbit))
		{
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		

	}
	cout << zeller(y, m, d) << endl;
	return 0;
}