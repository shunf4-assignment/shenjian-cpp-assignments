/* 1652270 计算机2班 冯舜 */
/*HYPERBejeweled_SJProject - 90-b1-base.cpp*/
#include "90-b1.h"

void coordCopy(Coord *a, Coord *b)
{
	(*a).x = (*b).x;
	(*a).y = (*b).y;
}

void initializeMap(Map *map, int wallElement, int spaceElement)
{
	for (int i = 0; i < MAXGRID + 2; i++)
	{
		for (int j = 0; j < MAXGRID + 2; j++)
		{
			if (i == 0 || j == 0 || i >(*map).w || j >(*map).h)
				(*map).mapArray[j][i] = wallElement;
			else
				(*map).mapArray[j][i] = spaceElement;
		}
	}
}

void initializeMap(SMap *map, int wallElement, int spaceElement)
{
	for (int i = 0; i < MAXGRID + 2; i++)
	{
		for (int j = 0; j < MAXGRID + 2; j++)
		{
			if (i == 0 || j == 0 || i >(*map).w || j >(*map).h)
				(*map).mapArray[j][i] = wallElement;
			else
				(*map).mapArray[j][i] = spaceElement;
		}
	}
}

void printMap(Map *map, Map *overlayMap, bool colourful)
{
	int foreColor, backColor;
	COORD_ start;
	getxy(hout, start.X, start.Y);
	restoreColor();
	cout << "  |";
	for (int i = 1; i <= map->w; i++)
	{
		cout << setw(2) << i;
	}
	gracefullyReturn(start.X);
	cout << "--+" << setfill('-') << setw(MAXGRID * 2 + 1) << "" << setfill(' ');
	gracefullyReturn(start.X);

	for (int j = 1; j <= map->h; j++)
	{
		cout << numToLetter[j - 1] << " |";
		for (int i = 1; i <= map->w; i++)
		{
			backColor = commonColor[0];
			foreColor = commonColor[1];
			setcolor(hout, backColor, foreColor);

			cout << " ";
			if (overlayMap != NULL && overlayMap->mapArray[j][i] >= 1)
			{
				backColor = commonColor[2];
			}
			if (colourful)
			{
				foreColor = ballColor[map->mapArray[j][i]];
			}
			setcolor(hout, backColor, foreColor);
			cout << map->mapArray[j][i];

		}
		restoreColor();
		coarselyReturn();
	}
}

void initEmerge(Map *map)
{
	for (int i = 1; i <= map->w; i++)
	{
		for (int j = 1; j <= map->h; j++)
		{
			map->mapArray[j][i] = rand() % ballNum + 1;
		}
	}
}

void checkInARow(Map *map, Map *oMap)
{
	int thisColor, tmpBall;
	//initializeMap(oMap, -1, 0);
	for (int i = 1; i <= map->w; i++)
	{
		for (int j = 1; j <= map->h; j++)
		{
			thisColor = map->mapArray[j][i];
			for (const char *d = directions; *d;)
			{
				Coord tmpCoord[] = { {-1,-1},{ -1,-1 } };
				tmpBall = 0;
				for (int k = 0; k < 2; k++)
				{
					tmpCoord[k].y = j + *d++ -2;
					tmpCoord[k].x = i + *d++ - 2;
					if (map->mapArray[tmpCoord[k].y][tmpCoord[k].x] == thisColor)
					{
						tmpBall++;
					}
				}

				if (tmpBall == 2)
				{
					for (int k = 0; k < 2; k++)
						oMap->mapArray[tmpCoord[k].y][tmpCoord[k].x] = 1;
					oMap->mapArray[j][i] = 1;
				}
			}
			
		}
	}
}

int getGrid(const Map *map, const Map *map2)
{
	int x = map->sel.x, y = map->sel.y;
	if (map2) {
		x = map2->sel.x;
		y = map2->sel.y;
	}
		
	return map->mapArray[y][x];
}
int getGrid(const Map *map, const Coord c)
{
	return map->mapArray[c.y][c.x];
}
int *getGridPointer(Map *map, const Coord c)
{
	return &(map->mapArray[c.y][c.x]);
}
int *getGridPointer(SMap *map, const Coord c)
{
	return &(map->mapArray[c.y][c.x]);
}

