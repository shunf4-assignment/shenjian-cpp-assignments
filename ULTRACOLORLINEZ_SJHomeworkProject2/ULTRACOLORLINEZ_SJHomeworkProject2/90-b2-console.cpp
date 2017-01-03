/* 1652270 计算机2班 冯舜 */
/*90-b2-base.cpp*/
#include "90-b2.h"
/* For completing all graphic operations such as print tables and frames, change fonts and textsize and do things related to the cursor*/



void printArray(int (*mapArray)[CL_MAXGRID + 2], bool printColor, int wallElement, int spaceElement, int(*overlayMap)[CL_MAXGRID + 2])
{
	//打印表头
	cout << "  |";
	for (int i = 1; i < CL_MAXGRID + 2 && mapArray[1][i] != wallElement; i++)
	{
		cout << setw(2) << i;
	}
	cout << endl << "--+" << setfill('-') << setw(CL_MAXGRID * 2 + 1) << "" << setfill(' ') << endl;

	//开始打印每行
	for (int(*p)[11] = mapArray + 1; p < mapArray + CL_MAXGRID + 1 && mapArray[p-mapArray][1]!= wallElement; p++)
	{
		cout << numToLetter[p - mapArray] << " |";
		for (int *q = *p + 1; q < *p + 1 + CL_MAXGRID && mapArray[p - mapArray][q - *p] != wallElement; q++)
		{
			
			if (printColor)
			{
				cout << " ";
				if (*q >= 2)
				{
					setcolor(hout, colorList[*q] > 7 ? COLOR_HBLACK : COLOR_HWHITE, colorList[*q]);
					//setcolor(hout, COLOR_BLACK, colorList[*q]);
				}
				if (overlayMap != NULL && overlayMap[p - mapArray][q - *p] >= 1 && mapArray[p - mapArray][q - *p] == spaceElement)
					cout << "*";
				else 
					cout << *q;
				if (*q >= 2)
				{
					setcolor(hout, colorList[0], colorList[1]);//恢复默认颜色
				}
			}
			else if (overlayMap != NULL)
			{
				setcolor(hout, overlayMap[p - mapArray][q - *p] >=1 ? COLOR_HYELLOW : colorList[0], overlayMap[p - mapArray][q - *p] >= 1 ? COLOR_BLUE : colorList[1]);
				cout << " ";
				cout << *q;
				setcolor(hout, colorList[0], colorList[1]);
			}
			else
			{
				cout << setw(2);
				if (*q == spaceElement)
					cout << "";
				else
					cout << *q;
			}
		}
		cout << endl;
	}
}

void graphicNoInsideBorder(int(*mapArray)[CL_MAXGRID + 2], int x, int y)
{
	int w, h;
	getMapWidthHeight(mapArray, w, h);
	for (int r = 0; r <= h + 1; r++)
	{
		gotoxy(hout, x, y + r);
		if (r == 0 || r==h+1)
		{
			cout << box[r == h + 1 ? 8 : 0] << box[r == h + 1 ? 9 : 1];
			for (int c = 0; c < w; c++)
			{
				cout << box[2] << box[3];
			}
			cout << box[r == h + 1 ? 10 : 4] << box[r == h + 1 ? 11 : 5];
		}
		else
		{
			cout << box[6] << box[7];
			cout << setw(w * 2) << "";
			cout << box[6] << box[7];
		}
	}

	for (int i = 1; i <= w; i++)
	{
		for (int j = 1; j <= h; j++)
		{
			if (mapArray[j][i] >= 2)
			{
				setcolor(hout, colorList[0], colorList[mapArray[j][i]]);
				gotoxy(hout, x + 2 * i, y + j);
				cout << "●";
			}
		}
	}

	setcolor(hout, colorList[0], colorList[1]);
	gotoxy(hout, x, y+h+2);
}

