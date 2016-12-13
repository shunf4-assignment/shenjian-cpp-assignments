/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include <iostream>
using namespace std;

int outer_function(int param)
{
	return param;
}

int main()
{
	char *p = "8910";
	*(p + 1) = 'A';
	cout << *(p) << endl;
	return 0;
}