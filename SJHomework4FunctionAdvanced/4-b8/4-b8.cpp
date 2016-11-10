/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

int max(int a, int b)
{
	int maxValue = a;
	if (maxValue < b)
		maxValue = b;
	return maxValue;
}

int max(int a, int b, int c)
{
	int maxValue = a;
	if (maxValue < b)
		maxValue = b;
	if (maxValue < c)
		maxValue = c;
	return maxValue;
}

int max(int a, int b, int c, int d)
{
	int maxValue = a;
	if (maxValue < b)
		maxValue = b;
	if (maxValue < c)
		maxValue = c;
	if (maxValue < d)
		maxValue = d;
	return maxValue;
}

int main()
{
	int paraNum, a1 = 1, a2 = 1, a3 = 1, a4 = 1, maxResult;
	bool valid;

	do
	{
		a1 = 1, a2 = 1, a3 = 1, a4 = 1;
		valid = true;
		cout << "�����������ȡ���ֵ����������������������";
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

		valid = true;
		switch (paraNum)
		{
		case 2:
			cin >> a1 >> a2;
			break;
		case 3:
			cin >> a1 >> a2 >> a3;
			break;
		case 4:
			cin >> a1 >> a2 >> a3 >> a4;
			break;
		}

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "������ִ��������¿�ʼ��������" << endl;
			continue;
		}
		else if (a1 <= 0 || a2 <= 0 || a3 <= 0 || a4 <= 0)
		{
			valid = false;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "�����з��������������¿�ʼ��������" << endl;
			continue;
		}
	} while (!valid);

	switch (paraNum)
	{
		case 2:
			maxResult = max(a1, a2);
			break;
		case 3:
			maxResult = max(a1, a2, a3);
			break;
		case 4:
			maxResult = max(a1, a2, a3, a4);
			break;
	}

	cout << "���ֵΪ�� " << maxResult << endl;

	return 0;
}
