/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

//n��Ϊһ�������������Ա�ʾ �ݴ� + 1 ���������ݵ�ʱ�򷵻�0�����������ʱ����1��ʾ1-1=0���ݡ�
int is_power(int num, int base, int n = 1)
{
	if (num == 1)
		return n;
	if (num % base != 0)
	{
		return 0;
	}
	else
	{
		return is_power(num / base, base, n + 1);
	}
}

int main()
{
//REINPUT:
	int n, b;
	bool valid;
	int powerNum = 0;

	do
	{
		valid = true;
		cout << "����������һ��ʮ�����������ʹ�����Ļ�����";
		cin >> n >> b;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

		if (n <= 0 || b <= 1)
		{
			valid = false;
			cout << "���볬����Χ�����������롣" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

	} while (!valid);

	powerNum = (is_power(n, b));

	cout << n;
	cout << (powerNum ? " �� " : " ���� ");
	cout << b;
	cout << " ��";
	if (powerNum)
	{
		cout << " ";
		cout << powerNum - 1;
		cout << " ��";
	}
	cout << "��";

	cout << endl;
	//goto REINPUT;

	return 0;
}
