/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

void truncateReversed(int n)
{
	cout << abs(n % 10);

	if (abs(n) >= 10)
	{
		cout << " ";
		truncateReversed(n / 10);
	}
	else if (n < 0)
		cout << " -";
}

int main()
{
	int n;
	bool valid;

	do
	{
		valid = true;
		cout << "�Ͽ�����һ������n��";
		cin >> n;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		
	} while (!valid);

	truncateReversed(n);
	cout << endl;

	return 0;
}
