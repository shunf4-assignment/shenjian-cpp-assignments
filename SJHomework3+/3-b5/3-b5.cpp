/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <cmath>
using namespace std;


int main()
{
	double a, b, c;
	double p, S;

	cout << "�������������߳��ȣ�����ʵ�����ÿո��������3.0 4.0 5.2����";
	cin >> a >> b >> c;
	if (a <= 0 || b <= 0 || c <= 0)
	{
		cout << "�����������з�������" << endl;
	}
	else if (a + b > c && b + c > a && a + c > b)
	{
		//���Թ���������
		//��л�����ṩ���׹�ʽ
		p = (a + b + c) / 2;
		S = sqrt(p * (p - a) * (p - b) * (p - c));
		cout << "�����ε������S = " << S << endl;
	}
	else
	{
		cout << "���߲�����������Σ�" << endl;
	}

	cout << "���������" << endl;
	return 0;
}