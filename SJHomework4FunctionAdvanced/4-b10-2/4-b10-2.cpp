/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

template <typename T1>
/* �˴�����fun������ʵ�� */
T1 fun(T1 n)
{
	T1 sum = 1;
	while (!!(n - 1))
	{
		sum += n;
		n += -1;
	}
	return sum;
}

/* main������׼�޸� */
int main()
{
	short          s1 = 255, s2 = s1 + 1;
	unsigned short us1 = 255, us2 = us1 + 1;
	int            i1 = 65535, i2 = i1 + 1;
	unsigned int   ui1 = 65535, ui2 = ui1 + 1;

	cout << fun(s1) << endl; //������� 32640
	cout << fun(s2) << endl; //������� -32640
	cout << fun(us1) << endl; //������� 32640
	cout << fun(us2) << endl; //������� 32896
	cout << fun(i1) << endl; //������� 2147450880
	cout << fun(i2) << endl; //������� -2147450880
	cout << fun(ui1) << endl; //������� 2147450880
	cout << fun(ui2) << endl; //������� 2147516416

	return 0;
}
