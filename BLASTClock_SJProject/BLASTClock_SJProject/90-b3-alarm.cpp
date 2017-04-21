/* 1652270 计算机2班 冯舜 */
/*BLASTClock_SJProject - 90-b3-alarm.cpp*/
#include "90-b3.h"

void playAudio()
{
	const char * const mci1 = "open ";
	const char * const mci2 = " type mpegvideo alias alarm";
	int mcistrlen = strlen(mci1) + strlen(audioFileName) + strlen(mci2);
	char *mcistr;
	mcistr = new(nothrow) char[mcistrlen + 1];
	if (!mcistr)
		return;
	strcpy_s(mcistr, mcistrlen + 1, mci1);
	strcat_s(mcistr, mcistrlen + 1, audioFileName);
	strcat_s(mcistr, mcistrlen + 1, mci2);
	mciSendString(mcistr, NULL, 0, NULL);
	mciSendString("play alarm repeat", NULL, 0, NULL);
	delete[]mcistr;
}

void stopAudio()
{
	mciSendString("stop alarm", NULL, 0, NULL);
	mciSendString("close alarm", NULL, 0, NULL);
}

int checkTrigAlarm(SYSTEMTIME *stp, Alarm **alarms)
{
	TIMESTAMP ts;
	Alarm ** p;
	SystemTimeToFileTime(stp, &ts.ft);
	for (p = alarms; *p; p++)
	{
		if ((*p)->nexttime.li.QuadPart <= ts.li.QuadPart)
		{
			//gotcha
			break;
		}
	}
	if (*p)
	{
		initViewAlarm();
		cout << "您的闹钟：" << endl;
		viewThisAlarm(p, alarms);
		cout << endl << "到时。请按任意键停止闹铃的播放。" << endl;
		//msgStr("闹钟响了！");
		updateAlarmNextTime(**p);
		orderAlarm(alarms);
		writeAlarm(alarms);
		playAudio();
		system("pause");
		stopAudio();
		return STATUS_OK;
	}
	else
	{
		return FERROR_GENERAL;
	}
}

void printTime(SYSTEMTIME st)
{
	cout << st.wYear << "-" << st.wMonth << "-" << st.wDay << " ";
	cout << setw(2) << st.wHour << ":";
	cout << setfill('0') << setw(2) << st.wMinute;
	cout << "." << setfill('0') << setw(2) << st.wSecond << setfill(' ');
}

void turnSystemTimeToStamp(Alarm &a)
{
	//For once alarm, the 'stamp' in Alarm struct is exactly the time when the program alarms.
	//For repeating alarm, for easy computing, the 'stamp' needs to record the very beginning moment of the week when the alarm is set.s
	if (a.alarmtype == ALARM_REPEAT)
	{
		SYSTEMTIME st1;
		st1 = a.t;
		st1.wHour = st1.wMinute = st1.wSecond = st1.wMilliseconds = 0;
		addSecondsToSystemTime(&(st1), &(st1), 0);  //normalize wDayOfWeek
		addSecondsToSystemTime(&(st1), &(st1), -st1.wDayOfWeek * 24 * 3600);

		SystemTimeToFileTime(&(st1), &(a.stamp.ft));
	}
	else
	{
		addSecondsToSystemTime(&(a.t), &(a.t), 0);  //normalize wDayOfWeek
		SystemTimeToFileTime(&(a.t), &(a.stamp.ft));
	}

}

