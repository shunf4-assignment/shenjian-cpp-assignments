/* 1652270 计算机2班 冯舜 */
/*BLASTClock_SJProject - 90-b3-clock.cpp*/
#include "90-b3.h"

void updateHourHand(Clock &c, SYSTEMTIME t)
{
	double angle;
	double handLen;
	handLen = c.radius * handlenHour;
	if (t.wHour != c.hour || t.wMinute != c.min)
	{
		angle = 2 * pi / 12 * c.hour + pi / 6 * c.min / 60; //+ pi / 6 / 60 * c.sec / 60;
		setcolor(hout, c.colorBack, c.colorBack);
		drawLineByPoint(c.centerPos, { short(round(c.centerPos.X + (handLen * sin(angle)) / ratioCharWidthOverHeight)), short(round(c.centerPos.Y - handLen * cos(angle))) }, thickHour, thickHour);
	}

	angle = 2 * pi / 12 * t.wHour + pi / 6 * t.wMinute / 60; //+ pi / 6 / 60 * t.wSecond / 60;
	setcolor(hout, c.colorFore, c.colorFore);
	drawLineByPoint(c.centerPos, { short(round(c.centerPos.X + (handLen * sin(angle)) / ratioCharWidthOverHeight)), short(round(c.centerPos.Y - handLen * cos(angle))) }, thickHour, thickHour);
}

void updateMinuteHand(Clock &c, SYSTEMTIME t)
{
	double angle;
	double handLen;
	handLen = c.radius * handlenMinute;
	if (t.wMinute != c.min)
	{
		angle = 2 * pi / 60 * c.min;
		setcolor(hout, c.colorBack, c.colorBack);
		drawLineByPoint(c.centerPos, { short(round(c.centerPos.X + (handLen * sin(angle)) / ratioCharWidthOverHeight)), short(round(c.centerPos.Y - handLen * cos(angle))) }, thickMinute, thickMinute);
	}

	angle = 2 * pi / 60 * t.wMinute;
	setcolor(hout, c.colorFore, c.colorFore);
	drawLineByPoint(c.centerPos, { short(round(c.centerPos.X + (handLen * sin(angle)) / ratioCharWidthOverHeight)), short(round(c.centerPos.Y - handLen * cos(angle))) }, thickMinute, thickMinute);
}

void updateSecondHand(Clock &c, SYSTEMTIME t)
{
	double angle;
	double handLen;

	angle = 2 * pi / 60 * c.sec;
	handLen = c.radius * handlenSecond;
	setcolor(hout, c.colorBack, c.colorBack);
	drawLineByPoint(c.centerPos, { short(round(c.centerPos.X + (handLen * sin(angle)) / ratioCharWidthOverHeight)), short(round(c.centerPos.Y - handLen * cos(angle))) }, thickSecond, thickSecond);
	angle = 2 * pi / 60 * t.wSecond;
	setcolor(hout, c.colorFore, c.colorFore);
	drawLineByPoint(c.centerPos, { short(round(c.centerPos.X + (handLen * sin(angle)) / ratioCharWidthOverHeight)), short(round(c.centerPos.Y - handLen * cos(angle))) }, thickSecond, thickSecond);
}

void getTimeToHMS(SYSTEMTIME st, Clock &c)
{
	c.year = st.wYear;
	c.month = st.wMonth;
	c.day = st.wDay;
	c.hour = st.wHour;
	c.min = st.wMinute;
	c.sec = st.wSecond;
}

void getTimeToHMS(SYSTEMTIME st, EClock &c)
{
	c.year = st.wYear;
	c.month = st.wMonth;
	c.day = st.wDay;
	c.hour = st.wHour;
	c.min = st.wMinute;
	c.sec = st.wSecond;
}

