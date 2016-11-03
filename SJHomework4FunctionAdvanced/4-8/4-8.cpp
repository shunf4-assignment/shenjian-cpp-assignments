/* 1652270 �����2�� ��˴ */
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
	double x, result;

	do
	{
		cout << "��ֱ�����n x��ֵ���ո������";
		cin >> n >> x;
		if (cin.rdstate() != ios_base::failbit) {
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (1);

	result = legendre(n, x);
	cout << "P_" << n << "(" << x << ") = " << result << endl;

	return 0;
}
