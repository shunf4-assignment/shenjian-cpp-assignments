/* 1652270 �����2�� ��˴ */
/*HYPERBejeweled_SJProject - 90-b1-base.cpp*/
#include <iostream>
using namespace std;

int outer_function(int param)
{
	return param;
}

int main()
{
	//REINPUT:
	int n;
	bool valid;

	do
	{
		valid = true;
		cout << "�����룺";
		cin >> n;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (n <= 0)
		{
			valid = false;
			cout << "���볬����Χ�����������롣" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

	} while (!valid);

	cout << outer_function(n);
	cout << endl;
	//goto REINPUT;
	return 0;
}
