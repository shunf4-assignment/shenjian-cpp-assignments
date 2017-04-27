/* 1652270 计算机2班 冯舜 */
/*BLASTClock_SJProject - 90-b3.h*/
#pragma once
#pragma comment(lib, "Winmm.lib")
#include "cmd_console_tools.h"
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <conio.h>
#include <fstream>
#include <strstream>

using namespace std;

#define NEXT_GOTO_CLOCK 1
#define NEXT_GOTO_ECLOCK 2
#define NEXT_GO_BACK 3
#define NEXT_DO_NOTHING 0
#define NEXT_GOTO_VIEWALARM 4

#define ALARM_ONCE 0
#define ALARM_REPEAT 1
#define ALARMLIST_INITIALSIZE 2
#define ALARM_BUFLEN 8

#define MAX_AFTER_YEAR 100

#define FERROR_MEMORY_LOW -1
#define FERROR_FILE_FAIL -2
#define FERROR_GENERAL -3
#define STATUS_OK 0

#define ALARMFILE_MAX_LINELEN 60

#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max)()

/*Const Numbers*/
const int fontCommSize = 1;
const int fontNormalSize = 22;
const int windowClockW = 640;
const int windowClockH = 400;
const int windowNormalW = 80;
const int windowNormalH = 25;
const int windowNormalB = 1000;
const int colorCommBack = COLOR_BLACK;
const int colorCommFore = COLOR_WHITE;
const int thickSecond = 1;
const int thickMinute = 2;
const int thickHour = 5;
const int figreStrokeNum = 7;
const int thickColon = 4;
const int timeRefresh = 20;
const int dayOfThisMonth[2][13] = { { 0, 31, 28, 31,30,31,30,31,31,30,31,30,31 },{ 0, 31, 29, 31,30,31,30,31,31,30,31,30,31 } };
const double handlenSecond = 0.9;
const double handlenMinute = 0.75;
const double handlenHour = 0.4;
const double lenGrad = 0.08;
const double clfSecondsPer100ns = 100. * 1.E-9;
const COORD clockCenterPos = { 320, 120 };
const COORD EClockStartPos = { 60, 100 };


const double pi = 3.14159265;
const double ratioCharWidthOverHeight = 0.5;

const bool debugSwitch = 0;
const int sizeGridComm = 16;
const COORD clockTextPos1 = { 100, 300 };
const COORD clockTextPos2 = { 100, 320 };
const COORD clockDatePos = { 100, 240 };

/*Const Strings*/
const wchar_t * const fontCommName = L"新宋体";
const wchar_t * const fontNormalName = L"新宋体";
const char * const alarmFileName = ".\\1652270\\clock.ini";
const char * const weekDayName = "日一二三四五六";
const char * const audioFileName = ".\\1652270\\Marimba-tune-loop-118-bpm.mp3";
const char * const hintText1 = "ａ－查看闹钟　ｅ－电子时钟";
const char * const hintText2 = "ｃ－指针时钟　ｑ－退出";
const char * const fullNumbers = "０１２３４５６７８９－";
const char * const fullWeek = "日一二三四五六";


/*Structs*/
struct Clock
{
	COORD centerPos;
	short radius;
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
	int colorFore;
	int colorBack;
};

struct Figure
{
	COORD startPos;
	short widthX;
	short widthY;
	short thickX;
	short thickY;
	short n;
};

struct Stroke
{
	double sxr;  //startXRatio
	double syr;  //startYRatio
	double exr;  //end...
	double eyr;
};

struct EClock
{
	COORD startPos;
	short widthX;
	short widthY;
	short thickX;
	short thickY;
	short gap;
	short spaceBetw;
	bool havesec;
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
	int colorFore;
	int colorBack;
};

typedef union {
	ULARGE_INTEGER li;
	FILETIME       ft;
} TIMESTAMP;

struct Alarm
{
	int alarmtype;
	SYSTEMTIME t;
	int weekgap;
	int weekday;
	TIMESTAMP stamp;
	TIMESTAMP nexttime;
};


