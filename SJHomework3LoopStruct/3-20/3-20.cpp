/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>
using namespace std;


int main()
{
	int factorLimit = 0, factorSum = 0;
	for (int i = 2; i <= 1000; i++)
	{
		factorLimit = (int)(sqrt(i));
		factorSum = 1;  //题目要求应该是真因子，所以i不包括进去，Sum默认初始值为1，因数循环从2开始。
		for (int j = 2; j <= factorLimit; j++)
		{
			if (i % j == 0)
			{
				factorSum += j + i / j;
			}
		}

		//cout << factorSum << " " << factorLimit << " " << i << endl;

		if (factorSum == i) {
			//i是完数
			cout << i << ",its factors are ";
			for (int j = 1; j < i; j++)
			{
				if (i % j == 0)
				{
					if (j != 1)
						cout << ",";
					cout << j;
				}
			}
			cout << endl;
		}
	}

	return 0;
}