/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;


int main()
{
	double a, x, x2;
	
	cout << "������x = ��a �е� a (ʵ�ͳ���)�� ";
	cin >> a;

	if (a >= 0) {

		//x�ƽ���ֵ����������⣬������Ϊ a
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

		cout << "ƽ�����ƽ�ֵΪ�� x = " << setiosflags(ios::fixed) << setprecision(15) << x2 << endl;
		cout << "��ʱ x = " << setiosflags(ios::fixed) << setprecision(15) << x << "�� x2 = " << x2 << "�����߲�಻��1e-5" << endl;
	}
	else
	{
		cout << "��Ҫ�Ը���������" << endl;
	}

	return 0;
}