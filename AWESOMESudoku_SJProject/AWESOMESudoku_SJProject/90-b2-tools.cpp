/* 1652270 �����2�� ��˴ */
/*AWESOMESudokuSJProject - 90-b2-tools.cpp*/
#include "90-b2.h"

COORD getxy_(const HANDLE hout)
{
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(hout, &binfo);

	return binfo.dwCursorPosition;
}

void restoreColor()
{
	setcolor(hout, commonColor[0], commonColor[1]);
}

void gracefullyReturn(int startX)
{
	COORD start;
	start = getxy_(hout);
	gotoxy(hout, startX, start.Y + 1);
}

int charSelFile(char * const fileName)
{
	item *files = NULL;
	char input[fileNameLen];
	int getFileStatus;
	getFileStatus = getFileList(files, NULL);
	if (getFileStatus == -1)
	{
		//cout << "�ڴ治�������ͷ��ڴ档" << endl;
		itemFree(files);
		return -1;
	}
	cout << "��ǰĿ¼�µ����������ļ��У�" << endl;
	itemPrint(files);
	itemFree(files);
	cout << endl << "��������ص��ļ���(����ȡ25�ַ�)��";
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

void printLine(const char * const str, int line)
{
	clearLines(line);
	cout << str << endl;
}