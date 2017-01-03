/* 1652270 计算机2班 冯舜 */
/*90-b2-base.cpp*/

#include "90-b2.h"

void initializeMap(int(*map)[CL_MAXGRID + 2], int w, int h, int wallElement, int spaceElement)
{
	for (int(*p)[CL_MAXGRID + 2] = map; p < map + CL_MAXGRID + 2; p++)
	{
		for (int *q = *p; q < *p + CL_MAXGRID + 2; q++)
		{
			if (p == map || q == *p || p > map + h || q > *p + w)
				*q = wallElement;
			else
				*q = spaceElement;
		}
	}
}

void combineMap(int(*toMap)[CL_MAXGRID + 2], int(*fromMap)[CL_MAXGRID + 2], int w, int h, int inElement = 1)
{
	for (int i=1;i<=w;i++)
	{
		for (int j = 1; j <= h; j++)
		{
			if (fromMap[j][i] >= 2)
				toMap[j][i] = inElement;
		}
	}
}

void getMapWidthHeight(int(*map)[CL_MAXGRID + 2], int &width, int &height)
{
	for (int w = 1; w < CL_MAXGRID + 2; w++)
	{
		if (map[1][w] == 1)
		{
			width = w - 1;
			break;
		}
	}
	for (int h = 1; h < CL_MAXGRID + 2; h++)
	{
		if (map[h][1] == 1)
		{
			height = h - 1;
			break;
		}
	}
	return;
}

//随机在地图涌现几个球，颜色完全随机。返回true表示成功，返回false表示地图已经满了（包括已经满了），所以填不下去。
bool randomEmerge(int(*map)[CL_MAXGRID + 2], int num, bool autoFlush, int *nextBalls)
{
	int emptyArray[CL_MAXGRID*CL_MAXGRID+1] = { 0 };
	int *e = emptyArray;
	int i,ran,ran2,tmpLastPos;
	int w,h;
	getMapWidthHeight(map, w, h);
	for (int i = 1; i < w + 1; i++)
	{
		for (int j = 1; j < h + 1; j++)
		{
			if (map[j][i] == 0)
			{
				*(e++) = j*(CL_MAXGRID + 1) + i;
			}
		}
	}

	tmpLastPos = e - emptyArray - 1;
	//通过对num计数，不断随机生成彩球
	for (i = 0; i < num && tmpLastPos >= 0; i++)
	{
		ran = rand() % (tmpLastPos+1);
		if (nextBalls != NULL)
		{
			ran2 = *(nextBalls++) - 2;
		}
		else
		{
			ran2 = rand() % CL_BALLNUM;
		}
		map[emptyArray[ran] / (CL_MAXGRID + 1)][emptyArray[ran] % (CL_MAXGRID + 1)] = ran2 + 2;
		
		if(autoFlush)
			if (checkIAR(map, emptyArray[ran], NULL, false, emptyArray, &tmpLastPos, NULL))
				i--;
		arrayShift(emptyArray, tmpLastPos--, ran);
	}
	if (tmpLastPos < 0)
	{
		//地图已经满了
		return false;
	}
	else
	{
		return true;
	}
}

int *decodePos(int encoded)
{
	static int pos[2] = {0};
	pos[0] = encoded / (CL_MAXGRID + 1);
	pos[1] = encoded % (CL_MAXGRID + 1);
	return pos;
}

void decodePos_(int encoded, int &j, int &i)
{
	j = encoded / (CL_MAXGRID + 1);
	i = encoded % (CL_MAXGRID + 1);
}

int encodePos(int *pos)
{
	return pos[0] * (CL_MAXGRID + 1) + pos[1];
}

bool checkEmpty(int(*map)[CL_MAXGRID + 2], int w, int h, int emptyMark = 0)
{
	bool empty = true;
	for (int i = 1; i <= w; i++)
	{
		for (int j = 1; j <= h; j++)
		{
			if (map[j][i] != emptyMark || empty == false)
			{
				empty = false;
				break;
			}
		}
		if (empty == false)
		{
			break;
		}
	}
	return empty;
}

