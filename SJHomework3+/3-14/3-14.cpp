/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

int main()
{
	int i1, i2, i3, i4;
	int tmp;  //�м��������������������
	int intlabel, minimum;  //�Ǻű���

	cout << "�����ĸ������������ÿո�����������ûس����������ĴΡ�" << endl << "�����룺";
	cin >> i1 >> i2 >> i3 >> i4;
	cout << endl;

	intlabel = 1;
	minimum = i1;
	intlabel = (minimum > i2) ? (minimum = i2, 2) : (intlabel);
	intlabel = (minimum > i3) ? (minimum = i3, 3) : (intlabel);
	intlabel = (minimum > i4) ? (minimum = i4, 4) : (intlabel);  //��minimum����������Ƚϣ�ѡ����Сֵ�����ҽ���Сֵ��Ӧ����Ÿ�ֵ��intlabel

	//����С�����ֺ�i1��һ������
	tmp = i1;
	i1 = minimum;
	(intlabel == 2) ? (i2 = tmp) : (i2);
	(intlabel == 3) ? (i3 = tmp) : (i3);
	(intlabel == 4) ? (i4 = tmp) : (i4);

	//������ֻ��Ҫ��i2 i3 i4���򼴿�
	if (i2 > i3)
	{
		tmp = i2;
		i2 = i3;
		i3 = tmp;
	}

	if (i4 < i2)
	{
		tmp = i2;
		i2 = i4;
		i4 = i3;
		i3 = tmp;
	}
	else if (i4 >= i2 && i4 < i3)
	{
		tmp = i4;
		i4 = i3;
		i3 = tmp;
	}

	cout << "���������";
	cout << i1 << ", " << i2 << ", " << i3 << ", " << i4 << endl;

	return 0;
}