void graphicTable(int(*mapArray)[CL_MAXGRID + 2], int x, int y)
{
	int w, h;
	getMapWidthHeight(mapArray, w, h);
	for (int r = 0; r <= h + 1; r++)
	{
		if (r == 0 || r == h + 1)
		{
			gotoxy(hout, x, y + r * 2 - 2* (r==h+1));
			cout << box[r == h + 1 ? 8 : 0] << box[r == h + 1 ? 9 : 1];
			for (int c = 0; c < w; c++)
			{
				cout << box[2] << box[3];
				if (c != w - 1)
				{
					cout << boxIn[r == h + 1 ? 8 : 0] << boxIn[r == h + 1 ? 9 : 1];
				}
			}
			cout << box[r == h + 1 ? 10 : 4] << box[r == h + 1 ? 11 : 5];
		}
		else
		{
			gotoxy(hout, x, y + r * 2 - 1);
			cout << box[6] << box[7];
			for (int sp = 0; sp < w; sp++)
			{
				cout << setw(2) << "";
				cout << box[6] << box[7];
			}
			gotoxy(hout, x, y + r * 2 );
			if (r != h)
			{
				cout << boxIn[2] << boxIn[3];
				for (int sp = 0; sp < w; sp++)
				{
					cout << box[2] << box[3];
					if (sp != w - 1)
						cout << boxIn[4] << boxIn[5];
				}
				cout << boxIn[6] << boxIn[7];
			}
		}
	}

	for (int i = 1; i <= w; i++)
	{
		for (int j = 1; j <= h; j++)
		{
			if (mapArray[j][i] >= 2)
			{
				setcolor(hout, colorList[0], colorList[mapArray[j][i]]);
				gotoxy(hout, x + 4 * i - 2, y + j * 2 - 1);
				cout << "●";
			}
		}
	}

	setcolor(hout, colorList[0], colorList[1]);
	gotoxy(hout, x, y + 2*h + 1);
}

void mouseActions(int startX, int startY, int promptX, int promptY, int quitX, int quitY, int * position, int w, int h) // quit时，position=-1
{
	int X = 0, Y = 0, action;
	int mapX = -1, mapY = -1;
	bool loop = true;
	enable_mouse(hin);
	setcursor(hout, CURSOR_INVISIBLE);

	while (loop)
	{
		action = read_mouse(hin, X, Y);
		if ((X - 2 - startX) % 4 <= 1 && (Y - 1 - startY) % 2 == 0 && (X - 2 - startX) / 4 + 1 >=1 && (X - 2 - startX) / 4 + 1 <= w && (Y - 1 - startY) / 2 + 1 >=1 && (Y - 1 - startY) / 2 + 1 <=h)
		{
			mapX = (X - 2 - startX) / 4 + 1;
			mapY = (Y - 1 - startY) / 2 + 1;
		}
		else
		{
			mapX = mapY = -1;
		}
		/*gotoxy(hout, promptX, promptY+2);
		cout << "当前坐标：  " << Y << " 行 " << X << " 列" << setw(20) << "";*/
		gotoxy(hout, promptX, promptY);
		setcolor(hout, colorList[0], colorList[1]);
		if (mapX != -1 && mapY != -1)
			cout << "当前坐标：  " << numToLetter[mapY] << " 行 " << mapX << " 列" << setw(30) << "" ;
		else
			cout << "鼠标不在游戏方格内" << setw(30) << "";

		switch (action)
		{
			case MOUSE_LEFT_BUTTON_CLICK:
				if ((X - 2 - startX) % 4 <= 1 && (Y - 1 - startY) % 2 <= 1 && mapX >= 1 && mapX <= w && mapY >= 1 && mapY <= h)
				{
					loop = false;
					*position = mapY * (CL_MAXGRID + 1) + mapX;
				}
				break;
			case MOUSE_RIGHT_BUTTON_CLICK:
				loop = false;
				*position = -1;
				break;
		}
		Sleep(20);
	}
}

void addGraphicalBall(int startX, int startY, int currPos, int ballType, int bgColor, int offset)
{
	int i, j;
	decodePos_(currPos, j, i);
	gotoxy(hout, startX + 4 * i - 2 + 2*(offset % 3 -1), startY + j * 2 - 1 + offset / 3-1);
	if (ballType != 0)
	{
		setcolor(hout, bgColor, colorList[ballType]);
		cout << "●";
	}
	else if (offset != 4)
	{
		restoreColor();
		cout << box[(offset % 3 == 1) ? 2 : 6] << box[(offset % 3 == 1) ? 3 : 7];
	}
	else
	{
		cout << "  ";
	}
}

