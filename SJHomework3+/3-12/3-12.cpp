/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <cmath>
using namespace std;


int main()
{
	int inputInteger, i_;
	int d5, d4, d3, d2, d1;
	int digitCount;

	cout << "������ 5 λ���ڣ��� 5 λ������������";
	cin >> inputInteger;
	i_ = inputInteger;

	cout << "����������λ��Ϊ��";
	digitCount = (int)log10(inputInteger) + 1;
	cout << digitCount << endl;
	

	d5 = (int)(i_ / 1e4);
	i_ -= d5 * (int)1e4;
	
	d4 = (int)(i_ / 1e3);
	i_ -= d4 * (int)1e3;

	d3 = (int)(i_ / 1e2);
	i_ -= d3 * (int)1e2;

	d2 = (int)(i_ / 1e1);
	i_ -= d2 * (int)1e1;

	d1 = (int)(i_);
	i_ -= d1;

	cout << "˳�������";
	(!d5 && digitCount <= 5) ? 1 : ((cout << d5 << " "), 1);
	(!d4 && digitCount <= 4) ? 1 : ((cout << d4 << " "), 1);
	(!d3 && digitCount <= 3) ? 1 : ((cout << d3 << " "), 1);
	(!d2 && digitCount <= 2) ? 1 : ((cout << d2 << " "), 1);
	(!d1 && digitCount <= 1) ? 1 : ((cout << d1), 1);
	cout << endl;

	cout << "���������";
	(!d1 && digitCount <= 1) ? 1 : ((cout << d1 << " "), 1);
	(!d2 && digitCount <= 2) ? 1 : ((cout << d2 << " "), 1);
	(!d3 && digitCount <= 3) ? 1 : ((cout << d3 << " "), 1);
	(!d4 && digitCount <= 4) ? 1 : ((cout << d4 << " "), 1);
	(!d5 && digitCount <= 5) ? 1 : ((cout << d5), 1);

	cout << endl;
	return 0;

}