/* 1652270 计算机2班 冯舜 */
/*AWESOMESudokuSJProject - 90-b2-tools.cpp*/
#include "90-b2.h"

void startInit()
{
	srand(unsigned int(time(0)));
	system("color 07");
	system("cls");
	system("title 数独游戏 - by 顺子");
}

void pressEnterToContinue(char *p)
{
	//如函数名
	if (p == NULL)
		p = "按 Enter 按键继续……";
	cout << p << endl;
	while (_getch() != '\r')
		;
	return;
}

COORD getxy_(const HANDLE hout)
{
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(hout, &binfo);

	return binfo.dwCursorPosition;
}

//将Color返回到commonColor指定的前景背景
void restoreColor()
{
	setcolor(hout, commonColor[0], commonColor[1]);
}

//换行，但横坐标不变
void gracefullyReturn(int startX)
{
	COORD start;
	start = getxy_(hout);
	gotoxy(hout, startX, start.Y + 1);
}

//字符界面下选文件
int charSelFile(char * const fileName)
{
	item *files = NULL;
	char input[fileNameLen];
	int getFileStatus;
	getFileStatus = getFileList(files, NULL);
	if (getFileStatus == -1)
	{
		//没有内存
		itemFree(files);
		return -1;
	}
	if (files == NULL)
	{
		//没有文件
		;
	}
	cout << "当前目录下的数独数据文件有：" << endl;
	if (itemCount(files) == 0)
	{
		cout << "（空）" << endl;
	}
	else
	{
		itemPrint(files);
	}
	itemFree(files);
	cout << endl << "请输入加载的文件名(最多读取25字符，空输入默认读取sudoku.txt)：";
	cin.get(input, 26);
	cin.clear();
	cin.ignore(FS_MAX_LENGTH, '\n');
	cin.sync();

	if (strlen(input) == 0)
	{
		strcpy(input, "sudoku.txt");
	}

	strcpy(fileName, input);
	return 0;
}

//图形选框中选文件
int listSelFile(char * const fileName, listbox *fileList, Clickable **clickable)
{
	int lastIndex, lastTop, inputStatus = -1, getFileStatus;
	void * args[4] = { fileList, &lastIndex, &lastTop, NULL };

	getFileStatus = getFileList(fileList->items, fileList);
	if (getFileStatus == -1)
	{
		//没有内存
		itemFree(fileList->items);
		return -1;
	}
	
	if (fileList->itemLen == 0)
	{
		//没有文件
		return -2;
	}

	boxDraw(fileList);

	inputTrig(clickable);

	strcpy(fileName, itemNext(fileList->items, fileList->index)->text);

	
	return 0;
}

COORD coordPlus(COORD c1, COORD c2)
{
	COORD result;
	result.X = c1.X + c2.X;
	result.Y = c1.Y + c2.Y;
	return result;
}

COORD coordPlus(COORD c1, short X, short Y)
{
	COORD result;
	result.X = c1.X + X;
	result.Y = c1.Y + Y;
	return result;
}

void clearLines(int line)
{
	int cols, lines, buffer_coles, buffer_lines, x, y;
	getconsoleborder(hout, cols, lines, buffer_coles, buffer_lines);
	getxy(hout, x, y);
	cout << setw(cols - x) << "";
	line--;
	for (int i = 0; i < line; i++)
	{
		cout << setw(cols) << "";
	}
	gotoxy(hout, x, y);
}


void clearLines(int line, int limitCharPerLine)
{
	int cols = limitCharPerLine, x, y;
	getxy(hout, x, y);
	cout << setw(cols - x) << "";
	line--;
	for (int i = 0; i < line; i++)
	{
		cout << setw(cols) << "";
	}
	gotoxy(hout, x, y);
}

void printLine(const char * const str, int line)
{
	clearLines(line);
	cout << str << endl;
}