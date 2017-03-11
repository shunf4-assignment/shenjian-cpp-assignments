/*1652270 计算机2班 冯舜*/
#include <iostream>
using namespace std;

int main()
{
	char c1 = 'a', c2 = 'b', c3 = 'c', c4 = '\101', c5 = '\116';
	cout << c1 << c2 << c3 << '\n';
	cout << "\t\b" << c4 << '\t' << c5 << '\n';
	return 0;
}

/*
程序功能：
先依次输出字符a,b,c，并且换行
再输出一个水平制表符，但再向后退一列，输出A；之后再输出一个水平制表符，输出N，换行。
*/