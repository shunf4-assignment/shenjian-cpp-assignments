/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <cmath>
using namespace std;


int main()
{
	int factorLimit = 0, factorSum = 0;
	for (int i = 2; i <= 1000; i++)
	{
		factorLimit = (int)(sqrt(i));
		factorSum = 1;  //��ĿҪ��Ӧ���������ӣ�����i��������ȥ��SumĬ�ϳ�ʼֵΪ1������ѭ����2��ʼ��
		for (int j = 2; j <= factorLimit; j++)
		{
			if (i % j == 0)
			{
				factorSum += j + i / j;
			}
		}

		//cout << factorSum << " " << factorLimit << " " << i << endl;

		if (factorSum == i) {
			//i������
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