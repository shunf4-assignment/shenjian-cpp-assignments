/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
/*BLASTClock_SJProject - 90-b3-tools.cpp*/
#include "90-b3.h"

void addSecondsToSystemTime(SYSTEMTIME* timeIn, SYSTEMTIME* timeOut, double sec)
{
	TIMESTAMP t;
	SystemTimeToFileTime(timeIn, &(t.ft));
	t.li.QuadPart += ULONGLONG(sec / clfSecondsPer100ns);
	FileTimeToSystemTime(&(t.ft), timeOut);
}

bool isLeapYear(int year)
{
	return (year % 400 == 0 || year % 100 != 0 && year % 4 == 0);
}

void inputInt(int* p, const char * promptText, const char * cinUngoodText, const char * outLimitText, int lowerLimit, int upperLimit, bool clearBuffer = false)
{
	bool valid;
	do
	{
		valid = true;
		cout << promptText;
		cin >> *p;

		if (!cin.good())
		{
			valid = false;
			cout << cinUngoodText << endl;
		}
		else if (*p > upperLimit || *p < lowerLimit)
		{
			valid = false;
			cout << outLimitText << endl;
		}

		if (!valid)
		{
			cin.clear();
			cin.ignore(FS_MAX_LENGTH, '\n');
			//cin.putback('\1');
			//cin.ignore(FS_MAX_LENGTH, '\1');
			//cin.ignore(1);
		}

	} while (!valid);
	if (clearBuffer)
	{
		cin.ignore(FS_MAX_LENGTH, '\n');
		//cin.putback('\1');
		//cin.ignore(FS_MAX_LENGTH, '\1');
		//cin.ignore(1);
	}
}

void setGlobalColor(int back, int fore)
{
	//run command like "color f0"
	char colorStr[9];
	char colorPlus[2];
	strcpy_s(colorStr, "color ");
	sprintf_s(colorPlus, "%x", back);
	strcat_s(colorStr, colorPlus);
	sprintf_s(colorPlus, "%x", fore);
	strcat_s(colorStr, colorPlus);
	system(colorStr);
}

void initViewAlarm()
{
	setGlobalColor(colorCommBack, colorCommFore);
	setcolor(hout, colorCommBack, colorCommFore);
	system("cls");
	system("title Ë³×ÓÄÖÖÓ");
	setfontsize(hout, fontNormalName, fontNormalSize);
	setconsoleborder(hout, windowNormalW, windowNormalH, windowNormalB);
}

void initClock()
{
	setGlobalColor(colorCommBack, colorCommFore);
	setcolor(hout, colorCommBack, colorCommFore);
	system("cls");
	system("title Ë³×ÓÄÖÖÓ");
	setfontsize(hout, fontCommName, fontCommSize);
	setconsoleborder(hout, windowClockW, windowClockH, windowClockH);
}

void drawCircleAtUpperLeft(COORD pos, int radius)   //radius represents the length of (radius) chars' height.
{
	pos.X += short(round(radius / ratioCharWidthOverHeight));
	pos.Y += radius;
	drawCircleAtCenter(pos, radius);

}

void drawPoint(COORD point, int widthX, int widthY)
{
	//widthX here represents real console coordinate
	int minX = int(round(point.X - ((widthX - 1) / 2)));
	int minY = point.Y - (widthY - 1) / 2;
	int maxX = int(round(point.X + ((widthX - 1) / 2)));
	int maxY = point.Y + (widthY - 1) / 2;
	if (widthY % 2 == 0)
	{
		maxY++;
	}
	if (widthX % 2 == 0)
	{
		maxX++;
	}
	for (int y = minY; y <= maxY; y++)
	{
		gotoxy(hout, minX, y);
		/*for (int i = 0; i < maxX - minX + 1; i++)
		{
			printf(" ");
		}*/
		cout << setw(maxX - minX + 1) << "";
	}
}

void drawHorizontalLine(COORD point, int widthX, int widthY)
{
	//widthX here represents real console coordinate
	int minX = point.X - ((widthX - 1) / 2);
	int minY = point.Y - (widthY - 1) / 2;
	int maxX = point.X + ((widthX - 1) / 2);
	int maxY = point.Y + (widthY - 1) / 2;
	if (widthY % 2 == 0)
	{
		maxY++;
	}
	if (widthX % 2 == 0)
	{
		maxX++;
	}
	for (int y = minY; y <= maxY; y++)
	{
		gotoxy(hout, minX, y);
		/*for (int i = 0; i < maxX - minX + 1; i++)
		{
		printf(" ");
		}*/
		cout << setw(maxX - minX + 1) << "";
	}
}