int checkInARowWithScore(Map *map, Map *oMapP, int *score, int combo)
{
	checkInARow(map, oMapP);
	int total = 0;
	Map oMap = *oMapP;
	Map mMap = { {0}, map->w, map->h };
	initializeMap(&mMap, -1, 0);
	
	for (oMap.sel.x = 1; oMap.sel.x <= oMap.w; oMap.sel.x++)
	{
		for (oMap.sel.y = 1; oMap.sel.y <= oMap.h; oMap.sel.y++)
		{
			if (getGrid(&mMap, &oMap) != 1 && getGrid(&oMap) == 1)
			{
				total = DFS(&oMap, &mMap, score, combo);
			}
		}
	}
	return total;
}

bool isMapEmpty(Map *map)
{
	bool empty = true;
	for (int i = 1; i <= map->w; i++)
	{
		for (int j = 1; j <= map->h; j++)
		{
			if (map->mapArray[j][i] != 0)
				empty = false;
			if (!empty)
				break;
		}
		if (!empty)
			break;
	}
	return empty;
}

void removeBallsErased(Map *map, Map *oMapP)
{
	Map oMap = *oMapP;

	for (oMap.sel.x = 1; oMap.sel.x <= oMap.w; oMap.sel.x++)
	{
		for (oMap.sel.y = 1; oMap.sel.y <= oMap.h; oMap.sel.y++)
		{
			if (getGrid(oMapP) == 1)
			{
				*getGridPointer(map, oMap.sel) = 0;
			}
		}
	}
}

void checkHint(Map *map, Map *oMap)
{
	int thisColor, tmpBall[2];
	initializeMap(oMap, -1, 0);
	for (int i = 1; i <= map->w; i++)
	{
		for (int j = 1; j <= map->h; j++)
		{
			thisColor = map->mapArray[j][i];
			for (const char *d = directions; *d;)
			{
				Coord tmpCoord[2] = { -1,-1,-1,-1 };
				for (int k = 0; k < 2; k++)
				{
					tmpCoord[k].y = j + *d++ - 2;
					tmpCoord[k].x = i + *d++ - 2;
					tmpBall[k] = getGrid(map, tmpCoord[k]);
				}
				for (int k = 0; k < 2; k++)
				{
					if (tmpBall[k] == thisColor)
					{
						Coord tmpCoord2[2] = { -1,-1,-1,-1 };
						if (tmpCoord[1 - k].y == -1 || tmpCoord[1 - k].x == -1)
							break;
						for (const char *d2 = directions; *d2;)
						{
							for (int l = 0; l < 2; l++)
							{
								tmpCoord2[l].y = tmpCoord[1 - k].y + *d2++ - 2;
								tmpCoord2[l].x = tmpCoord[1 - k].x + *d2++ - 2;
								if (getGrid(map, tmpCoord2[l]) == thisColor && (tmpCoord2[l].x != i || tmpCoord2[l].y != j))
								{
									*getGridPointer(oMap, tmpCoord2[l]) = 1;
									*getGridPointer(oMap, tmpCoord[1 - k]) = 1;
								}
							}
						}
					}
				}
				if (tmpBall[0] == tmpBall[1])
				{
					Coord tmpCoord2[2] = { -1,-1,-1,-1 };
					for (const char *d2 = directions; *d2;)
					{
						for (int l = 0; l < 2; l++)
						{
							tmpCoord2[l].y = j + *d2++ - 2;
							tmpCoord2[l].x = i + *d2++ - 2;
							if (getGrid(map, tmpCoord2[l]) == tmpBall[0] && (tmpCoord2[l].x != tmpCoord[0].x || tmpCoord2[l].y != tmpCoord[0].y) && (tmpCoord2[l].x != tmpCoord[1].x || tmpCoord2[l].y != tmpCoord[1].y))
							{
								*getGridPointer(oMap, tmpCoord2[l]) = 1;
								oMap->mapArray[j][i] = 1;
							}
						}
					}
				}
				
			}
		}
	}
}


int DFS(Map *oMap, Map *mMap, int *score, int combo)
{
	Coord c = oMap->sel;
	Coord cStack[MAXGRID * MAXGRID] = { {0,0} };
	Coord *p = cStack;
	const char *d;
	Coord tmpCoord;
	Coord currCoord;
	int total = 1;
	*p++ = c;
	*getGridPointer(mMap, c) = 1;

	while (p != cStack)
	{
		d = directions;
		p--;
		currCoord = p[0];
		while (*d) {
			tmpCoord.y = currCoord.y + *d++ - 2;
			tmpCoord.x = currCoord.x + *d++ - 2;
			if (getGrid(oMap, tmpCoord) == 1 && getGrid(mMap, tmpCoord) != 1)
			{
				*getGridPointer(mMap, tmpCoord) = 1;
				*p++ = tmpCoord;
				total++;
			}
		}
	}
	if(score)
		*score += int(comboList(combo) * scoreGet(total));
	return total;
}

