/* 1652270 计算机2班 冯舜 */
/*AWESOMESudokuSJProject - 90-b2.h*/
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "cmd_console_tools.h"
#include "time.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <cmath>
#include <fstream>
#include <cstring>

//cin.ignore中用，代表缓冲区大小
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max)()

using namespace std;

//debug开关，调试用
const bool debug = false;

//画边框用
const char box[] = "┏━┓┃┗┛";
const char boxIn[] = "┳┣╋┫┻";


/*Const Numbers*/
const int fileNameLen = 26;
const int sleepTime = 100;

/*Const Strings*/
const char * const DFSStr1 = "深度优先搜索计算次数： ";
const char * const DFSStr2 = " 次，深度 ";
const char * const DFSStr3 = " 层，最深 ";
const char * const DFSStr4 = " 层。";

const int DFSlen1 = strlen(DFSStr1);
const int DFSlen2 = 10;
const int DFSlen3 = strlen(DFSStr2);
const int DFSlen4 = 2;
const int DFSlen5 = strlen(DFSStr3);
const int DFSlen6 = 2;


/*Structures*/
/*用以描述图形化选框中的选项。链表结构。*/
struct item
{
	char *text;
	item *next;
};

/*用以描述数独中某一格子的位置。*/
struct Coord
{
	short x;
	short y;
};

/*用以描述图形化选框的相关信息，如绑定的选项列表、宽高、位置*/
struct listbox
{
	item *items;
	int w;
	int h;
	COORD pos;
	int index;  //当前选中项的编号
	int top;	//列表显示出来第一项的编号
	int itemLen;
};

/*用以描述一个具体的数独棋盘的状态。*/
struct Sudoku
{
	int t[11][11];
};

/*棋局，用以描述一盘数独的先后步骤关系。链表结构。*/
struct composition
{
	Sudoku c;
	composition *next;
	composition *prev;
};

/*描述一个数独棋盘的初始设定状态。*/
struct Board
{
	Sudoku *s;			//绑定的当前数独状态。
	Sudoku *initial;	//初始的数独状态。
	Sudoku *o;			//overlay Sudoku，用来冲突标色用。
	COORD start;		//开始绘制的控制台坐标。
	Coord sel;			//当前选中的格子。
	COORD *bulletin;	//绑定的提示文字的绘制位置。
	int toInput;		//接下来要在某个格子中输入的内容。
};

/*描述一个可以通过鼠标、键盘操作的事物。*/
struct Clickable
{
	bool moveTrig;		//若鼠标在其上移动可以激活操作它，置 true。
	bool keyTrig;		//若键盘操作可以激活操作它，置 true。
	COORD rectTop1;		//鼠标可操作区域的左上角顶点。（包含）
	COORD rectTop2;		//鼠标可操作区域的右下角顶点。（不包含）
	int (*trigFunc)(const INPUT_RECORD rec, void **args);//鼠标、键盘操作有效时，所调用的函数。
	void **args;		//给上述函数传递的参数的指针 构成的数组。
};

/*自动解数独用，用以描述一个数独状态中，每个格子可以填哪些数字。（用位模式记录）*/
struct SudokuValue
{
	short t[11][11];
};

/*Handles*/
const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄

//默认背景，默认前景，字符已填，字符未填，字符冲突，选择高亮，冲突背景
const int commonColor[] = {COLOR_WHITE, COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_HRED, COLOR_HBLACK, COLOR_HWHITE};
const char numToLetter[] = "abcdefghijklmn";


/*Base*/
int itemAppend(item *&i, const char * const p, listbox *l);
item* itemNext(item * const p, int n);
int itemFree(item *head);
int itemCount(item *head);
void itemsDraw(listbox *l);
void itemsUpdate(listbox *l, int lastIndex, int lastTop);
int boxDraw(listbox *l);
int getFileList(item *&items, listbox *l);
int itemPrint(item *head);
void initSudoku(Sudoku *s, int wallElement, int spaceElement);
void initSudoku(Sudoku *s, Sudoku *o);
int inputSudoku(Sudoku *s, ifstream *f);
int charSudoku(Sudoku *s, Sudoku *initial, Sudoku *o);
int validSudoku(Sudoku *s, Sudoku *overMap);
int compAppend(composition *&i, const Sudoku &c);
composition* compNext(composition * const p, int n);
composition* compPrev(composition * const p, int n);
int compFree(composition *head);
int compDropTail(composition *&head, int n);
int compCount(composition *head);
int compCount(composition *head, composition *p);
bool isSudokuFull(Sudoku *s);
int *getGridPointer(Sudoku *s, const Coord c);
int *getInputAble(Board *b);
int lengthOfValueSquare(short s, int *theOnly);
int parseGrid(Sudoku *s, SudokuValue *v);
int gridEliminate(SudokuValue *v, int j, int i, int d);
int squareAssign(SudokuValue *v, int j, int i, int d);
int depthSearch(SudokuValue *v, int *dfsArgs, Board *b);


/*Tools*/
void pressEnterToContinue(char *p);
COORD getxy_(const HANDLE hout);
void restoreColor();
void gracefullyReturn(int startX);
int charSelFile(char * const fileName);
void clearLines(int line);
void printLine(const char * const str, int line = 1);
int inputTrig(Clickable **clist);
int boxTrig(INPUT_RECORD iRec, void **args);
int listSelFile(char * const fileName, listbox *fileList, Clickable **clickable);
COORD coordPlus(COORD c1, COORD c2);
COORD coordPlus(COORD c1, short X, short Y);
void clearLines(int line, int limitCharPerLine);
void startInit();

/*Graphics*/
void printBoard(Board *b);
int selTrig(INPUT_RECORD iRec, void**args);
void cleanInputBox(COORD inputPos);
int boardTrig(INPUT_RECORD iRec, void **args);
void updateGrid(Board *b, Coord c, int fore, int back);
void drawBkFw(COORD bkfwStart, COORD bkfwWH);
void drawInputBox(COORD inputPos);
void drawBox(short w, short h);
int backTrig(INPUT_RECORD iRec, void **args);
void cleanInputBox(COORD inputPos);
void updateInputAble(Board *b, COORD *bulletin);
void updateBoardAuto(Board *b, SudokuValue *vp, int* args);
void printDFSProgress(int *args, COORD *bulletin);