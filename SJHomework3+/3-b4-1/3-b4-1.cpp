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

	h = ((x > 0 && y > 0) + 2 * (x < 0 && y > 0) + 3 * (x < 0 && y < 0) + 4 * (x > 0 && y < 0)) * !!(x*y) * (fabs(x) + fabs(y) <= 3);
	
	cout << "该点的高度值为： h = " << h << endl;
	return 0;
}