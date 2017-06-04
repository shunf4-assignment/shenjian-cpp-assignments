/* 1652270 计算机2班 冯舜 */
/* DOOMEDBigint_SJProject 90-b5-main.cpp */
#include "90-b5.h"

int main()
{
	try
	{
		int testStep = 5;
		bool allTest = 0;
		if (testStep == 1 || allTest)
		{
			cout << "测试创建 bigint" << endl;
			bigint b1;

			cout << "无参构造的 b1，期望输出 0，实际输出：\t\t";
			cout << b1 << endl;

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

			cout << "用int赋值 12300，期望输出 12300，实际输出：\t";
			b1 = 12300;
			cout << b1 << endl;

			cout << "用 b4 == 1230000000012300 赋值 b1\n\t期望输出 1230000000012300，实际输出：\t";
			b1 = b4;
			cout << b4 << endl;
		}
		if (testStep == 2 || allTest)
		{
			bigint a = "-72371626000514826365485330891017761326969912546873932263032307886126369713540461421192023396317290185";
			bigint b = "85071710656031275995862754692395358960735888973429618282131145669509492965176110735633615775481331112";
			bigint c = 7919376479651642;
			a.print();
			cout << endl;
			b.print();
			cout << endl;
			cout << (a + b) << endl;
			cout << (b - a) << endl;
			cout << endl;
			cout << (b * c) << endl;
		}
		if (testStep == 3 || allTest)
		{
			bigint a = "-0";
			bigint x = "-654650460274952057652017016752178115761568787978079580780178950712851075078";
			bigint b = "-7";
			bigint c;
			bigint d;

			__int64 dividendInit = 7919376479651642;
			__int64 divisorInit = 209820526280;
			for (int i = 0; i < 4; i++)
			{
				__int64 dividend = i & 1 ? -dividendInit : dividendInit;
				__int64 divisor = i & 2 ? -divisorInit : divisorInit;
				cout << dividend << " / " << divisor << " ";
				d.equalsDiv(dividend, divisor, c);
				cout << "商数：期望是 " << dividend / divisor << ", 实际是 " << d << endl;
				cout << "余数：期望是 " << dividend % divisor << ", 实际是 " << c << endl;
			}

		}
		if (testStep == 4 || allTest)
		{
			bigint c, d;
			cin >> c >> d;
			bigint e = c / d;
			cout << e << endl;
		}
		if (testStep == 5 || allTest)
		{
			bigint A, B, C;
			cin >> A >> B >> C;
			cout << A + B << endl;
			cout << A - B << endl;
			cout << A * B << endl;
			cout << A / C << endl;
		}

	}
	catch (bad_alloc &exp)
	{
		cerr << exp.what() << endl;
		return STAT_OVERFLOW;
	}
	return 0;
}