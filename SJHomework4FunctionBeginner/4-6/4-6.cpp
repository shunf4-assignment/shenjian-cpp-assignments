/* 1652270 �����2�� ��˴ */
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
		cout << "����������ax^3+bx^2+cx+d==0��a b c d��ֵ���ÿո������";
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

	cout << "������ 1 ������һ����Ϊ�� x = " << root << endl;
	return 0;
}