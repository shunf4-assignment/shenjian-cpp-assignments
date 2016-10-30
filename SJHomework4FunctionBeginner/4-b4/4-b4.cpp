/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;

const int MAX_X = 69;	//定义*组成的边框的宽度
const int MAX_Y = 17;	//定义*组成的边框的高度

						/* 将光标移动到指定位置 */
void gotoxy(HANDLE hout, int X, int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}

/* 在指定位置处打印一个指定的字符 */
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
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
	int    i;

	/* 生成伪随机数的种子，只需在程序开始时执行一次即可 */
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

	/* 随机显示20个大写字母，字母的值、XY坐标都随机显示
	rand()函数的功能：随机生成一个在 0-32767 之间的整数
	注意：程序有bug，如果两次循环生成的XY坐标恰好完全相同，则字母数量会不足20个（仅说明，不需要解决此bug） */
	for (i = 0; i < 20; i++)
		showch(hout, rand() % MAX_X + 1, rand() % MAX_Y + 1, 'A' + rand() % 26);

	/* 在此处添加需要的代码-begin */
	
	int keyInput;
	int currentX = (MAX_X + 1)/2, currentY = (MAX_Y + 1) / 2, nextX, nextY;  //光标调到中心
	gotoxy(hout, currentX, currentY);
	while (1)
	{
		keyInput = _getch();
		nextX = currentX;
		nextY = currentY;
		if (keyInput == 'q')
			break;
		if (keyInput == ' ')
		{
			putchar(' ');
			gotoxy(hout, nextX, nextY);  //输出字符后会前进一格，退回去
		}
		switch (keyInput)
		{
			case ('i'):
				nextY = getNewCoord(false, currentY, -1);
				break;
			case ('k'):
				nextY = getNewCoord(false, currentY, 1);
				break;
			case ('j'):
				nextX = getNewCoord(true, currentX, -1);
				break;
			case ('l'):
				nextX = getNewCoord(true, currentX, 1);
				break;
					
		}
		gotoxy(hout, nextX, nextY);
		currentX = nextX;
		currentY = nextY;
	
	}

	/* 在此处添加需要的代码-end */

	gotoxy(hout, 0, 23);
	cout << "游戏结束，按回车键退出." << endl;
	getchar();
	return 0;
}