int *getMiniDistance(int(*distanceMap)[CL_MAXGRID + 2], int(*visitedMap)[CL_MAXGRID + 2], int w, int h)
{
	int mini = INT_MAX;
	static int coord[2] = {-1,-1};
	coord[0] = -1;
	coord[1] = -1;
	for (int i = 1; i <= w; i++)
	{
		for (int j = 1; j <= h; j++)
		{
			if (distanceMap[j][i] < mini && visitedMap[j][i] == 0)
			{
				mini = distanceMap[j][i];
				coord[0] = j;
				coord[1] = i;
			}
		}
	}
	return coord;
}

int * staticPath(int(*map)[CL_MAXGRID + 2], int source, int dest)
{
	//找路
	int *tmp, tmp2;
	int visitedMap[CL_MAXGRID + 2][CL_MAXGRID + 2] = { 0 };
	int distanceMap[CL_MAXGRID + 2][CL_MAXGRID + 2] = { 0 };
	int parentMap[CL_MAXGRID + 2][CL_MAXGRID + 2] = { 0 };
	int sourcePos[2] = {(tmp=decodePos(source),*tmp), tmp[1] };
	int destPos[2] = { (tmp = decodePos(dest), *tmp), tmp[1] };
	int w, h;
	getMapWidthHeight(map, w, h);
	static int path[(CL_MAXGRID + 2) *(CL_MAXGRID + 2)] = { 0 };
	int *p;
	int thisPos;
	bool isStraight;
	int thisParent;

	for (int i = 0; i < (CL_MAXGRID + 2) *(CL_MAXGRID + 2); i++)
	{
		path[i] = 0;
	}

	initializeMap(visitedMap, w, h, -1, 0);
	combineMap(visitedMap, map, w, h, 1);
	initializeMap(distanceMap, w, h, INT_MAX, INT_MAX);
	initializeMap(parentMap, w, h, -2, -1);

	distanceMap[sourcePos[0]][sourcePos[1]] = 0;
	visitedMap[sourcePos[0]][sourcePos[1]] = 0;

	while (!checkEmpty(visitedMap, w, h, 1))
	{
		int *miniCoord = getMiniDistance(distanceMap, visitedMap, w, h);
		int thisCoord[2];
		if (miniCoord[0] == -1 || visitedMap[destPos[0]][destPos[1]] == 1)
		{
			break;
		}

		visitedMap[miniCoord[0]][miniCoord[1]] = 1;

		for (char *p = "\2\3\1\2\2\1\3\2"; *p != '\0'; p++,p++)
		{
			thisCoord[0] = miniCoord[0] + *p - 2;
			thisCoord[1] = miniCoord[1] + *(p + 1) - 2;
			if (map[thisCoord[0]][thisCoord[1]] >= 1)
			{
				continue;
			}
			thisParent = parentMap[miniCoord[0]][miniCoord[1]];
			isStraight = miniCoord[0] - thisParent / (1 + CL_MAXGRID) != (*p - 2) || miniCoord[1] - thisParent % (1 + CL_MAXGRID) != (*(p + 1) - 2);
			((tmp2 = distanceMap[miniCoord[0]][miniCoord[1]] + 1 + isStraight) < distanceMap[thisCoord[0]][thisCoord[1]]) && (distanceMap[thisCoord[0]][thisCoord[1]] = tmp2, parentMap[thisCoord[0]][thisCoord[1]] = encodePos(miniCoord));
		}
	}
	p = path + 1;
	if (visitedMap[destPos[0]][destPos[1]] == 1)
	{
		//Path found.
		thisPos = dest;
		do
		{
			*(p++) = thisPos;
			thisPos = parentMap[thisPos / (1+CL_MAXGRID)][thisPos % (1+CL_MAXGRID)];
		} while (thisPos != source);
		*p = thisPos;
	}
	
	tmp2 = 2;
	return p;
}

