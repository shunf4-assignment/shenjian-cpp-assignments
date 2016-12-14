/* 1652270 计算机2班 冯舜 */
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <iomanip>
#include "cmd_console_tools.h"

using namespace std;

const int maxDisk = 10;
const int baseMarginX = 6;
const char towerName[] = { 'A', 'B', 'C' };
const int halfTowerGap = 4;
const int colorHalfTowerGap = 4;
const int textTowerBaseYOffset1 = 7;
const int textTowerBaseYOffset2 = 7;
const int drawTowerBaseYOffset = 3;
const int towerDrawPreSpace = 6;
const int towerDrawGap = 6;
const int towerDrawLength = 2 * maxDisk + 5;
const int colorList[] = { 0, COLOR_RED, COLOR_BLUE, COLOR_CYAN,COLOR_GREEN,COLOR_PINK,COLOR_HRED,COLOR_HBLUE,COLOR_HCYAN,COLOR_HGREEN,COLOR_HPINK };

int totalMove = 0;
int towers[3][maxDisk] = { { 0 },{ 0 },{ 0 } };
int towerPointer[] = { 0,0,0 };  //指的是层数+1，也就是Push下一个圆盘应该在的位置

void pause(int speed)
{
	switch (speed)
	{
		case 0:
			_getch();
			break;
		default:
			Sleep(1010 - speed * 200);
	}
}
void pause_()
{
	/*freopen("CON", "r", stdin);
	system("pause>nul");
	freopen("in.txt", "r", stdin);*/
	_getch();
}

int getXPos(bool lower, int towerNo, int towerHeight)
{
	return baseMarginX + halfTowerGap * (2 * towerNo + 1) + 2 * towerNo;
}

int getYPos(bool lower, int towerNo, int towerHeight)
{
	return  ((-2 - towerHeight + maxDisk + textTowerBaseYOffset1) + ((lower) ? (maxDisk + textTowerBaseYOffset2) : 0));
}

int Push(int towerNum, int diskSize)
{
	towers[towerNum][towerPointer[towerNum]++] = diskSize;
	return diskSize;
}

int Pop(int towerNum)
{
	return towers[towerNum][--towerPointer[towerNum]];
}

void printTowerBase(HANDLE h, bool lower = false)
{
	gotoxy(h, baseMarginX, getYPos(lower, 0, -1));
	for (int i = 0; i < halfTowerGap * 6 + 6; i++)
		cout << '=';
	cout << endl;
	cout << setw(baseMarginX + halfTowerGap) << "";
	cout << setw(2) << "A";
	cout << setw(2 * halfTowerGap) << "";
	cout << setw(2) << "B";
	cout << setw(2 * halfTowerGap) << "";
	cout << setw(2) << "C";
	
}

int diskLength(int disk)
{ //dick的长度
	return disk * 2 + 3;
}

void drawTower(HANDLE h)
{
	for (int towerNo = 0; towerNo < 3; towerNo++)
	{
		showch(h, towerDrawPreSpace + (towerDrawLength * towerNo) + towerDrawGap * towerNo, maxDisk + drawTowerBaseYOffset, ' ', COLOR_HYELLOW, COLOR_BLACK, towerDrawLength);
		for (int i = 0; i < maxDisk + drawTowerBaseYOffset - 2; i++)
		{
			showch(h, towerDrawPreSpace + (towerDrawLength * towerNo) + towerDrawLength / 2 + towerDrawGap * towerNo, maxDisk + drawTowerBaseYOffset - i - 1, ' ', COLOR_HYELLOW, COLOR_BLACK, 1);
			pause(5);
		}
	}
}

void drawTowerAndInitDisk(HANDLE h, int origin, int num)
{
	drawTower(h);
	for (int i = 0; i < num; i++)
	{
		showch(h, towerDrawPreSpace + (towerDrawLength * origin) + towerDrawLength / 2 + towerDrawGap * origin - diskLength(towers[origin][i]) / 2, maxDisk + drawTowerBaseYOffset - i - 1, ' ', colorList[towers[origin][i]], COLOR_BLACK, diskLength(towers[origin][i]));
		pause(5);
	}
}

