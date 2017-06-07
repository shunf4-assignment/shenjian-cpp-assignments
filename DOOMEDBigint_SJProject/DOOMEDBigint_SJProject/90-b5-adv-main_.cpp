/* 1652270 �����2�� ��˴ */
/* 90-b5-main.cpp */
#include "90-b5-adv.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <windows.h>

/*
*	bigint gcd(const bigint &x, const bigint &y)
*		�� x , y �����������
*/
bigint gcd(const bigint &x, const bigint &y)
{
	bigint x_ = x;
	bigint y_ = y;
	bigint tmp;
	bigint *larger = &x_, *smaller = &y_, *third = &tmp, *fourth;

	while (*smaller != 0)
	{
		*third = *larger % *smaller;
		fourth = larger;
		larger = smaller;
		smaller = third;
		third = fourth;
	}

	return *larger;
}

/*
*	bigint gcd_all(bigint x[], unsigned x_len)
*		�� x �е�Ԫ�������������
*/
bigint gcd_all(bigint *x, unsigned x_len)
{
	if (x_len < 2)
		return *x;
	bigint result = gcd(x[0], x[1]);
	for (unsigned i = 2; i < x_len; i++)
	{
		result = gcd(result, x[i]);
	}
	return result;
}

int main()
{
	try
	{
		LARGE_INTEGER tick, fc_begin, fc_end;

		int testStep = 9;
		int excludeStep = 0;
		bool allTest = 1;

		if ((testStep == 1 || allTest) &&
			excludeStep != 1)
		{
			cout << "�����Խ׶� 1 - ������ԡ�" << endl;
			cout << "���Դ��� bigint" << endl;
			bigint b1;

			cout << "�޲ι���� b1��������� 0��ʵ�������\t\t";
			cout << b1 << endl;

#if (0)
			cout << "���ַ������� 0��������� 0��ʵ�������\t\t";
			bigint b2 = "0";
			cout << b2 << endl;

			cout << "���ַ�����ֵ -0��������� 0��ʵ�������\t";
			b1 = "-0";
			cout << b1 << endl;


			cout << "���ַ�����ʼ�� -123456789\n\t������� -123456789��ʵ�������\t\t";
			bigint b3 = "-123456789";
			cout << b3 << endl;


			cout << "���ַ�����ʼ�� 1230000000012300\n\t������� 1230000000012300��ʵ�������\t";
			bigint b4 = "1230000000012300";
			cout << b4 << endl;
#else
			bigint b3;
#endif

			cout << "��int��ֵ 12300��������� 12300��ʵ�������\t";
			b3 = 12300;
			cout << b3 << endl;

			cout << "��int��ֵ 0��������� 0��ʵ�������\t";
			b1 = 0;
			cout << b1 << endl;

			cout << "�� b3 == 12300 ��ֵ b1\n\t������� 12300��ʵ�������\t";
			b1 = b3;
			cout << b1 << endl;
			cout << endl << endl;
		}

		if ((testStep == 2 || allTest )&& excludeStep != 2)
		{
			cout << "�����Խ׶� 2 - �Ӽ��˲��ԡ�" << endl;

			QueryPerformanceFrequency(&tick);
			QueryPerformanceCounter(&fc_begin);

			bigint a;
			bigint b;
			
			cin >> a >> b;

			cout << "a = " << a << endl << "b = " << b << endl;
			cout << endl;
			cout << "a + b" << " = ";
			cout << endl;
			cout << "������\n12700084655516449630377423801377597633765976426555686019098837783383123251635649314441592379164040927" << endl;
			cout << "ʵ�ʣ�" << endl;
			cout << (a + b) << endl;

			cout << "b - a" << " = ";
			cout << endl;
			cout << "������\n157443336656546102361348085583413120287705801520303550545163453555635862678716572156825639171798621297" << endl;
			cout << "ʵ�ʣ�" << endl;
			cout << (b - a) << endl;
			cout << endl;

			cout << "a * b" << " = ";
			cout << endl;
			cout << "������\n-6156778026822307310278021106208140580051089585316244808378851600651895150471527828101423722906091499944700911381607419930684971988560121467141431188318022015980339202571419873619804928348086364572735720" << endl;
			cout << "ʵ�ʣ�" << endl;
			cout << (a * b) << endl;

			QueryPerformanceCounter(&fc_end);
			clog << setiosflags(ios::fixed) << setprecision(3);
			clog << "�׶� 2 ������" << endl;
			clog << "ʱ��Ƶ�ʣ�" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
			clog << setprecision(0);
			clog << "ʱ�Ӽ�����" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
			clog << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "��" << endl;

			cout << endl << endl;

		}
		if ((testStep == 3 || allTest) && excludeStep != 3)
		{
			cout << "�����Խ׶� 3 - �������ԡ�" << endl;

			QueryPerformanceFrequency(&tick);
			QueryPerformanceCounter(&fc_begin);

			bigint remainder;
			bigint quotient;

			int dividendInit = 1584648620;
			int divisorInit = 13838;

			for (int i = 0; i < 4; i++)
			{
				int dividend = i & 1 ? -dividendInit : dividendInit;
				int divisor = i & 2 ? -divisorInit : divisorInit;
				bigint dividendBig = dividend;
				bigint divisorBig = divisor;
				cout << dividend << " / " << divisor << endl;
				cout << dividendBig << " / " << divisorBig << endl;
				
				quotient = dividendBig / divisorBig;
				remainder = dividendBig % divisorBig;

				cout << "������������ " << dividend / divisor << ", ʵ���� " << quotient << endl;
				cout << "������������ " << dividend % divisor << ", ʵ���� " << remainder << endl;
			}

			QueryPerformanceCounter(&fc_end);
			clog << setiosflags(ios::fixed) << setprecision(3);
			clog << "�׶� 3 ������" << endl;
			clog << "ʱ��Ƶ�ʣ�" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
			clog << setprecision(0);
			clog << "ʱ�Ӽ�����" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
			clog << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "��" << endl;

			cout << endl << endl;

		}
		if ((testStep == 4 || allTest) && excludeStep != 4)
		{
			cout << "�����Խ׶� 4 - ����������� 1 ��" << endl;

			QueryPerformanceFrequency(&tick);
			QueryPerformanceCounter(&fc_begin);

			bigint x = 0;
			bigint y = 0;
			bigint z = 0;

			for (int i = 0; i < 6; i++)
			{
				cout << "������һ���� x��";
				cin >> x;
				cout << "������һ���� y��";
				cin >> y;
				cout << "x + y = " << x + y << endl;
				cout << "x - y = " << x - y << endl;
				if (i < 5)
				{
					cout << "x * y = " << x * y << endl;
					cout << "x / y = " << x / y << endl;
					cout << "x % y = " << x % y << endl;
				
					cout << "cout << (x++) << endl : " << endl;
					cout << (x++) << endl;
					cout << "cout << (++x) << endl : " << endl;
					cout << (++x) << endl;
					cout << "cout << (x--) << endl : " << endl;
					cout << (x--) << endl;
					cout << "cout << (--x) << endl : " << endl;
					cout << (--x) << endl;
				}
			}

			QueryPerformanceCounter(&fc_end);
			clog << setiosflags(ios::fixed) << setprecision(3);
			clog << "�׶� 4 ������" << endl;
			clog << "ʱ��Ƶ�ʣ�" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
			clog << setprecision(0);
			clog << "ʱ�Ӽ�����" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
			clog << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "��" << endl;

			cout << endl << endl;

		}

		if ((testStep == 5 || allTest) && excludeStep != 5)
		{
			cout << "�����Խ׶� 5 - ����������� 2 ��" << endl;

			QueryPerformanceFrequency(&tick);
			QueryPerformanceCounter(&fc_begin);

			bigint a[10], b[10];
			for (int i = 0; i < 10; i++)
			{
				cin >> a[i];
			}
			for (int i = 0; i < 10; i++)
			{
				cin >> b[i];
			}

			cout << a[2] + b[3] << endl;
			cout << a[7] - b[4] << endl;
			cout << a[0] * b[1] << endl;
			cout << a[9] / b[0] << endl;
			cout << a[8] % b[1] << endl;

			cout << (a[1] += b[2]) << endl;
			cout << a[1] << endl;

			cout << (a[3] = b[8] = b[2]) << endl;
			cout << a[3] << endl;
			cout << b[8] << endl;

			cout << ++a[4] << endl << b[6]-- << endl;

			cout << -a[5] << endl << +a[5] << endl;
			cout << (a[2] + 1000 < b[8]) << endl;
			cout << (a[3] == b[8]) << endl;
			cout << (a[8] >= a[6]) << endl;

			cout << gcd_all(a + 5, 3) << endl;

			QueryPerformanceCounter(&fc_end);
			clog << setiosflags(ios::fixed) << setprecision(3);
			clog << "�׶� 5 ������" << endl;
			clog << "ʱ��Ƶ�ʣ�" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
			clog << setprecision(0);
			clog << "ʱ�Ӽ�����" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
			clog << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "��" << endl;

			cout << endl << endl;

		}
		clog << "�������н�����" << endl;
	}
	catch (bad_alloc &exp)
	{
		cerr << exp.what() << endl;
		cout << "�ڴ治�㣬�����޷��������С�" << endl;
		return STAT_OVERFLOW;
	}
	return 0;
}