int scoreGet(int n)
{
	return int(8*log(n));
}

void eliminateIAR(Map *map, Map *oMap, SMap *sMap)
{
	Coord c = { 0,0 };
	//int *tmpP;
	for (c.y = 1; c.y <= map->h; c.y++)
	{
		for (c.x = 1; c.x <= map->w; c.x++)
		{
			if (getGrid(oMap, c))
			{
				sMap->mapArray[(sMap->pointer[c.x])++][c.x] = rand() % ballNum + 1;
				*getGridPointer(map, c) = 0;
			}
		}
	}
}

void enterNew_(Map *map, SMap *sMap)
{
//	COORD tmpc;
	int downOffset = 0;
	int startZero[MAXGRID + 2] = { 0 };
	for (int i = 1; i <= sMap->w; i++)
	{
		for (int j = 1; j <= sMap->h; j++)
		{
			if (map->mapArray[j][i] == 0)
			{
				startZero[i] = j;
				break;
			}
		}
	}
	for (int i = 1; i <= sMap->w; i++)
	{
		for (int j = startZero[i] + sMap->pointer[i] -1; j >= 1; j--)
		{
			if (j > sMap->pointer[i])
				map->mapArray[j][i] = map->mapArray[j - sMap->pointer[i]][i];
			else
			{
				map->mapArray[j][i] = sMap->mapArray[j - 1][i];
			}
		}
	}
}
void enterNew(Map *map, SMap *sMap)
{
	enterNewMoveDown(NULL, map, sMap);
}

bool enterCheckIfAny(SMap *sMap, int downOffset)
{
	bool any = false;
	for (int i = 1; i <= sMap->w; i++)
	{
		if (sMap->pointer[i] > 0 && sMap->pointer[i] - downOffset > 0)
		{
			any = true;
		}
	}
	return any;
}
void enterNewMoveDown(Board *b, Map *map, SMap *sMap)
{
	COORD tmpc;
	Coord tmpCoord, *currPosP;
	int lastZero[MAXGRID + 2], counter = 0;

	if (b != NULL)
	{
		currPosP = &(b->currPos);
	}
	else
	{
		currPosP = &tmpCoord;
	}

	while (enterCheckIfAny(sMap, 0))
	{
		for (int i = 1; i <= sMap->w; i++)
		{
			if (sMap->pointer[i] > 0)
			{
				/*
				计算这一列最底下的0对应纵坐标
				实际上替换成“最底下的那片0的最上面一个0”效率会更高
				*/
				for (int j = sMap->h; j >= 1; j--)
				{
					if (map->mapArray[j][i] == 0)
					{
						lastZero[i] = j;
						break;
					}
				}

				/*上述0上面的所有格子下移半格*/
				for (int j = lastZero[i] - 1; j >= 0; j--)
				{
					tmpc.X = tmpc.Y = 0;
					*currPosP = { i, j };
					addGraphicalBall(b, 0, 0, tmpc);
					tmpc.Y = 1;
					addGraphicalBall(b, map->mapArray[j][i], 0, tmpc);
				}
				/*新球进场半格*/
				*currPosP = { i , 0 };
				tmpc.Y = 1;
				addGraphicalBall(b, sMap->mapArray[sMap->pointer[i] - 1][i], 0, tmpc);
				
			}
		}
		counter++;
		if(b)
			Sleep(calInterval(counter));
		for (int i = 1; i <= sMap->w; i++)
		{
			if (sMap->pointer[i] > 0)
			{

				/*上述0上面的所有格子再次下移半格到位*/
				for (int j = lastZero[i]; j >= 1; j--)
				{
					
					tmpc.Y = -1;
					map->mapArray[j][i] = map->mapArray[j - 1][i];
					*currPosP = { i, j };
					addGraphicalBall(b, 0, 0, tmpc);
					tmpc.Y = 0;
					addGraphicalBall(b, map->mapArray[j][i], 0, tmpc);
				}

				/*新球进场到第一格*/
				*currPosP = { i , 1 };
				
				map->mapArray[1][i] = sMap->mapArray[--(sMap->pointer[i])][i];
				tmpc.Y = -1;
				addGraphicalBall(b, 0, 0, tmpc);
				tmpc.Y = 0;
				addGraphicalBall(b, map->mapArray[1][i], 0, tmpc);

				
			}
		}
		if (b)
			Sleep(calInterval(counter + 1));
		counter++;
	}
	gotoEndOfBoard(b);
	restoreColor();
}