void drawCircleAtCenter(COORD pos, int radius)   //radius represents the length of (radius) chars' height.
{
	const int density = 360;
	double angleSlice = 2 * pi / density;
	double drawX, drawY;
	double thisAngle;
	COORD drawPos;
	setcolor(hout, colorCommFore, colorCommBack);
	for (int i = 0; i < density; i++)
	{
		thisAngle = i * angleSlice;
		drawX = round(pos.X + radius * cos(thisAngle) / ratioCharWidthOverHeight);
		drawY = round(pos.Y - radius * sin(thisAngle));
		drawPos.X = int(drawX);
		drawPos.Y = int(drawY);
		drawPoint(drawPos, 2, 2);
	}
}

int sgn(int x)
{
	if (x > 0)
		return 1;
	else if (x < 0)
		return -1;
	else
		return 0;
}

int sgn(double x)
{
	if (x > 0)
		return 1;
	else if (x < 0)
		return -1;
	else
		return 0;
}

void drawLineByPoint(COORD point1, COORD point2, int widthX, int widthY)
{
	//make a function like y = ax + b
	short deltaX = abs(point1.X - point2.X);
	short deltaY = abs(point1.Y - point2.Y);
	short tmp;
	int minX, minY, maxX, maxY;
	if (deltaY == 0)
	{
		if (point1.X > point2.X)
		{
			tmp = point1.X;
			point1.X = point2.X;
			point2.X = tmp;
		}
		minX = point1.X - ((widthX - 1) / 2);
		minY = point1.Y - (widthY - 1) / 2;
		maxX = point2.X + ((widthX - 1) / 2);
		maxY = point1.Y + (widthY - 1) / 2;
		if (widthY % 2 == 0)
		{
			maxY++;
		}
		if (widthX % 2 == 0)
		{
			maxX++;
		}
		for (int y = minY; y <= maxY; y++)
		{
			gotoxy(hout, minX, y);
			/*for (int i = 0; i < maxX - minX + 1; i++)
			{
			printf(" ");
			}*/
			cout << setw(maxX - minX + 1) << "";
		}
	}
	else if (deltaX * ratioCharWidthOverHeight < deltaY)
	{
		//drawLineByPointReversed(point1, point2);
		short unitX = sgn(point2.X - point1.X) * 2;
		short unitY = sgn(point2.Y - point1.Y);
		double k = double(point2.X - point1.X) / double(point2.Y - point1.Y);
		double b = point1.X - k * point1.Y;
		double offsetX;
		short currX = point1.X;
		for (short currY = point1.Y; sgn(point2.Y - currY) == sgn(unitY); currY += unitY)
		{
			
			offsetX = k * currY + b;
			if (sgn(offsetX - currX) == sgn(unitX))
			{
				currX += unitX;
			}
			drawPoint({ currX, currY }, widthX, widthY);
		}
	}
	else
	{
		short unitX = sgn(point2.X - point1.X) * 2;
		short unitY = sgn(point2.Y - point1.Y);
		double k = double(point2.Y - point1.Y) / double(point2.X - point1.X);
		double b = point1.Y - k * point1.X;
		double offsetY;
		short currY = point1.Y;
		for (short currX = point1.X;  sgn(point2.X - currX) == sgn(unitX); currX += unitX)
		{
			
			offsetY = k * currX + b;
			if (sgn(offsetY - currY) == unitY)
			{
				currY += unitY;
			}
			drawPoint({ currX, currY }, widthX, widthY);
		}
		
	}
}

void msgInt(int n)
{
	static char str[100] = "";
	sprintf_s(str, "mshta vbscript:msgbox(\"%d\",64,\"\")(window.close)", n);
	system(str);
}

void msgChr(char n)
{
	static char str[100] = "";
	sprintf_s(str, "mshta vbscript:msgbox(\"%c\",64,\"\")(window.close)", n);
	system(str);
}

void msgStr(const char * n)
{
	static char str[100] = "";
	sprintf_s(str, "mshta vbscript:msgbox(\"%s\",64,\"\")(window.close)", n);
	system(str);
}

int keyBoardHit()
{
	unsigned char c;
	if (!_kbhit())
		return NEXT_DO_NOTHING;
	c = _getch();
	if (c == 0 || c == 0xe0)
	{
		_getch();
		return NEXT_DO_NOTHING;
	}
	c = toupper(c);
	if (c == 'E')
	{
		return NEXT_GOTO_ECLOCK;
	}
	if (c == 'C')
	{
		return NEXT_GOTO_CLOCK;
	}
	if (c == 'Q')
	{
		return NEXT_GO_BACK;
	}
	if (c == 'A')
	{
		return NEXT_GOTO_VIEWALARM;
	}
	return NEXT_DO_NOTHING;
}