/*1652311 Ã·Óï±ù ¼Æ¿Æ3°à*/
#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	int a[10][10] = { { 1 },{ 1,1 },{ 1 },{ 1 },{ 1 } ,{ 1 },{ 1 },{ 1 },{ 1 },{ 1 } }, i, j;
	int m;
	for (i = 0; i <= 9; i++) {
		for (m = 0; m < 10 - i; m++)
			cout << "  ";
		
		for (j = 0; j <= i; j++) {
			if (j >= 1 && i >= 2) {
				a[i][j] = a[i - 1][j] + a[i - 1][j - 1];
			}
			cout << setw(3) << a[i][j] << "  ";
		}
		cout << endl;

	}
	cout << endl;

	return 0;

}