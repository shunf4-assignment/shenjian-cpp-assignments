/* 1652270 计算机2班 冯舜 */
/*90-b2.h*/
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "cmd_console_tools.h"
#include "time.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
using namespace std;
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max)()

const int CL_MAXGRID = 9;
const int CL_BALLNUM = 7;
const char numToLetter[] = " ABCDEFGHIJKLMN";
const int colorList[] = { COLOR_HWHITE,COLOR_BLACK,COLOR_HRED,COLOR_RED,COLOR_HYELLOW,COLOR_HGREEN,COLOR_HCYAN,COLOR_BLUE,COLOR_HPINK, COLOR_HWHITE, COLOR_WHITE, COLOR_RED, COLOR_PINK };
const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄
const char box[] = "┏━┓┃┗┛";
const char boxIn[] = "┳┣╋┫┻";
const int sleepTime1 = 100;
const int kingLen = 8;
const int pretLen = 8;
const int kingHeight = 10;
const char * const kingStr = "   Ｍ ◇   ○_┼  /│ │   ∧ │  /  \\  ";
const char * const pretStr = "↖   △   ×_○      │\\     ∧     /  \\";
const char * const kingDef = "     ???   ○     /│\\     ∧     /  \\  ";
const char * const pretWin = "↖   Ｍ   ×_○ 神剑 │\\     ∧     /  \\";


void initializeMap(int(*map)[CL_MAXGRID + 2], int w, int h, int wallElement = 1, int spaceElement = 0);
void printArray(int(*mapArray)[CL_MAXGRID + 2], bool printColor = true, int wallElement = 1, int spaceElement = 0, int (*overlayMap)[CL_MAXGRID + 2] = NULL);
bool randomEmerge(int(*map)[CL_MAXGRID + 2],  int num, bool autoFlush = true,int* nextBalls = NULL);
void arrayShift(int * arr, int lastPos, int removePos);
void pressEnterToContinue();

//处理输入检查
template <typename T>
void msg(char *p, T i)
{
	char str[800] = { 0 };
	char str2[800] = { 0 };
	sprintf(str2, p, i);
	sprintf(str, "msg * %s\"", str2);
	system(str);
}

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
			cin.putback('x');
			cin.ignore(FS_MAX_LENGTH, '\n');
		}

	} while (!valid);
	if (clearBuffer)
	{
		cin.putback('x');
		cin.ignore(FS_MAX_LENGTH, '\n');
	}
}

void inputCertainLen(char * _Str, int _Count);
int* staticPath(int(*map)[CL_MAXGRID + 2], int source, int dest);
bool inputMove(int(*gameMap)[CL_MAXGRID + 2], int &source, int&dest)
;
void inputWidthHeight(int &w, int &h);
void drawPathOnMap(int(*pathMap)[CL_MAXGRID + 2], int(*gameMap)[CL_MAXGRID + 2], int *path, bool drawDest = true);
int *getGridPointer(int(*gameMap)[CL_MAXGRID + 2], int encodedPos);
void ballMove(int(*gameMap)[CL_MAXGRID + 2], int encodedSource, int encodedDest);
int checkIAR(int(*gameMap)[CL_MAXGRID + 2], int startPoint, int *score, bool giveScore, int *emptyArray, int *lastPos, int *gameStats);
void regenBalls(int * nextBalls, int n = 3);
void getMapWidthHeight(int(*map)[CL_MAXGRID + 2], int &w, int &h);
void graphicNoInsideBorder(int(*mapArray)[CL_MAXGRID + 2], int x, int y);
void graphicTable(int(*mapArray)[CL_MAXGRID + 2], int x, int y, bool border);
int encodePos(int *pos);
int mouseActions(int startX, int startY, int promptX, int promptY, int quitX, int quitY, int * position, int w, int h, bool keyBoard);
int inputMoveByMouse(int(*gameMap)[CL_MAXGRID + 2], int &source, int&dest, int tableStartX, int tableStartY, int promptX, int promptY, int prompt2X, int prompt2Y, int quitX, int quitY, int menuX, int menuY, bool keyBoard);
int *decodePos(int encoded);
void decodePos_(int encoded, int &j, int &i);
void addGraphicalBall(int startX, int startY, int currPos, int ballType, int bgColor, int offset, bool select);
void graphicRoute(int(*gameMap)[CL_MAXGRID + 2], int *path, int tableStartX, int tableStartY, int ballType);
void restoreColor();

void drawInitUI(int tableWidth, int tableHeight, int tableStartX, int tableStartY, int menuX, int menuY, int KingX, int PretenderX, int KingY, int PretenderY, int nextBallsX, int nextBallsY, int scoreKX, int scoreKY, int scorePX, int scorePY, int(*gameMap)[CL_MAXGRID + 2], int windowWidth, int statX, int statY, bool nextBallsVisible, bool gameStatsVisible, int score, int kingScore);
void updateScore(int score, int scorePX, int scorePY);
void updateNextBalls(int *nextBalls, int nextBallsX, int nextBallsY, bool visible, bool refreshFrameNow, bool refreshContent);
void updateStats(int(*gameMap)[CL_MAXGRID + 2], int *gameStats, int *gameStatsBallDel, int statX, int statY, int tableHeight, bool visible, bool refreshFrameNow, bool refreshContent);
int read_mouse_and_key(const HANDLE hin, int &X, int &Y, const int enable_read_mouse_moved);
void updateKingPret(int score, int kingScore, int KingX, int KingY, int PretenderX, int PretenderY, bool dialog = false);