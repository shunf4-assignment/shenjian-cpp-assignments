/*1652340 �����3�� �����*/
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <fstream>
#include "90-b5-adv.h"
bigint gcd(const bigint &a, const bigint &b)
{
	return b == 0 ? a : gcd(b, a % b);
}
bigint add(const bigint &a, const bigint &b)
{
	return const_cast<bigint &&>(a + b);
}
int main()
{	
	bigint a, b;
	bigint c[50];

	//freopen("90-b5-adv-data.txt", "r", stdin);
	//freopen("90-b5-adv-ans.txt", "w", stdout);

	for (int i = 1; i <= 3; ++i)
	{
		clog << "��" << i << "���εĲ���ing" << endl;
		clog << "------------------------------------" << endl;


		clog << "��������в���1��" << endl;
		/*-----------------------------------------------*/
		cout << "����������a" << endl;
		cin >> a;
		c[0] = a;
		cout << "����������b" << endl;
		cin >> b;
		c[1] = a % b;
		a /= b;
		cout << "a/=b�Ľ��Ϊ " << a << endl;
		cout << "ԭ����aģb�Ľ��Ϊ " << c[1] << endl;
		cout << "ԭ����a + b =" << add(c[0], b) << endl;
		bigint d = std::move(const_cast<bigint &&>(a * b));
		cout << "ԭ����a * (a / b) �Ľ��Ϊ " << d << endl;

		cout << "����a * (a / b) + (a % b) == a�� �����������Ӧ��Ϊtrue" << endl;
		cout << boolalpha << (d + c[1] == c[0]) << endl;
		/*-----------------------------------------------*/


		clog << "��������в���2��" << endl;
		/*-----------------------------------------------*/
		cout << "������������c, d" << endl;
		cin >> c[1] >> c[0];
		cout << "c��d���Ϊ" << c[1] * c[0] << endl;
		/*-----------------------------------------------*/

		clog << "��������в���3��" << endl;
		/*-----------------------------------------------*/
		cout << "������������e, f" << endl;

		cin >> c[0] >> c[1];
		cout << "e - f = " << c[0] - c[1] << endl;
		cout << "f--���Ϊ" << endl;
		cout << c[1]-- << endl;
		cout << "++f���Ϊ" << endl;
		cout << ++c[1] << endl;
		cout << "ע����������Ӧ����� ������f" << endl;
		cout << "e += f ���Ϊ" << endl;
		cout << (c[0] += c[1]) << endl;
		cout << "a * (a / b) = " << d << endl;
		cout << " a * (a / b) < f ֵΪ " << (d < c[1]) << endl;
		cout << " a * (a / b) == f ֵΪ " << (d == c[1]) << endl;
		cout << " a * (a / b) > f ֵΪ " << (d > c[1]) << endl;
		cout << " a * (a / b) <= f ֵΪ " << (d <= c[1]) << endl;
		cout << " a * (a / b) >= f ֵΪ " << (d >= c[1]) << endl;
		cout << " a * (a / b) != f ֵΪ " << (d != c[1]) << endl;
		/*----------------------------------------------*/
		clog << "��" << i << "���εĲ���done" << endl;
		clog << "------------------------------------" << endl;
	}
	return 0;
}