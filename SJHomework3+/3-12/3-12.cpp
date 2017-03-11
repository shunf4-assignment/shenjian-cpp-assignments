/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>
using namespace std;


int main()
{
	int inputInteger, i_;
	int d5, d4, d3, d2, d1;
	int digitCount;

	cout << "请输入 5 位以内（含 5 位）的正整数：";
	cin >> inputInteger;
	i_ = inputInteger;

	cout << "该正整数的位数为：";
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

	cout << "顺序输出：";
	(!d5 && digitCount <= 5) ? 1 : ((cout << d5 << " "), 1);
	(!d4 && digitCount <= 4) ? 1 : ((cout << d4 << " "), 1);
	(!d3 && digitCount <= 3) ? 1 : ((cout << d3 << " "), 1);
	(!d2 && digitCount <= 2) ? 1 : ((cout << d2 << " "), 1);
	(!d1 && digitCount <= 1) ? 1 : ((cout << d1), 1);
	cout << endl;

	cout << "逆序输出：";
	(!d1 && digitCount <= 1) ? 1 : ((cout << d1 << " "), 1);
	(!d2 && digitCount <= 2) ? 1 : ((cout << d2 << " "), 1);
	(!d3 && digitCount <= 3) ? 1 : ((cout << d3 << " "), 1);
	(!d4 && digitCount <= 4) ? 1 : ((cout << d4 << " "), 1);
	(!d5 && digitCount <= 5) ? 1 : ((cout << d5), 1);

	cout << endl;
	return 0;

}