void updateAlarmNextTime(Alarm &a, bool force )
{
	
	SYSTEMTIME st, oldSt, newSt;
	TIMESTAMP ts, newTs;
	int weeksSinceInitialWeek;
	GetLocalTime(&st);
	newSt = st;
	SystemTimeToFileTime(&st, &(ts.ft));
	if (a.alarmtype == ALARM_ONCE)
	{
		if (a.stamp.li.QuadPart < ts.li.QuadPart && !force)
		{
			//outdated alarm
			a.nexttime.li.QuadPart = MAXLONGLONG;
		}
		else
		{
			a.nexttime = a.stamp;
		}
		return;
	}

	weeksSinceInitialWeek = int((ts.li.QuadPart - a.stamp.li.QuadPart) * clfSecondsPer100ns) / (7 * 86400);
	weeksSinceInitialWeek += a.weekgap - 1;
	weeksSinceInitialWeek = weeksSinceInitialWeek / a.weekgap * a.weekgap;
	FileTimeToSystemTime(&(a.stamp.ft), &oldSt);
	do
	{
		for (int i = 0; i < 7; i++)
		{
			if ((a.weekday >> i) & 1)
			{
				addSecondsToSystemTime(&oldSt, &newSt, (weeksSinceInitialWeek * 7 + i) *(86400) + a.t.wHour * 3600 + a.t.wMinute * 60 + a.t.wSecond);
				SystemTimeToFileTime(&newSt, &(newTs.ft));
				if (newTs.li.QuadPart > ts.li.QuadPart)
				{
					break;
				}
			}
		}
		if (!(newTs.li.QuadPart > ts.li.QuadPart))
		{
			addSecondsToSystemTime(&oldSt, &oldSt, 7 * 86400 * a.weekgap);
		}
	} while (newTs.li.QuadPart <= ts.li.QuadPart);
	a.nexttime = newTs;

}

int addAlarm(Alarm **&alarms, int originalAlarmsSize)
{
	int inp;
	SYSTEMTIME st;
	char buf[ALARM_BUFLEN + 1];
	Alarm newAlarm;
	Alarm **newAlarmsP, *newAlarmP;


	newAlarmsP = (Alarm **)realloc(alarms, (originalAlarmsSize + 2) * sizeof(Alarm *));
	if (!newAlarmsP)
	{
		return FERROR_MEMORY_LOW;
	}
	alarms = newAlarmsP;

	newAlarmP = (Alarm *)malloc(sizeof(Alarm) * 1);

	if (!newAlarmP)
	{
		return FERROR_MEMORY_LOW;
	}

	alarms[originalAlarmsSize + 1] = NULL;
	alarms[originalAlarmsSize] = newAlarmP;

	cout << ALARM_ONCE << ": 一次性闹钟     " << ALARM_REPEAT << ": 重复闹钟" << endl;
	cout << "2: 倒计时" << endl;
	inputInt(&inp, "请输入：", "输入非法。", "输入超出限制。", 0, 2, false);
	newAlarm.alarmtype = inp;

	if (newAlarm.alarmtype != 2)
	{

		GetLocalTime(&st);
		if (newAlarm.alarmtype == ALARM_ONCE)
		{
			inputInt(&inp, "请输入年：", "输入非法。", "输入超出限制。", st.wYear, st.wYear + MAX_AFTER_YEAR, false);
			newAlarm.t.wYear = inp;
			GetLocalTime(&st);
			inputInt(&inp, "请输入月：", "输入非法。", "输入超出限制。", 1, 12, false);
			newAlarm.t.wMonth = inp;
			GetLocalTime(&st);
			inputInt(&inp, "请输入日：", "输入非法。", "输入超出限制。", 1, dayOfThisMonth[isLeapYear(newAlarm.t.wYear)][newAlarm.t.wMonth], false);
			newAlarm.t.wDay = inp;
		}
		else
		{
			newAlarm.t = st;
		}
		inputInt(&inp, "请输入时：", "输入非法。", "输入超出限制。", 0, 23, false);
		newAlarm.t.wHour = inp;
		inputInt(&inp, "请输入分：", "输入非法。", "输入超出限制。", 0, 59, false);
		newAlarm.t.wMinute = inp;
		newAlarm.t.wSecond = 0;
		newAlarm.t.wMilliseconds = 0;
		GetLocalTime(&st);
		if (newAlarm.alarmtype == ALARM_REPEAT)
		{


			inputInt(&inp, "输入隔周数（每周->1，每单/双周->2，此周始计）：", "输入非法。", "输入超出限制。", 1, INT_MAX, true);
			newAlarm.weekgap = inp;
			cout << "输入每周响闹情况。xxr:休息日，gzr:工作日，mr:每日，单独制定如 0101010:每周一三五响闹。" << endl;
			cin.getline(buf, strlen(buf) + 1);
			inp = 0;
			if (strcmp(buf, "xxr") == 0)
			{
				strcpy_s(buf, "1000001");
			}
			if (strcmp(buf, "gzr") == 0)
			{
				strcpy_s(buf, "0111110");
			}
			if (strcmp(buf, "mt") == 0)
			{
				strcpy_s(buf, "1111111");
			}
			for (unsigned int i = 0; i < 7; i++)
			{
				if ((buf[i] - '0'))
					inp |= (1 << i);
			}
			newAlarm.weekday = inp;
			turnSystemTimeToStamp(newAlarm);
		}
		else
		{
			newAlarm.weekgap = newAlarm.weekday = 0;
			turnSystemTimeToStamp(newAlarm);
		}

	}
	else
	{

		int tickHour, tickMinute, tickSecond;
		int totalSec = 0;
		inputInt(&tickHour, "请输入倒计时的小时数：", "输入非法。", "输入超出限制。", 0, INT_MAX, false);
		inputInt(&tickMinute, "请输入分钟数：", "输入非法。", "输入超出限制。", 0, INT_MAX, false);
		inputInt(&tickSecond, "请输入秒钟数：", "输入非法。", "输入超出限制。", 0, INT_MAX, false);
		totalSec += tickHour * 3600;
		totalSec += tickMinute * 60;
		totalSec += tickSecond;

		newAlarm.alarmtype = ALARM_ONCE;
		newAlarm.weekgap = newAlarm.weekday = 0;
		GetLocalTime(&st);
		newAlarm.t = st;
		addSecondsToSystemTime(&(newAlarm.t), &(newAlarm.t), totalSec);
		turnSystemTimeToStamp(newAlarm);
	}

	updateAlarmNextTime(newAlarm);
	*newAlarmP = newAlarm;
	orderAlarm(alarms);
	writeAlarm(alarms);
	return STATUS_OK;
}

