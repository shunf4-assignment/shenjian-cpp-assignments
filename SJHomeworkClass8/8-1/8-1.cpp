/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

class Time
{
	// 删除。//原：void set_time(void);
	// 删除。//原：void show_time(void);
public: //新增
	int hour;
	int minute;
	int sec;
};

void set_time(void); //新增
void show_time(void); //新增

Time t;
int main()
{
	set_time();
	show_time();
	return 0;
}

void set_time(void) //原：int set_time(void)
{
	cin >> t.hour;
	cin >> t.minute;
	cin >> t.sec;
}

void show_time(void) //原：int show_time(void)
{
	cout << t.hour << ":" << t.minute << ":" << t.sec << endl;
}