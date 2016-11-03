/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

//int COUNT = 0;

int Fibonacci(int n)
{
	//COUNT += 1;
	if (n == 1)
		return 1;
	if (n == 2)
		return 1;
	if (n <= 0)
		return 0;
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main()
{
	int n;
	bool valid;

	do
	{
		valid = true;
		cout << "请输入你需要斐波那契数列的第几项：";
		cin >> n;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

		if (n < 0)
			valid = false;

	} while (!valid);

	cout << Fibonacci(n);
	cout << endl;
	//cout << COUNT << endl;

	return 0;
}
