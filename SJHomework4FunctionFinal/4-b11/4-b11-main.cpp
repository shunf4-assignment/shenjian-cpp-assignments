/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>  //由于程序要用到数学函数sqrt，故应包含头文件cmath
using namespace std;

void linearEquation(double b, double c);

void positiveDelta(double a, double b, double D);

void zeroDelta(double a, double b);

void negativeDelta(double a, double b, double D);

int main()
{
	double a, b, c;
	double D;

	do
	{
		cout << "依次输入方程 ax^2 + bx + c == 0 的参数 a, b, c，用空格隔开，如5 3.2 7。\n请输入：";
		cin >> a >> b >> c;
		if (cin.rdstate() != ios_base::failbit) {
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

	} while (1);

	if (fabs(a) < 1e-8)
		linearEquation(b, c);
	else
	{
		D = b * b - 4 * a * c;
		if (D > 1e-8)
			positiveDelta(a, b, D);
		else if (fabs(D) < 1e-8)
			zeroDelta(a, b);
		else
			negativeDelta(a, b, D);

	}

	cout << "程序运行结束。" << endl;

	return 0;
}