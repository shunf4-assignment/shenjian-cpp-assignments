/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <cmath>
using namespace std;


int main()
{
	double x1, y1, x2, y2, x3, y3;
	double vectorProduct, S;

	cout << "�����������������x,y���꣬������6��ʵ�����ÿո��������2.0 3.0 3.0 4.0 4.0 5.0 ��ʾ(2,3)��(3,4)��(4,5)��" << endl;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	
	vectorProduct = (x2 - x1)*(y2 - y3) - (y2 - y1)*(x2 - x3); //���
	if (fabs(vectorProduct) < 1e-8) {
		//��ѧ����������������ƽ�У��ȼ������㲻�ܹ���������
		cout << "�������㲻�ܹ��������Σ�" << endl;
	}
	else
	{
		S = fabs(vectorProduct) / 2;
		cout << "�����㹹�������ε���� S = " << S << endl;
	}

	cout << "���������" << endl;
	return 0;
}