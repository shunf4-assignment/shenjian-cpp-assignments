/* 1652270 �����2�� ��˴ */
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
		cout << "����������Ҫ쳲��������еĵڼ��";
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