void drawGrad(Clock &c)
{
	double handLen = c.radius * (1 - lenGrad);
	double angle;

	setcolor(hout, c.colorFore, c.colorFore);
	for (int i = 0; i < 12; i++)
	{
		angle = 2 * pi / 12 * i;

		drawLineByPoint({ short(round(c.centerPos.X + (c.radius * sin(angle)) / ratioCharWidthOverHeight)), short(round(c.centerPos.Y - c.radius * cos(angle))) }, { short(round(c.centerPos.X + (handLen * sin(angle)) / ratioCharWidthOverHeight)), short(round(c.centerPos.Y - handLen * cos(angle))) }, thickSecond, thickSecond);
	}
}

void drawFigure(Figure &f)
{
	double totalWidth = f.widthX - f.thickX;
	double totalHeight = f.widthY - f.thickY;
	double strokeStartX;
	double strokeStartY;
	double strokeEndX;
	double strokeEndY;
	for (const Stroke(*p) = patFigures[f.n]; p->exr + p->eyr + p->sxr + p->syr; p++)
	{
		strokeStartX = f.startPos.X + totalWidth * p->sxr;
		strokeStartY = f.startPos.Y + totalHeight * p->syr;
		strokeEndX = f.startPos.X + totalWidth * p->exr;
		strokeEndY = f.startPos.Y + totalHeight * p->eyr;
		drawLineByPoint({ short(round(strokeStartX)),short(round(strokeStartY)) }, { short(round(strokeEndX)),short(round(strokeEndY)) }, f.thickX, f.thickY);
	}
}

void drawColon(COORD startPos, int widthY)
{
	drawPoint({ startPos.X , short(round(startPos.Y + widthY * 1. / 3)) }, int(round(thickColon / ratioCharWidthOverHeight)), thickColon);
	drawPoint({ startPos.X , short(round(startPos.Y + widthY * 2. / 3)) }, int(round(thickColon / ratioCharWidthOverHeight)), thickColon);
}

void clearAll(COORD leftTop, COORD rightBottom)
{
	short unit = sgn(rightBottom.Y - leftTop.Y);
	for (short i = leftTop.Y; i <= rightBottom.Y; i += unit)
	{
		gotoxy(hout, leftTop.X, i);
		cout << setw(rightBottom.X - leftTop.X + 1) << "";
	}

}

void drawTwoDigit(Figure &f, COORD startPos, int widthX, int gap, short num1, short num2)
{
	f.n = num1;
	f.startPos = startPos;
	drawFigure(f);
	f.n = num2;
	f.startPos = { short(startPos.X + widthX + gap), startPos.Y };
	drawFigure(f);
}

void drawEClock(EClock &e, SYSTEMTIME st, bool force)
{
	short count = e.havesec ? (6) : (4);
	short totalW = count * e.gap + (count + 1) *e.widthX;
	short totalH = e.widthY;
	Figure f;
	f.thickX = e.thickX;
	f.thickY = e.thickY;
	f.widthX = e.widthX;
	f.widthY = e.widthY;
	//setcolor(hout, colorCommBack, colorCommBack);
	//clearAll({ e.startPos.X, e.startPos.Y }, { e.startPos.X + totalW - 1, e.startPos.Y + totalH - 1 });
	//setcolor(hout, colorCommFore, colorCommFore);

	if (st.wHour != e.hour || force)
	{
		if (!force)
		{
			setcolor(hout, e.colorBack, e.colorBack);
			drawTwoDigit(f, e.startPos, e.widthX, e.gap, e.hour / 10, e.hour % 10);
		}
		setcolor(hout, e.colorFore, e.colorFore);
		drawTwoDigit(f, e.startPos, e.widthX, e.gap, st.wHour / 10, st.wHour % 10);
	}

	if (st.wMinute != e.min || force)
	{
		if (!force)
		{
			setcolor(hout, e.colorBack, e.colorBack);
			drawTwoDigit(f, { e.startPos.X + e.widthX * 2 + e.gap * 1 + e.spaceBetw, e.startPos.Y }, e.widthX, e.gap, e.min / 10, e.min % 10);
		}
		setcolor(hout, e.colorFore, e.colorFore);
		drawTwoDigit(f, { e.startPos.X + e.widthX * 2 + e.gap * 1 + e.spaceBetw, e.startPos.Y }, e.widthX, e.gap, st.wMinute / 10, st.wMinute % 10);
	}

	if (force)
	{
		setcolor(hout, e.colorFore, e.colorFore);
		drawColon({ e.startPos.X + e.widthX * 2 + e.gap * 1 + e.spaceBetw / 2, e.startPos.Y }, e.widthY);
	}

	if (e.havesec && st.wSecond != e.sec || force)
	{
		if (force)
		{
			setcolor(hout, e.colorFore, e.colorFore);
			drawColon({ e.startPos.X + e.widthX * 4 + e.gap * 2 + e.spaceBetw * 3 / 2, e.startPos.Y }, e.widthY);
		}

		if (!force)
		{
			setcolor(hout, e.colorBack, e.colorBack);
			drawTwoDigit(f, { e.startPos.X + e.widthX * 4 + e.gap * 2 + e.spaceBetw * 2, e.startPos.Y }, e.widthX, e.gap, e.sec / 10, e.sec % 10);
		}

		setcolor(hout, e.colorFore, e.colorFore);
		drawTwoDigit(f, { e.startPos.X + e.widthX * 4 + e.gap * 2 + e.spaceBetw * 2, e.startPos.Y }, e.widthX, e.gap, st.wSecond / 10, st.wSecond % 10);
	}

}

