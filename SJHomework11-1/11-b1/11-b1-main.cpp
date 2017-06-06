/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <sstream>
#include "11-b1-datetime.h"
using namespace std;

template <typename T1, typename T2>
T1 positiveRemainder(T1 dividend, T2 divisor)
{
	T1 remainder = dividend % divisor;
	if (remainder < 0)
		remainder += divisor;
	return remainder;
}

void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

typedef union {
	ULARGE_INTEGER li;
	FILETIME       ft;
} TIMESTAMP;

SYSTEMTIME addSystemTime(SYSTEMTIME st, long long sec)
{
	TIMESTAMP t;
	SystemTimeToFileTime(&st, &(t.ft));
	t.li.QuadPart += sec * 10000000;
	FileTimeToSystemTime(&(t.ft), &st);
	return st;
}

SYSTEMTIME addSystemTime_mod(SYSTEMTIME st, long long sec, SYSTEMTIME zero)
{
	TIMESTAMP t;
	TIMESTAMP tzero;
	SystemTimeToFileTime(&st, &(t.ft));
	SystemTimeToFileTime(&zero, &(tzero.ft));
	t.li.QuadPart += sec * 10000000;
	t.li.QuadPart = positiveRemainder(long long(t.li.QuadPart) - long long(tzero.li.QuadPart), 63114336000000000i64) + long long(tzero.li.QuadPart);
	FileTimeToSystemTime(&(t.ft), &st);
	return st;
}

long long diffSystemTime(SYSTEMTIME st1, SYSTEMTIME st2)
{
	TIMESTAMP t1;
	TIMESTAMP t2;
	SystemTimeToFileTime(&st1, &(t1.ft));
	SystemTimeToFileTime(&st2, &(t2.ft));

	return (long long(t1.li.QuadPart) - long long( t2.li.QuadPart)) / 10000000;
}

void testDateTime(const char *expected, const DateTime &d, bool show = 1)
{
	cout << "期望 ";
	cout << expected << "\t\t";
	cout << "实际 ";
	if (show)
		d.show();
	else
		cout << d << endl;
}