void drawInitUI(int tableWidth, int tableHeight, int tableStartX, int tableStartY, int menuX, int menuY, int KingX, int PretenderX, int KingY, int PretenderY, int nextBallsX, int nextBallsY, int scoreKX, int scoreKY, int scorePX, int scorePY, int(*gameMap)[CL_MAXGRID + 2], int windowWidth, int statX, int statY)
{
	gotoxy(hout, menuX, menuY);
	setcolor(hout, COLOR_WHITE, COLOR_BLACK);
	cout << setw(windowWidth) << "";

	gotoxy(hout, scoreKX, scoreKY);
	restoreColor();
	cout << "┏━━━┓";
	gotoxy(hout, scoreKX, scoreKY + 1);
	cout << "┃ " << setw(4) << "" << " ┃";
	gotoxy(hout, scoreKX, scoreKY + 2);
	cout << "┗━━━┛";

	gotoxy(hout, scorePX, scorePY);
	restoreColor();
	cout << "┏━━━┓";
	gotoxy(hout, scorePX, scorePY+1);
	cout << "┃ " << setw(4) << "" << " ┃";
	gotoxy(hout, scorePX, scorePY+2);
	cout << "┗━━━┛";

	gotoxy(hout, nextBallsX, nextBallsY);
	restoreColor();
	cout << "╔─╦─╦─╗";
	gotoxy(hout, nextBallsX, nextBallsY+1);
	cout << "│  │  │  │";
	gotoxy(hout, nextBallsX, nextBallsY+2);
	cout << "╘─╧─╧─╛";

	gotoxy(hout, statX, statY);
	restoreColor();
	cout << "╔━━━━━━━━━━╗";
	for (int i = 1; i <= tableHeight - 2; i++)
	{
		gotoxy(hout, statX, statY + i);
		cout << "┃                    ┃";
	}
	gotoxy(hout, statX, statY + tableHeight-1);
	cout << "╚━━━━━━━━━━╝";
}
 
void updateScore(int score, int scorePX, int scorePY)
{
	gotoxy(hout, scorePX + 3, scorePY+1);
	restoreColor();
	cout << setw(4) << "";
	gotoxy(hout, scorePX + 3, scorePY + 1);
	cout << setw(4) << score;
}

void updateNextBalls(int *nextBalls, int nextBallsX, int nextBallsY)
{
	int *p = nextBalls;
	int x = nextBallsX + 2;
	while (*p)
	{
		gotoxy(hout, x, nextBallsY + 1);
		x += 4;
		setcolor(hout, colorList[0], colorList[*p]);
		cout << "●";
		p++;
	}
	restoreColor();
}

void updateStats(int (*gameMap)[CL_MAXGRID+2], int *gameStats, int *gameStatsBallDel, int statX, int statY)
{
	int w, h;
	int empty = 0;
	getMapWidthHeight(gameMap, w, h);
	for (int i = 0; i < CL_BALLNUM; i++)
	{
		gameStats[i + 2] = 0;
	}
	for (int i = 1; i <= w; i++)
	{
		for (int j = 1; j <= h; j++)
		{
			if (gameMap[j][i] == 0)
			{
				empty += 1;
			}
			else
			{
				gameStats[gameMap[j][i]]++;
			}
		}
	}
	gotoxy(hout, statX + 3, statY + 1);
	cout << setiosflags(ios::fixed) << setprecision(1) << "空：" << empty << "(" << empty*100. / (w*h) << "%)";
	for (int i = 0; i < CL_BALLNUM; i++)
	{
		gotoxy(hout, statX + 3, statY + i + 3);
		setcolor(hout, colorList[0], colorList[i + 2]);
		cout << "●";
		restoreColor();
		cout << "：" << gameStats[i+2] << "(" << gameStats[i + 2] *100. / (w*h) << "%), 消" << gameStatsBallDel[i + 2];
	}

}