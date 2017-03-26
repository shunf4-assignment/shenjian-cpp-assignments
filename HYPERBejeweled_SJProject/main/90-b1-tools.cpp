/* 1652270 计算机2班 冯舜 */
/*HYPERBejeweled_SJProject - 90-b1-tools.cpp*/
#include "90-b1.h"

void startInit()
{
	srand(unsigned int(time(0)));
	system("color f0");
	system("title 控制台消消乐 - by 顺子");
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
			setfontsize(hout, L"新宋体", 20);
			break;
		case 1:
			setconsoleborder(hout, w ? w : 100, h ? h : 25, b ? b : 500);
			setfontsize(hout, L"新宋体", 20);
			break;
		case 4:
			setconsoleborder(hout, w ? w : 50, h ? h : 30, b ? b : 30);
			setfontsize(hout, L"新宋体", 20);
			break;
		default:
			setconsoleborder(hout, w, h, 500);
			setfontsize(hout, L"新宋体", 20);
			break;
	}
	
	restoreColor();
	system("cls");
	
}

void pressEnterToContinue(char *p)
{
	//如函数名
	if (p == NULL)
		p = "按Enter按键继续……";
	cout << p << endl;
	while (_getch() != '\r')
		;
	return;
}

void inputWidthHeight(int &w, int &h)
{
	inputThing(&w, "请输入游戏区域的宽(5-9)：", "输入非法！", "输入超过限制！", 5, 9, true);
	inputThing(&h, "请输入游戏区域的高(5-9)：", "输入非法！", "输入超过限制！", 5, 9, true);
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