int *getGridPointer(int(*gameMap)[CL_MAXGRID + 2], int encodedPos)
{
	int *tmp = decodePos(encodedPos);
	return &(gameMap[tmp[0]][tmp[1]]);
}

void ballMove(int(*gameMap)[CL_MAXGRID + 2], int encodedSource, int encodedDest)
{
	int *pd = getGridPointer(gameMap, encodedDest);
	int *ps = getGridPointer(gameMap, encodedSource);
	*pd = *ps;
	*ps = 0;
}

int checkIAR(int(*gameMap)[CL_MAXGRID + 2], int startPoint, int *score, bool giveScore, int *emptyArray, int *lastPos, int *gameStats)
{
	char *p = "\x1\x2\x3\x2\x2\x1\x2\x3\x1\x3\x3\x1\x1\x1\x3\x3";
	int *thisPoint, *tmp;
	int sameColor = *getGridPointer(gameMap, startPoint);
	int ballCount = 0;
	int ballCountPart = 0;
	int startPointP[2] = { (tmp = decodePos(startPoint),tmp[0]),tmp[1] };
	int w,h;
	getMapWidthHeight(gameMap, w, h);
	
	while (*p)
	{
		ballCountPart = 0;
		for (int i = 0; i < 2; i++)
		{
			thisPoint = decodePos(startPoint);
			while (thisPoint[1] >= 1 && thisPoint[1] <= w && thisPoint[0] >= 1 && thisPoint[0] <= h && (gameMap[thisPoint[0]][thisPoint[1]] == sameColor || thisPoint[0] == startPointP[0] && thisPoint[1] == startPointP[1]))
			{
				thisPoint[0] += *p - 2;
				thisPoint[1] += *(p + 1) - 2;
				ballCountPart++;
			}
			p++, p++;
		}
		ballCountPart--;
		if (ballCountPart >= 5)
		{
			p -= 4;
			for (int i = 0; i < 2; i++)
			{
				thisPoint = decodePos(startPoint);
				while (thisPoint[1] >= 1 && thisPoint[1] <= w && thisPoint[0] >= 1 && thisPoint[0] <= h && (gameMap[thisPoint[0]][thisPoint[1]] == sameColor || thisPoint[0] == startPointP[0] && thisPoint[1] == startPointP[1]))
				{
					gameMap[thisPoint[0]][thisPoint[1]] = 0;
					ballCount++;
					if (emptyArray != NULL && !(thisPoint[0] == startPointP[0] && thisPoint[1] == startPointP[1]))
					{
						emptyArray[++(*lastPos)] = encodePos(thisPoint);
					}
					thisPoint[0] += *p - 2;
					thisPoint[1] += *(p + 1) - 2;
				}
				p++, p++;
			}
			ballCount--;
		}
		
		
		
	}
	if (ballCount > 0) {
		if (giveScore)
			*score = (ballCount - 1)*(ballCount - 2);
		if (emptyArray != NULL)
		{
			emptyArray[++(*lastPos)] = startPoint;
		}
		if (gameStats != NULL)
		{
			gameStats[sameColor] += ballCount;
		}
		//msg("ballcount:%i", ballCount);
	}
	return ballCount;
}

void regenBalls(int * nextBalls, int n)
{
	for (int i = 0; i < n; i++)
	{
		nextBalls[i] = rand() % CL_BALLNUM + 2;
	}
}

void drawPathOnMap(int(*pathMap)[CL_MAXGRID + 2], int(*gameMap)[CL_MAXGRID + 2], int *path, bool drawDest)
{
	int pathCount = 1;
	while (*path)
	{
		if (drawDest && *(path + 1) == 0 || pathCount >= 1)
			pathMap[*path / (1 + CL_MAXGRID)][*path % (1 + CL_MAXGRID)] = pathCount;
		pathCount++;
		path--;
	}
}