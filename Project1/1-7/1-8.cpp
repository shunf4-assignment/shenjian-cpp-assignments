/* 1652270 计算机2班 冯舜 */
/* 2016/09/21 22:41 Created */
/* 2016/09/22 06:59 Modified */
#include <iostream>  //新增
using namespace std;  //新增

int main()   //int main();
{
	int a, b, c;  //int a,b;
	cin >> a >> b;  //新增
	c = a + b;
	cout << "a+b=" << c;  //cout >> "a+b=" >> a + b;
}

/* 
程序错因：
1、 int main()句后多加了分号，致使函数定义提前结束，后面的大括号内语句失去意义，同时编译报错“缺少函数标题”；
2、未首先定义c的类型而直接将a+b赋值给c，会出现错误“未声明的标识符”；
3、没有“包含指令”，即没有#include <iostream> 语句，将导致cout被识别为“未声明的标识符”；而要使用这“包含指令”，又应该搭配using namespace std;，原程序均缺乏。
4、计算a+b时a和b的值尚未定义；
5、cout若是用作输出，其不等号方向反了

程序功能：
该程序实现接受两个整形输入a,b并输出其和c。
*/