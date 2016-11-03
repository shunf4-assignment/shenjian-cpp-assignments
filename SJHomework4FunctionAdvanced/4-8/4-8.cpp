/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

double legendre(int n, double x)
{
	if (n == 0)
	{
		return 1;
	}
	if (n == 1)
	{
		return x;
	}
	return ((2 * n - 1) * x * legendre(n - 1, x) - (n - 1) * legendre(n - 2, x)) / n;
}

int main()
{
	int n;
	bool valid;
	double x, result;

	do
	{
		valid = true;
		cout << "请分别输入n x的值，空格隔开：";
		cin >> n >> x;
		if (cin.rdstate() != ios_base::failbit) {
			valid = true;
		}
		else
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

		if (n <= 0)
			valid = false;
	} while (!valid);

	result = legendre(n, x);
	cout << "P_" << n << "(" << x << ") = " << result << endl;

	return 0;
}
