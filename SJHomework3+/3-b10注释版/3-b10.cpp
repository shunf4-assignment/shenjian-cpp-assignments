/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;
#define out0 cout << "零"
#define nout cout << ""
#define outthis (toOut == 1) ? (cout << "壹") : (nout),(toOut == 2) ? (cout << "贰") : (nout),(toOut == 3) ? (cout << "叁") : (nout),(toOut == 4) ? (cout << "肆") : (nout),(toOut == 5) ? (cout << "伍") : (nout),(toOut == 6) ? (cout << "陆") : (nout),(toOut == 7) ? (cout << "柒") : (nout),(toOut == 8) ? (cout << "捌") : (nout),(toOut == 9) ? (cout << "玖") : (nout),(toOut == 0) ? (cout << "零") : (nout)
/*
描述一下 outthis 的代码逻辑
将toOut赋值为某个个位数的话，执行outthis，就可以输出相应大写。
outthis有十个子表达式，分别用逗号隔开。每个语句形如(toOut == 1) ? (cout << "壹") : (nout)，很容易看懂，其中nout表示 cout << ""，表示什么都不输出。
*/

#define groupOutput ((!p1) ? ((!zeroPut && (p2 + p3 + p4)) ? (zeroPut = true, out0, z) : z) : (toOut = p1, outthis, cout << "仟", zeroPut = false, z), ((!p2) ? ((!zeroPut && (p3 + p4)) ? (zeroPut = true, out0, z) : z) : (toOut = p2, outthis, cout << "佰", zeroPut = false, z)), ((!p3) ? ((!zeroPut && (p4)) ? (zeroPut = true, out0, z) : z) : (toOut = p3, outthis, cout << "拾", zeroPut = false, z)), ((!p4) ? (z) : (toOut = p4, outthis, zeroPut = false, z)))
/*
描述一下 groupOutput 的代码逻辑

这段表达式的主要作用是将四位成组的数字 p1 p2 p3 p4 按照 X千X百…… 的格式输出。

z是一个为0的布尔值，用途是放在三目运算符 boolean1 ? () : () 里没有操作的地方充数，简单来说就是什么都不干。
zeroPut是用来指示“零”是否在以前就已经输出过的开关，可以用来防止重复输出零。


开始：对于p1, 先检查是否可以输出零。最开始的分支结构是(!p1)，若p1为零则进行接下来的步骤2,3，否则从步骤4开始。
2. 进一步检查可以输出零的条件(!zeroPut && (p2 + p3 + p4))：zeroPut开关关闭，且p2 p3 p4不全为零 （若是全为零，就相当于[0]000，可以省略零）
3. 2为真，则进行输出零的操作。这个时候要将zeroPut开关置于true，表示从这一位开始输出零. 对于p1的所有输出结束。
步骤4：若p1不为0，则需要对p1进行输出。先将toOut（里面放置即将输出的数字）的值定为p1的值。然后执行outthis操作（见上），是千百十位的要相应输出千百十。还要将zeroPut开关置于false，表明从这一位开始不再输出零. 对于p1的所有输出结束。

对于p2, p3, p4：与p1相同的流程，除了在检查输出零的条件中，p2 p3 p4改成比该位低的所有位即可（低位全为零，相当于01[0]0，零一百[零] 的[零] 可以省略）
*/

int main()
{
	double inputNum, inputNumCopy;
	int d10, d9, d8, d7, d6, d5, d4, d3, d2, d1, dm1, dm2, p1, p2, p3, p4, toOut;
	bool zeroPut = true, z = 0, hasYuan = false;  //zeroPut的初始值置为true是因为避免出现 “零十亿”

	cout << "请输入待转换的金额数：(0.01到100亿) ";
	cin >> inputNum;
	inputNumCopy = inputNum;

	(((((((((inputNumCopy -= (d10 = (int)(inputNumCopy / 1e9)) * 1e9) -= (d9 = (int)(inputNumCopy / 1e8)) * 1e8) -= (d8 = (int)(inputNumCopy / 1e7)) * 1e7) -= (d7 = (int)(inputNumCopy / 1e6)) * 1e6) -= (d6 = (int)(inputNumCopy / 1e5)) * 1e5) -= (d5 = (int)(inputNumCopy / 1e4)) * 1e4) -= (d4 = (int)(inputNumCopy / 1e3)) * 1e3) -= (d3 = (int)(inputNumCopy / 1e2)) * 1e2) -= (d2 = (int)(inputNumCopy / 1e1)) * 1e1) -= (d1 = (int)(inputNumCopy));  //整数部分

	inputNumCopy = (int)(inputNumCopy * 100 + 0.5);  //小数部分
	(inputNumCopy -= (dm1 = (int)(inputNumCopy / 10)) * 10) -= (dm2 = (int)(inputNumCopy));

	cout << "分解结果：" << endl;
	cout << "\t十亿位： " << d10 << endl;
	cout << "\t  亿位： " << d9 << endl;
	cout << "\t千万位： " << d8 << endl;
	cout << "\t百万位： " << d7 << endl;
	cout << "\t十万位： " << d6 << endl;
	cout << "\t  万位： " << d5 << endl;
	cout << "\t  千位： " << d4 << endl;
	cout << "\t  百位： " << d3 << endl;
	cout << "\t  十位： " << d2 << endl;
	cout << "\t  个位： " << d1 << endl;
	cout << "\t十分位： " << dm1 << endl;
	cout << "\t百分位： " << dm2 << endl;

	cout << "大写：";

	hasYuan = !!(d10 + d9 + d8 + d7 + d6 + d5 + d4 + d3 + d2 + d1);
	p1 = 0, p2 = 0, p3 = d10, p4 = d9, groupOutput, (p1 + p2 + p3 + p4) && (cout << "亿");  //用&&相当于用if，因为短路运算
	p1 = d8, p2 = d7, p3 = d6, p4 = d5, groupOutput, (p1 + p2 + p3 + p4) && (cout << "万");
	p1 = d4, p2 = d3, p3 = d2, p4 = d1, groupOutput, hasYuan && (cout << "圆");

	(!dm1) ? ((hasYuan && dm2) ? (out0) : (nout)) : (toOut = dm1, outthis, cout << "角"), (!dm2) ? (!!(inputNum) && (cout << "整"), z) : (toOut = dm2, outthis, cout << "分", z);

	(!(inputNum)) && (cout << "零圆整");

	cout << endl;
	cout << "程序运行结束。" << endl;

	return 0;
}