/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <cmath>
using namespace std;

double negativeZeroToZero(double x)
{
	//��-0ת��0�����򷵻�ԭ��������
	return fabs(x) < 1e-8 ? 0 : x;
}

void linearEquation(double b, double c)
{
	cout << "�ⲻ��һ��һԪ���η��̡�" << endl;
	if (fabs(b) < 1e-8)
	{
		cout << "����Ҳ����һ��һ�η��̡�";
		if (fabs(c) >= 1e-8)
		{
			cout << "��û�и���" << endl;
		}
		else
		{
			cout << "����ʵ���������ĸ���" << endl;
		}
	}
	else
		cout << "�����Կ�������ĸ�Ϊ x = " << negativeZeroToZero(-c / b) << endl;
}

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

void zeroDelta(double a, double b)
{
	//���ȸ�
	double x1;
	x1 = (-b) / (2 * a);

	cout << "���̴����������ʵ����" << endl;
	cout << "x1 = x2 = " << negativeZeroToZero(x1) << endl;
}

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
