/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

static double doubleStaticGlobal = 3.14;

int fun(int x)
{
	static int intStatic = 7;
	int y;
	intStatic++;
	y = x + intStatic;
	return y;
}

int main()
{
	
	return 0;
}
