/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

class Days {
private:
	int year;
	int month;
	int day;
	int is_leap_year();  //�ж��Ƿ����꣬�ǣ�����1  /   �񣺷���0
public:
	int calc_days();     //�����ǵ���ĵڼ���
						 /* ������Բ���������Ҫ�����Ա�����Ķ��壬�������� */
	Days(int y, int m, int d);
	bool valid();
};

/* �˴��������Ա����������ʵ�� */
Days::Days(int y, int m, int d) : year(y), month(m), day(d)
{

}

int Days::is_leap_year()
{
	return (year % 100 != 0 && year % 4 == 0) || (year % 400 == 0);
}

bool Days::valid()
{
	static int dayThisMonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month > 12 || month < 1)
	{
		return false;
	}
	dayThisMonth[2] = 28 + is_leap_year();
	if (!((day <= dayThisMonth[month]) && (day > 0)))
		return false;
	return true;
}

int Days::calc_days()
{
	static int dayThisMonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (!valid())
		return -1;
	int dayNoLastMonthEnd = 0;
	dayThisMonth[2] = 28 + is_leap_year();

	for (int i = 1; i <= month - 1; i++)
	{
		dayNoLastMonthEnd += dayThisMonth[i];
	}

	dayNoLastMonthEnd += day;
	return dayNoLastMonthEnd;
}



/* main������׼�� */
int main()
{
	if (1) {
		Days d1(2012, 3, 18);
		cout << "Ӧ�����78�� ʵ���ǣ�" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 12, 31);
		cout << "Ӧ�����365��ʵ���ǣ�" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2012, 12, 31);
		cout << "Ӧ�����366��ʵ���ǣ�" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 2, 29);
		cout << "Ӧ�����-1�� ʵ���ǣ�" << d1.calc_days() << endl;
	}

	return 0;
}
