/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <cmath>
using namespace std;


int main()
{
	double x, y;
	short h;
	cout << "���������������ϵ��x,y���꣬����ʵ����x��y�ÿո���������ûس������������롣" << endl;
	cout << "�����룺 (��3 2)";
	cin >> x >> y;

	h = 0;
	if (fabs(x*y - 0) < 1e-8)
	{
		//��������������
		;
	}
	else
	{
		if (x > 0 && y > 0 && x + y <= 3)
		{
			h = 1;
		}
		else if (x < 0 && y > 0 && -x + y <= 3)
		{
			h = 2;
		}
		else if (x < 0 && y < 0 && -x + -y <= 3)
		{
			h = 3;
		}
		else if (x > 0 && y < 0 && x + -y <= 3)
		{
			h = 4;
		}
	}
	cout << "�õ�ĸ߶�ֵΪ�� h = " << h << endl;
	return 0;
}