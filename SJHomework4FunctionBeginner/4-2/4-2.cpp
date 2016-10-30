/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <cmath>  //���ڳ���Ҫ�õ���ѧ����sqrt����Ӧ����ͷ�ļ�cmath
using namespace std;

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
			cout << "�����Կ�������ĸ�Ϊ x = " << (-c / b) << endl;
}

void positiveDelta(double a, double b, double D)
{
	//�����ȸ�
	double x1;
	double x2;
	x1 = (-b + sqrt(D)) / (2 * a);
	x2 = (-b - sqrt(D)) / (2 * a);

	if (fabs(x1) < 1e-8)
		x1 = 0;
	if (fabs(x2) < 1e-8)
		x2 = 0;
	cout << "���̴�����������ʵ����" << endl;
	cout << "x1 = " << x1 << endl;
	cout << "x2 = " << x2 << endl;
}

void zeroDelta(double a, double b)
{
	//���ȸ�
	double x1;
	x1 = (-b) / (2 * a);
	if (fabs(x1) < 1e-8)
		x1 = 0;
	cout << "���̴����������ʵ����" << endl;
	cout << "x1 = x2 = " << x1 << endl;
}

void negativeDelta(double a, double b, double D)
{
	//�����
	double x1, im;
	D = 0 - D;
	x1 = (-b) / (2 * a);
	if (fabs(x1) < 1e-8)
		x1 = 0;
	im = sqrt(D) / fabs(2 * a);
	cout << "���̴������������" << endl;
	if (fabs(x1 - 0) >= 1e-8) {
		//�Ǵ�����
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
		//������
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

int main()
{
	double a, b, c;
	double D;
	
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
		linearEquation(b, c);
	else
	{
		D = b * b - 4 * a * c;
		if (D > 1e-8)
			positiveDelta(a, b, D);
		else if (fabs(D) < 1e-8)
			zeroDelta(a, b);
		else
			negativeDelta(a, b, D);
		
	}

	cout << "�������н�����" << endl;

	return 0;
}