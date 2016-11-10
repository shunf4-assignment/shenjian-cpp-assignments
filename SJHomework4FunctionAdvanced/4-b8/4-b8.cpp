/* 1652270 计算机2班 冯舜 */
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
		cout << "请依次输入待取最大值的整数个数和所有整数：";
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
			cout << "输入出现错误，请重新开始所有输入" << endl;
			continue;
		}
		else if (a1 <= 0 || a2 <= 0 || a3 <= 0 || a4 <= 0)
		{
			valid = false;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			cout << "输入有非正整数，请重新开始所有输入" << endl;
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

	cout << "最大值为： " << maxResult << endl;

	return 0;
}
