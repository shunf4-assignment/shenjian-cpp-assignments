/* 1652270 计算机2班 冯舜 */
/*90-b2-console.cpp*/
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

void graphicTable(int(*mapArray)[CL_MAXGRID + 2], int x, int y, bool border)
{
	int w, h;
	getMapWidthHeight(mapArray, w, h);
	if (border)
	{
		for (int r = 0; r <= h + 1; r++)
		{
			if (r == 0 || r == h + 1)
			{
				gotoxy(hout, x, y + r * 2 - 2 * (r == h + 1));
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
				gotoxy(hout, x, y + r * 2);
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

int mouseActions(int startX, int startY, int promptX, int promptY, int quitX, int quitY, int * position, int w, int h, bool keyBoard) // quit时，position=-1
{
	int X = 0, Y = 0, action;
	int mapX = -1, mapY = -1;
	bool loop = true;
	enable_mouse(hin);
	setcursor(hout, CURSOR_INVISIBLE);

	while (loop)
	{
		action = keyBoard?read_mouse_and_key(hin, X, Y,1): read_mouse(hin, X, Y, 1);

		if (action >= 0x72 && action <= 0x74)
		{
			return action; //Fn键码
		}
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
	return -1;  //鼠标
}

void addGraphicalBall(int startX, int startY, int currPos, int ballType, int bgColor, int offset, bool select)
{
	int i, j;
	decodePos_(currPos, j, i);
	gotoxy(hout, startX + 4 * i - 2 + 2*(offset % 3 -1), startY + j * 2 - 1 + offset / 3-1);
	if (ballType != 0)
	{
		setcolor(hout, bgColor, colorList[ballType]);
		cout << (select?"◎":"●");
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

void calHeight(int score, int kingScore, int height, int &hp, int &hk)
{
	if (score > kingScore)
	{
		hp = height;
		hk = height - (score - kingScore) / 20;
		(hk < 0) && (hk = 0);
	}
	else
	{
		hk = height;
		hp = int(height * (score * 1. / kingScore));
	}
}

void updateKingPret(int score, int kingScore, int KingX, int KingY, int PretenderX, int PretenderY, bool dialog)
{
	int hk, hp;
	calHeight(score, kingScore, kingHeight, hp, hk);

	for (int i = -1; i < int(kingHeight + strlen(kingStr) / kingLen); i++)
	{
		gotoxy(hout, KingX - 2, KingY + i);
		cout << setw(kingLen + 8) << "";
	}
	for (int i = -1; i < int(kingHeight + strlen(pretStr) / pretLen); i++)
	{
		gotoxy(hout, PretenderX - 2, PretenderY + i);
		cout << setw(pretLen + 8) << "";
	}
	if (dialog)
	{
		gotoxy(hout, KingX, KingY + kingHeight - hk - 1);
		cout << "@顺 来";

		gotoxy(hout, PretenderX - 2, PretenderY + kingHeight - hp - 1);
		cout << "反、反抗沈坚暴政";
	}

	setcolor(hout, colorList[0], colorList[CL_BALLNUM + 4]);
	for (char *p = (char *)((kingScore > score) ? kingStr : kingDef); *p;)
	{
		gotoxy(hout, KingX, KingY + (p - ((kingScore > score) ? kingStr : kingDef)) / kingLen + kingHeight - hk);
		for (int i = 0; i < kingLen; i++)
		{
			cout << *p;
			p++;
		}
	}

	setcolor(hout, colorList[CL_BALLNUM + 3], colorList[CL_BALLNUM + 4]);
	for (int i = 0; i < hk + 1; i++)
	{
		gotoxy(hout, KingX, KingY + strlen(kingStr) / kingLen + kingHeight - i);
		for (int j = 0; j < kingLen / 2; j++)
			cout << "  ";
	}

	setcolor(hout, colorList[0], colorList[CL_BALLNUM + 5]);
	for (char *p = (char *)((kingScore > score) ? pretStr : pretWin); *p;)
	{
		gotoxy(hout, PretenderX, PretenderY + (p - ((kingScore > score) ? pretStr : pretWin)) / pretLen + kingHeight - hp);
		for (int i = 0; i < pretLen; i++)
		{
			cout << *p;
			p++;
		}
	}
	setcolor(hout, colorList[CL_BALLNUM + 3], colorList[CL_BALLNUM + 5]);
	for (int i = 0; i < hp + 1; i++)
	{
		gotoxy(hout, PretenderX, PretenderY + strlen(pretStr) / pretLen + kingHeight - i);
		for (int j = 0; j < pretLen / 2; j++)
			cout << "  ";
	}
	restoreColor();
}

void drawInitUI(int tableWidth, int tableHeight, int tableStartX, int tableStartY, int menuX, int menuY, int KingX, int PretenderX, int KingY, int PretenderY, int nextBallsX, int nextBallsY, int scoreKX, int scoreKY, int scorePX, int scorePY, int(*gameMap)[CL_MAXGRID + 2], int windowWidth, int statX, int statY, bool nextBallsVisible, bool gameStatsVisible, int score, int kingScore)
{
	

	gotoxy(hout, menuX, menuY);
	setcolor(hout, COLOR_WHITE, COLOR_BLACK);
	cout << setw(windowWidth) << "";

	gotoxy(hout, scoreKX, scoreKY);
	restoreColor();
	cout << "┏━━━┓";
	gotoxy(hout, scoreKX, scoreKY + 1);
	cout << "┃ " << " 100" << " ┃";
	gotoxy(hout, scoreKX, scoreKY + 2);
	cout << "┗━━━┛";
	gotoxy(hout, scoreKX, scoreKY + 3);
	cout << "  沈坚  ";

	gotoxy(hout, scorePX, scorePY);
	restoreColor();
	cout << "┏━━━┓";
	gotoxy(hout, scorePX, scorePY+1);
	cout << "┃ " << setw(4) << "" << " ┃";
	gotoxy(hout, scorePX, scorePY+2);
	cout << "┗━━━┛";
	gotoxy(hout, scorePX, scorePY + 3);
	cout << "    顺  ";
	
	updateKingPret(score, kingScore, KingX, KingY, PretenderX, PretenderY, true);
	updateNextBalls(NULL, nextBallsX, nextBallsY, nextBallsVisible, true, false); updateKingPret(score, kingScore, KingX, KingY, PretenderX, PretenderY);
	updateStats(NULL, NULL, NULL, statX, statY, tableHeight, gameStatsVisible, true, false);
}
 
void updateScore(int score, int scorePX, int scorePY)
{
	gotoxy(hout, scorePX + 3, scorePY+1);
	restoreColor();
	cout << setw(4) << "";
	gotoxy(hout, scorePX + 3, scorePY + 1);
	cout << setw(4) << score;
}

void updateNextBalls(int *nextBalls, int nextBallsX, int nextBallsY, bool visible, bool refreshFrameNow, bool refreshContent)
{
	int *p = nextBalls;
	int x = nextBallsX + 2;
	if (refreshFrameNow)
	{
		if (visible)
		{
			gotoxy(hout, nextBallsX, nextBallsY);
			restoreColor();
			cout << "╔━╦━╦━╗";
			gotoxy(hout, nextBallsX, nextBallsY + 1);
			cout << "┃  ┃  ┃  ┃";
			gotoxy(hout, nextBallsX, nextBallsY + 2);
			cout << "╚━╩━╩━╝";
		}
		else
		{
			gotoxy(hout, nextBallsX, nextBallsY);
			restoreColor();
			cout << "              ";
			gotoxy(hout, nextBallsX, nextBallsY + 1);
			cout << "              ";
			gotoxy(hout, nextBallsX, nextBallsY + 2);
			cout << "              ";
		}
	}
	if (refreshContent)
	{
		if (visible)
		{

			while (*p)
			{
				gotoxy(hout, x, nextBallsY + 1);
				x += 4;
				setcolor(hout, colorList[0], colorList[*p]);
				cout << "●";
				p++;
			}
		}
	}
	
	restoreColor();
}

void updateStats(int (*gameMap)[CL_MAXGRID+2], int *gameStats, int *gameStatsBallDel, int statX, int statY, int tableHeight, bool visible, bool refreshFrameNow, bool refreshContent)
{
	int w, h;
	int empty = 0;
	if (refreshFrameNow)
	{
		if (visible)
		{
			gotoxy(hout, statX, statY);
			restoreColor();
			cout << "╔━━━━━━━━━━╗";
			for (int i = 1; i <= tableHeight -5; i++)
			{
				gotoxy(hout, statX, statY + i);
				cout << "┃                    ┃";
			}
			gotoxy(hout, statX, statY + tableHeight - 4);
			cout << "╚━━━━━━━━━━╝";
		}
		else
		{
			gotoxy(hout, statX, statY);
			restoreColor();
			cout << setw(24) << "";
			for (int i = 1; i <= tableHeight - 2; i++)
			{
				gotoxy(hout, statX, statY + i);
				cout << setw(24) << "";
			}
			gotoxy(hout, statX, statY + tableHeight - 1);
			cout << setw(24) << "";
		}
	}

	if (refreshContent && visible)
	{
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
		cout << setiosflags(ios::fixed) << setprecision(1) << "空：" << setw(2) << empty << "(" << setw(4) << empty*100. / (w*h) << "%)";
		for (int i = 0; i < CL_BALLNUM; i++)
		{
			gotoxy(hout, statX + 2, statY + i + 3);
			setcolor(hout, colorList[0], colorList[i + 2]);
			cout << "●";
			restoreColor();
			cout << "：" << setw(2) << gameStats[i + 2] << "(" << setw(4) << gameStats[i + 2] * 100. / (w*h) << "%), 消" << setw(3) << gameStatsBallDel[i + 2];
		}
	}
	

}

void graphicRoute(int(*gameMap)[CL_MAXGRID + 2], int *path, int tableStartX, int tableStartY, int ballType)
{
	int pathCount = 1;
	int x0, y0, x1, y1;
	path--;
	while (*path)
	{
		decodePos_(*path, y1, x1);
		decodePos_(*(path + 1), y0, x0);


		addGraphicalBall(tableStartX, tableStartY, *(path + 1), 0, colorList[0], 4, false);
		addGraphicalBall(tableStartX, tableStartY, *(path + 1), ballType, colorList[0], (x1 - x0 + 1) + 3 * (y1 - y0 + 1), false);
		Sleep(sleepTime1 / 2);

		addGraphicalBall(tableStartX, tableStartY, *path, ballType, colorList[0], 4, false);
		addGraphicalBall(tableStartX, tableStartY, *(path + 1), 0, colorList[0], (x1 - x0 + 1) + 3 * (y1 - y0 + 1), false);

		Sleep(sleepTime1 / 2);

		pathCount++;
		path--;
	}
}