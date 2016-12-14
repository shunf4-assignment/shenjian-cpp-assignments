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
const int textTowerBaseYOffset1 = 3;
const int textTowerBaseYOffset2 = 3;
const int drawTowerBaseYOffset = 3;
const int towerDrawPreSpace = 6;
const int towerDrawGap = 6;
const int towerDrawLength = 2 * maxDisk + 5;
const int colorList[] = { 0, COLOR_RED, COLOR_BLUE, COLOR_CYAN,COLOR_GREEN,COLOR_PINK,COLOR_HRED,COLOR_HBLUE,COLOR_HCYAN,COLOR_HGREEN,COLOR_HPINK,1333,2444,3433 };
const int defaultBg = COLOR_BLACK;
const int defaultFg = COLOR_WHITE;
const int defaultTw = COLOR_YELLOW;
const int speedList[] = { 1500, 800, 300, 100, 60, 20, 8, 2, 1, 0 };

int totalMove = 0;
int towers[3][maxDisk] = { { 0 },{ 0 },{ 0 } };
int towerPointer[] = { 0,0,0 };  //指的是层数+1，也就是Push下一个圆盘应该在的位置

void pause(int speed, bool faster = false)
{
	Sleep(faster ? (speedList[speed % 10] / 4) : speedList[speed % 10]);
}
void pause_()
{
	/*freopen("CON", "r", stdin);
	system("pause>nul");
	freopen("in.txt", "r", stdin);*/
	_getch();
}

