/* 1652270 �����2�� ��˴ */
/* 2016/09/22 10:35 Created */
/* 2016/09/22 10:53 Modified */
#include <iostream>
using namespace std;

int main()
{
	void sort(int x, int y, int z);
	int x, y, z;
	cin >> x >> y >> z;
	/*
	cout << x << endl;
	cout << y << endl;
	cout << z << endl;
	*/
	sort(x, y, z);
	return 0;
}

void sort(int x, int y, int z)
{
	int temp;
	if (x > y) { temp = x; x = y; y = temp; }  //{ }��3�����������ǽ�x��y��ֵ����
	if (z < x) cout << z << ',' << x << ',' << y << endl;
	else if (z < y) cout << x << ',' << z << ',' << y << endl;
	else cout << x << ',' << y << ',' << z << endl;
}

/*
��������������
Input		Output
3 6 10 	3,6,10
6 3 10	3,6,10
10 6 3	3,6,10
10,6,3	-858993460,-858993460,10
��	-858993460,-858993460,-858993460

�����ܣ�
�ó���ʵ�ֽ���������������x,y,z��������С�������������С�
*/