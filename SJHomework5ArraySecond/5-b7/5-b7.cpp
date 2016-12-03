/* 1652270 �����2�� ��˴ */
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <iomanip>
using namespace std;

const int maxDisk = 10;
const int baseMarginX = 6;
int speed = 0;
int dispArr = 0;
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
char towerName[] = { 'A', 'B', 'C' };
int totalMove = 0;
int towers[3][maxDisk] = { { 0 },{ 0 },{ 0 } };
int towerPointer[] = { 0,0,0 };  //ָ���ǲ���+1��Ҳ����Push��һ��Բ��Ӧ���ڵ�λ��

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hout, coord);
}

void pause()
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

void showch(int x, int y, char c)
{
	gotoxy(x, y);
	putchar(c);
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

void printTowerBase()
{
	gotoxy(baseMarginX, maxDisk + 3);
	cout << "===================================" << endl;
	cout << "               A       B       C";
}

void printTowerGra(bool clean = true)
{

	for (int towerNo = 0; towerNo < 3; towerNo++)
	{
		int thisY = maxDisk + 1;
		int thisX = baseMarginX + 8 * (towerNo + 1);
		for (int towerDisk = 0; towerDisk < (clean?maxDisk:towerPointer[towerNo]); towerDisk++)
		{
			gotoxy(thisX, thisY);
			if (towerDisk < towerPointer[towerNo])
				cout << setw(2) << towers[towerNo][towerDisk];
			else
				cout << "  ";
			thisY -= 1;
		}
	}
}

void printTowerMove(int from, int to, int num)
{
	gotoxy(baseMarginX + 8 * (from + 1), maxDisk + 1 - towerPointer[from] + 1);
	cout << "  ";
	gotoxy(baseMarginX + 8 * (to + 1), maxDisk + 1 - towerPointer[to]);
	cout << setw(2) << num;
}

void printArray(int num, int from, int to, bool initial = false)
{
	if (!initial)
		cout << "Step" << setw(5) << setfill('0') << totalMove << setfill(' ') << ":(" << num << ")@" << towerName[from] << "-->" << towerName[to] << ". ";
	else
		cout << "��ʼ��               ";
	if (dispArr)
		for (int towerNo = 0; towerNo < 3; towerNo++)
		{
			cout << towerName[towerNo] << ":";
			for (int i = 0; i < towerPointer[towerNo]; i++)
			{
				cout << " " << setw(2) << towers[towerNo][i];
			}
			for (int i = 0; i < 3 * maxDisk - 3 * towerPointer[towerNo]; i++)
			{
				cout << ' ';
			}
		}
	pause();
}

//A:0,B:1,C:2
void Move(int from, int to, int num)
{
	totalMove += 1;
	printTowerMove(from, to, num);
	Pop(from);
	Push(to, num);
	//printTowerGra();
	gotoxy(0, maxDisk + 5);
	printArray(num, from, to);
	cout << endl;
}

void HanoiStep(int origin, int dest, int totalNum)
{
	//����������һ�鶯��Ϊ����ŵ���衱
	char intermediate;

	if (totalNum == 1)
	{
		Move(origin, dest, 1);
		return;
	}
	intermediate = 0 + 1 + 2 - origin - dest;
	HanoiStep(origin, intermediate, totalNum - 1);
	Move(origin, dest, totalNum);
	HanoiStep(intermediate, dest, totalNum - 1);
}

void HanoiInit(int origin, int dest, int totalNum)
{
	for (int i = 0; i < totalNum; i++)
	{
		towers[origin][i] = totalNum - i;
	}
	towerPointer[origin] = totalNum;
	system("cls");
	cout << "�� " << char(origin + 'A') << " �ƶ��� " << char(dest + 'A') << " ���� " << totalNum << " �㣬��ʱ����Ϊ" << speed << "��" << (dispArr ? "": "��") << "��ʾ�ڲ�����ֵ��";
	printTowerBase();
	printTowerGra();

	gotoxy(0, maxDisk + 5);
	printArray(-1, -1, -1, true);
	cout << endl;
	HanoiStep(origin, dest, totalNum);
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

int main()
{
	int n;
	char towerOrigin, towerDest;
	bool valid;
	system("cls");
	system("mode con cols=140 lines=25");
	do
	{
		valid = true;
		cout << "��ʼ���ж��ٲ�Բ��(1-" << maxDisk << ")��";
		cin >> n;

		if (!cin.good())
		{
			valid = false;
			cout << "���벻�Ϸ������������롣" << endl;
			cin.clear();
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			continue;
		}

		if (n < 1 || n > maxDisk)
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
		cin >> towerOrigin;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			continue;
		}

		if (!(towerOrigin >= 'A' && towerOrigin <= 'C' || towerOrigin >= 'a' && towerOrigin <= 'c'))
		{
			valid = false;
			cout << "���볬����Χ�����������롣" << endl;
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			continue;
		}

		towerOrigin = toUpperCase(towerOrigin);

	} while (!valid);
	cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
	do
	{
		valid = true;
		cout << "�Ƶ��ĸ�����(A-C����ͬ��֮ǰ�������)";
		cin >> towerDest;

		if (!cin.good())
		{
			valid = false;
			cout << "���벻�Ϸ������������롣" << endl;
			cin.clear();
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			continue;
		}

		if (!(towerDest >= 'A' && towerDest <= 'C' || towerDest >= 'a' && towerDest <= 'c'))
		{
			valid = false;
			cout << "���볬����Χ�����������롣" << endl;
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			continue;
		}

		towerDest = toUpperCase(towerDest);
		if (towerDest == towerOrigin)
		{
			valid = false;
			cout << "������������ͬ�����������롣" << endl;
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			continue;
		}
	} while (!valid);
	do
	{
		valid = true;
		cout << "�����ƶ��ٶȣ�0Ϊ��������ֶ����У�1-5�ֱ�Ϊ��810ms-10ms����Զ����У���";
		cin >> speed;

		if (!cin.good() || speed > 5 || speed < 0)
		{
			valid = false;
			cout << "���벻�Ϸ������������롣" << endl;
			cin.clear();
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			continue;
		}
	} while (!valid);
	do
	{
		valid = true;
		cout << "�Ƿ���ʾ����ֵ����1-�� 0-�񣩣�";
		cin >> dispArr;

		if (!cin.good() || dispArr > 1 || dispArr < 0)
		{
			valid = false;
			cout << "���벻�Ϸ������������롣" << endl;
			cin.clear();
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			continue;
		}
	} while (!valid);
	cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
	totalMove = 0;
	HanoiInit(towerOrigin - 'A', towerDest - 'A', n);
	cout << "�ܹ��ƶ� " << totalMove << " ����" << endl;
	return 0;
}
