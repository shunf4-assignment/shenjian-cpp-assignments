/* 1652270 �����2�� ��˴ */
/* 2016/09/21 22:41 Created */
/* 2016/09/21 23:02 Modified */
#include <iostream>
using namespace std;
int main()
{
	int a, b, c;
	int f(int x, int y, int z);
	cin >> a >> b >> c;
	c = f(a, b, c);
	cout << c << endl;
	return 0;
}

int f(int x, int y, int z)
{
	int m;
	if (x < y) m = x;
	else m = y;
	if (z < m) m = z;
	return (m);
}
/* ��������������
Input		Output
10 15 20	10
10 20 15	10
15 10 20	10
15 20 10	10
20 10 15	10
20 15 10	10

�ó���Ĺ����ǣ����������������ֵ����룬�����������С������
*/