/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

class Time
{
	// ɾ����//ԭ��void set_time(void);
	// ɾ����//ԭ��void show_time(void);
public: //����
	int hour;
	int minute;
	int sec;
};

void set_time(void); //����
void show_time(void); //����

Time t;
int main()
{
	set_time();
	show_time();
	return 0;
}

void set_time(void) //ԭ��int set_time(void)
{
	cin >> t.hour;
	cin >> t.minute;
	cin >> t.sec;
}

void show_time(void) //ԭ��int show_time(void)
{
	cout << t.hour << ":" << t.minute << ":" << t.sec << endl;
}