void restoreColor(HANDLE h)
{
	setcolor(h, defaultBg, defaultFg);
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

void drawTower(HANDLE h, int speed)
{
	for (int towerNo = 0; towerNo < 3; towerNo++)
	{
		showch(h, towerDrawPreSpace + (towerDrawLength * towerNo) + towerDrawGap * towerNo, maxDisk + drawTowerBaseYOffset, ' ', defaultTw, defaultBg, towerDrawLength);
		for (int i = 0; i < maxDisk + drawTowerBaseYOffset - 2; i++)
		{
			showch(h, towerDrawPreSpace + (towerDrawLength * towerNo) + towerDrawLength / 2 + towerDrawGap * towerNo, maxDisk + drawTowerBaseYOffset - i - 1, ' ', defaultTw, defaultBg, 1);
			pause(speed);
		}
	}
}
void drawDiskAtGivenPlace(HANDLE h, int towerNo, int towerHeight, int num)
{
	showch(h, towerDrawPreSpace + (towerDrawLength * towerNo) + towerDrawLength / 2 + towerDrawGap * towerNo - diskLength(num) / 2, maxDisk + drawTowerBaseYOffset - towerHeight - 1, ' ', colorList[num], defaultBg, diskLength(num));
	return;
}

void hideDiskAtGivenPlace(HANDLE h, int towerNo, int towerHeight, int num)
{
	showch(h, towerDrawPreSpace + (towerDrawLength * towerNo) + towerDrawLength / 2 + towerDrawGap * towerNo - diskLength(num) / 2, maxDisk + drawTowerBaseYOffset - towerHeight - 1, ' ', defaultBg, defaultBg, diskLength(num));
	if (towerHeight < maxDisk + drawTowerBaseYOffset - 2)
		showch(h, towerDrawPreSpace + (towerDrawLength * towerNo) + towerDrawLength / 2 + towerDrawGap * towerNo, maxDisk + drawTowerBaseYOffset - towerHeight - 1, ' ', defaultTw, defaultBg, 1);
}

void drawMoveDiskUpOne(HANDLE h, int origin, int oriPlace)
{
	hideDiskAtGivenPlace(h, origin, oriPlace, towers[origin][towerPointer[origin]]);
	drawDiskAtGivenPlace(h, origin, oriPlace + 1, towers[origin][towerPointer[origin]]);
	return;
}

void drawMoveDiskDownOne(HANDLE h, int origin, int oriPlace)
{
	hideDiskAtGivenPlace(h, origin, oriPlace, towers[origin][towerPointer[origin]
		- 1]);
	drawDiskAtGivenPlace(h, origin, oriPlace - 1, towers[origin][towerPointer[origin] - 1]);
	return;
}

void drawMoveDiskRightOne(HANDLE h, int oriX, int len, int right, int color) //如果右移，right置为1，左移置为-1
{
	switch (right)
	{
		case 1:
			showch(h, oriX, drawTowerBaseYOffset - 2, ' ', defaultBg, defaultBg, 1);
			showch(h, oriX + len, drawTowerBaseYOffset - 2, ' ', color, defaultBg, 1);
			break;
		case -1:
			showch(h, oriX + len - 1, drawTowerBaseYOffset - 2, ' ', defaultBg, defaultBg, 1);
			showch(h, oriX - 1, drawTowerBaseYOffset - 2, ' ', color, defaultBg, 1);
			break;
	}
	return;
}

void drawInitDisk(HANDLE h, int origin, int num, int speed)
{
	for (int i = 0; i < num; i++)
	{
		drawDiskAtGivenPlace(h, origin, i, towers[origin][i]);
		pause(speed);
	}
	restoreColor(h);

}

void drawMoveDisk(HANDLE h, int origin, int dest, int num, int speed)
{
	int oriPlace = towerPointer[origin];
	for (int i = 0; i < maxDisk - towerPointer[origin] + drawTowerBaseYOffset - 2; i++)
	{
		drawMoveDiskUpOne(h, origin, oriPlace++);
		pause(speed);
	}
	int u = (dest - origin > 0) ? 1 : -1;
	int oriX = towerDrawPreSpace + (towerDrawLength * origin) + towerDrawLength / 2 + towerDrawGap * origin - diskLength(num) / 2;
	for (int i = 0; i < abs((towerDrawLength + towerDrawGap) * (dest - origin)); i++)
	{
		drawMoveDiskRightOne(h, oriX, diskLength(num), u, colorList[num]);
		oriX += u;
		pause(speed, true);

	}
	for (int i = 0; i < maxDisk - towerPointer[dest] + drawTowerBaseYOffset - 1; i++)
	{
		drawMoveDiskDownOne(h, dest, oriPlace--);
		pause(speed);
	}
	restoreColor(h);
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
	gotoxy(h, getXPos(lower, to, towerPointer[to] - 1), getYPos(lower, to, towerPointer[to] - 1));
	cout << setw(2) << num;
}

void printArray(int num, int from, int to, bool initial, bool outArray, bool outNum, int mode, int speed)
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
	if ((mode == 4 || mode == 8) && (speed / 10))
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
			pause(speed);
			break;
		case 6:
		case 7:
		case 8:
			outArray = true;
			drawMoveDisk(h, from, to, num, speed);
			if (mode == 7)
			{
				break;
			}
			printTowerMove(h, from, to, num, true);
			gotoxy(h, 0, maxDisk + textTowerBaseYOffset1 + maxDisk + textTowerBaseYOffset2 + 1);
			printArray(num, from, to, false, outArray, true, mode, speed);
			break;
	}
	if (speed / 10)
	{
		_getch();
	}
	cout << endl;
}

void HanoiStep(HANDLE h, int origin, int dest, int totalNum, int mode, int speed, bool outerCall = true)
{
	//定义这样的一组动作为“汉诺步骤”
	int intermediate;
	static bool mode7Moved = false;
	if (outerCall)
		mode7Moved = false;
	if (mode == 7 && !mode7Moved || mode != 7) {
		if (totalNum == 1)
		{
			Move(h, origin, dest, 1, mode, speed);
			mode7Moved = true;
			return;
		}
		intermediate = 0 + 1 + 2 - origin - dest;
		HanoiStep(h, origin, intermediate, totalNum - 1, mode, speed, false);
		if (mode == 7 && mode7Moved)
			return;
		Move(h, origin, dest, totalNum, mode, speed);
		HanoiStep(h, intermediate, dest, totalNum - 1, mode, speed, false);
	}
	else
	{
		return;
	}
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
		case 7:
		case 9:
		case 8:
			printTowerBase(h, true);
			printTowerGra(h, true, true);
			gotoxy(h, 0, maxDisk + textTowerBaseYOffset1 + maxDisk + textTowerBaseYOffset2 + 1);
			printArray(-1, -1, -1, true, true, true, mode, speed);
			cout << endl;
			break;
	}
}

