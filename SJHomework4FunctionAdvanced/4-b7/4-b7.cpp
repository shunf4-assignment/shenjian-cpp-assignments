/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

//n作为一个计数器，可以表示 幂次 + 1 ，当不是幂的时候返回0，当两数相等时返回1表示1-1=0次幂。
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
		cout << "请依次输入一个十进制正整数和待计算的基数：";
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
			cout << "输入超出范围，请重新输入。" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

	} while (!valid);

	powerNum = (is_power(n, b));

	cout << n;
	cout << (powerNum ? " 是 " : " 不是 ");
	cout << b;
	cout << " 的";
	if (powerNum)
	{
		cout << " ";
		cout << powerNum - 1;
		cout << " 次";
	}
	cout << "幂";

	cout << endl;
	//goto REINPUT;

	return 0;
}
