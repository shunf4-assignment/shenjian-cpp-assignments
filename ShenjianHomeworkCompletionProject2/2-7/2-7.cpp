/*1652270 计算机2班 冯舜*/
#include <iostream>
using namespace std;

int main()
{
	int i, j, m, n;
	i = 8;
	j = 10;
	m = ++i + j++; //19
	n = (++i) + (++j) + m;  //41
	cout << i << '\t' << m << '\t' << n << endl;  //10 19 41
	return 0;
}

/*
程序功能：
将8的值赋给i，10赋给j。
进行一些表达式的运算，改变了i和j的值，并且将表达式的值赋给m和n。
最后输出i,m,n的值，用制表符隔开，并且换行。
输出：
10	19	41

*/