/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include <iostream>
using namespace std;

void l(int * p)
{
	p[0] = 5;
}

int main()
{
	//REINPUT:
	const char y[5] = { 'a','b' };
	char *p = (char *)y;
	*p = 'c';
	cout << y[0];
	//goto REINPUT;
	return 0;
}
