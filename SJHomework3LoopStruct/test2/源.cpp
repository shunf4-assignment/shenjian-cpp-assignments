/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <windows.h> //取系统时间
using namespace std;


int main()
{
	LARGE_INTEGER tick, fc_begin, fc_end;

	QueryPerformanceFrequency(&tick);	//获得时钟频率
	QueryPerformanceCounter(&fc_begin);	//获得初始硬件定时器计数

	/* 此处是你的程序开始 */
	double a, b, c;
	a = -6, b = 0;
	c = a / 0;
	cout << c << endl;
	/* 此处是你的程序结束 */

	QueryPerformanceCounter(&fc_end);//获得终止硬件定时器计数
	cout << setiosflags(ios::fixed) << setprecision(3);
	cout << "时钟频率：" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
	cout << setprecision(0);
	cout << "时钟计数：" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
	cout << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "秒" << endl;

	return 0;
}