void HanoiGame(HANDLE h, int origin, int dest, int totalNum, int speed)
{
	char str[80] = { '\0' };

	while (true) {
		gotoxy(h, 0, maxDisk + textTowerBaseYOffset1 + maxDisk + textTowerBaseYOffset2 + 3);
		cout << setw(140) << "";
		gotoxy(h, 0, maxDisk + textTowerBaseYOffset1 + maxDisk + textTowerBaseYOffset2 + 4);
		cout << setw(140) << "";
		gotoxy(h, 0, maxDisk + textTowerBaseYOffset1 + maxDisk + textTowerBaseYOffset2 + 3);
		if (towerPointer[dest] == totalNum)
		{
			cout << "游戏结束，你赢了。";
			break;
		}
		cout << "输入命令，如AC代表从A到C:";
		cin >> str;
		if (strlen(str) != 2 || str[0] > 'C' || str[0] < 'A' || str[1] > 'C' || str[1] < 'A' || str[0] == str[1])
		{
			cout << "输入错误或超出范围，请重新输入。" << endl;
			Sleep(1000);
			continue;
		}
		if (towerPointer[(str[0] - 'A')] == 0)
		{
			cout << "移出的柱上没有圆盘，请重新输入。" << endl;
			Sleep(1000);
			continue;
		}
		if (towerPointer[(str[1] - 'A')] != 0 && towers[(str[1] - 'A')][towerPointer[(str[1] - 'A')] - 1] < towers[(str[0] - 'A')][towerPointer[(str[0] - 'A')] - 1])
		{
			cout << "将造成大盘压小盘，请重新输入。" << endl;
			Sleep(1000);
			continue;
		}
		Move(h, str[0] - 'A', str[1] - 'A', towers[str[0] - 'A'][towerPointer[str[0] - 'A'] - 1], 8, speed);
	}


}

void Hanoi(HANDLE h, int origin, int dest, int totalNum, int mode, int speed)
{
	//给塔栈初始化
	restoreColor(h);
	system("cls");
	if (mode != 5) {
		cout << "从 " << char(origin + 'A') << " 移动到 " << char(dest + 'A') << " ，共 " << totalNum << " 层。" << endl;
		for (int i = 0; i < totalNum; i++)
		{
			towers[origin][i] = totalNum - i;
		}
		for (int i = 0; i < 3; i++)
		{
			towerPointer[i] = 0;
		}
		towerPointer[origin] = totalNum;
	}
	if (mode >= 5)
	{
		drawTower(h, speed);
		if (mode == 5)
			return;
		drawInitDisk(h, origin, totalNum, speed);
		if (mode == 6)
			return;
	}
	OutputInit(h, mode, speed);
	if (mode != 9)
	{
		if(mode >= 4)
			pause(2);
		HanoiStep(h, origin, dest, totalNum, mode, speed);
	}
	else
	{
		HanoiGame(h, origin, dest, totalNum, speed);
	}
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
	int pressCont = 0;

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
	if (mode == 4 || mode == 8 || mode == 7 || mode == 9) {
		do
		{
			valid = true;
			cout << "输入移动速度（0-9从最慢到最快）：";
			cin >> *speed;

			if (!cin.good() || *speed > 9 || *speed < 0)
			{
				valid = false;
				cout << "输入不合法，请重新输入。" << endl;
				cin.clear();
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
				continue;
			}
		} while (!valid);
		cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
		if (mode != 9 && mode != 7)
		{
			do
			{
				valid = true;
				cout << "是(1)否(0)每一步都按回车键暂停？";
				cin >> pressCont;

				if (!cin.good() || pressCont > 1 || pressCont < 0)
				{
					valid = false;
					cout << "输入不合法，请重新输入。" << endl;
					cin.clear();
					cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
					continue;
				}
			} while (!valid);
			*speed += pressCont * 10;
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
		}

	}
}

int main()
{
	int mode;
	int n;
	char towerOrigin, towerDest, opt;
	int speed;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	setconsoleborder(h, maxDisk * 10 + 18, 40);
	restoreColor(h);
	while (true)
	{
		mode = 1;
		speed = 3;
		system("cls");

		//freopen("in.txt", "r", stdin);

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
		restoreColor(h);
		if (mode >= 4)
		{
			gotoxy(h, 0, maxDisk + textTowerBaseYOffset1 + maxDisk + textTowerBaseYOffset2 + 3);
		}
		if (mode == 9)
			cout << endl;
		cout << "按任意键";
		_getch();
	}
	return 0;
}
