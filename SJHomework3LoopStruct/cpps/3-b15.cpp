/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <windows.h> //ȡϵͳʱ��
using namespace std;


int main()
{
	LARGE_INTEGER tick, fc_begin, fc_end;

	QueryPerformanceFrequency(&tick);	//���ʱ��Ƶ��
	QueryPerformanceCounter(&fc_begin);	//��ó�ʼӲ����ʱ������

	/* �˴�����ĳ���ʼ */

	int d1, d2, d3, d4, d5, d6, d7, d8, d9;  //d=digit, �ڼ�������
	int num1, num2, num3, equCount;
	//int d1_, d2_, d3_, d4_, d5_, d6_, d7_, d8_, d9_;
	//int s1, s2, s3, s4, s5, s6, s7, s8, s9;

	/*
	���������߼�
		Ҫ������ʾ����С����˳������ظ��Ľ�������Կ������Ƿ��С����ֻ�迴��λ�Ĳ�ͬ���ɡ�
	*/
	d1 = d2 = d3 = d4 = d5 = d6 = d7 = d8 = d9 = 1;
	equCount = 0;
	for (d1 = 1; d1 <= 5; d1++) // ��ʼ������һ����λ�������ڵ�һ����λ������С�ߣ�����19xx/3=6xx���������λ��1-5ȡֵ
	{
		for (d2 = 1; d2 <= 9; d2++)
		{
			if (d2 == d1)
				continue;
			for (d3 = 1; d3 <= 9; d3++)
			{
				if (d3 == d2 || d3 == d1)
					continue;
				num1 = 100 * d1 + 10 * d2 + d3;
				for (d4 = d1 + 1; d4 <= 9; d4++)
				{
					if (d4 == d3 || d4 == d2)
						continue;
					for (d5 = 1; d5 <= 9; d5++)
					{
						if (d5 == d4 || d5 == d3 || d5 == d2 || d5 == d1)
							continue;
						for (d6 = 1; d6 <= 9; d6++)
						{
							if (d6 == d5 || d6 == d4 || d6 == d3 || d6 == d2 || d6 == d1)
								continue;
							num2 = 100 * d4 + 10 * d5 + d6;
							for (d7 = d4 + 1; d7 <= 9; d7++)
							{
								if (d7 == d6 || d7 == d5 || d7 == d3 || d7 == d2)
									continue;
								for (d8 = 1; d8 <= 9; d8++)
								{
									if (d8 == d7 || d8 == d6 ||  d8 == d5 || d8 == d4 || d8 == d3 || d8 == d2 || d8 == d1)
										continue;
									for (d9 = 1; d9 <= 9; d9++)
									{
										if (d9 == d8 || d9 == d7 || d9 == d6 ||  d9 == d5 || d9 == d4 || d9 == d3 || d9 == d2 || d9 == d1)
											continue;
										num3 = 100 * d7 + 10 * d8 + d9;
										if (num1 + num2 + num3 == 1953)
										{
											equCount += 1;
											//cout << "No." << setw(4) << equCount << " : " << d1 << d2 << d3 << " + " << d4 << d5 << d6 << " + " << d7 << d8 << d9 << " = 1953\n";
											//cout << "No." << setw(3) << equCount << ":" << num1 << "+" << num2 << "+" << num3 << "=1953\n";
											putchar('N');
											putchar('o');
											putchar('.');
											putchar(char((equCount / 100) + 48));
											putchar(char((equCount / 10 % 10) + 48));
											putchar(char((equCount % 10) + 48));
											putchar(':');
											putchar(char(d1 + 48));
											putchar(char(d2 + 48));
											putchar(char(d3 + 48));
											putchar('+');
											putchar(char(d4 + 48));
											putchar(char(d5 + 48));
											putchar(char(d6 + 48));
											putchar('+');
											putchar(char(d7 + 48));
											putchar(char(d8 + 48));
											putchar(char(d9 + 48));
											putchar('=');
											putchar('1');
											putchar('9');
											putchar('5');
											putchar('3');
											putchar('\n');
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	cout << "total = " << equCount << endl;

	/* �˴�����ĳ������ */

	QueryPerformanceCounter(&fc_end);//�����ֹӲ����ʱ������
	cout << setiosflags(ios::fixed) << setprecision(3);
	cout << "ʱ��Ƶ�ʣ�" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
	cout << setprecision(0);
	cout << "ʱ�Ӽ�����" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
	cout << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "��" << endl;

	return 0;
}