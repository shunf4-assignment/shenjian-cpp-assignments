/* 1652270 计算机2班 冯舜 */
#include "4-b12.h"  //要用个内联函数negativeZeroToZero，所以函数源文件也引用头文件

void zeroDelta(double a, double b)
{
	//两等根
	double x1;
	x1 = (-b) / (2 * a);

	cout << "方程存在两个相等实根。" << endl;
	cout << "x1 = x2 = " << negativeZeroToZero(x1) << endl;
}