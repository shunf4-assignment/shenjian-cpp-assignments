/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;

const int MAX_X = 69;	//����*��ɵı߿�Ŀ��
const int MAX_Y = 17;	//����*��ɵı߿�ĸ߶�

						/* ������ƶ���ָ��λ�� */
void gotoxy(HANDLE hout, int X, int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}

/* ��ָ��λ�ô���ӡһ��ָ�����ַ� */
void showch(HANDLE hout, int X, int Y, char ch)
{
	gotoxy(hout, X, Y);
	putchar(ch);
}

int getNewCoord(bool isX, int coord, int offset)
{
	int minimum = 1, maximum = MAX_Y, newCoord = coord;
	if (isX)
		maximum = MAX_X;
	newCoord += offset;
	if (newCoord > maximum)
		newCoord = maximum;
	if (newCoord < minimum)
		newCoord = minimum;

	return newCoord;
}

int main()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //ȡ��׼����豸��Ӧ�ľ��
	int    i;

	/* ����α����������ӣ�ֻ���ڳ���ʼʱִ��һ�μ��� */
	srand(unsigned int(time(0)));

	cout << "***********************************************************************" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "*                                                                     *" << endl;
	cout << "***********************************************************************" << endl;

	/* �����ʾ20����д��ĸ����ĸ��ֵ��XY���궼�����ʾ
	rand()�����Ĺ��ܣ��������һ���� 0-32767 ֮�������
	ע�⣺������bug���������ѭ�����ɵ�XY����ǡ����ȫ��ͬ������ĸ�����᲻��20������˵��������Ҫ�����bug�� */
	for (i = 0; i < 20; i++)
		showch(hout, rand() % MAX_X + 1, rand() % MAX_Y + 1, 'A' + rand() % 26);

	/* �ڴ˴������Ҫ�Ĵ���-begin */

	int keyInput;
	int currentX = (MAX_X + 1) / 2, currentY = (MAX_Y + 1) / 2, nextX, nextY;  //����������
	gotoxy(hout, currentX, currentY);
	while (1)
	{
		keyInput = _getch();
		nextX = currentX;
		nextY = currentY;
		if (keyInput == 'q' || keyInput == 'Q')
			break;
		
		if (keyInput == 0xe0) //���������0xe0��ʼ
		{
			keyInput = _getch();  //���ʱ���ٶ�һ��
			switch (keyInput)
			{
			case (0x48):
				nextY = getNewCoord(false, currentY, -1);
				break;
			case (0x50):
				nextY = getNewCoord(false, currentY, 1);
				break;
			case (0x4b):
				nextX = getNewCoord(true, currentX, -1);
				break;
			case (0x4d):
				nextX = getNewCoord(true, currentX, 1);
				break;

			}
			gotoxy(hout, nextX, nextY);
			currentX = nextX;
			currentY = nextY;
			continue;
		}
		if (keyInput)
		{
			putchar((char)keyInput);
			gotoxy(hout, nextX, nextY);  //����ַ����ǰ��һ���˻�ȥ
		}

	}

	/* �ڴ˴������Ҫ�Ĵ���-end */

	gotoxy(hout, 0, 23);
	cout << "��Ϸ���������س����˳�." << endl;
	getchar();
	return 0;
}