void deleteAlarm(Alarm **&alarms, int alarmNo)
{
	int count = 0;
	Alarm **p;
	for (p = alarms; *p; p++)
		;
	count = p - alarms;
	free(alarms[alarmNo - 1]);
	memcpy_s(alarms + alarmNo - 1, (count - alarmNo + 2) * sizeof(Alarm *), alarms + alarmNo, (count - alarmNo + 1) * sizeof(Alarm *));
	writeAlarm(alarms);
}

void viewThisAlarm(Alarm **p, Alarm **alarms)
{
	TIMESTAMP ts1;
	SYSTEMTIME st1;
	cout << setw(2) << (p - alarms + 1) << ". ";
	if ((*p)->alarmtype == ALARM_REPEAT)
	{
		cout << "重复闹钟  ";
	}
	else if ((*p)->alarmtype == ALARM_ONCE)
	{
		cout << "一次闹钟  ";
	}
	else
	{
		cout << "???闹钟  ";
	}
	printTime((*p)->t);
	cout << "  ";
	if (debugSwitch)
	{
		cout << "内部timestamp标记：";
		ts1 = (*p)->stamp;
		FileTimeToSystemTime(&(ts1.ft), &st1);
		printTime(st1);
		cout << "  ";
	}
	if ((*p)->alarmtype == ALARM_REPEAT)
	{
		cout << "每 " << (*p)->weekgap << " 周重复一次，";
		cout << "在 ";
		for (int i = 0; i < 7; i++)
		{
			if (((*p)->weekday >> i) & 1)
			{
				cout << weekDayName[i * 2] << weekDayName[i * 2 + 1];
			}
		}
		cout << " 响铃  ";
	}
	cout << "下次响闹时间：";
	ts1 = (*p)->nexttime;
	FileTimeToSystemTime(&(ts1.ft), &st1);
	printTime(st1);
}

