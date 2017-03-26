/* 1652270 计算机2班 冯舜 */
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
		//cout << "内存不够，请释放内存。" << endl;
		itemFree(files);
		return -1;
	}
	cout << "当前目录下的数独数据文件有：" << endl;
	itemPrint(files);
	cout << endl << "请输入加载的文件名(最多读取25字符)：";
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