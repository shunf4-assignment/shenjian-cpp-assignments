/* 1652270 计算机2班 冯舜 */
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
	cout << "请输入二进制：";
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
			cout << "不是有效二进制码。" << endl;
			return 2;
		}
		unit *= 2;
	}
	cout << "这个二进制码的十进制表示：" << val << endl;
	//goto REINPUT;
	return 0;
}
