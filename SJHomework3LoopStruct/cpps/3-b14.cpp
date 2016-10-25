/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int y, m, dayForThisMonth, leapYear, w, weekLoop, dayLoop;
	bool valid;
	valid = false;  //��ֵ��Ϊfalse����Ϊ������һ������ѭ��

	while (!valid)
	{
		cout << "������������(2000-2030)���·�(1-12)���ո������";
		cin >> y >> m;


		valid = true;
		if (y < 2000 || y > 2030)
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
	}

	valid = false;
	while (!valid)
	{
		cout << "��������µ�һ������ڣ�0-6������0��ʾ�����죩" << endl;
		cin >> w;
		valid = true;
		if (w < 0 || w > 6)
		{
			cout << "������д��Ч����������д" << endl;
			valid = false;
		}
	}

	cout << "���µ��������£�" << endl;
	cout << "��  һ  ��  ��  ��  ��  ��" << endl;

	dayLoop = 1 - w;  //��һ�첻�����յ�ʱ��Ҫ����ո���ô��ѭ������Ҫ��Ӧ������Ҫ����ո�ı�־��ΪdayLoop������
	weekLoop = 0;  //��ѭ���м�¼��ǰ������ڣ���հף���Ӧ������

	while (dayLoop <= dayForThisMonth)
	{
		if (weekLoop != 0)
			cout << "  ";
		if (dayLoop > 0)
		{
			cout << setw(2) << dayLoop;
		}
		else
		{
			cout << "  ";
		}

		if (weekLoop == 6)
			cout << endl;
		
		weekLoop = (weekLoop + 1) % 7;
		dayLoop += 1;
	}
	cout << endl;
	
	return 0;
}