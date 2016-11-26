/* 1652270 计算机2班 冯舜 */
#include "4-b12.h"  //要用个内联函数negativeZeroToZero，所以函数源文件也引用头文件

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

