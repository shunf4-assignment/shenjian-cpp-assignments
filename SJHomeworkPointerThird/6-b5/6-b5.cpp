/* 1652270 �����2�� ��˴ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
using namespace std;
#define FS_LEN 32

int main()
{
	//REINPUT:
	char bin[FS_LEN],*end;
	int val = 0, len, unit = 1;
	cout << "����������ƣ�";
	cin >> bin;
	len = strlen(bin);
	end = bin + len - 1;
	for (; end >= bin ;end--)
	{
		if (*end == '1')
		{
			val += unit;
		}
		else if (*end == '0')
		{
			;
		}
		else
		{
			cout << "������Ч�������롣" << endl;
			return 2;
		}
		unit *= 2;
	}
	cout << "������������ʮ���Ʊ�ʾ��" << val << endl;
	//goto REINPUT;
	return 0;
}
