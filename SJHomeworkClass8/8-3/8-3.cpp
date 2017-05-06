/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include <iostream>
using namespace std;

class Time
{
private:
	int hour;
	int minute;
	int sec;
public:
	
	void inputHour();

	void inputMinute();

	void inputSec();

	void output();

};

int main()
{
	Time t1;
	t1.inputHour();
	t1.inputMinute();
	t1.inputSec();
	t1.output();
	return 0;
}

void Time::inputHour()
{
	cin >> this->hour;
}
void Time::inputMinute()
{
	cin >> minute;
}
void Time::inputSec()
{
	cin >> sec;
}
void Time::output()
{
	cout << hour << ":" << minute << ":" << sec << endl;
}