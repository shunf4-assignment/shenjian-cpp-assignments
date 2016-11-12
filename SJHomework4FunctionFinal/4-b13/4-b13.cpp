/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <cmath>  //���ڳ���Ҫ�õ���ѧ����sqrt����Ӧ����ͷ�ļ�cmath
using namespace std;

double a, b, c;
double D;

double negativeZeroToZero(double x)
{
	//��-0ת��0�����򷵻�ԭ��������
	return fabs(x) < 1e-8 ? 0 : x;
}

void linearEquation()
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

void positiveDelta()
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

void zeroDelta()
{
	//���ȸ�
	double x1;
	x1 = (-b) / (2 * a);

	cout << "���̴����������ʵ����" << endl;
	cout << "x1 = x2 = " << negativeZeroToZero(x1) << endl;
}

void negativeDelta()
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

int main()
{
	do
	{
		cout << "�������뷽�� ax^2 + bx + c == 0 �Ĳ��� a, b, c���ÿո��������5 3.2 7��\n�����룺";
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

	cout << "�������н�����" << endl;

	return 0;
}