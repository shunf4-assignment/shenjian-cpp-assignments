/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <iomanip>
using namespace std;


int main()
{

	short i, i_;
	cout << "Please input a number: ";
	cin >> i;
	i_ = i;

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


	cout << "��λ��" << d5 << endl;
	cout << "ǧλ��" << d4 << endl;
	cout << "��λ��" << d3 << endl;
	cout << "ʮλ��" << d2 << endl;
	cout << "��λ��" << d1 << endl;

	return 0;
}