/* 1652270 �����2�� ��˴ */

#define _CRT_SECURE_NO_WARNINGS		//ʹ����VS2015��Ϊunsafe�ĺ���
#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

struct tj_time {
	int tj_year;		//��ʾ���
	int tj_month;	//��ʾ��(1-12)
	int tj_day;		//��ʾ��(1-28/29/30/31)
	int tj_hour;		//��ʾСʱ(0-23)
	int tj_minute;	//��ʾ��(0-59)
	int tj_second;	//��ʾ��(0-59)
};

/* �����ڴ˶���������Ҫ�ĺ��� */
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

/* ����ϵͳ��ת����������ʾ����������ֵת��Ϊ�뱾�����ƵĽṹ�岢��� */
void system_time_output(const time_t input_time)  //time_t�ı�����64λ�޷�������
{
	struct tm *tt;	//struct tm Ϊϵͳ����Ľṹ��

	tt = localtime(&input_time);	//localtimeΪϵͳ����

									/* tm_*** Ϊstruct tm�еĳ�Ա���ͱ����struct tj_time��������ݲ���ȫ���ϣ����庬���Լ������������ */
	cout << tt->tm_year + 1900 << '-' << tt->tm_mon + 1 << '-' << tt->tm_mday << ' ' << tt->tm_hour << ':' << tt->tm_min << ':' << tt->tm_sec << endl;

	return;
}

/* ������� */
void tj_time_output(struct tj_time *tp)
{
	/* ʵ���Զ���ṹ������������ʽ��system_time_output��ͬ */
	cout << tp->tj_year << '-' << tp->tj_month << '-' << tp->tj_day << ' ' << tp->tj_hour << ':' << tp->tj_minute << ':' << tp->tj_second << endl;
}

struct tj_time *tj_time_convert(int input_time)
{
	static struct tj_time result;	//���徲̬�ֲ���������׼��

									/* ʵ�ֹ��̿�ʼ�������������Ӧ�Ķ��弰ִ����伴�� */
	//ʱ������
	//���������ʱ��UTC+08:00�Ļ���ʹ��
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

									/* ʵ�ֹ��̽��� */

	return &result;	//ע�⣬���ص��Ǿ�̬�ֲ������ĵ�ַ������䲻׼��
}

int main()
{
	int test_time[] = { 1, 123456789, 349823021, 987654321, 1202990407, 1216468807, 1250312143, 1272636353, 1326193524, 1336549496, 1392837128, 1625675376, 2052743737 };
	int i;
	struct tj_time *tp;

	for (i = 0; i<sizeof(test_time) / sizeof(int); i++) {
		cout << "��ʱ����        ��" << test_time[i] << endl;
		cout << "ϵͳת���Ľ��  ��";
		system_time_output(test_time[i]);

		cout << "�Զ���ת���Ľ����";
		tp = tj_time_convert(test_time[i]);
		tj_time_output(tp);

		cout << endl << "���س�������" << endl;
		getchar();
	}

	if (1) {
		struct tj_time *tp;
		int t = (int)time(0);		//ϵͳ������ȡ��ǰϵͳʱ�䣨��1970-01-01 00:00:00��ʼ����������time_t Ϊϵͳ�����64λ������

		cout << "ϵͳת���ĵ�ǰϵͳʱ�䣺";
		system_time_output(t);

		cout << "�Զ���ת����ǰϵͳʱ�䣺";
		tp = tj_time_convert(t);
		tj_time_output(tp);

		cout << endl << "���س�������" << endl;
		getchar();
	}

	return 0;
}
