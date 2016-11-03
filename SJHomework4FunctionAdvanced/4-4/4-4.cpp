/* 1652270 计算机2班 冯舜 */
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

	do
	{
		cout << "请分别输入a b c的值，空格隔开：";
		cin >> a >> b >> c;
		if (cin.rdstate() != ios_base::failbit) {
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
	} while (1);

	result = fac(a) + fac(b) + fac(c);
	cout << "a! + b! + c! = " << result << endl;

	return 0;
}
