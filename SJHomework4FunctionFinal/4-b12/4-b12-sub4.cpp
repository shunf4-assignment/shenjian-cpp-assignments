/* 1652270 �����2�� ��˴ */
#include "4-b12.h"  //Ҫ�ø���������negativeZeroToZero�����Ժ���Դ�ļ�Ҳ����ͷ�ļ�

void negativeDelta(double a, double b, double D)
{
	//�����
	double x1, im;
	D = 0 - D;

	x1 = (-b) / (2 * a);
	im = sqrt(D) / fabs(2 * a);

	cout << "���̴������������" << endl;

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