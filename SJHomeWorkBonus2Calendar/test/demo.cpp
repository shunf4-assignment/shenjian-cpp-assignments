/* 1652270 �����2�� ��˴ */
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