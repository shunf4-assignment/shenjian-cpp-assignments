/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

int additionTerms(int i)
{

	if (i == 1)
		return 1;

	int unit = -1;
	if (i < 1)
		unit = 1;
	return additionTerms(i + unit) + i*i;
}

int main()
{
	int n;
	bool valid;

	do
	{
		valid = true;
		cout << "������һ������n��";
		cin >> n;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

		if (n <= 0)
		{
			valid = false;
			cout << "���볬����Χ�����������롣" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

	} while (!valid);

	cout << "Sum_i=1^n(i^2) = " << additionTerms(n);
	cout << endl;

	return 0;
}