int viewAlarm(Alarm **&alarms)
{
	char c;
	Alarm **p;
	while (true)
	{
		initViewAlarm();
		cout << "当前的闹钟设定有：" << endl << endl;
		for (p = alarms; *p; p++)
		{
			if (p - alarms)
				cout << endl;
			viewThisAlarm(p, alarms);
			cout << " ";
		}
		if (p == alarms)
		{
			cout << "（空）" << endl;
		}
		cout << endl << endl;
		cout << "a. 添加闹铃     b.删除闹铃" << endl;
		cout << "c. 返回         d.重设闹铃响闹时间" << endl;
		cout << "" << endl;
		do
		{
			cout << "输入：";
			cin >> c;
			c = tolower(c);
			if (c >= 'a' && c <= 'd')
			{
				break;
			}
			else
			{
				cout << "输入非法。" << endl;
			}
			cin.clear();
			cin.ignore(FS_MAX_LENGTH, '\n');
			cin.sync();
		} while (true);
		if (c == 'a')
		{
			//add alarm
			if (addAlarm(alarms, p - alarms) == STATUS_OK)
			{
				cout << "添加成功！" << endl;
				system("pause");
			}
			else
			{
				cout << "添加失败！" << endl;
				system("pause");
			}
		}
		if (c == 'b')
		{
			//delete alarm
			int alarmNo;
			inputInt(&alarmNo, "请输入闹钟编号：", "输入非法", "输入超出限制", 1, p - alarms, true);
			deleteAlarm(alarms, alarmNo);
		}
		if (c == 'c')
		{
			break;
		}
		if (c == 'd')
		{
			for (Alarm **p = alarms; *p; p++)
			{
				updateAlarmNextTime(**p, true);
			}
			orderAlarm(alarms);
			writeAlarm(alarms);
		}
	}

	//system("pause");
	return STATUS_OK;
}

int createAlarmFile()
{
	ofstream fo;
	fo.open(alarmFileName, ios::out);
	if (!fo.is_open())
	{
		return FERROR_FILE_FAIL;
	}
	fo << "#(repeat/once) y m d hour min sec weekgap nexttimestamp SMTWTFS" << endl;
	fo.close();
	return STATUS_OK;
}

void freeAlarm(Alarm **alarms)
{
	for (Alarm **p = alarms; (*p); p++)
	{
		free(*p);
	}
	free(alarms);
}

int writeAlarm(Alarm **alarms)
{
	Alarm **p;
	ofstream f;
	int status;

	status = createAlarmFile();
	if (status != STATUS_OK)
		return status;
	f.open(alarmFileName, ios::app);
	if (!f.is_open())
	{
		return FERROR_FILE_FAIL;
	}

	for (p = alarms; *p; p++)
	{
		f << (((*p)->alarmtype == ALARM_REPEAT) ? "repeat " : "once ");
		f << ((*p)->t.wYear) << " " << ((*p)->t.wMonth) << " " << ((*p)->t.wDay) << " ";
		f << ((*p)->t.wHour) << " " << ((*p)->t.wMinute) << " " << ((*p)->t.wSecond) << " " << ((*p)->weekgap) << " " << ((*p)->nexttime.li.QuadPart) << " ";
		for (int i = 0; i < 7; i++)
		{
			f << char('0' + !!(((*p)->weekday >> i) & 1));
		}
		f << endl;
	}

	f.close();
	return STATUS_OK;
}

