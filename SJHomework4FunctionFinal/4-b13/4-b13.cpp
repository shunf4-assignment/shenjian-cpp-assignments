/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>  //由于程序要用到数学函数sqrt，故应包含头文件cmath
using namespace std;

double a, b, c;
double D;

double negativeZeroToZero(double x)
{
	//将-0转成0，否则返回原来的数字
	return fabs(x) < 1e-8 ? 0 : x;
}

void linearEquation()
{
	cout << "这不是一个一元二次方程。" << endl;
	if (fabs(b) < 1e-8)
	{
		cout << "并且也不是一个一次方程。";
		if (fabs(c) >= 1e-8)
		{
			cout << "它没有根。" << endl;
		}
		else
		{
			cout << "所有实数均是它的根。" << endl;
		}
	}
	else
		cout << "但是仍可求出它的根为 x = " << negativeZeroToZero(-c / b) << endl;
}

void positiveDelta()
{
	//两不等根
	double x1;
	double x2;
	x1 = (-b + sqrt(D)) / (2 * a);
	x2 = (-b - sqrt(D)) / (2 * a);

	cout << "方程存在两个不等实根。" << endl;
	cout << "x1 = " << negativeZeroToZero(x1) << endl;
	cout << "x2 = " << negativeZeroToZero(x2) << endl;
}

void zeroDelta()
{
	//两等根
	double x1;
	x1 = (-b) / (2 * a);

	cout << "方程存在两个相等实根。" << endl;
	cout << "x1 = x2 = " << negativeZeroToZero(x1) << endl;
}

void negativeDelta()
{
	//两虚根
	double x1, im;
	D = 0 - D;

	x1 = (-b) / (2 * a);
	im = sqrt(D) / fabs(2 * a);

	cout << "方程存在两个虚根。" << endl;

	cout << "x1 = ";
	if (fabs(x1 - 0) >= 1e-8) {
		cout << x1 << " + ";
	}
	if (fabs(im - 1) >= 1e-8)
		cout << im << ' ';
	cout << "i" << endl;
	cout << "x2 = ";
	if (fabs(x1 - 0) >= 1e-8) {
		cout << x1 << " ";
	}
	cout << "- ";
	if (fabs(im - 1) >= 1e-8)
		cout << im << ' ';
	cout << "i" << endl;

}

int main()
{
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
		linearEquation();
	else
	{
		D = b * b - 4 * a * c;
		if (D > 1e-8)
			positiveDelta();
		else if (fabs(D) < 1e-8)
			zeroDelta();
		else
			negativeDelta();

	}

	cout << "程序运行结束。" << endl;

	return 0;
}