/*1652325 3�� ��һ��*/
#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std;
int main()
{
	srand(unsigned int(time(0)));
	int x, a = 1;
	double y, z = 0.0, d;
	cout << "��������" << endl;
	cin >> x;
	cout << "������" << endl;
	cin >> y;
	y = (y + 0.001) * 100;//��y��������������100��

	start:
	d = y;
	a = 1;
	z = 0.0;
	while (a <= x) {
		z = (rand()*rand() / (32767.0*32767.0))*y;//��ȡ�����z
		while ((double)d<(1.5)*z) z = (rand()*rand() / (32767.0*32767.0))*y;//ȷ��z�ķ�Χ��������z����
		if (z < 1) z = 1;//�����z�����ʱ��100��
		else if (d - z < x - a)z = d - x + a;
		if (a == x&&z < d) z = d;
		cout << "��" << a << "�������Ǯ��" << ":";
		cout << setiosflags(ios::fixed) << setprecision(2) << (double)z / 100 << endl;
		d -= z;
		a++;
	}
	system("pause");
	goto start;
	return 0;
}