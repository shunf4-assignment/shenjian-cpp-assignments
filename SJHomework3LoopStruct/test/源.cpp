/*1652325 3班 张一鸣*/
#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std;
int main()
{
	srand(unsigned int(time(0)));
	int x, a = 1;
	double y, z = 0.0, d;
	cout << "输入人数" << endl;
	cin >> x;
	cout << "输入金额" << endl;
	cin >> y;
	y = (y + 0.001) * 100;//将y换成整数，扩大100倍

	start:
	d = y;
	a = 1;
	z = 0.0;
	while (a <= x) {
		z = (rand()*rand() / (32767.0*32767.0))*y;//获取随机数z
		while ((double)d<(1.5)*z) z = (rand()*rand() / (32767.0*32767.0))*y;//确定z的范围，不想让z过大
		if (z < 1) z = 1;//这里的z是输出时的100倍
		else if (d - z < x - a)z = d - x + a;
		if (a == x&&z < d) z = d;
		cout << "第" << a << "个红包的钱数" << ":";
		cout << setiosflags(ios::fixed) << setprecision(2) << (double)z / 100 << endl;
		d -= z;
		a++;
	}
	system("pause");
	goto start;
	return 0;
}