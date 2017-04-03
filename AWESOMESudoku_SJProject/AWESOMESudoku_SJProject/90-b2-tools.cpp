/* 1652270 �����2�� ��˴ */
/*AWESOMESudokuSJProject - 90-b2-tools.cpp*/
#include "90-b2.h"

void startInit()
{
	srand(unsigned int(time(0)));
	system("color 07");
	system("cls");
	system("title ������Ϸ - by ˳��");
}

void pressEnterToContinue(char *p)
{
	//�纯����
	if (p == NULL)
		p = "�� Enter ������������";
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

//��Color���ص�commonColorָ����ǰ������
void restoreColor()
{
	setcolor(hout, commonColor[0], commonColor[1]);
}

//���У��������겻��
void gracefullyReturn(int startX)
{
	COORD start;
	start = getxy_(hout);
	gotoxy(hout, startX, start.Y + 1);
}

//�ַ�������ѡ�ļ�
int charSelFile(char * const fileName)
{
	item *files = NULL;
	char input[fileNameLen];
	int getFileStatus;
	getFileStatus = getFileList(files, NULL);
	if (getFileStatus == -1)
	{
		//û���ڴ�
		itemFree(files);
		return -1;
	}
	if (files == NULL)
	{
		//û���ļ�
		;
	}
	cout << "��ǰĿ¼�µ����������ļ��У�" << endl;
	if (itemCount(files) == 0)
	{
		cout << "���գ�" << endl;
	}
	else
	{
		itemPrint(files);
	}
	itemFree(files);
	cout << endl << "��������ص��ļ���(����ȡ25�ַ���������Ĭ�϶�ȡsudoku.txt)��";
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

//ͼ��ѡ����ѡ�ļ�
int listSelFile(char * const fileName, listbox *fileList, Clickable **clickable)
{
	int lastIndex, lastTop, inputStatus = -1, getFileStatus;
	void * args[4] = { fileList, &lastIndex, &lastTop, NULL };

	getFileStatus = getFileList(fileList->items, fileList);
	if (getFileStatus == -1)
	{
		//û���ڴ�
		itemFree(fileList->items);
		return -1;
	}
	
	if (fileList->itemLen == 0)
	{
		//û���ļ�
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