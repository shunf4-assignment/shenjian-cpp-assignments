/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;


int main()
{
	int i, j;
	double bonus = 0;

	cout << "请输入当月利润 i = (元)";
	cin >> i;

	j = i / 100000;

	switch (j)
	{
		case 0:
			bonus = i * 0.1;
			break;
		case 1:
			bonus = 100000 * 0.1 + (i - 100000) * 0.075;
			break;
		case 2:
		case 3:
			bonus = 100000 * 0.1 + 100000 * 0.075 + (i - 200000) * 0.05;
			break;
		case 4:
		case 5:
			bonus = 100000 * 0.1 + 100000 * 0.075 + 200000 * 0.05 + (i - 400000) * 0.03;
			break;
		case 6:
		case 7:
		case 8:
		case 9:
			bonus = 100000 * 0.1 + 100000 * 0.075 + 200000 * 0.05 + 200000 * 0.03 + (i - 600000) * 0.015;
			break;
		default:
			bonus = 100000 * 0.1 + 100000 * 0.075 + 200000 * 0.05 + 200000 * 0.03 + 400000 * 0.015 + (i - 1000000) * 0.01;
			break;
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