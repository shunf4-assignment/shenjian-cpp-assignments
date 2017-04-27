/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
/*BLASTClock_SJProject - 90-b3-main.cpp*/
#include "90-b3.h"



void clockInterfaces(ifstream &f, Alarm **&a)
{
	int status;
	int toWhere = NEXT_GOTO_CLOCK;
	int lastMain;
	while (true)
	{
		if (toWhere == NEXT_GOTO_CLOCK)
		{
			lastMain = NEXT_GOTO_CLOCK;
			status = clockMain(f, a);
		}
		else if (toWhere == NEXT_GOTO_ECLOCK)
		{
			lastMain = NEXT_GOTO_ECLOCK;
			status = EClockMain(f, a);
		}
		else if (toWhere == NEXT_GOTO_VIEWALARM)
		{
			viewAlarm(a);
			status = lastMain;
		}
		else if (toWhere == NEXT_GO_BACK)
			break;
		toWhere = status;
	}
}



int main()
{


	Alarm **alarms = NULL;
	ifstream f;
	f.open(".\\1652270\\HZK16", ios::in | ios::binary);
	if (!f.is_open())
	{
		cout << "ºº×Ö¿âHZK16²»´æÔÚ" << endl;
		return 0;
	}
	int status;
	status = readAlarm(alarms);
	if (status != STATUS_OK)
	{
		cout << "Error reading alarm config " << alarmFileName << "." << endl;
		return status;
	}
	/*status = writeAlarm(alarms);
	if (status != STATUS_OK)
	{
		cout << "Error writing alarm config " << alarmFileName << "." << endl;
		return status;
	}*/
	
	clockInterfaces(f, alarms);

	freeAlarm(alarms);
	initViewAlarm();
	return 0;
}
