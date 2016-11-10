/* 1652270 计算机2班 冯舜 */
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

	cout << "请依次输入待取最小值的整数个数和所有整数：";
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
				cout << "输入出现错误，请从第一个数开始再次写入" << endl;
			}
			else if (a1 <= 0 || a2 <= 0)
			{
				valid = false;
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "输入有非正整数，请从第一个数开始再次写入" << endl;
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
				cout << "输入出现错误，请从第一个数开始再次写入" << endl;
			}
			else if (a1 <= 0 || a2 <= 0 || a3 <= 0)
			{
				valid = false;
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "输入有非正整数，请从第一个数开始再次写入" << endl;
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
				cout << "输入出现错误，请从第一个数开始再次写入" << endl;
			}
			else if (a1 <= 0 || a2 <= 0 || a3 <= 0 || a4 <= 0)
			{
				valid = false;
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				cout << "输入有非正整数，请从第一个数开始再次写入" << endl;
			}

		} while (!valid);
		minResult = min(a1, a2, a3, a4);
		break;
	}
	cout << "最小值为： " << minResult << endl;

	return 0;
}