int main()
{
	int testStep = 13;
	bool allTest = 1;

	if (testStep == 1 || allTest)
	{
		DateTime d1;
		DateTime d2(2017, 6, 5);
		DateTime d3(2015, 5, 31, 23, 59, 59);

		cout << "【阶段 1】用正确赋值初始化" << endl;
		testDateTime("1900.1.1 0.0.0", d1);
		testDateTime("2017.6.5 0.0.0", d2);
		testDateTime("2015.5.31 23.59.59", d3);
		
		wait_for_enter();
	}

	if (testStep == 2 || allTest)
	{
		DateTime d1(1870, 3, 15);
		DateTime d2(2112, 6, 5);
		DateTime d3(2002, 22, 14);
		DateTime d4(2002, 4, 31);
		DateTime d5(2015, 5, 31, -2, 59, 59);
		DateTime d6(2015, 5, 31, 24, 33, 59);
		DateTime d7(2015, 5, 31, 0, -5, 59);
		DateTime d8(2015, 5, 31, 0, 60, 59);
		DateTime d9(2015, 5, 31, 0, 59, 72);

		cout << "【阶段 2】用非法赋值初始化" << endl;
		testDateTime("1900.3.15 0.0.0", d1);
		testDateTime("1900.6.5 0.0.0", d2);
		testDateTime("2002.1.14 0.0.0", d3);
		testDateTime("2002.4.1 0.0.0", d4);
		testDateTime("2015.5.31 0.59.59", d5);
		testDateTime("2015.5.31 0.33.59", d6);
		testDateTime("2015.5.31 0.0.59", d7);
		testDateTime("2015.5.31 0.0.59", d8);
		testDateTime("2015.5.31 0.59.0", d9);

		wait_for_enter();
	}

	if (testStep == 3 || allTest)
	{
		DateTime d1(2017, 2, 29);
		DateTime d2(1900, 2, 29, 0, 59, 59);
		DateTime d3(2000, 2, 29, 0, 59,59);

		cout << "【阶段 3】含闰年判断的初始化" << endl;
		testDateTime("2017.2.1 0.0.0", d1);
		testDateTime("1900.2.1 0.59.59", d2);
		testDateTime("2000.2.29 0.59.59", d3);

		wait_for_enter();
	}

	if (testStep == 4 || allTest)
	{
		DateTime d1(1870, 3, 15, 5, 34, 23);
		DateTime d2(2112, 6, 5);
		DateTime d3(2002, 22, 14);
		DateTime d4(2002, 4, 31, 7, 12, 21);

		cout << "【阶段 4】测试 set 函数" << endl;
		d1.set(2017, 5, 18, 5, 34, 23);
		d2.set(2017, 5, 5, 0,0,0);
		d3.set(2017,1,14,0,0,0);
		d4.set(2017, 5, 18, 23, 0, 0);
		testDateTime("2017.5.18 5.34.23", d1);
		testDateTime("2017.5.5 0.0.0", d2);
		testDateTime("2017.1.14 0.0.0", d3);
		testDateTime("2017.5.18 23.0.0", d4);

		wait_for_enter();
	}

	if (testStep == 5 || allTest)
	{
		DateTime d1(1976, 2, 29, 5, 34, 23);
		DateTime d2(2033, 6, 5);
		DateTime d3(2002, 12, 14);

		cout << "【阶段 5】非法测试 set 函数" << endl;
		d1.set(2112, 0, 0, 5, 34, 23);
		d2.set(2017, 0, 31, 0,0,0);
		d3.set(0, 2, 29, 0, 0, 0);
		testDateTime("1900.1.1 0.0.0", d1);
		testDateTime("1900.1.1 0.0.0", d2);
		testDateTime("1900.1.1 0.0.0", d3);

		wait_for_enter();
	}

	if (testStep == 6 || allTest)
	{
		DateTime d1(1976, 2, 29, 5, 34, 23);
		DateTime d2;
		int y, M, d, h, m, s;

		cout << "【阶段 6】测试 get、测试 cout" << endl;
		d1.get(y, M, d, h, m, s);
		cout << "应当依次输出 1976 2 29 5 34 23，实际为 \t\t";
		cout << y << " " << M << " " << d << " " << h << " " << m << " " << s << endl << endl;

		testDateTime("1976年2月29日 5:34.23", d1, 0);
		testDateTime("1900年1月1日 0:0.0", d2, 0);

		wait_for_enter();
	}

	if (testStep == 7 || allTest)
	{
		DateTime d1;
//		int y, M, d, h, m, s;

		stringstream stream;
		stream << "2017 5 18 1 2 3 ";
		stream << "2016 2 29 8 0 0 ";
		stream << "2017 2 29 0 8 59 ";
		stream << "1799 8 18 20 59 59 ";
		stream << "2112 12 18 20 59 59 ";
		stream << "2014 15 18 20 59 59 ";
		stream << "2014 6 31 20 59 59 ";
		stream << "2112 15 34 20 59 59 ";
		stream << "2000 2 2 24 59 59 ";
		stream << "2000 2 2 2 -1 59 ";
		stream << "2000 2 2 2 5 60 ";
		stream << "2000 2 2 a 5 60 ";

		stream.seekg(0, ios::beg);

		auto backup = cin.rdbuf();
		cin.set_rdbuf(stream.rdbuf());

		cout << "【阶段 7】测试输入" << endl;
		
		cin >> d1;
		testDateTime("2017.5.18 1.2.3", d1, 0);
		cin >> d1;
		testDateTime("2016.2.29 8.0.0", d1, 0);
		cin >> d1;
		testDateTime("2017.2.1 0.8.59", d1, 0);
		cin >> d1;
		testDateTime("1900.8.18 20.59.59", d1, 0);
		cin >> d1;
		testDateTime("1900.12.18 20.59.59", d1, 0);
		cin >> d1;
		testDateTime("2014.1.18 20.59.59", d1, 0);
		cin >> d1;
		testDateTime("2014.6.1 20.59.59", d1, 0);
		cin >> d1;
		testDateTime("1900.1.1 20.59.59", d1, 0);
		cin >> d1;
		testDateTime("2000.2.2 0.59.59", d1, 0);
		cin >> d1;
		testDateTime("2000.2.2 2.0.59", d1, 0);
		cin >> d1;
		testDateTime("2000.2.2 2.5.0", d1, 0);
		cin >> d1;
		testDateTime("1900.1.1 0.0.0", d1, 0);

		cin.clear();

		cin.set_rdbuf(backup);

		wait_for_enter();
	}

	if (testStep == 8 || allTest)
	{
		SYSTEMTIME zero;
		SYSTEMTIME stdTime;
		zero.wDay = 1;
		zero.wDayOfWeek = -1;
		zero.wHour = 0;
		zero.wMilliseconds = 0;
		zero.wMinute = 0;
		zero.wSecond = 0;
		zero.wMonth = 1;
		zero.wYear = 1900;
		
		const int testTime = 10;
		char expectedStr[30] = "";
		long long testNum[testTime] = {
			0,
			6311433599,
			1446256844,
			86399,
			478643345,
			333567432,
			3422474569,
			73048000,
			6311433601,
			6311500000,
			//-6311433601,
			//-1
		};


		cout << "【阶段 8】转换构造函数测试" << endl;
		for (int i = 0; i < testTime / 2; i++)
		{
			DateTime d(testNum[i]);
			stdTime = addSystemTime(zero, positiveRemainder(testNum[i], 6311433600i64));
			sprintf_s(expectedStr, "%d年%d月%d日 %d:%d.%d", stdTime.wYear, stdTime.wMonth, stdTime.wDay, stdTime.wHour, stdTime.wMinute, stdTime.wSecond);
			testDateTime(expectedStr, d);
		}

		DateTime d;
		for (int i = testTime / 2; i < testTime; i++)
		{
			d = testNum[i];
			stdTime = addSystemTime(zero, positiveRemainder(testNum[i], 6311433600i64));
			sprintf_s(expectedStr, "%d年%d月%d日 %d:%d.%d", stdTime.wYear, stdTime.wMonth, stdTime.wDay, stdTime.wHour, stdTime.wMinute, stdTime.wSecond);
			testDateTime(expectedStr, d);
		}

		wait_for_enter();
	}

	if (testStep == 9 || allTest)
	{
		SYSTEMTIME zero;
		SYSTEMTIME stdTime;
		zero.wDay = 1;
		zero.wDayOfWeek = -1;
		zero.wHour = 0;
		zero.wMilliseconds = 0;
		zero.wMinute = 0;
		zero.wSecond = 0;
		zero.wMonth = 1;
		zero.wYear = 1900;

		const int testTime = 4;
		char expectedStr[30] = "";
		DateTime d[testTime] = 
		{
			{1900, 1,1,0,0,0},
			{2099,12,31,23,59,59},
			{2044, 3,1, 4, 28,44},
			{2038, 1, 19, 23,33,33}
		};


		cout << "【阶段 9】类型转换函数测试" << endl;
		for (int i = 0; i < testTime; i++)
		{
			d[i].get((int&)(stdTime.wYear), (int&)(stdTime.wMonth), (int&)(stdTime.wDay), (int&)(stdTime.wHour), (int&)(stdTime.wMinute), (int&)(stdTime.wSecond));
			
			cout << "期望 " << diffSystemTime(stdTime, zero);
			cout << "\t\t实际 " << long long(d[i]) << endl;
		}

		wait_for_enter();
	}

	if (testStep == 9 || allTest)
	{
		SYSTEMTIME zero;
		SYSTEMTIME stdTime;
		zero.wDay = 1;
		zero.wDayOfWeek = -1;
		zero.wHour = 0;
		zero.wMilliseconds = 0;
		zero.wMinute = 0;
		zero.wSecond = 0;
		zero.wMonth = 1;
		zero.wYear = 1900;

		const int testTime = 4;
		char expectedStr[30] = "";
		DateTime d[testTime] =
		{
			{ 1900, 1,1,0,0,0 },
			{ 2099,12,31,23,59,59 },
			{ 2044, 3,1, 4, 28,44 },
			{ 2038, 1, 19, 23,33,33 }
		};


		cout << "【阶段 9】类型转换函数测试" << endl;
		for (int i = 0; i < testTime; i++)
		{
			d[i].get((int&)(stdTime.wYear), (int&)(stdTime.wMonth), (int&)(stdTime.wDay), (int&)(stdTime.wHour), (int&)(stdTime.wMinute), (int&)(stdTime.wSecond));

			cout << "期望 " << diffSystemTime(stdTime, zero);
			cout << "\t\t实际 " << long long(d[i]) << endl;
		}

		wait_for_enter();
	}

	if (testStep == 10 || allTest)
	{
		SYSTEMTIME zero;
		SYSTEMTIME d1ST;
		SYSTEMTIME d2ST;
		zero.wDay = 1;
		zero.wDayOfWeek = -1;
		zero.wHour = 0;
		zero.wMilliseconds = 0;
		zero.wMinute = 0;
		zero.wSecond = 0;
		zero.wMonth = 1;
		zero.wYear = 1900;

		const int testTime = 8;
		char expectedStr[30] = "";
		DateTime d1 = { 2017, 2, 28, 0, 0, 3 };
		DateTime d2;
		long long offsets[testTime] = {
			86400,
			8640000,
			214749377,
			31536000,
			31622400,
			4,
			86400,
			31536000
		};

		cout << "【阶段 10】加减秒数" << endl;
		d1.get((int&)(d1ST.wYear), (int&)(d1ST.wMonth), (int&)(d1ST.wDay), (int&)(d1ST.wHour), (int&)(d1ST.wMinute), (int&)(d1ST.wSecond));
		for (int i = 0; i < 5; i++)
		{
			d2 = d1 + offsets[i];
			d2ST = addSystemTime(d1ST, offsets[i]);
			sprintf_s(expectedStr, "%d年%d月%d日 %d:%d.%d", d2ST.wYear, d2ST.wMonth, d2ST.wDay, d2ST.wHour, d2ST.wMinute, d2ST.wSecond);
			cout << "期望 " << expectedStr;
			cout << "\t\t实际 " << d2 << endl;
		}

		for (int i = 5; i < 8; i++)
		{
			d2 = d1 - offsets[i];
			d2ST = addSystemTime(d1ST, -offsets[i]);
			sprintf_s(expectedStr, "%d年%d月%d日 %d:%d.%d", d2ST.wYear, d2ST.wMonth, d2ST.wDay, d2ST.wHour, d2ST.wMinute, d2ST.wSecond);
			cout << "期望 " << expectedStr;
			cout << "\t\t实际 " << d2 << endl;
		}

		DateTime d3 = { 1900, 1, 1, 0, 0, 1 };
		DateTime d4 = { 2099, 12, 31, 23, 59, 58 };
		DateTime d5;
		long long offsets2[4] = {
			-2,
			-4,
			2,
			4
		};

		d3.get((int&)(d1ST.wYear), (int&)(d1ST.wMonth), (int&)(d1ST.wDay), (int&)(d1ST.wHour), (int&)(d1ST.wMinute), (int&)(d1ST.wSecond));
		for (int i = 0; i < 2; i++)
		{
			d5 = d3 + offsets2[i];
			d2ST = addSystemTime_mod(d1ST, offsets2[i], zero);
			sprintf_s(expectedStr, "%d年%d月%d日 %d:%d.%d", d2ST.wYear, d2ST.wMonth, d2ST.wDay, d2ST.wHour, d2ST.wMinute, d2ST.wSecond);
			cout << "期望 " << expectedStr;
			cout << "\t\t实际 " << d5 << endl;
		}

		d4.get((int&)(d1ST.wYear), (int&)(d1ST.wMonth), (int&)(d1ST.wDay), (int&)(d1ST.wHour), (int&)(d1ST.wMinute), (int&)(d1ST.wSecond));
		for (int i = 2; i < 4; i++)
		{
			d5 = d4 + offsets2[i];
			d2ST = addSystemTime_mod(d1ST, offsets2[i], zero);
			sprintf_s(expectedStr, "%d年%d月%d日 %d:%d.%d", d2ST.wYear, d2ST.wMonth, d2ST.wDay, d2ST.wHour, d2ST.wMinute, d2ST.wSecond);
			cout << "期望 " << expectedStr;
			cout << "\t\t实际 " << d5 << endl;
		}

		wait_for_enter();
	}

	if (testStep == 11 || allTest)
	{
		SYSTEMTIME zero;
		SYSTEMTIME d1ST;
		SYSTEMTIME d2ST;
		SYSTEMTIME d3ST;
		zero.wDay = 1;
		zero.wDayOfWeek = -1;
		zero.wHour = 0;
		zero.wMilliseconds = 0;
		zero.wMinute = 0;
		zero.wSecond = 0;
		zero.wMonth = 1;
		zero.wYear = 1900;

		char expectedStr[30] = "";
		DateTime d1 = { 2017, 2, 28, 0, 0, 3 };
		DateTime d3;
		DateTime d2[5] = {
			{2022, 5,3,23,45,44},
			{1977, 1,1,4,5,4},
			{2017,2,28,6,0,5},
			{2099,12,31,23,59,59},
			{1900,1,1,0,0,0}
		};

		cout << "【阶段 11】测试日期差值" << endl;
		d1.get((int&)(d1ST.wYear), (int&)(d1ST.wMonth), (int&)(d1ST.wDay), (int&)(d1ST.wHour), (int&)(d1ST.wMinute), (int&)(d1ST.wSecond));
		d3.get((int&)(d3ST.wYear), (int&)(d3ST.wMonth), (int&)(d3ST.wDay), (int&)(d3ST.wHour), (int&)(d3ST.wMinute), (int&)(d3ST.wSecond));
		for (int i = 0; i < 3; i++)
		{
			d2[i].get((int&)(d2ST.wYear), (int&)(d2ST.wMonth), (int&)(d2ST.wDay), (int&)(d2ST.wHour), (int&)(d2ST.wMinute), (int&)(d2ST.wSecond));
			cout << "期望 " << diffSystemTime(d2ST, d1ST);
			cout << "\t\t实际 " << (d2[i] - d1) << endl;
		}

		for (int i = 3; i < 5; i++)
		{
			d2[i].get((int&)(d2ST.wYear), (int&)(d2ST.wMonth), (int&)(d2ST.wDay), (int&)(d2ST.wHour), (int&)(d2ST.wMinute), (int&)(d2ST.wSecond));
			cout << "期望 " << diffSystemTime(d2ST, d3ST);
			cout << "\t\t实际 " << (d2[i] - d3) << endl;
		}

		wait_for_enter();
	}

	if (testStep == 12 || allTest)
	{
		DateTime d1(1997, 2, 28, 23, 59, 59);
		DateTime d2(1996, 3, 1, 0,0,0);
		DateTime d3(2002, 11, 23, 3,4,5);
		DateTime d4(1900, 1, 1, 0, 0, 0);
		DateTime d5(2099, 12, 31, 23, 59, 58);

		cout << "【阶段 12】测试 ++ --" << endl;
		testDateTime("1997.2.28 23.59.59", d1++);
		d2--;
		testDateTime("2002.11.23 3.4.6", ++d3);
		testDateTime("1900.1.1 0.0.0", d4--);
		d5++;
		d5++;
		testDateTime("1997.3.1 0.0.0", d1);
		testDateTime("1996.2.29 23.59.59", d2);
		testDateTime("2002.11.23 3.4.6", d3);
		testDateTime("2099.12.31 23.59.59", d4);
		testDateTime("1900.1.1 0.0.0", d5);

		wait_for_enter();
	}

	if (testStep == 13 || allTest)
	{
		DateTime d1(1997, 2, 28, 23, 59, 59);
		DateTime d2(1997, 3, 1, 0, 0, 0);
		DateTime d3(2002, 11, 23, 3, 4, 5);

		d2--;

		cout << "【阶段 13】测试 ++ --" << endl;
		cout << "比较结果应为0，实际为：" << (d1 >  d2) << endl;
		cout << "比较结果应为1，实际为：" << (d1 >= d2) << endl;
		cout << "比较结果应为0，实际为：" << (d1 <  d2) << endl;
		cout << "比较结果应为1，实际为：" << (d1 <= d2) << endl;
		cout << "比较结果应为1，实际为：" << (d1 == d2) << endl;
		cout << "比较结果应为0，实际为：" << (d1 != d2) << endl;

		cout << "比较结果应为0，实际为：" << (d1 >  d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 >= d3) << endl;
		cout << "比较结果应为1，实际为：" << (d1 <  d3) << endl;
		cout << "比较结果应为1，实际为：" << (d1 <= d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 == d3) << endl;
		cout << "比较结果应为1，实际为：" << (d1 != d3) << endl;

		wait_for_enter();
	}

	return 0;
}