int readAlarm(Alarm **&alarms)
{
	Alarm **p;
	ifstream f;
	//SYSTEMTIME st, st_;
	char c;
	int count = 0, status;
	char line[ALARMFILE_MAX_LINELEN];
	char buf[ALARMFILE_MAX_LINELEN];

	//GetLocalTime(&st);
	//st_ = st;

	f.open(alarmFileName, ios::in);
	if (!f.is_open())
	{
		//return FERROR_FILE_FAIL;
		status = createAlarmFile();
		if (status != STATUS_OK)
			return status;
		f.open(alarmFileName, ios::in);
		if (!f.is_open())
		{
			return FERROR_FILE_FAIL;
		}
	}

	istrstream s(line, sizeof line);
	while (f.good())
	{
		f.get(line, ALARMFILE_MAX_LINELEN, '\n');
		s.seekg(0, ios::beg);
		s >> c;
		if (c == '#' || c == '\0')
		{
			//comment or space
			;
		}
		else
		{
			count++;
		}
		f.ignore(ALARMFILE_MAX_LINELEN, '\n');
		f.peek();
	}
	f.clear();
	f.seekg(0, ios::beg);

	//alarms = new(nothrow) Alarm *[count + 1];
	alarms = (Alarm **)malloc((count + 1) * sizeof(Alarm *));
	if (!alarms)
	{
		f.close();
		return FERROR_MEMORY_LOW;
	}

	for (int i = 0; i < count + 1; i++)
	{
		alarms[i] = NULL;
	}

	p = alarms;
	f.get(line, ALARMFILE_MAX_LINELEN, '\n');
	while (f.good())
	{
		s.seekg(0, ios::beg);
		s >> c;
		if (c == '#')
		{
			//comment
			;
		}
		else
		{
			s.seekg(0, ios::beg);
			//*p = new(nothrow) Alarm;
			*p = (Alarm *)malloc(sizeof(Alarm));
			if (!(*p))
			{
				freeAlarm(alarms);
				return FERROR_MEMORY_LOW;
			}
			s >> buf;
			if (!strcmp(buf, "repeat"))
			{
				(*p)->alarmtype = ALARM_REPEAT;
			}
			else
			{
				(*p)->alarmtype = ALARM_ONCE;
			}
			s >> (*p)->t.wYear;
			s >> (*p)->t.wMonth;
			s >> (*p)->t.wDay;
			s >> (*p)->t.wHour;
			s >> (*p)->t.wMinute;
			s >> (*p)->t.wSecond;
			s >> (*p)->weekgap;
			s >> (*p)->nexttime.li.QuadPart;
			s >> buf;
			(*p)->weekday = 0;
			(*p)->t.wMilliseconds = 0;
			for (unsigned int i = 0; i < strlen(buf); i++)
			{
				if ((buf[i] - '0'))
					(*p)->weekday |= (1 << i);
			}
			turnSystemTimeToStamp(**p);
			//SystemTimeToFileTime(&((*p)->t), &((*p)->stamp.ft));
			p++;
		}
		f.ignore(ALARMFILE_MAX_LINELEN, '\n');
		//f.peek();
		f.get(line, ALARMFILE_MAX_LINELEN, '\n');

	}
	orderAlarm(alarms);
	f.close();
	return STATUS_OK;
}

void orderAlarm(Alarm **alarms)
{
	int count;
	int minIndex = -1;
	ULONGLONG minTime = 0;
	Alarm **p, *tmp;
	for (p = alarms; *p; p++)
		;
	count = p - alarms;
	for (int i = 0; i < count; i++)
	{
		minIndex = i;
		minTime = alarms[i]->nexttime.li.QuadPart;
		for (int j = i + 1; j < count; j++)
		{
			if (alarms[j]->nexttime.li.QuadPart < minTime)
			{
				minIndex = j;
				minTime = alarms[j]->nexttime.li.QuadPart;
			}
		}
		tmp = alarms[minIndex];
		alarms[minIndex] = alarms[i];
		alarms[i] = tmp;
	}
}