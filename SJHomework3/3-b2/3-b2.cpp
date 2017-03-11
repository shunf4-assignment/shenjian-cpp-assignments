/* 1652270 计算机2班 冯舜 */
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


	cout << "万位：" << d5 << endl;
	cout << "千位：" << d4 << endl;
	cout << "百位：" << d3 << endl;
	cout << "十位：" << d2 << endl;
	cout << "个位：" << d1 << endl;

	return 0;
}