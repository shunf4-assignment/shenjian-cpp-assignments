/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

int min(int a, int b, int c = -1, int d = -1)
{
	int minValue = a;
	if (minValue > b)
		minValue = b;
	if (minValue > c && c > 0)
		minValue = c;
	if (minValue > d && d > 0)
		minValue = d;
	return minValue;
}

int main()
{
	int paraNum, a1, a2, a3, a4, minResult;
	bool valid;

	cout << "�����������ȡ��Сֵ����������������������";
	cin >> paraNum;

	if (!cin.good())
	{
		valid = false;
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		return -1;
	}
	if (paraNum < 2 || paraNum > 4)
		return -1;

	switch (paraNum)
	{
	case 2:
		do
		{
			valid = true;
			cin >> a1 >> a2;
			if (!cin.good())
			{
				valid = false;
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "������ִ�����ӵ�һ������ʼ�ٴ�д��" << endl;
			}
			else if (a1 <= 0 || a2 <= 0)
			{
				valid = false;
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "�����з�����������ӵ�һ������ʼ�ٴ�д��" << endl;
			}

		} while (!valid);
		minResult = min(a1, a2);
		break;
	case 3:
		do
		{
			valid = true;
			cin >> a1 >> a2 >> a3;
			if (!cin.good())
			{
				valid = false;
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "������ִ�����ӵ�һ������ʼ�ٴ�д��" << endl;
			}
			else if (a1 <= 0 || a2 <= 0 || a3 <= 0)
			{
				valid = false;
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "�����з�����������ӵ�һ������ʼ�ٴ�д��" << endl;
			}

		} while (!valid);
		minResult = min(a1, a2, a3);
		break;
	case 4:
		do
		{
			valid = true;
			cin >> a1 >> a2 >> a3 >> a4;
			if (!cin.good())
			{
				valid = false;
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "������ִ�����ӵ�һ������ʼ�ٴ�д��" << endl;
			}
			else if (a1 <= 0 || a2 <= 0 || a3 <= 0 || a4 <= 0)
			{
				valid = false;
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "�����з�����������ӵ�һ������ʼ�ٴ�д��" << endl;
			}

		} while (!valid);
		minResult = min(a1, a2, a3, a4);
		break;
	}
	cout << "��СֵΪ�� " << minResult << endl;

	return 0;
}
