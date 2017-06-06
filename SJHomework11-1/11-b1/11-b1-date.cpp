/* 1652270 �����2�� ��˴ */
#include "11-b1-date.h"

/* ���� Date ������г�Ա����������ʵ�� */
Date::Date() : year(1900), month(1), day(1)
{
}

Date::Date(int y, int m, int d) : year(y), month(m), day(d)
{
	int validDays;
	if (year > 2099 || year < 1900)
		year = 1900;
	if (month > 12 || month < 1)
		month = 1;
	validDays = dayOfMonth[month] + (month == 2 && isLeapYear());
	if (day < 1 || day > validDays)
		day = 1;
}

bool Date::isLeapYear()const
{
	return _isLeapYear(year);
}

bool Date::set(int y, int m, int d)
{
	int validDays;
	if (1)
	{
		year = y;
		if (year > 2099 || year < 1900)
		{
			this->Date::Date();
			return false;
		}
	}

	if (1)
	{
		month = m;
		if (month > 12 || month < 1)
		{
			this->Date::Date();
			return false;
		}
	}

	validDays = dayOfMonth[month] + (month == 2 && isLeapYear());

	if (1)
	{
		day = d;
		if (day < 1 || day > validDays)
		{
			this->Date::Date();
			return false;
		}
	}
	return true;
}

void Date::get(int &y, int &m, int &d) const
{
	y = year;
	m = month;
	d = day;
}

void Date::show() const
{
	cout << (*this) << endl;
}

Date::Date(int days)
{
	days = (days + 73049 - 1) % 73049 + 1;
	if (days < 1)
	{
		year = 1900;
		month = day = 1;
		return;
	}
	/*if (days <= 1)
	{
		year = 1900;
		month = day = 1;
		return;
	}
	if (days >= 73049)
	{
		year = 2099;
		month = 12;
		day = 31;
		return;
	}*/
	int dayOfThisYear, dayOfThisMonth;
	int y = 1900, m = 1;
	//�������ѭ��
	while (true)
	{
		dayOfThisYear = (365 + _isLeapYear(y));
		if (days <= dayOfThisYear)
			break;
		days -= dayOfThisYear;
		y++;
	}
	year = y;
	//���½���ѭ��
	while (true)
	{
		dayOfThisMonth = dayOfMonth[m] + (m == 2 && isLeapYear());
		if (days <= dayOfThisMonth)
			break;
		days -= dayOfThisMonth;
		m++;
	}
	month = m;
	day = days;
}

Date::operator int() const
{
	//�������ѭ��
	int y = 1900;
	int totalDays = 0;
	for (; y < year; y++)
	{
		totalDays += (365 + _isLeapYear(y));
	}
	//���½���ѭ��
	int m = 1;
	for (; m < month; m++)
	{
		totalDays += (dayOfMonth[m] + (m == 2 && isLeapYear()));
	}
	//��������ռ���
	totalDays += day;
	return totalDays;
}

/* �������Ҫ������ȫ�ֺ�����ʵ�֣�����д�ڴ˴� */
ostream & operator<<(ostream &out, const Date &d)
{
	out << d.year << "��" << d.month << "��" << d.day << "��";
	return out;
}

istream & operator >> (istream &in, Date &d)
{
	int tmpY, tmpM, tmpD;
	in >> tmpY >> tmpM >> tmpD;
	d.Date::Date(tmpY, tmpM, tmpD);
	if (!in.good())
	{
		d.Date::Date();
	}
	return in;
}

bool _isLeapYear(int year)
{
	return (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
}

Date operator++(Date &d, int)
{
	Date d_ = d;
	d = d + 1;
	return d_;
}

Date & operator++(Date &d)
{
	d = d + 1;
	return d;
}

Date operator--(Date &d, int)
{
	Date d_ = d;
	d = d - 1;
	return d_;
}

Date & operator--(Date &d)
{
	d = d - 1;
	return d;
}