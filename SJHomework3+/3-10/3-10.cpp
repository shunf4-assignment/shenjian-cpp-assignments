/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;


int main()
{
	double y;
	double x;

	cout << "请输入 x = （实数）";
	cin >> x;

	if (x < 1)
	{
		y = x;
	}
	else if (x >= 10)
	{
		y = 3 * x - 11;
	}
	else
	{
		y = 2 * x - 1;
	}

	cout << "y = " << y << endl;

	return 0;
}