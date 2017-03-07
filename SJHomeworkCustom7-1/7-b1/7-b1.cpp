/* 1652270 计算机2班 冯舜 */

#define _CRT_SECURE_NO_WARNINGS		//使用了VS2015认为unsafe的函数
#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

struct tj_time {
	int tj_year;		//表示年份
	int tj_month;	//表示月(1-12)
	int tj_day;		//表示日(1-28/29/30/31)
	int tj_hour;		//表示小时(0-23)
	int tj_minute;	//表示分(0-59)
	int tj_second;	//表示秒(0-59)
};

/* 可以在此定义其它需要的函数 */
bool leap(int year)
{
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}
int calYear(int *input_time)
{
	/*start: 1970*/
	int nowyear = 1970;
	int day = 365;

	while (true)
	{
		day = 365;
		if (leap(nowyear))
		{
			/*leap*/
			day++;
		}
		if (*input_time >= day * 86400)
		{
			*input_time -= day * 86400;
			nowyear++;
		}
		else
		{
			break;
		}
	}
	return nowyear;
}

int calMonth(int year, int *input_time)
{
	int dayThisMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31,0}, *dayMPointer = dayThisMonth;

	if (leap(year))
		dayThisMonth[1] = 29;

	while (true)
	{
		if (*input_time >= *dayMPointer * 86400)
		{
			*input_time -= *dayMPointer * 86400;
		}
		else
		{
			break;
		}
		dayMPointer++;
	}
	return dayMPointer - dayThisMonth + 1;
}

/* 调用系统的转换函数将表示描述的整型值转换为与本题相似的结构体并输出 */
void system_time_output(const time_t input_time)  //time_t的本质是64位无符号整数
{
	struct tm *tt;	//struct tm 为系统定义的结构体

	tt = localtime(&input_time);	//localtime为系统函数

									/* tm_*** 为struct tm中的成员，和本题的struct tj_time具体的内容不完全符合，具体含义自己查找相关资料 */
	cout << tt->tm_year + 1900 << '-' << tt->tm_mon + 1 << '-' << tt->tm_mday << ' ' << tt->tm_hour << ':' << tt->tm_min << ':' << tt->tm_sec << endl;

	return;
}

/* 输出函数 */
void tj_time_output(struct tj_time *tp)
{
	/* 实现自定义结构的输出，输出形式与system_time_output相同 */
	cout << tp->tj_year << '-' << tp->tj_month << '-' << tp->tj_day << ' ' << tp->tj_hour << ':' << tp->tj_minute << ':' << tp->tj_second << endl;
}

struct tj_time *tj_time_convert(int input_time)
{
	static struct tj_time result;	//定义静态局部变量，不准动

									/* 实现过程开始，在下面添加相应的定义及执行语句即可 */
	//时差修正
	//本程序仅供时区UTC+08:00的机器使用
	input_time += 8 * 3600;
	result.tj_year = calYear(&input_time);
	result.tj_month = calMonth(result.tj_year, &input_time);
	result.tj_day = input_time / 86400 + 1;
	input_time %= 86400;
	result.tj_hour = input_time / 3600;
	input_time %= 3600;
	result.tj_minute = input_time / 60;
	input_time %= 60;
	result.tj_second = input_time;

									/* 实现过程结束 */

	return &result;	//注意，返回的是静态局部变量的地址，本语句不准动
}

int main()
{
	int test_time[] = { 1, 123456789, 349823021, 987654321, 1202990407, 1216468807, 1250312143, 1272636353, 1326193524, 1336549496, 1392837128, 1625675376, 2052743737 };
	int i;
	struct tj_time *tp;

	for (i = 0; i<sizeof(test_time) / sizeof(int); i++) {
		cout << "当时秒数        ：" << test_time[i] << endl;
		cout << "系统转换的结果  ：";
		system_time_output(test_time[i]);

		cout << "自定义转换的结果：";
		tp = tj_time_convert(test_time[i]);
		tj_time_output(tp);

		cout << endl << "按回车键继续" << endl;
		getchar();
	}

	if (1) {
		struct tj_time *tp;
		int t = (int)time(0);		//系统函数，取当前系统时间（从1970-01-01 00:00:00开始的秒数），time_t 为系统定义的64位整型数

		cout << "系统转换的当前系统时间：";
		system_time_output(t);

		cout << "自定义转换当前系统时间：";
		tp = tj_time_convert(t);
		tj_time_output(tp);

		cout << endl << "按回车键继续" << endl;
		getchar();
	}

	return 0;
}
