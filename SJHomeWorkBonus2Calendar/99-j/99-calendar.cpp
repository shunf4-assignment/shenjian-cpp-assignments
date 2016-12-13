/* 1652270 计算机2班 冯舜 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
using namespace std;

#define row 4
#define prespace 6
#define space 3
#define halftitle (space + 2)*7 / 2 - 2
#define gap 3
#define column 3

int zeller(int year, int month, int day)
{
	int c, w;
	(month < 3) && (year = year - 1, month = month + 12);
	c = year / 100, year = year % 100;
	w = year + year / 4 + c / 4 - 2 * c + 13 * (month + 1) / 5 + day - 1;
	return ((w % 7 + 7) % 7);
}

void gotoxy(HANDLE hout, int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hout, coord);
}

void setColor(HANDLE h, bool red, bool green, bool blue, bool inten)
{
	SetConsoleTextAttribute(h, (FOREGROUND_RED * red) | (FOREGROUND_BLUE * blue) | (FOREGROUND_GREEN * green) | (FOREGROUND_INTENSITY * inten));
}

void calendarForWholeYear(int year)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	char weekday[] = "一二三四五六日";
	int monthDay[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

	monthDay[2] += (year % 400 == 0) || (year % 400 != 0 && year % 4 == 0);
	setColor(h, 0, 1, 1, 1);
	cout << setw(prespace) << "" << setw((halftitle + 2) * 3) << "" << year;
	setColor(h, 1, 1, 1, 1);
	cout << " 年 年历" << endl;
	setColor(h, 1, 1, 1, 0);
	for (int q = 0; q < row; q++)
	{
		cout << endl << setw(prespace) << "";
		for (int m = 0; m < 3; m++)
		{//输出X月
			cout << setw(halftitle + (m > 0)*(halftitle + gap)) << "" << setw(2);
			setColor(h, 1, 0, 0, 1);
			cout << q * 3 + m + 1 << " 月";
		}
		setColor(h, 1, 1, 1, 1);
		cout << endl << setw(prespace) << "";
		for (int m = 0; m < 3; m++)
		{//输出星期头
			for (int w = 0; w < 7; w++)
			{
				if (w == 5)
					setColor(h, 1, 1, 0, 1);
				if (w == 6)
					setColor(h, 1, 0, 0, 1);
				if (w == 0)
					setColor(h, 1, 1, 1, 1);
				cout << setw(space) << "" << weekday[w * 2] << weekday[w * 2 + 1];
			}
			cout << setw(gap) << "";
			setColor(h, 1, 1, 1, 0);
		}

		int currDay[3] = { (-6 - zeller(year, q * 3 + 1, 1)) % 7 ,(-6 - zeller(year, q * 3 + 2, 1))%7 ,(-6 - zeller(year, q * 3 + 3, 1))%7 };
		for (int i = 0; i < 6 * 7 * column; i++)
		{
			if (i % (7 * 3) == 0)
			{
				cout << endl;
				cout << setw(prespace) << "";
			}
			if (i % (7 * 3) % 7 == 0 && i % (7 * 3) != 0)
				cout << setw(gap) << "";
			cout << setw(space) << "";
			cout << setw(2);
			if (i % (7 * 3) % 7 == 5)
				setColor(h, 1, 1, 0, 1);
			if (i % (7 * 3) % 7 == 6)
				setColor(h, 1, 0, 0, 1);
			if (i % (7 * 3) % 7 == 0)
				setColor(h, 1, 1, 1, 1);
			if (currDay[i % (7 * 3) / 7] + 1 > 0 && currDay[i % (7 * 3) / 7] + 1 <= monthDay[i % (7 * 3) / 7 + 1 + q * 3])
			{
				cout << currDay[i % (7 * 3) / 7] + 1;
			}
			else
			{
				cout << "";
			}
			currDay[i % (7 * 3) / 7] += 1;
		}
		cout << endl;
	}
	setColor(h, 1, 1, 1, 0);
	cout << endl;
}

void calendarDecorate()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO pBuffer;
	GetConsoleScreenBufferInfo(h, &pBuffer);

	setColor(h, 0, 1, 0, 1);

	int xPos[4] = { prespace };
	int yPos[5] = { 2 };

	for (int i = 1; i < 4; i++)
	{
		xPos[i] = int(xPos[i - 1] + (space + 2) * 7 + gap / 2. + gap / 2. * (i != 1));
		xPos[i] += (xPos[i] - prespace) % 2 * ((i % 2) * 2 - 1);
	}
	for (int i = 1; i < 5; i++)
	{
		yPos[i] = yPos[i - 1] + 9;
	}

	for (int i = 0; i < 5; i++)
	{
		gotoxy(h, prespace, yPos[i]);
		for (int x = int(xPos[0] + 2); x <= xPos[3]; x += 2)
		{
			cout << "━";
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int y = yPos[0]; y <= yPos[4]; y++)
		{
			gotoxy(h, xPos[i], y);
			if ((y - yPos[0]) % 9 == 0)
			{
				if ((y - yPos[0]) / 9 == 0)
				{
					if (i == 0)
						cout << "┏";
					else if (i == 3)
						cout << "┓";
					else
						cout << "┳";
				}
				else if ((y - yPos[0]) / 9 == 4)
				{
					if (i == 0)
						cout << "┗";
					else if (i == 3)
						cout << "┛";
					else
						cout << "┻";
				}
				else
				{
					if (i == 0)
						cout << "┣";
					else if (i == 3)
						cout << "┫";
					else
						cout << "╋";
				}
			}
			else
				cout << "┃";
		}
	}
	double ratio = 0.2;
	int halfwidth = (prespace + (((space + 2) * 21 + gap * 2) / 2));
	int leftedge = int(halfwidth * (1 - ratio));
	leftedge += (leftedge - prespace) % 2;
	int rightedge = int(halfwidth * (1 + ratio));
	rightedge += (rightedge - prespace) % 2;
	setColor(h, 0, 1, 0, 1);

	gotoxy(h, leftedge, 0);
	cout << "╔";
	for (int x = leftedge + 2; x < rightedge; x += 2)
	{
		cout << "━";
	}
	gotoxy(h, rightedge, 0);
	cout << "╗";
	gotoxy(h, leftedge, 2);
	cout << "╩";
	gotoxy(h, rightedge, 2);
	cout << "╩";
	gotoxy(h, leftedge, 1);
	cout << "│";
	gotoxy(h, rightedge, 1);
	cout << "│";

	gotoxy(h, int(prespace), 1);
	cout << "◇";
	for (int i = prespace; i < leftedge - 4; i += 2)
	{
		cout << "·";
	}
	cout << "★";
	gotoxy(h, rightedge + 2, 1);
	cout << "★";

	for (int i = rightedge + 4; i < xPos[3]; i += 2)
	{
		cout << "·";
	}
	cout << "◇";
	setColor(h, 1, 1, 1, 0);
	gotoxy(h, pBuffer.dwCursorPosition.X, pBuffer.dwCursorPosition.Y);
}

int main()
{
	int y;
	bool valid;
	char sysStr[30] = { '\0' };

	//REINPUT:
	sprintf(sysStr, "mode con cols=%d lines=44", prespace * 2 + (space + 2) * (7 * 3) + 2 * gap + 3);
	system(sysStr);

	//freopen("input.txt", "r", stdin);

	valid = false;
	while (!valid) {
		cout << "请输入年份：";
		cin >> y;
		valid = true;

		if (!(cin.rdstate() != ios_base::failbit))
		{
			cout << "输入非法，请重新输入。" << endl;
			cin.clear();
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			valid = false;
			continue;
		}

		if (y < 1900 || y > 2100)
		{
			cout << "年份非法，请重新输入" << endl;
			cin.clear();
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			valid = false;
			continue;
		}

	}
	system("cls");
	cout << endl;
	//calendar(dayForThisMonth, week, dayForLastMonth);
	calendarForWholeYear(y);
	calendarDecorate();
	//goto REINPUT;

	return 0;
}