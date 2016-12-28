/* 1652270 计算机2班 冯舜 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
using namespace std;
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max())

template <typename T>
void inputThing(T* p, const char * promptText, const char * cinUngoodText, const char * outLimitText, T lowerLimit, T upperLimit, bool clearBuffer = false)
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
		}

	} while (!valid);
	if (clearBuffer)
		cin.ignore(FS_MAX_LENGTH, '\n');
}

void standardInput(int* p, int pLen, const char * varName, int lowerLimit = 0, int upperLimit = 1048576, bool clearBuffer = false, bool displayPrompt = true)
{
	char promptText[80] = { '\0' };
	sprintf(promptText, "请输入 %s 的值(%d-%d)：", varName, lowerLimit, upperLimit);
	for (int *p2 = p; p2 - p < pLen; p2++)
		inputThing(p2, displayPrompt ? promptText : "", "输入类型错误，请重新输入。", "输入超出范围，请重新输入", lowerLimit, upperLimit, clearBuffer);
}

void standardInput(double* p, int pLen, const char * varName, double lowerLimit = 0, double upperLimit = INFINITY, bool clearBuffer = false, bool displayPrompt = true)
{
	char promptText[80] = { '\0' };
	sprintf(promptText, "请输入 %s 的值(%lf-%lf)：", varName, lowerLimit, upperLimit);
	for (double *p2 = p; p2 - p < pLen; p2++)
		inputThing(p, displayPrompt ? promptText : "", "输入类型错误，请重新输入。", "输入超出范围，请重新输入", lowerLimit, upperLimit, clearBuffer);
}

template <typename T, typename T2>
void standardInput(T *p, int pLen, const char * varName, T2 lowerLimit = 0, T2 upperLimit = 0, bool clearBuffer = false, bool displayPrompt = false)
{
	char promptText[80] = { '\0' };
	sprintf(promptText, "请输入 %s 的值：", varName);
	//for(T p2 = *p;p2 - *p < pLen; p2++)
	for (T* p2 = p; p2 - p < pLen; p2++)
		standardInput(*p2, sizeof(*p) / sizeof(**p), varName, lowerLimit, upperLimit, clearBuffer, false);
}

void displayArr(int * p, int n, bool bracket)
{
	cout << "{";
	int *pCopy = p;
	for (; pCopy < p + n;pCopy++)
	{
		cout << " " << *(pCopy) << ((pCopy < p + n - 1) ? "," : "");
	}
	cout << " }";
}

template <typename T>
void displayArr(T * p, int n = 1, bool bracket = false)
{
	if (bracket)
		cout << "{";
	T *pCopy = p;
	for (; pCopy < p + n;)
	{
		cout << " ";
		displayArr(*pCopy, sizeof(*pCopy) / sizeof(**pCopy), true);
		if (pCopy < p + n - 1)
			cout << ",";
		*pCopy++;

	}
	if (bracket)
		cout << " }";
}

const int direction[4][2] = { 0,1,1,0,0,-1,-1,0 };
bool foundPath = false;

void printMatrix(int (*map)[11])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (map[i][j] == -1)
				cout << "d ";
			else if (map[i][j] == -2)
				cout << "s ";
			else if (map[i][j] == 0)
				cout << "  ";
			else
				cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void push(char * arr, char charToPush, char endMark = '\0')
{
	char *p = arr;
	while (*p != endMark)
		p++;
	*(p++) = charToPush;
	*p = endMark;
}

char pop(char * arr, char endMark = '\0')
{
	char *p = arr;
	char c = '\0';
	while (*p != endMark)
		p++;
	if (p > arr)
	{
		c = *(--p);
		*p = endMark;
	}
	return c;
}
bool moveStep(int(*map)[11], int(*mapMark)[11], char *mapRoute, int x1, int y1, int x2, int y2)
{
	
	int thisX, thisY;
	char d[8] = {0};
	if (abs(x1 - x2) > abs(y1 - y2))
	{
		if (x1 - x2 > 0)
		{
			if (y1 - y2 > 0)
			{
				strcpy(d, "\x04\x03\x01\x02");
			}
			else
			{
				strcpy(d, "\x04\x01\x03\x02");
			}
		}
		else
		{
			if (y1 - y2 > 0)
			{
				strcpy(d, "\x02\x03\x01\x04");
			}
			else
			{
				strcpy(d, "\x02\x01\x03\x04");
			}
		}
	}
	else
	{
		if (x1 - x2 > 0)
		{
			if (y1 - y2 > 0)
			{
				strcpy(d, "\x03\x04\x02\x01");
			}
			else
			{
				strcpy(d, "\x03\x02\x04\x01");
			}
		}
		else
		{
			if (y1 - y2 > 0)
			{
				strcpy(d, "\x03\x02\x04\x01");
			}
			else
			{
				strcpy(d, "\x01\x02\x04\x03");
			}
		}
	}
	if (foundPath)
	{
		return true;
	}
	for (int i = 0; i<4; i++)
	{
		thisX = x1 + direction[(int)d[i]-1][0];
		thisY = y1 + direction[(int)d[i]-1][1];
		push(mapRoute, d[i]);
		if (thisX == x2 && thisY == y2)
		{
			foundPath = true;
			return true;
		}
		if (map[thisX][thisY] < 1 && mapMark[thisX][thisY] != 1)
		{
			mapMark[thisX][thisY] = 1;
			moveStep(map, mapMark, mapRoute, thisX, thisY, x2, y2);
		}
		if (!foundPath)
			pop(mapRoute);
		else
			return true;
	}
	
	return foundPath;
}
bool findPath(int map[][11], char * mapRoute, int x1, int y1, int x2, int y2)
{
	int mapMark[11][11] = { 0 };
	mapMark[x1][y1] = 1;
	mapMark[x2][y2] = 1;
	for (int i = 0; i < 11; i++)
	{
		mapMark[i][0] = 1;
		mapMark[0][i] = 1;
		mapMark[10][i] = 1;
		mapMark[i][10] = 1;

	}
	return moveStep(map, mapMark, mapRoute, x1, y1, x2, y2);
}

void moveStepInit(int(*map)[11], int(*mapMark)[11], char *mapRoute, int x1, int y1, int x2, int y2)
{
	for (int i = 0;i<4;i++)
	{
		push(mapRoute, i);
		//moveStep(map, mapMark, mapRoute, i, x1, y1, x2, y2);
	}
}



int main()
{
	srand((unsigned int)time_t());
	REINPUT:
	//int map[11][11] = { 0 };
	int map[11][11] = {
		1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,1,
		1,0,1,1,1,1,1,0,0,0,1,
		1,0,1,0,0,0,1,0,0,0,1,
		1,0,1,0,0,0,1,1,1,0,1,
		1,0,1,0,0,0,0,0,0,0,1,
		1,0,1,0,0,0,1,1,0,0,1,
		1,0,1,1,1,1,1,0,1,0,1,
		1,0,0,0,0,0,0,0,1,0,1,
		1,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1
	};
	char mapRoute[121] = {0};
	foundPath = false;
	
	/*for (int i = 0; i < 11; i++)
	{
		map[i][0] = 1;
		map[0][i] = 1;
		map[10][i] = 1;
		map[i][10] = 1;
	}
	for (int i = 0; i < 20; i++)
	{
		map[rand() % 11][rand() % 11] = 1;
	}
	int r1 = rand() % 11;
	for (int i = 0; i < 11; i++)
	{
		map[i][r1] = 1;
	}
	map[3][r1] = 0;
	int xd = rand() % 9+1;
	int yd = rand() % 9+1;
	int xs = rand() % 9+1;
	int ys = rand() % 9+1;
	map[xs][ys] = -2;
	map[xd][yd] = -1;*/
	int xs = 7;
	int ys = 7;
	int xd = 6;
	int yd = 3;
	map[xs][ys] = -2;
	map[xd][yd] = -1;
	cout << (findPath(map, mapRoute, xs, ys, xd, yd) ? "t":"f") << endl;
	printMatrix(map);
	cout << endl;
	for (char *p = mapRoute; *p != '\0'; p++)
	{
		switch (*p)
		{
			case 1:
				cout << "右 ";
				break;
			case 2:
				cout << "下 ";
				break;
			case 3:
				cout << "左 ";
				break;
			case 4:
				cout << "上 ";
				break;
		}
	}
	system("pause&cls");
	goto REINPUT;
	return 0;
}
