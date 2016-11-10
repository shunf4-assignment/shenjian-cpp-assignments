/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

void truncate(int n, bool displaySpace = 1)
{
	if (n < 0)
	{
		cout << "-" << " ";
		n = -n;
	}
	if (n >= 10)
		truncate(n / 10);
	cout << (n % 10);
	if (displaySpace)
		cout << " ";
}

int main()
{
	int n;

	while (true)
	{
		cout << "快输入一个整数n：";
		cin >> n;

		if (!cin.good())
		{
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			break;
		}
	}

	truncate(n, 0);
	cout << endl;

	return 0;
}
