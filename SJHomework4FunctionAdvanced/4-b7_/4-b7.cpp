/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

int is_power(int num, int base)
{
	if (num == 1)
		return 1;
	if (num % base != 0)
	{
		return 0;
	}
	else
	{
		return is_power(num / base, base);
	}
}

int main()
{
	//REINPUT:
	int n, b;
	bool valid;
	int powerNum = 0;

	do
	{
		valid = true;
		cout << "����������һ��ʮ�����������ʹ�����Ļ�����";
		cin >> n >> b;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

		if (n <= 0 || b <= 1)
		{
			valid = false;
			cout << "���볬����Χ�����������롣" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

	} while (!valid);

	powerNum = (is_power(n, b));

	cout << powerNum;
	cout << endl;
	//goto REINPUT;

	return 0;
}
