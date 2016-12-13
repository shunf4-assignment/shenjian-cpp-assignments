/* 1652270 �����2�� ��˴ */
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <iomanip>
#include "cmd_console_tools.cpp"

using namespace std;

const int maxDisk = 10;
const int baseMarginX = 6;
const char towerName[] = { 'A', 'B', 'C' };
const int halfTowerGap = 4;
const int colorHalfTowerGap = 4;
const int textTowerBaseYOffset1 = 7;
const int textTowerBaseYOffset2 = 7;

int totalMove = 0;
int towers[3][maxDisk] = { { 0 },{ 0 },{ 0 } };
int towerPointer[] = { 0,0,0 };  //ָ���ǲ���+1��Ҳ����Push��һ��Բ��Ӧ���ڵ�λ��

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
	gotoxy(h, baseMarginX, maxDisk + textTowerBaseYOffset1 + lower ? (maxDisk + textTowerBaseYOffset2) : 0);
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

void printTowerGra(HANDLE h, bool clean, bool lower = false)
{

	for (int towerNo = 0; towerNo < 3; towerNo++)
	{
		int thisY = maxDisk + textTowerBaseYOffset1 + lower ? (maxDisk + textTowerBaseYOffset2) : 0;
		int thisX = baseMarginX + halfTowerGap * (2 * towerNo - 1) + 2 * towerNo;
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
	gotoxy(h, baseMarginX + halfTowerGap * (2 * from - 1) + 2 * from, (maxDisk + textTowerBaseYOffset1 + lower ? (maxDisk + textTowerBaseYOffset2) : 0) - 1 - towerPointer[from]);
	cout << "  ";
	gotoxy(h, baseMarginX + halfTowerGap * (2 * to - 1) + 2 * to, (maxDisk + textTowerBaseYOffset1 + lower ? (maxDisk + textTowerBaseYOffset2) : 0) - 1 - towerPointer[to]);
	cout << setw(2) << num;
}

void printArray(int num, int from, int to, bool initial = false, bool outArray = false)
{
	if (!initial)
		cout << "Step" << setw(5) << setfill('0') << totalMove << setfill(' ') << ":(" << num << ")@" << towerName[from] << "-->" << towerName[to] << ". ";
	else
		cout << "��ʼ��               ";
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
	pause();
}

//A:0,B:1,C:2
void Move(HANDLE h, int from, int to, int num, int mode)
{
	totalMove += 1;
	Pop(from);
	Push(to, num);
	//��ʼ���
	bool outArray = false;
	switch (mode)
	{
		case 4:
			gotoxy(h, 0, maxDisk + textTowerBaseYOffset1 + 2);
		case 3:
			outArray = true;
		case 2:
		case 1:
			printArray(num, from, to, false, outArray);
			break;
		case 8:
			gotoxy(h, 0, maxDisk + textTowerBaseYOffset1 + maxDisk + textTowerBaseYOffset2 + 1);
			printArray(num, from, to, false, outArray);
			break;
	}
	cout << endl;
}

void HanoiStep(HANDLE h, int origin, int dest, int totalNum, int mode)
{
	//����������һ�鶯��Ϊ����ŵ���衱
	char intermediate;

	if (totalNum == 1)
	{
		Move(h, origin, dest, 1, mode);
		return;
	}
	intermediate = 0 + 1 + 2 - origin - dest;
	HanoiStep(h, origin, intermediate, totalNum - 1, mode);
	Move(h, origin, dest, totalNum, mode);
	HanoiStep(h, intermediate, dest, totalNum - 1, mode);
}

void OutputInit(HANDLE h, int mode)
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
			printArray(-1, -1, -1, true);
			cout << endl;
			break;
		case 8:
			printTowerBase(h, true);
			printTowerGra(h, true, true);
			gotoxy(h, 0, maxDisk + textTowerBaseYOffset1 + maxDisk + textTowerBaseYOffset2 + 1);
			printArray(-1, -1, -1, true);
			cout << endl;
			break;
	}
}

