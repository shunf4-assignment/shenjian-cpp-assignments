/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

int fac(int n)
{
	if (n == 0 || n == 1)
		return 1;
	if (n < 0)
		return INT_MAX;
	return fac(n - 1) * n;
}

int main()
{
	int a, b, c, result;
	bool valid;

	do
	{
		valid = true;
		cout << "��ֱ�����a b c��ֵ���ո������";
		cin >> a >> b >> c;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

		if (a < 0 || b < 0 || c < 0)
			valid = false;
	} while (!valid);


	result = fac(a) + fac(b) + fac(c);
	cout << "a! + b! + c! = " << result << endl;

	return 0;
}
