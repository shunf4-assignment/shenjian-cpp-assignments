/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include <iostream>
using namespace std;

int outer_function(int param)
{
	return param;
}

int main()
{
	int a[2][3] = { 1,2,3,4,5,6 };
	int b[4] = { 7,8,9,0 };
	int *p[2];
	p = &a[0];
	//cout << &(&b[4]) << endl;
	cout << sizeof(*a) << endl;
	return 0;
}
