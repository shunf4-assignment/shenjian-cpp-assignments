/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <cmath>  //���ڳ���Ҫ�õ���ѧ����sqrt����Ӧ����ͷ�ļ�cmath
using namespace std;

void linearEquation(double b, double c);

void positiveDelta(double a, double b, double D);

void zeroDelta(double a, double b);

void negativeDelta(double a, double b, double D);

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