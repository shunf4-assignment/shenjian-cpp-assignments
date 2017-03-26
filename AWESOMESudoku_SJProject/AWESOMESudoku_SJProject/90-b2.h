
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
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max)()

using namespace std;

const char box[] = "┏━┓┃┗┛";
const char boxIn[] = "┳┣╋┫┻";


/*Const Numbers*/
const int fileNameLen = 26;

/*Structures*/
struct item
{
	char *text;
	item *next;
};

struct Coord
{
	short x;
	short y;
};

struct listbox
{
	item *items;
	int w;
	int h;
	COORD pos;
	int index;
	int top;
	int itemLen;
};

struct Sudoku
{
	int t[11][11];
	Coord sel;
};


/*Handles*/
const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄

//默认背景，默认前景，字符已填，字符未填
const int commonColor[] = {COLOR_BLACK, COLOR_WHITE, COLOR_HBLUE, COLOR_HYELLOW};
const char numToLetter[] = "abcdefghijklmn";


/*Base*/
int itemAppend(item *&i, const char * const p, listbox *l);
item* itemNext(item * const p, int n);
int itemFree(item *head);
void itemsDraw(listbox *l);
void itemsUpdate(listbox *l, int lastIndex, int lastTop);
int boxDraw(listbox *l);
int boxWaitInput(listbox *l, int *lastIndex, int* lastTop);
int getFileList(item *&items, listbox *l);
int itemPrint(item *head);
void initSudoku(Sudoku *s, int wallElement, int spaceElement);
int inputSudoku(Sudoku *s, ifstream *f);
int charSudoku(Sudoku *s);

/*Tools*/
COORD getxy_(const HANDLE hout);
void restoreColor();
void gracefullyReturn(int startX);
int charSelFile(char * const fileName);