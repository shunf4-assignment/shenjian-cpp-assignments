/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <iomanip>
using namespace std;


int main()
{
	cout << "九九乘法表" << endl;

	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= i; j++) {
			cout << j << "x" << i << "=" << setw(2) << (i*j) << "  ";
		}
		cout << endl;
	}

	return 0;
}