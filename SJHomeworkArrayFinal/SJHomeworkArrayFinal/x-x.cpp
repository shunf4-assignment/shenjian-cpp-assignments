/* 1652270 �����2�� ��˴ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int main()
{
	char *s = (char *)malloc(sizeof(char) * 1000);
	cout << s << endl;
	free(s);
	return 0;
}