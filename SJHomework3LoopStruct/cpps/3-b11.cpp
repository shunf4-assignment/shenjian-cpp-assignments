/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>
#include <iomanip>
#include <windows.h>

using namespace std;

//此程序在计算负数的时候精度很差，负数绝对值越大越不精确
int main()
{
	double x, loopVar, loopTerm, sum; //loopVar表示循环次数，也作为loopTerm循环乘x/loopVar的因数；loopTerm是e^x泰勒展开中的第loopVar+1项
	long t1, t2; //开始时候运行时间

	cout << "输入要计算e^x的自变量 x = ";
	cin >> x;

	loopVar = 0;
	loopTerm = 1;
	sum = 0;

	//开始计时
	t1 = GetTickCount();
	while (fabs(loopTerm) >= 1e-5)
	{
		sum += loopTerm;
		//cout << loopTerm << endl;
		loopVar += 1;
		loopTerm = loopTerm * x / loopVar;
	}

	//结束计时
	t2 = GetTickCount();

	cout << "e^x = " << setiosflags(ios::fixed) << setprecision (15) << sum << endl;

	//cout << t1 << " " << t2;
	//cout << "运行用时" << setprecision(12) << (t2 - t1) / 1000. << "秒。";
	
	return 0;
}