/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include <iostream>
#include <iomanip>
using namespace std;


int main()
{
	const int triLine = 10;
	const int wide = 6;
	int triArray[triLine][triLine] = { 1 };

	for (int i = 0; i < triLine; i++)
	{
		for (int k = 0; k < (triLine - i) * wide / 2; k++)
			cout << ' ';
		for (int j = 0; j < i + 1; j++)
		{
			if (j == 0 || j == i)
			{
				triArray[i][j] = 1;
			}
			else
				triArray[i][j] = triArray[i - 1][j - 1] + triArray[i - 1][j];

			if (j != 0)
				cout << setw(wide);
			cout << triArray[i][j];
		}
		cout << endl;
	}
	return 0;
}
