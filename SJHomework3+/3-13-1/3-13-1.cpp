/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>
using namespace std;


int main()
{
	int i;
	double bonus = 0;

	cout << "请输入当月利润 i = (元)";
	cin >> i;

	if (i >= 0)
	{
		if (i <= 100000)
		{
			bonus = i * 0.1;
		}
		else if (i <= 200000)
		{
			bonus = 100000 * 0.1 + (i - 100000) * 0.075;
		}
		else if (i <= 400000)
		{
			bonus = 100000 * 0.1 + 100000 * 0.075 +(i - 200000) * 0.05;
		}
		else if (i <= 600000)
		{
			bonus = 100000 * 0.1 + 100000 * 0.075 + 200000 * 0.05 + (i - 400000) * 0.03;
		}
		else if (i <= 1000000)
		{
			bonus = 100000 * 0.1 + 100000 * 0.075 + 200000 * 0.05 + 200000 * 0.03 + (i - 600000) * 0.015;
		}
		else if (i > 1000000)
		{
			bonus = 100000 * 0.1 + 100000 * 0.075 + 200000 * 0.05 + 200000 * 0.03 + 400000 * 0.015 + (i - 1000000) * 0.01;
		}
	}
	else
	{
		bonus = -1;
	}

	if (fabs(bonus + 1) > 1e-6)
	{
		cout << "应发奖金： " << bonus << " 元。" << endl;
	}
	else
	{
		cout << "你的输入错误。" << endl;
	}
	cout << "程序结束。" << endl;
	return 0;
}