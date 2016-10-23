/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;


int main()
{
	double a, x, x2;
	
	cout << "请输入x = √a 中的 a (实型常数)： ";
	cin >> a;

	if (a >= 0) {

		//x逼近初值好像可以任意，暂且置为 a
		x = a;
		x2 = a;


		do
		{
			x = x2;
			if (fabs(x - 0) < 1e-12) {
				x2 = 0;
				break;
			}
			x2 = 0.5 * (x + a / x);
		} while (fabs(x - x2) >= 1e-5);

		cout << "平方根逼近值为： x = " << setiosflags(ios::fixed) << setprecision(15) << x2 << endl;
		cout << "此时 x = " << setiosflags(ios::fixed) << setprecision(15) << x << "， x2 = " << x2 << "，两者差距不足1e-5" << endl;
	}
	else
	{
		cout << "不要对负数开根。" << endl;
	}

	return 0;
}