/*1652270 计算机2班 冯舜*/
#include <iostream>
using namespace std;

char encrypt(char s1, int offset)
{
	char firstLetter;
	if (s1 >= 65 && s1 <= (65 + 25))
	{
		//大写字母
		firstLetter = 65;
	}
	else if (s1 >= 97 && s1 <= (97 + 25))
	{
		//小写字母
		firstLetter = 97;
	}
	else
	{
		return '?';
	}
	return ((s1 - firstLetter) + offset + 26) % 26 + firstLetter;
}

int main()
{
	char c1 = 'C', c2 = 'h', c3 = 'i', c4 = 'n', c5 = 'a';
	c1 = encrypt(c1, 4);
	c2 = encrypt(c2, 4);
	c3 = encrypt(c3, 4);
	c4 = encrypt(c4, 4);
	c5 = encrypt(c5, 4);
	cout << c1 << c2 << c3 << c4 << c5 << endl;
	return 0;
}

/*
程序功能：
声明5个char型变量，分别赋值为C,h,i,n,a，再调用encrypt函数对其进行凯撒加密。最后依次输出c1到c5，
展示加密结果为Glmre。
*/