void printHanziStr(ifstream &f, short gridSize, COORD startPos, const char * hanzi)
{
	for (const char * p = hanzi; *p; p++, p++)
	{
		printHanZi(f, gridSize, startPos, (const unsigned char *)p);
		startPos.X += short(round(gridSize / ratioCharWidthOverHeight));
	}
}

void printHanZi(ifstream &f, short gridSize, COORD startPos, const unsigned char * hanzi)
{
	if (hanzi[0] < 0xA0 || hanzi[1] < 0xA0)
	{
		char str[40];
		sprintf_s(str, "遇到了非GB2312字符：%c%c", hanzi[0], hanzi[1]);
		msgStr(str);
		return;
	}
	char hanziQW[2];
	char *form;
	int gridSizeCompletedBytes = (gridSize + 7) / 8;
	int numOfBytes = (gridSize * gridSizeCompletedBytes);
	form = new(nothrow) char[numOfBytes];
	if (!form)
		return;
	int offset;
	hanziQW[0] = hanzi[0] - 0xA0;
	hanziQW[1] = hanzi[1] - 0xA0;
	offset = (94 * (hanziQW[0] - 1) + (hanziQW[1] - 1)) * numOfBytes;
	f.seekg(offset, ios::beg);
	f.read(form, numOfBytes);
	for (int j = 0; j < gridSize; j++)
	{
		gotoxy(hout, startPos.X, startPos.Y + j);
		for (int i = 0; i < gridSize; i++)
		{
			if ((form[j * gridSizeCompletedBytes + i / 8] >> (7 - i % 8)) & 1)
			{
				setcolor(hout, colorCommFore, colorCommFore);
			}
			else
			{
				setcolor(hout, colorCommBack, colorCommBack);
			}
			cout << setw(2) << "";
		}
	}
	delete[]form;
}

template <typename T>
void displayDate(ifstream &f, T c, SYSTEMTIME st, bool force)
{
	char buf[10];
	char str[30] = "";
	if (c.day != st.wDay || force)
	{
		sprintf_s(buf, "%d", st.wYear);
		for (int i = 0; buf[i]; i++)
		{
			strncat_s(str, fullNumbers + (buf[i] - '0') * 2, 2);
		}
		strcat_s(str, "年");
		sprintf_s(buf, "%2d", st.wMonth);
		for (int i = 0; buf[i]; i++)
		{
			if (buf[i] == ' ')
			{
				strcat_s(str, "　");
			}
			else
				strncat_s(str, fullNumbers + (buf[i] - '0') * 2, 2);
		}
		strcat_s(str, "月");
		sprintf_s(buf, "%2d", st.wDay);
		for (int i = 0; buf[i]; i++)
		{
			if (buf[i] == ' ')
			{
				strcat_s(str, "　");
			}
			else
				strncat_s(str, fullNumbers + (buf[i] - '0') * 2, 2);
		}
		strcat_s(str, "日　周");
		strncat_s(str, fullWeek + (st.wDayOfWeek) * 2, 2);
		printHanziStr(f, sizeGridComm, clockDatePos, str);
	}
}

