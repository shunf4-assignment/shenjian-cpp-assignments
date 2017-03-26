/* 1652270 �����2�� ��˴ */
/*HYPERBejeweled_SJProject - 90-b1-tools.cpp*/
#include "90-b1.h"

void startInit()
{
	srand(unsigned int(time(0)));
	system("color f0");
	system("title ����̨������ - by ˳��");
}

void restoreColor()
{
	setcolor(hout, commonColor[0], commonColor[1]);
}

void gracefullyReturn(int startX)
{
	COORD_ start;
	getxy(hout, start.X, start.Y);
	gotoxy(hout, startX, start.Y + 1);
}

void gracefullyReturn()
{
	COORD_ start;
	getxy(hout, start.X, start.Y);
	gotoxy(hout, start.X, start.Y + 1);
}

void coarselyReturn()
{
	COORD_ start;
	getxy(hout, start.X, start.Y);
	gotoxy(hout, 0, start.Y + 1);
}

int calInterval(int count)
{
	return (int)(dropInterval * (sqrt(count + 1) - sqrt(count)));
}

int calInterval_(int count)
{
	return (int)(dropInterval );
}

void partInit(int part, int w, int h, int b)
{
	switch (part)
	{
		case 0:
			setconsoleborder(hout, w ? w : 100, h ? h : 25, b ? b : 500);
			setfontsize(hout, L"������", 20);
			break;
		case 1:
			setconsoleborder(hout, w ? w : 100, h ? h : 25, b ? b : 500);
			setfontsize(hout, L"������", 20);
			break;
		case 4:
			setconsoleborder(hout, w ? w : 50, h ? h : 30, b ? b : 30);
			setfontsize(hout, L"������", 20);
			break;
		default:
			setconsoleborder(hout, w, h, 500);
			setfontsize(hout, L"������", 20);
			break;
	}
	
	restoreColor();
	system("cls");
	
}

void pressEnterToContinue(char *p)
{
	//�纯����
	if (p == NULL)
		p = "��Enter������������";
	cout << p << endl;
	while (_getch() != '\r')
		;
	return;
}

void inputWidthHeight(int &w, int &h)
{
	inputThing(&w, "��������Ϸ����Ŀ�(5-9)��", "����Ƿ���", "���볬�����ƣ�", 5, 9, true);
	inputThing(&h, "��������Ϸ����ĸ�(5-9)��", "����Ƿ���", "���볬�����ƣ�", 5, 9, true);
}

COORD_ boardUIWH(Map *map, bool border)
{
	COORD_ c;
	if (border)
	{
		c.X = map->w * 4 + 2;
		c.Y = map->h * 2 + 1;
	}
	else
	{
		c.X = map->w * 2 + 4;
		c.Y = map->h + 2;
	}
	return c;
}

COORD_ windowWHCal(Map *map, COORD_ boardWH, int mode)
{
	COORD_ c;
	if (mode >= 4 && mode <= 7 )
	{
		c.X = int(boardWH.X * (1 + part45Spaces[2] + part45Spaces[3]));
		c.Y = int(boardWH.Y * (1 + part45Spaces[0] + part45Spaces[1]));
	}
	else
	{
		c.X = int(boardWH.X * (1 + part45Spaces[2] + part45Spaces[3]));
		c.Y = int(boardWH.Y * (1 + part45Spaces[0] + part45Spaces[1]));
	}
	
	return c;
}

COORD_ startXYCal(COORD_ boardWH, int mode)
{
	COORD_ c;
	if (mode >= 4 && mode <= 7)
	{
		c.X = int(boardWH.X * part45Spaces[2]);
		c.Y = int(boardWH.Y * part45Spaces[0]);
	}
	else
	{
		c.X = int(boardWH.X * part45Spaces[2]);
		c.Y = int(boardWH.Y * part45Spaces[0]);
	}

	return c;
}

void gotoEndOfBoard(Board *b)
{
	gotoxy(hout, 0, b->sc.Y + b->map->h * 2 + 1);
}

void gotoHeadOfBoard(Board *b)
{
	gotoxy(hout, 0, b->sc.Y - 1);
}


void clearLines(int line)
{
	int cols, lines, buffer_coles, buffer_lines, x, y;
	getconsoleborder(hout, cols, lines, buffer_coles, buffer_lines);
	getxy(hout, x, y);
	cout << setw(cols - x) << "";
	line--;
	for (int i = 0; i < line; i++)
	{
		cout << setw(cols) << "";
	}
	gotoxy(hout, x, y);
}

int sgn(int x)
{
	return (x > 0 ? 1 : (x == 0 ? 0 : -1));
}

double comboList(int combo)
{
	return pow(1.5, combo);
}