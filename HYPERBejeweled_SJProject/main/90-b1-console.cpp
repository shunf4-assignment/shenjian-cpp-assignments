/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
/*HYPERBejeweled_SJProject - 90-b1-console.cpp*/
#include "90-b1.h"

void drawBalls(int w,int h, int x, int y, Board *b, Map *oMap, bool insideBorder)
{
	for (int i = 1; i <= w; i++)
	{
		for (int j = 1; j <= h; j++)
		{
			if (b->map->mapArray[j][i] >= 1)
			{
				setcolor(hout, ((oMap && oMap->mapArray[j][i]) ? (b->highBgColor) : (b->bgColor)), ballColor[b->map->mapArray[j][i]]);
				if (insideBorder)
				{
					gotoxy(hout, x + 4 * i - 2, y + j * 2 - 1);
					cout << "¡ñ";
				}
				else
				{
					gotoxy(hout, b->sc.X + 2 * i, b->sc.Y + j);
					cout << "¡ñ";
				}
			}
		}
	}
}

void graphicNoInsideBorder(Board *b, Map *oMap)
{
	int h = b->map->h;
	int w = b->map->w;
	setcolor(hout, b->bgColor, b->frameColor);
	for (int r = 0; r <= h + 1; r++)
	{
		gotoxy(hout, b->sc.X, b->sc.Y + r);
		if (r == 0 || r == h + 1)
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

	drawBalls(w, h, b->sc.X, b->sc.Y, b, oMap, false);

	restoreColor();
	gotoxy(hout, b->sc.X, b->sc.Y + h + 2);
}

void graphicTable(Board *b, bool border, Map *oMap)
{
	int h = b->map->h;
	int w = b->map->w;
	int x = b->sc.X;
	int y = b->sc.Y;
	setcolor(hout, b->bgColor, b->frameColor);
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

	drawBalls(w, h, b->sc.X, b->sc.Y, b, oMap, true);

	gotoEndOfBoard(b);
	restoreColor();
	gracefullyReturn(b->sc.X);
}

void addGraphicalBall(Board *b, int ballType, int ballStatus, COORD offset)
{
	if (b == NULL)
		return;
	
	gotoxy(hout, b->sc.X + 4 * b->currPos.x - 2 + offset.X *2, b->sc.Y + 2 * b->currPos.y - 1 + offset.Y);
	if (ballType == -1)
	{
		ballType = getGrid(b->map, b->currPos);
	}

	if (ballType != 0)
	{
		setcolor(hout, b->bgColor, ballColor[ballType]);
		cout << ballChar[ballStatus * 2] << ballChar[ballStatus * 2+1];
	}
	else 
	{
		setcolor(hout, b->bgColor, b->frameColor);
		if (abs(offset.X) == 1 || abs(offset.Y) == 1)
			cout << box[(offset.Y != 0) ? 2 : 6] << box[(offset.Y != 0) ? 3 : 7];
		else
			cout << "  ";
	}
}

void eliminateIARGraph(Board *b, Map *map, Map *oMap)
{
	Coord c = { 0,0 };
	int ballStatus;
	//int *tmpP;
	for (ballStatus = 2; ballStatus <= 7; ballStatus++)
	{
		for (c.y = 1; c.y <= map->h; c.y++)
		{
			for (c.x = 1; c.x <= map->w; c.x++)
			{
				if (getGrid(oMap, c))
				{
					b->currPos = c;
					addGraphicalBall(b, getGrid(map, c), ballStatus, { 0,0 });
				}
			}
		}
		Sleep(explodeInterval);
	}
	gotoEndOfBoard(b);
	restoreColor();
	gracefullyReturn(b->sc.X);
}

Coord getCoordonBoard(Board *b, COORD *c)
{
	Coord r;
	r.x = (c->X - b->sc.X + 2) / 4;
	r.y = (c->Y - b->sc.Y + 1) / 2;
	//gotoxy(hout, 0, 0);
	if ((c->X - b->sc.X + 2) % 4 > 2 || (c->Y - b->sc.Y + 1) % 2 == 1 || c->X - b->sc.X <= 1 || r.x > b->map->w || c->Y - b->sc.Y < 1 || r.y > b->map->h)
	{
		r.x = 0;
		r.y = 0;
	}
	//cout << r.x << "," << r.y;

	return r;
}