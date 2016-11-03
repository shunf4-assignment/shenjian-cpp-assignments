/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

double minusTerm(double a, double b, double c, double d, double x)
{
	double fx, derifx;
	fx = a * x*x*x + b * x*x + c * x + d;
	derifx = 3 * a * x*x + 2 * b * x + c;
	return (x - fx / derifx);
}

double newtonMethod(double a, double b, double c, double d, double startFrom = 1)
{
	double x1, x2;
	x2 = startFrom;
	do
	{
		x1 = x2;
		//cout << x2 << endl;
		x2 = minusTerm(a, b, c, d, x1);
	} while (fabs(x2 - x1) >= 1e-5);
	return x2;
}

int main()
{
	double a, b, c, d, root;
	/*do
	{
		cout << "请依次输入ax^3+bx^2+cx+d==0中a b c d的值，用空格隔开：";
		cin >> a >> b >> c >> d;
		if (cin.rdstate() != ios_base::failbit) {
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

	} while (1);*/

	a = 1, b = 2, c = 3, d = 4;
	root = newtonMethod(a, b, c, d, 1);

	cout << "方程在 1 附近的一个根为： x = " << root << endl;
	return 0;
}