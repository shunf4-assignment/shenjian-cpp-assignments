/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>
using namespace std;


int main()
{
	double x, y;
	short h;
	cout << "请依次输入坐标上点的x,y坐标，接受实数。x和y用空格隔开，或用回车隔开依次输入。" << endl;
	cout << "请输入： (如3 2)";
	cin >> x >> y;

	h = 0;
	if (fabs(x*y - 0) < 1e-8)
	{
		//落在了坐标轴上
		;
	}
	else
	{
		if (x > 0 && y > 0 && x + y <= 3)
		{
			h = 1;
		}
		else if (x < 0 && y > 0 && -x + y <= 3)
		{
			h = 2;
		}
		else if (x < 0 && y < 0 && -x + -y <= 3)
		{
			h = 3;
		}
		else if (x > 0 && y < 0 && x + -y <= 3)
		{
			h = 4;
		}
	}
	cout << "该点的高度值为： h = " << h << endl;
	return 0;
}