const struct Stroke patFigures[10][figreStrokeNum] =
{
	{ { 0,0,1,0 },{ 0,0,0,1 },{ 1,0,1,1 },{ 0,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
	{ { 1,0,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
	{ { 0,0,1,0 },{ 1,0,1,0.5 },{ 1,0.5,0,0.5 },{ 0,0.5,0,1 },{ 0,1,1,1 },{ 0,0,0,0 } ,{ 0,0,0,0 } },
	{ { 0,0,1,0 },{ 1,0,1,0.5 },{ 1,0.5,0,0.5 },{ 1,0.5,1,1 },{ 0,1,1,1 },{ 0,0,0,0 } ,{ 0,0,0,0 } },
	{ { 0,0,0,0.5 },{ 0,0.5,1,0.5 },{ 1,0,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } ,{ 0,0,0,0 } },
	{ { 1,0,0,0 },{ 0,0,0,0.5 },{ 0,0.5,1,0.5 },{ 1,0.5,1,1 },{ 1,1,0,1 },{ 0,0,0,0 } ,{ 0,0,0,0 } },
	{ { 1,0,0,0 },{ 0,0,0,0.5 },{ 0,0.5,1,0.5 },{ 1,0.5,1,1 },{ 1,1,0,1 },{ 0,1,0,0.5 } ,{ 0,0,0,0 } },
	{ { 0,0,1,0 },{ 1,0,1,1 },{ 0,0,0,0 } ,{ 0,0,0,0 } ,{ 0,0,0,0 } ,{ 0,0,0,0 } ,{ 0,0,0,0 } },
	{ { 0,0,1,0 },{ 0,0,0,1 },{ 0,0.5,1,0.5 } ,{ 1,0,1,1 } ,{ 0,1,1,1 } ,{ 0,0,0,0 } ,{ 0,0,0,0 } },
	{ { 0,0,1,0 },{ 0,0,0,0.5 },{ 0,0.5,1,0.5 } ,{ 1,0,1,1 } ,{ 0,1,1,1 } ,{ 0,0,0,0 } ,{ 0,0,0,0 } }
};

/*Handles*/
const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄

/*Tool Func*/
void msgInt(int n);
void msgChr(char n);
void msgStr(const char * n);
int sgn(int x);
int sgn(double x);
void inputInt(int* p, const char * promptText, const char * cinUngoodText, const char * outLimitText, int lowerLimit, int upperLimit, bool clearBuffer);
bool isLeapYear(int year);
void addSecondsToSystemTime(SYSTEMTIME* timeIn, SYSTEMTIME* timeOut, double sec);
int keyBoardHit();

/*Graphics Func*/
void initClock();
void initMenu();
void initViewAlarm();
void setGlobalColor(int back, int fore);
void drawCircleAtUpperLeft(COORD pos, int radius);
void drawCircleAtCenter(COORD pos, int radius);
void drawLineByPoint(COORD point1, COORD point2, int widthX, int widthY);
void drawPoint(COORD point, int widthX, int widthY);

/*Clock Func*/
void updateHourHand(Clock &c, SYSTEMTIME t);
void updateMinuteHand(Clock &c, SYSTEMTIME t);
void updateSecondHand(Clock &c, SYSTEMTIME t);
void getTimeToHMS(SYSTEMTIME st, Clock &c);
void getTimeToHMS(SYSTEMTIME st, EClock &c);
void drawGrad(Clock &c);
void drawFigure(Figure &f);
void drawColon(COORD startPos, int widthY);
void clearAll(COORD leftTop, COORD rightBottom);
void GetLocalTime_(SYSTEMTIME &st, int n);
void printHanZi(ifstream &f, short gridSize, COORD startPos, const unsigned char * hanzi);
void drawEClock(EClock &e, SYSTEMTIME st, bool force = 0);
void drawTwoDigit(Figure &f, COORD startPos, int widthX, int gap, short num1, short num2);
int EClockMain(ifstream &f, Alarm **a);
int clockMain(ifstream &f, Alarm **a);


/*Alarm Func*/
void printTime(SYSTEMTIME st);
void turnSystemTimeToStamp(Alarm &a);
void updateAlarmNextTime(Alarm &a, bool force = false);
int addAlarm(Alarm **&alarms, int originalAlarmsSize);
void deleteAlarm(Alarm **&alarms, int alarmNo);
void viewThisAlarm(Alarm ** p, Alarm ** alarms);
int viewAlarm(Alarm **&alarms);
int createAlarmFile();
void freeAlarm(Alarm **alarms);
int writeAlarm(Alarm **alarms);
int readAlarm(Alarm **&alarms);
void orderAlarm(Alarm **alarms);
int checkTrigAlarm(SYSTEMTIME *stp, Alarm **alarms);
void viewThisAlarm(Alarm **p, Alarm **alarms);
void playAudio();