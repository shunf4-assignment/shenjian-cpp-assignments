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

		if (n <= 0 || b <= 0)
			valid = false;

	} while (!valid);

	cout << (is_power(n, b));
	cout << endl;
	//goto REINPUT;

	return 0;
}
