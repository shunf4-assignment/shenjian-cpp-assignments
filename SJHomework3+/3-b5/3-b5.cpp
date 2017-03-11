/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>
using namespace std;


int main()
{
	double a, b, c;
	double p, S;

	cout << "请依次输入三边长度，接受实数，用空格隔开（如3.0 4.0 5.2）：";
	cin >> a >> b >> c;
	if (a <= 0 || b <= 0 || c <= 0)
	{
		cout << "您的输入中有非正数！" << endl;
	}
	else if (a + b > c && b + c > a && a + c > b)
	{
		//可以构成三角形
		//感谢海伦提供海伦公式
		p = (a + b + c) / 2;
		S = sqrt(p * (p - a) * (p - b) * (p - c));
		cout << "三角形的面积：S = " << S << endl;
	}
	else
	{
		cout << "三边不能组成三角形！" << endl;
	}

	cout << "程序结束。" << endl;
	return 0;
}