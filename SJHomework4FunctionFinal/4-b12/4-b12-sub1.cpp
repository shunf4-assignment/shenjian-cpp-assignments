/* 1652270 计算机2班 冯舜 */
#include "4-b12.h"  //要用个内联函数negativeZeroToZero，所以函数源文件也引用头文件

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