void GetLocalTime_(SYSTEMTIME &st, int n)
{
	st.wSecond += n;
	if (st.wSecond >= 60)
	{
		st.wMinute += st.wSecond / 60;
		st.wSecond = st.wSecond % 60;
	}
	if (st.wMinute >= 60)
	{
		st.wHour += st.wMinute / 60;
		st.wMinute = st.wMinute % 60;

	}
	if (st.wHour >= 24)
	{
		st.wHour = st.wHour % 24;
	}
}

int clockMain(ifstream &f, Alarm **a)
{

	Clock c;
	SYSTEMTIME st;
	bool quit;
	int status;
	while (true)
	{
		initClock();
		quit = false;
		c.centerPos = clockCenterPos;
		c.radius = 80;
		c.colorBack = colorCommBack;
		c.colorFore = colorCommFore;
		c.hour = c.min = c.sec = 0;
		GetLocalTime(&st);
		getTimeToHMS(st, c);
		printHanziStr(f, sizeGridComm, clockTextPos1, hintText1);
		printHanziStr(f, sizeGridComm, clockTextPos2, hintText2);

		drawCircleAtCenter(c.centerPos, c.radius);
		drawGrad(c);
		updateSecondHand(c, st);
		updateMinuteHand(c, st);
		updateHourHand(c, st);
		displayDate(f, c, st, true);
		while (true)
		{
			if (c.sec != st.wSecond)
			{
				updateSecondHand(c, st);
				updateMinuteHand(c, st);
				updateHourHand(c, st);
				displayDate(f, c, st, true);
			}

			getTimeToHMS(st, c);

			Sleep(timeRefresh);
			status = keyBoardHit();
			if (status == NEXT_GOTO_ECLOCK || status == NEXT_GOTO_VIEWALARM || status == NEXT_GO_BACK)
			{
				return status;
			}
			status = checkTrigAlarm(&st, a);
			if (status == STATUS_OK)
			{
				return NEXT_GOTO_CLOCK;
			}
			GetLocalTime(&st);
		}
		if (quit)
			break;
	}
	return NEXT_GO_BACK;
}

int EClockMain(ifstream &f, Alarm **a)
{

	EClock e;
	SYSTEMTIME st;
	bool quit;
	int status;
	while (true)
	{
		initClock();
		quit = false;
		e.startPos = EClockStartPos;
		e.gap = 20;
		e.spaceBetw = 60;
		e.thickX = 6, e.thickY = 5;
		e.widthX = 60;
		e.widthY = 60;
		e.havesec = true;
		e.colorBack = colorCommBack;
		e.colorFore = colorCommFore;
		GetLocalTime(&st);
		printHanziStr(f, sizeGridComm, clockTextPos1, hintText1);
		printHanziStr(f, sizeGridComm, clockTextPos2, hintText2);
		getTimeToHMS(st, e);
		drawEClock(e, st, true);
		displayDate(f, e, st, true);
		while (true)
		{
			if (e.sec != st.wSecond)
			{
				drawEClock(e, st, 0);
				displayDate(f, e, st, true);
			}

			getTimeToHMS(st, e);

			Sleep(timeRefresh);
			status = keyBoardHit();
			if (status == NEXT_GOTO_CLOCK || status == NEXT_GOTO_VIEWALARM || status == NEXT_GO_BACK)
			{
				return status;
			}
			status = checkTrigAlarm(&st, a);
			if (status == STATUS_OK)
			{
				return NEXT_GOTO_ECLOCK;
			}
			GetLocalTime(&st);
		}
		if (quit)
			break;
	}
	return NEXT_GO_BACK;

}

