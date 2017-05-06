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
	void inputHour()
	{
		cin >> this->hour;
	}
	void inputMinute()
	{
		cin >> minute;
	}
	void inputSec()
	{
		cin >> sec;
	}
	void output()
	{
		cout << hour << ":" << minute << ":" << sec << endl;
	}
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