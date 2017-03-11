#include <iostream>
#include <cmath>  //由于程序要用到数学函数sqrt，故应包含头文件cmath
using namespace std;

int main()
{
	double a, b, c, x1, x2, im;
	double D;
	cout << "依次输入方程 ax^2 + bx + c == 0 的参数 a, b, c，用空格隔开，如5 3.2 7。\n请输入：";
	cin >> a >> b >> c;
	if (fabs(a) < 1e-8)
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
			cout << "但是仍可求出它的根为 x = " << (-c / b) << endl;
	}
	else
	{
		D = b * b - 4 * a * c;
		if (D > 1e-8)
		{
			//两不等根
			x1 = (-b + sqrt(D)) / (2 * a);
			x2 = (-b - sqrt(D)) / (2 * a);

			if (fabs(x1) < 1e-8)
				x1 = 0;
			if (fabs(x2) < 1e-8)
				x2 = 0;
			cout << "方程存在两个不等实根。" << endl;
			cout << "x1 = " << x1 << endl;
			cout << "x2 = " << x2 << endl;
		}
		else if (fabs(D) < 1e-8)
		{
			//两等根
			x1 = (-b) / (2 * a);
			if (fabs(x1) < 1e-8)
				x1 = 0;
			cout << "方程存在两个相等实根。" << endl;
			cout << "x1 = x2 = " << x1 << endl;
		}
		else
		{
			//两虚根
			D = 0 - D;
			x1 = (-b) / (2 * a);
			if (fabs(x1) < 1e-8)
				x1 = 0;
			im = sqrt(D) / fabs(2 * a);
			cout << "方程存在两个虚根。" << endl;
			if (fabs(x1 - 0) >= 1e-8) {
				//非纯虚数
				cout << "x1 = " << x1 << " + ";
				if (fabs(fabs(im) - 1) >= 1e-8)
					cout << im;
				cout << " i" << endl;

				cout << "x2 = " << x1 << " - ";
				if (fabs(fabs(im) - 1) >= 1e-8)
					cout << im;
				cout << " i" << endl;
			}
			else
			{
				//纯虚数
				cout << "x1 = ";
				if (fabs(fabs(im) - 1) >= 1e-8)
					cout << im;
				cout << " i" << endl;

				cout << "x2 = -";
				if (fabs(fabs(im) - 1) >= 1e-8)
					cout << im;
				cout << " i" << endl;
			}
			
		}
	}
	
	cout << "程序运行结束。" << endl;

	return 0;
}