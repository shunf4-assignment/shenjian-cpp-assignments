/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;
template <typename T1, typename T2>

/* �˴�����fun������ʵ�� */
void fun(T1 x, T2 y)
{
	int xS = sizeof(x);
	int yS = sizeof(y);
	if (xS < yS)
		cout << "����1��ռ�ռ� <  ����2��ռ�ռ�" << endl;
	else if (xS == yS)
		cout << "����1��ռ�ռ� == ����2��ռ�ռ�" << endl;
	else if (xS > yS)
		cout << "����1��ռ�ռ� >  ����2��ռ�ռ�" << endl;
}

/* main������׼�޸� */
int main()
{
	short  s1 = 0, s2 = 0;
	int    i1 = 0, i2 = 0;
	long   l1 = 0, l2 = 0;
	float  f1 = 0, f2 = 0;
	double d1 = 0, d2 = 0;

	fun(s1, s2); //������� ����1��ռ�ռ� == ����2��ռ�ռ�
	fun(i1, l2); //������� ����1��ռ�ռ� == ����2��ռ�ռ�
	fun(f1, d2); //������� ����1��ռ�ռ� <  ����2��ռ�ռ�
	fun(d1, f2); //������� ����1��ռ�ռ� >  ����2��ռ�ռ�
	fun(d2, l1); //������� ����1��ռ�ռ� >  ����2��ռ�ռ�

	return 0;
}

