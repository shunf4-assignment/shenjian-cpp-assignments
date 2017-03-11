/* 1652270 计算机2班 冯舜 */
/* 2016/09/22 07:06 Created */
/* 2016/09/22 10:30 Modified */
#include <iostream>
using namespace std;

int main()
{
	int a, b, c;  //int a, b;
	int add(int x, int y);  //新增
	cin >> a >> b;  //新增
	c = add(a, b);  //c = add(a, b)
	cout << "a+b=" << c << endl;
	return 0;
}

int add(int x, int y)  //int add(int x, int y);
{
	int z;  //新增
	z = x + y;
	return (z);
}

/*
程序错因：
1、 int add(int x, int y)句后多加了分号，致使函数定义提前结束，后面的大括号内语句失去意义，同时编译报错“缺少函数标题”；
2、未首先声明c的类型而直接将add(a,b)赋值给c，会出现错误“未声明的标识符”；
3、计算add(a, b)时a和b的值尚未定义，将导致执行add函数的时候“找不到标识符”；
4、add(a, b)明显是一句语句，但它的末尾没有分号；
5、add函数中没有声明z的类型而直接进行执行部分，将导致z成为“未声明的标识符”
6、在执行main函数的时候，add并未定义，故执行add(a,b)时提示“未找到标识符”（似乎只有C++会出现这个问题而C不会）
	解决办法1: 在main函数的局部声明部分增加int add(int x, int y); （本程序是如此修改的）
	解决办法2：直接将add函数的定义提前到main函数之前。

	具体信息：http://bbs.csdn.net/topics/380031633

程序功能：
该程序实现接受两个整形输入a,b并输出其和c。
*/