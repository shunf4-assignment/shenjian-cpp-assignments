/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;


int main()
{

	double i, i_, i__;
	cout << "Please input a number: ";
	cin >> i;
	i_ = i;

	int d10 = (int)(i_ / 1e9);
	i_ -= d10 * 1e9;
	int d9 = (int)(i_ / 1e8);
	i_ -= d9 * 1e8;
	int d8 = (int)(i_ / 1e7);
	i_ -= d8 * 1e7;
	int d7 = (int)(i_ / 1e6);
	i_ -= d7 * 1e6;
	int d6 = (int)(i_ / 1e5);
	i_ -= d6 * 1e5;
	int d5 = (int)(i_ / 1e4);
	i_ -= d5 * 1e4;
	int d4 = (int)(i_ / 1e3);
	i_ -= d4 * 1e3;
	int d3 = (int)(i_ / 1e2);
	i_ -= d3 * 1e2;
	int d2 = (int)(i_ / 1e1);
	i_ -= d2 * 1e1;
	int d1 = (int)(i_ / 1e0);
	i_ -= d1 * 1e0;

	i__ = (int)(i_ * 100 + 0.5);

	int dm1 = (int)(i__ / 10);
	i__ -= dm1 * 10;
	int dm2 = (int)(i__);

	cout << "ʮ��λ��" << d10 << endl;
	cout << "��λ��" << d9 << endl;
	cout << "ǧ��λ��" << d8 << endl;
	cout << "����λ��" << d7 << endl;
	cout << "ʮ��λ��" << d6 << endl;
	cout << "��λ��" << d5 << endl;
	cout << "ǧλ��" << d4 << endl;
	cout << "��λ��" << d3 << endl;
	cout << "ʮλ��" << d2 << endl;
	cout << "��λ��" << d1 << endl;
	cout << "ʮ��λ��" << dm1 << endl;
	cout << "�ٷ�λ��" << dm2 << endl;
	return 0;
}