void Hanoi(HANDLE h, int origin, int dest, int totalNum, int mode)
{
	//����ջ��ʼ��
	for (int i = 0; i < totalNum; i++)
	{
		towers[origin][i] = totalNum - i;
		towerPointer[i] = 0;
	}
	towerPointer[origin] = totalNum;
	system("cls");

	cout << "�� " << char(origin + 'A') << " �ƶ��� " << char(dest + 'A') << " ���� " << totalNum << " �㡣";

	OutputInit(h, mode);
	HanoiStep(h,origin, dest, totalNum);
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

int inputTower(int mode, int *n, char *towerOrigin, char *towerDest, int *speed)
{
	bool valid;
	if (mode >= 1 && mode <= 8 && mode != 5) {
		do
		{
			valid = true;
			cout << "��ʼ���ж��ٲ�Բ��(1-" << maxDisk << ")��";
			cin >> *n;

			if (!cin.good())
			{
				valid = false;
				cout << "���벻�Ϸ������������롣" << endl;
				cin.clear();
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
				continue;
			}

			if (*n < 1 || *n > maxDisk)
			{
				valid = false;
				cout << "���볬����Χ�����������롣" << endl;
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
				continue;
			}
		} while (!valid);
		cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');

		do
		{
			valid = true;
			cout << "���ĸ������ߣ�(A-C)";
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
				cout << "���볬����Χ�����������롣" << endl;
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
				continue;
			}

			*towerOrigin = toUpperCase(*towerOrigin);

		} while (!valid);
		cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');


		do
		{
			valid = true;
			cout << "�Ƶ��ĸ�����(A-C����ͬ��֮ǰ�������)";
			cin >> *towerDest;

			if (!cin.good())
			{
				valid = false;
				cout << "���벻�Ϸ������������롣" << endl;
				cin.clear();
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
				continue;
			}

			if (!(*towerDest >= 'A' && *towerDest <= 'C' || *towerDest >= 'a' && *towerDest <= 'c'))
			{
				valid = false;
				cout << "���볬����Χ�����������롣" << endl;
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
				continue;
			}

			*towerDest = toUpperCase(*towerDest);
			if (*towerDest == *towerOrigin)
			{
				valid = false;
				cout << "������������ͬ�����������롣" << endl;
				cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
				continue;
			}
		} while (!valid);
	}
	if (mode == 4 || mode == 8) {
		do
		{
			valid = true;
			cout << "�����ƶ��ٶȣ�0Ϊ��������ֶ����У�1-5�ֱ�Ϊ��810ms-10ms����Զ����У���";
			cin >> *speed;

			if (!cin.good() || *speed > 5 || *speed < 0)
			{
				valid = false;
				cout << "���벻�Ϸ������������롣" << endl;
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
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "---------------------------------\n\
		1.������\n\
		2.������(������¼)\n\
		3.�ڲ�������ʾ(����)\n\
		4.�ڲ�������ʾ(���� + ����)\n\
		5.ͼ�ν� - Ԥ�� - ������Բ��\n\
		6.ͼ�ν� - Ԥ�� - ����ʼ���ϻ�n������\n\
		7.ͼ�ν� - Ԥ�� - ��һ���ƶ�\n\
		8.ͼ�ν� - �Զ��ƶ��汾\n\
		9.ͼ�ν� - ��Ϸ��\n\
		0.�˳�\n\
		----------------------------------\n\
		[��ѡ��0 - 9]:";
	while (!(opt >= '0' && opt <= '9')) {
		opt = _getch();
	}
	mode = opt - '0';
	if (mode == 0)
		return 0;
	inputTower(mode, &n, &towerOrigin, &towerDest, &speed);
	totalMove = 0;
	Hanoi(h, towerOrigin - int('A'), towerDest - int('A'), n, mode);
	return 0;
}
