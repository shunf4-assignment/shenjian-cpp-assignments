/* 1652270 计算机2班 冯舜 */
/*HYPERBejeweled_SJProject - 90-b1.h*/
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

const int MAXGRID = 9;

/*Structure*/
//游戏内部的Coord
//若是Console的坐标，系统已有COORD结构体
struct Coord
{
	int x;
	int y;
};

struct Map
{
	int mapArray[MAXGRID + 2][MAXGRID + 2];
	int w;
	int h;
	Coord sel;
	Coord source;
	Coord dest;
};

//Substitute MAP
struct SMap
{
	int mapArray[MAXGRID + 2][MAXGRID + 2];
	int w;
	int h;
	int pointer[MAXGRID + 2];
	//int columns[MAXGRID];
};

struct COORD_
{
	int X;
	int Y;
};

struct Board
{
	Map *map;
	COORD_ sc; //Start Coord
	Coord currPos;
	int bgColor;
	int frameColor;
	int highBgColor;
};


/*Strings*/
const char numToLetter[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char directions[] = "\x01\x02\x03\x02\x02\x01\x02\x03\0";
const char box[] = "┏━┓┃┗┛";
const char boxIn[] = "┳┣╋┫┻";
const char * const ballChar = "●◎⊕⊙¤※﹡  ";
//const char * const ballSel = "";


/*Colors*/
/* common-background, common-foreground, common-highlighted, */
const int commonColor[] = { COLOR_HWHITE, COLOR_BLACK, COLOR_WHITE };
//const int ballColor[] = { 0, COLOR_HYELLOW, COLOR_HPINK, COLOR_HGREEN, COLOR_HCYAN, COLOR_HBLACK, COLOR_HBLUE, COLOR_YELLOW, COLOR_HRED, COLOR_CYAN };
const int ballColor[] = { 0, COLOR_HYELLOW, COLOR_HPINK, COLOR_HGREEN, COLOR_HCYAN};

/*Numbers*/

const int ballNum = sizeof(ballColor) / sizeof(ballColor[0]) - 1;
const int directNum = (sizeof(directions) / sizeof(directions[0]) - 1) / 4;
const int dropInterval = 80;
const int explodeInterval = 50;
const double part45Spaces[] = { 0.2,0.4,0.2,0.2 };


/*Handles*/
const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄

/*Input Function*/
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


/*Tool Function*/
void startInit();
void restoreColor();
void partInit(int part, int w = 0, int h = 0, int b = 0);
void pressEnterToContinue(char *p = NULL);
void gracefullyReturn(int startX);
void coarselyReturn();
int calInterval(int count);
void inputWidthHeight(int &w, int &h);
COORD_ boardUIWH(Map *map, bool border);
COORD_ windowWHCal(Map *map, COORD_ boardWH, int mode);
COORD_ startXYCal(COORD_ boardWH, int mode);
void gotoEndOfBoard(Board *b);

/*Base Array Function*/
void coordCopy(Coord *a, Coord *b);
void initializeMap(Map *map, int wallElement, int spaceElement);
void initializeMap(SMap *map, int wallElement, int spaceElement);
void printMap(Map *map, Map *overlayMap, bool colourful);
void DFS(Map *oMap, Map *mMap, int *score);
void checkHint(Map *map, Map *oMap);
void removeBallsErased(Map *map, Map *oMapP);
void checkInARowWithScore(Map *map, Map *oMapP, int *score);
int *getGridPointer(Map *map, const Coord c);
int getGrid(const Map *map, const Coord c);
int getGrid(const Map *map, const Map *map2 = NULL);
void checkInARow(Map *map, Map *oMap);
void initEmerge(Map *map);
int scoreGet(int n);
void enterNew(Map *map, SMap *sMap);
void eliminateIAR(Map *map, Map *oMap, SMap *sMap);
bool isMapEmpty(Map *map);

/*Graphic Function*/
void addGraphicalBall(Board *b, int ballType, int ballStatus, COORD offset);
void enterNewMoveDown(Board *b, Map *map, SMap *sMap);
void graphicNoInsideBorder(Board *b, Map *oMap);
void graphicTable(Board *b, bool border, Map *oMap);
void eliminateIARGraph(Board *b, Map *map, Map *oMap);

