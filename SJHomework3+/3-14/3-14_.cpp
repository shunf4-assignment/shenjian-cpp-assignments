/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

int main_()
{
	int i1, i2, i3, i4;
	int m1, m2, m3, m4;  //��С�����������ĸ���

	cout << "�����ĸ������������ÿո�����������ûس����������ĴΡ�" << endl << "�����룺";
	cin >> i1 >> i2 >> i3 >> i4;
	cout << endl;

	cout << i1 << ", " << i2 << ", " << i3 << ", " << i4 << endl;

	//ȷ��m1
	m1 = i1;
	if (m1 > i2) {
		m1 = i2;
	}
	if (m1 > i3) {
		m1 = i3;
	}
	if (m1 > i4) {
		m1 = i4;
	}


	//ȷ��m2
	m2 = m1;
	if (m2 <= m1 && i1 > m1)
		m2 = i1;
	else if (m2 > m1 && m2 > i1 && i1 > m1)
		m2 = i1;

	if (m2 <= m1 && i2 > m1)
		m2 = i2;
	else if (m2 > m1 && m2 > i2 && i2 > m1)
		m2 = i2;

	if (m2 <= m1 && i3 > m1)
		m2 = i3;
	else if (m2 > m1 && m2 > i3 && i3 > m1)
		m2 = i3;

	if (m2 <= m1 && i4 > m1)
		m2 = i4;
	else if (m2 > m1 && m2 > i4 && i4 > m1)
		m2 = i4;


	//ȷ��m3
	m3 = m2;
	if (m3 <= m2 && i1 > m2)
		m3 = i1;
	else if (m3 > m2 && m3 > i1 && i1 > m2)
		m3 = i1;

	if (m3 <= m2 && i2 > m2)
		m3 = i2;
	else if (m3 > m2 && m3 > i2 && i2 > m2)
		m3 = i2;

	if (m3 <= m2 && i3 > m2)
		m3 = i3;
	else if (m3 > m2 && m3 > i3 && i3 > m2)
		m3 = i3;

	if (m3 <= m2 && i4 > m2)
		m3 = i4;
	else if (m3 > m2 && m3 > i4 && i4 > m2)
		m3 = i4;

	//ȷ��m4
	m4 = m3;
	if (m4 < i1)
		m4 = i1;
	else if (m4 < i2)
		m4 = i2;
	else if (m4 < i3)
		m4 = i3;
	else if (m4 < i4)
		m4 = i4;
	
	cout << m1 << " " << m2 << " " << m3 << " " << m4 << endl;

	return 0;
}