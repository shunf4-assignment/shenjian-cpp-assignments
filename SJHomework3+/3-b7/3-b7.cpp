#include <iostream>
#include <cmath>  //���ڳ���Ҫ�õ���ѧ����sqrt����Ӧ����ͷ�ļ�cmath
using namespace std;

int main()
{
	double a, b, c, x1, x2, im;
	double D;
	cout << "�������뷽�� ax^2 + bx + c == 0 �Ĳ��� a, b, c���ÿո��������5 3.2 7��\n�����룺";
	cin >> a >> b >> c;
	if (fabs(a) < 1e-8)
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
	else
	{
		D = b * b - 4 * a * c;
		if (D > 1e-8)
		{
			//�����ȸ�
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
		else if (fabs(D) < 1e-8)
		{
			//���ȸ�
			x1 = (-b) / (2 * a);
			if (fabs(x1) < 1e-8)
				x1 = 0;
			cout << "���̴����������ʵ����" << endl;
			cout << "x1 = x2 = " << x1 << endl;
		}
		else
		{
			//�����
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
	}
	
	cout << "�������н�����" << endl;

	return 0;
}