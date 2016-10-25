/* 班级 学号 姓名 */
#include <iostream>
#include <stdlib.h>	//srand/rand函数
#include <time.h>	//time函数
using namespace std;
int main()
{
	int i;
	double x,s=0,offset;
	double a,b,c;
	srand((unsigned int)time(0));
	for (i = 0; i < 10000; i++)
	{
		a = (rand()+0.000001)*1. / 32767;
		b = (rand() + 0.000001)*1. / 32767;
		x = sqrt(-2 * log(a))*cos(2*3.14159*b);
		s = s + x;
		//cout << x << endl;
	}
	cout << s << endl;

	return 0;
}