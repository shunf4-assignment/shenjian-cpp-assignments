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

	h = ((x > 0 && y > 0) + 2 * (x < 0 && y > 0) + 3 * (x < 0 && y < 0) + 4 * (x > 0 && y < 0)) * !!(x*y) * (fabs(x) + fabs(y) <= 3);
	
	cout << "�õ�ĸ߶�ֵΪ�� h = " << h << endl;
	return 0;
}