void printTowerGra(HANDLE h, bool clean, bool lower)
{
	int thisX, thisY;
	for (int towerNo = 0; towerNo < 3; towerNo++)
	{
		thisY = getYPos(lower, towerNo, 0);
		thisX = getXPos(lower, towerNo, 0);
		for (int towerDisk = 0; towerDisk < (clean ? maxDisk : towerPointer[towerNo]); towerDisk++)
		{
			gotoxy(h, thisX, thisY);
			if (towerDisk < towerPointer[towerNo])
				cout << setw(2) << towers[towerNo][towerDisk];
			else
				cout << "  ";
			thisY -= 1;
		}
	}
}

void printTowerMove(HANDLE h, int from, int to, int num, bool lower = false)
{
	gotoxy(h, getXPos(lower, from, towerPointer[from]), getYPos(lower, from, towerPointer[from]));
	cout << "  ";
	gotoxy(h, getXPos(lower, to, towerPointer[to] -1), getYPos(lower, to, towerPointer[to] -1 ));
	cout << setw(2) << num;
}

void printArray(int num, int from, int to, bool initial, bool outArray, bool outNum,int mode, int speed)
{
	
	if (!initial) {
		if (outNum) {
			cout << "Step" << setw(5) << setfill('0') << totalMove << setfill(' ') << ":";
		}
		cout << "(" << num << ")@" << towerName[from] << "-->" << towerName[to] << ". ";
	}
	else
	{
		if (outNum)
			cout << "初始：               ";
	}
	if (outArray) {
		for (int towerNo = 0; towerNo < 3; towerNo++)
		{
			cout << towerName[towerNo] << ":";
			for (int i = 0; i < towerPointer[towerNo]; i++)
			{
				cout << setw(3) << towers[towerNo][i];
			}
			cout << setw(3 * maxDisk - 3 * towerPointer[towerNo]) << "";
		}
	}
	if(mode == 4 || mode == 8)
		pause(speed);
}

//A:0,B:1,C:2
void Move(HANDLE h, int from, int to, int num, int mode, int speed)
{
	totalMove += 1;
	Pop(from);
	Push(to, num);
	//开始输出
	bool outArray = false;
	bool outNum = false;
	switch (mode)
	{
		case 4:
			printTowerMove(h, from, to, num, false);
			gotoxy(h, 0, maxDisk + textTowerBaseYOffset1 + 2);
		case 3:
			outArray = true;
		case 2:
			outNum = true;
		case 1:
			printArray(num, from, to, false, outArray, outNum, mode, speed);
			break;
		case 8:
			gotoxy(h, 0, maxDisk + textTowerBaseYOffset1 + maxDisk + textTowerBaseYOffset2 + 1);
			printTowerMove(h, from, to, num, true);
			printArray(num, from, to, false, outArray, true, mode, speed);
			break;
	}
	cout << endl;
}

void HanoiStep(HANDLE h, int origin, int dest, int totalNum, int mode, int speed)
{
	//定义这样的一组动作为“汉诺步骤”
	char intermediate;

	if (totalNum == 1)
	{
		Move(h, origin, dest, 1, mode, speed);
		return;
	}
	intermediate = 0 + 1 + 2 - origin - dest;
	HanoiStep(h, origin, intermediate, totalNum - 1, mode, speed);
	Move(h, origin, dest, totalNum, mode, speed);
	HanoiStep(h, intermediate, dest, totalNum - 1, mode, speed);
}

void OutputInit(HANDLE h, int mode, int speed)
{
	switch (mode)
	{
		case 1:
		case 2:
			break;
		case 4:
			printTowerBase(h, false);
			printTowerGra(h, true, false);
			gotoxy(h, 0, maxDisk + textTowerBaseYOffset1 + 2);
		case 3:
			printArray(-1, -1, -1, true, true, true, mode, speed);
			cout << endl;
			break;
		case 8:
			printTowerBase(h, true);
			printTowerGra(h, true, true);
			gotoxy(h, 0, maxDisk + textTowerBaseYOffset1 + maxDisk + textTowerBaseYOffset2 + 1);
			printArray(-1, -1, -1, true, true, true, mode, speed);
			cout << endl;
			break;
	}
}

