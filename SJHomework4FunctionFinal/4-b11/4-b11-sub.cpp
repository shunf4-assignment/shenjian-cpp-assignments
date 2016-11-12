/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>
using namespace std;

double negativeZeroToZero(double x)
{
	//将-0转成0，否则返回原来的数字
	return fabs(x) < 1e-8 ? 0 : x;
}

void linearEquation(double b, double c)
{
	cout << "这不是一个一元二次方程。" << endl;
	if (fabs(b) < 1e-8)
	{
		cout << "并且也不是一个一次方程。";
		if (fabs(c) >= 1e-8)
		{
			cout << "它没有根。" << endl;
		}
		else
		{
			cout << "所有实数均是它的根。" << endl;
		}
	}
	else
		cout << "但是仍可求出它的根为 x = " << negativeZeroToZero(-c / b) << endl;
}

void positiveDelta(double a, double b, double D)
{
	//两不等根
	double x1;
	double x2;
	x1 = (-b + sqrt(D)) / (2 * a);
	x2 = (-b - sqrt(D)) / (2 * a);

	cout << "方程存在两个不等实根。" << endl;
	cout << "x1 = " << negativeZeroToZero(x1) << endl;
	cout << "x2 = " << negativeZeroToZero(x2) << endl;
}

void zeroDelta(double a, double b)
{
	//两等根
	double x1;
	x1 = (-b) / (2 * a);

	cout << "方程存在两个相等实根。" << endl;
	cout << "x1 = x2 = " << negativeZeroToZero(x1) << endl;
}

void negativeDelta(double a, double b, double D)
{
	//两虚根
	double x1, im;
	D = 0 - D;

	x1 = (-b) / (2 * a);
	im = sqrt(D) / fabs(2 * a);

	cout << "方程存在两个虚根。" << endl;

	cout << "x1 = ";
	if (fabs(x1 - 0) >= 1e-8) {
		cout << x1 << " + ";
	}
	if (fabs(im - 1) >= 1e-8)
		cout << im << ' ';
	cout << "i" << endl;
	cout << "x2 = ";
	if (fabs(x1 - 0) >= 1e-8) {
		cout << x1 << " ";
	}
	cout << "- ";
	if (fabs(im - 1) >= 1e-8)
		cout << im << ' ';
	cout << "i" << endl;

}
