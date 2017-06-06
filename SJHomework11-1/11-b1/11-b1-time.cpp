/* 1652270 计算机2班 冯舜 */
#include "11-b1-time.h"

Time::Time() : hour(0), minute(0), second(0)
{

}

Time::Time(int h, int m, int s) : hour(h), minute(m), second(s)
{
	if (hour < 0 || hour > 23)
		hour = 0;
	if (minute < 0 || minute > 59)
		minute = 0;
	if (second < 0 || second > 59)
		second = 0;
}

bool Time::set(int h, int m, int s)
{
	if (1)
	{
		hour = h;
		if (hour < 0 || hour > 23)
		{
			this->Time::Time();
			return false;
		}
	}
	if (1)
	{
		minute = m;
		if (minute < 0 || minute > 59)
		{
			this->Time::Time();
			return false;
		}
	}
	if (1)
	{
		second = s;
		if (second < 0 || second > 59)
		{
			this->Time::Time();
			return false;
		}
	}
	return true;
}

void Time::get(int &h, int &m, int &s) const
{
	h = hour;
	m = minute;
	s = second;
}

void Time::show()  const
{
	cout << *this << endl;
}

Time::Time(int seconds)
{
	seconds = (seconds + 86400) % 86400;
	if (seconds < 0)
	{
		hour = minute = second = 0;
		return;
	}
	hour = seconds / 3600;
	minute = seconds % 3600 / 60;
	second = seconds % 60;
}

Time::operator int() const
{
	return hour * 3600 + minute * 60 + second;
}

/*
*	int Time::plusSeconds(int seconds)
*		对本 Time 加上 seconds 秒（若seconds为复数，则减去其数值）
*		返回的是溢出次数，有正负号。
*		如加后，使 Time 两次由23.59.59变为0.0.0，则溢出次数为 2；
*		如减后，使 Time 三次由0.0.0变为23.59.59，则溢出次数为 -3。
*/
int Time::plusSeconds(int seconds)
{
	int overflow;	//时间量的溢出次数

	int timeSeconds = int(*this);
	timeSeconds += seconds;
	overflow = 0;
	if (timeSeconds >= 86400)
	{
		overflow = timeSeconds / 86400;
		timeSeconds %= 86400;
	}
	else if (timeSeconds < 0)
	{
		overflow = (timeSeconds / 86400) - 1;
		timeSeconds = (86400 + (timeSeconds % 86400)) % 86400;
	}

	this->Time::Time(timeSeconds);
	return overflow;
}

ostream & operator<<(ostream &out, const Time &t)
{
	out << t.hour << ":" << t.minute << "." << t.second;
	return out;
}

istream & operator >> (istream &in, Time &t)
{
	int tmpH, tmpM, tmpS;
	in >> tmpH >> tmpM >> tmpS;
	t.Time::Time(tmpH, tmpM, tmpS);
	if (!in.good())
	{
		t.Time::Time();
	}
	return in;
}

Time operator++(Time &t, int)
{
	Time t_ = t;
	t = t + 1;
	return t_;
}

Time & operator++(Time &t)
{
	t = t + 1;
	return t;
}

Time operator--(Time &t, int)
{
	Time t_ = t;
	t = t - 1;
	return t_;
}

Time & operator--(Time &t)
{
	t = t - 1;
	return t;
}

