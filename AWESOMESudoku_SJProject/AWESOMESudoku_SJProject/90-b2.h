/* 1652270 �����2�� ��˴ */
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

//cin.ignore���ã�����������С
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max)()

using namespace std;

//debug���أ�������
const bool debug = false;

//���߿���
const char box[] = "������������";
const char boxIn[] = "�שǩ�ϩ�";


/*Const Numbers*/
const int fileNameLen = 26;
const int sleepTime = 100;

/*Const Strings*/
const char * const DFSStr1 = "�������������������� ";
const char * const DFSStr2 = " �Σ���� ";
const char * const DFSStr3 = " �㣬���� ";
const char * const DFSStr4 = " �㡣";

const int DFSlen1 = strlen(DFSStr1);
const int DFSlen2 = 10;
const int DFSlen3 = strlen(DFSStr2);
const int DFSlen4 = 2;
const int DFSlen5 = strlen(DFSStr3);
const int DFSlen6 = 2;


/*Structures*/
/*��������ͼ�λ�ѡ���е�ѡ�����ṹ��*/
struct item
{
	char *text;
	item *next;
};

/*��������������ĳһ���ӵ�λ�á�*/
struct Coord
{
	short x;
	short y;
};

/*��������ͼ�λ�ѡ��������Ϣ����󶨵�ѡ���б���ߡ�λ��*/
struct listbox
{
	item *items;
	int w;
	int h;
	COORD pos;
	int index;  //��ǰѡ����ı��
	int top;	//�б���ʾ������һ��ı��
	int itemLen;
};

/*��������һ��������������̵�״̬��*/
struct Sudoku
{
	int t[11][11];
};

/*��֣���������һ���������Ⱥ����ϵ������ṹ��*/
struct composition
{
	Sudoku c;
	composition *next;
	composition *prev;
};

/*����һ���������̵ĳ�ʼ�趨״̬��*/
struct Board
{
	Sudoku *s;			//�󶨵ĵ�ǰ����״̬��
	Sudoku *initial;	//��ʼ������״̬��
	Sudoku *o;			//overlay Sudoku��������ͻ��ɫ�á�
	COORD start;		//��ʼ���ƵĿ���̨���ꡣ
	Coord sel;			//��ǰѡ�еĸ��ӡ�
	COORD *bulletin;	//�󶨵���ʾ���ֵĻ���λ�á�
	int toInput;		//������Ҫ��ĳ����������������ݡ�
};

/*����һ������ͨ����ꡢ���̲��������*/
struct Clickable
{
	bool moveTrig;		//������������ƶ����Լ������������ true��
	bool keyTrig;		//�����̲������Լ������������ true��
	COORD rectTop1;		//���ɲ�����������ϽǶ��㡣��������
	COORD rectTop2;		//���ɲ�����������½Ƕ��㡣����������
	int (*trigFunc)(const INPUT_RECORD rec, void **args);//��ꡢ���̲�����Чʱ�������õĺ�����
	void **args;		//�������������ݵĲ�����ָ�� ���ɵ����顣
};

/*�Զ��������ã���������һ������״̬�У�ÿ�����ӿ�������Щ���֡�����λģʽ��¼��*/
struct SudokuValue
{
	short t[11][11];
};

/*Handles*/
const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //ȡ��׼����豸��Ӧ�ľ��
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //ȡ��׼�����豸��Ӧ�ľ��

//Ĭ�ϱ�����Ĭ��ǰ�����ַ�����ַ�δ��ַ���ͻ��ѡ���������ͻ����
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