void Hanoi(HANDLE h, int origin, int dest, int totalNum, int mode, int speed)
{
	//给塔栈初始化
	system("cls");
	for (int i = 0; i < totalNum; i++)
	{
		towers[origin][i] = totalNum - i;
	}
	for (int i = 0; i < 3; i++)
	{
		towerPointer[i] = 0;
	}
	if (mode == 5)
	{
		drawTower(h);
		return;
	}
	if (mode == 6)
	{
		drawTowerAndInitDisk(h, origin, totalNum);
		return;
	}
	towerPointer[origin] = totalNum;

	cout << "从 " << char(origin + 'A') << " 移动到 " << char(dest + 'A') << " ，共 " << totalNum << " 层。" << endl;

	OutputInit(h, mode, speed);
	HanoiStep(h,origin, dest, totalNum, mode, speed);
}

char toUpperCase(char a)
{
	if (a >= 'a' && a <= 'z')
	{
		a = a - 'a' + 'A';
		//a - 65 + 97;
	}
	return a;
}

void inputTower(int mode, int *n, char *towerOrigin, char *towerDest, int *speed)
{
	bool valid;
	if (mode >= 1 && mode <= 9 && mode != 5) {
		do
		{
			valid = true;
			cout << "初始塔有多少层圆盘(1-" << maxDisk << ")：";
			cin >> *n;

			if (!cin.good())
			{
				valid = false;
				cout << "输入不合法，请重新输入。" << endl;
				cin.clear();
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
				continue;
			}

			if (*n < 1 || *n > maxDisk)
			{
				valid = false;
				cout << "输入超出范围，请重新输入。" << endl;
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
				continue;
			}
		} while (!valid);
		cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');

		do
		{
			valid = true;
			cout << "从哪个塔移走？(A-C)";
			cin >> *towerOrigin;

			if (!cin.good())
			{
				valid = false;
				cin.clear();
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
				continue;
			}

			if (!(*towerOrigin >= 'A' && *towerOrigin <= 'C' || *towerOrigin >= 'a' && *towerOrigin <= 'c'))
			{
				valid = false;
				cout << "输入超出范围，请重新输入。" << endl;
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
				continue;
			}

			*towerOrigin = toUpperCase(*towerOrigin);

		} while (!valid);
		cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');


		do
		{
			valid = true;
			cout << "移到哪个塔？(A-C，不同于之前输入的塔)";
			cin >> *towerDest;

			if (!cin.good())
			{
				valid = false;
				cout << "输入不合法，请重新输入。" << endl;
				cin.clear();
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
				continue;
			}

			if (!(*towerDest >= 'A' && *towerDest <= 'C' || *towerDest >= 'a' && *towerDest <= 'c'))
			{
				valid = false;
				cout << "输入超出范围，请重新输入。" << endl;
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
				continue;
			}

			*towerDest = toUpperCase(*towerDest);
			if (*towerDest == *towerOrigin)
			{
				valid = false;
				cout << "两个塔不能相同，请重新输入。" << endl;
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
				continue;
			}
		} while (!valid);
	}
	if (mode == 4 || mode == 8) {
		do
		{
			valid = true;
			cout << "输入移动速度（0为按任意键手动进行，1-5分别为按810ms-10ms间隔自动进行）：";
			cin >> *speed;

			if (!cin.good() || *speed > 5 || *speed < 0)
			{
				valid = false;
				cout << "输入不合法，请重新输入。" << endl;
				cin.clear();
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
				continue;
			}
		} while (!valid);
		cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
	}
}

int main()
{

	system("cls");
	system("mode con cols=140 lines=25");
	int mode = 1;
	int n;
	char towerOrigin, towerDest, opt;
	int speed;

	freopen("in.txt", "r", stdin);
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "		---------------------------------\n\
		1.基本解\n\
		2.基本解(步数记录)\n\
		3.内部数组显示(横向)\n\
		4.内部数组显示(纵向 + 横向)\n\
		5.图形解 - 预备 - 画三个圆柱\n\
		6.图形解 - 预备 - 在起始柱上画n个盘子\n\
		7.图形解 - 预备 - 第一次移动\n\
		8.图形解 - 自动移动版本\n\
		9.图形解 - 游戏版\n\
		0.退出\n\
		----------------------------------\n\
		[请选择0 - 9]:";

	do {
		opt = _getch();
	} while (!(opt >= '0' && opt <= '9'));
	cout << opt << endl;

	mode = opt - '0';
	if (mode == 0)
		return 0;
	inputTower(mode, &n, &towerOrigin, &towerDest, &speed);
	totalMove = 0;
	Hanoi(h, towerOrigin - int('A'), towerDest - int('A'), n, mode, speed);
	return 0;
}
