/* 1652270 计算机2班 冯舜 */
/* 90-b5-main.cpp */
#include "90-b5-adv.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <windows.h>

/*
*	bigint gcd(const bigint &x, const bigint &y)
*		对 x , y 求最大公因数。
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
*		对 x 中的元素求最大公因数。
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
			cout << "【测试阶段 1 - 构造测试】" << endl;
			cout << "测试创建 bigint" << endl;
			bigint b1;

			cout << "无参构造的 b1，期望输出 0，实际输出：\t\t";
			cout << b1 << endl;

#if (0)
			cout << "用字符串构造 0，期望输出 0，实际输出：\t\t";
			bigint b2 = "0";
			cout << b2 << endl;

			cout << "用字符串赋值 -0，期望输出 0，实际输出：\t";
			b1 = "-0";
			cout << b1 << endl;


			cout << "用字符串初始化 -123456789\n\t期望输出 -123456789，实际输出：\t\t";
			bigint b3 = "-123456789";
			cout << b3 << endl;


			cout << "用字符串初始化 1230000000012300\n\t期望输出 1230000000012300，实际输出：\t";
			bigint b4 = "1230000000012300";
			cout << b4 << endl;
#else
			bigint b3;
#endif

			cout << "用int赋值 12300，期望输出 12300，实际输出：\t";
			b3 = 12300;
			cout << b3 << endl;

			cout << "用int赋值 0，期望输出 0，实际输出：\t";
			b1 = 0;
			cout << b1 << endl;

			cout << "用 b3 == 12300 赋值 b1\n\t期望输出 12300，实际输出：\t";
			b1 = b3;
			cout << b1 << endl;
			cout << endl << endl;
		}

		if ((testStep == 2 || allTest )&& excludeStep != 2)
		{
			cout << "【测试阶段 2 - 加减乘测试】" << endl;

			QueryPerformanceFrequency(&tick);
			QueryPerformanceCounter(&fc_begin);

			bigint a;
			bigint b;
			
			cin >> a >> b;

			cout << "a = " << a << endl << "b = " << b << endl;
			cout << endl;
			cout << "a + b" << " = ";
			cout << endl;
			cout << "期望：\n12700084655516449630377423801377597633765976426555686019098837783383123251635649314441592379164040927" << endl;
			cout << "实际：" << endl;
			cout << (a + b) << endl;

			cout << "b - a" << " = ";
			cout << endl;
			cout << "期望：\n157443336656546102361348085583413120287705801520303550545163453555635862678716572156825639171798621297" << endl;
			cout << "实际：" << endl;
			cout << (b - a) << endl;
			cout << endl;

			cout << "a * b" << " = ";
			cout << endl;
			cout << "期望：\n-6156778026822307310278021106208140580051089585316244808378851600651895150471527828101423722906091499944700911381607419930684971988560121467141431188318022015980339202571419873619804928348086364572735720" << endl;
			cout << "实际：" << endl;
			cout << (a * b) << endl;

			QueryPerformanceCounter(&fc_end);
			clog << setiosflags(ios::fixed) << setprecision(3);
			clog << "阶段 2 结束。" << endl;
			clog << "时钟频率：" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
			clog << setprecision(0);
			clog << "时钟计数：" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
			clog << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "秒" << endl;

			cout << endl << endl;

		}
		if ((testStep == 3 || allTest) && excludeStep != 3)
		{
			cout << "【测试阶段 3 - 除法测试】" << endl;

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

				cout << "商数：期望是 " << dividend / divisor << ", 实际是 " << quotient << endl;
				cout << "余数：期望是 " << dividend % divisor << ", 实际是 " << remainder << endl;
			}

			QueryPerformanceCounter(&fc_end);
			clog << setiosflags(ios::fixed) << setprecision(3);
			clog << "阶段 3 结束。" << endl;
			clog << "时钟频率：" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
			clog << setprecision(0);
			clog << "时钟计数：" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
			clog << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "秒" << endl;

			cout << endl << endl;

		}
		if ((testStep == 4 || allTest) && excludeStep != 4)
		{
			cout << "【测试阶段 4 - 输入运算测试 1 】" << endl;

			QueryPerformanceFrequency(&tick);
			QueryPerformanceCounter(&fc_begin);

			bigint x = 0;
			bigint y = 0;
			bigint z = 0;

			for (int i = 0; i < 6; i++)
			{
				cout << "请输入一个数 x：";
				cin >> x;
				cout << "请输入一个数 y：";
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
			clog << "阶段 4 结束。" << endl;
			clog << "时钟频率：" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
			clog << setprecision(0);
			clog << "时钟计数：" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
			clog << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "秒" << endl;

			cout << endl << endl;

		}

		if ((testStep == 5 || allTest) && excludeStep != 5)
		{
			cout << "【测试阶段 5 - 输入运算测试 2 】" << endl;

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
			clog << "阶段 5 结束。" << endl;
			clog << "时钟频率：" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
			clog << setprecision(0);
			clog << "时钟计数：" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
			clog << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "秒" << endl;

			cout << endl << endl;

		}
		clog << "程序运行结束。" << endl;
	}
	catch (bad_alloc &exp)
	{
		cerr << exp.what() << endl;
		cout << "内存不足，程序无法继续运行。" << endl;
		return STAT_OVERFLOW;
	}
	return 0;
}