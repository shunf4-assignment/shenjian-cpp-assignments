/* 1652270 �����2�� ��˴ */
#include "4-b12.h"  //Ҫ�ø���������negativeZeroToZero�����Ժ���Դ�ļ�Ҳ����ͷ�ļ�

void positiveDelta(double a, double b, double D)
{
	//�����ȸ�
	double x1;
	double x2;
	x1 = (-b + sqrt(D)) / (2 * a);
	x2 = (-b - sqrt(D)) / (2 * a);

	cout << "���̴�����������ʵ����" << endl;
	cout << "x1 = " << negativeZeroToZero(x1) << endl;
	cout << "x2 = " << negativeZeroToZero(x2) << endl;
}

