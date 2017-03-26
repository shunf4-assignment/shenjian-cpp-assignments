/* 1652270 计算机2班 冯舜 */
/*AWESOMESudokuSJProject - 90-b2-main.cpp*/
#include "90-b2.h"





int test_filebox()
{
	listbox a;
	int lastIndex, lastTop, inputStatus = -1, selected, getFileStatus;
	a.h = 8;
	a.w = 20;
	a.index = 0;
	a.top = 0;
	a.itemLen = 0;
	a.pos.X = 4;
	a.pos.Y = 4;
	a.items = NULL;

	getFileStatus = getFileList(a.items, &a);
	if (getFileStatus == -1)
	{
		cout << "内存不够，请释放内存。\n程序即将退出。" << endl;
		itemFree(a.items);
		return -1;
	}
	
	//itemAppend(a.items, "项1", &a);

	boxDraw(&a);
	cout << endl;
	cout << endl;

	while (inputStatus != 3)
	{
		inputStatus = boxWaitInput(&a, &lastIndex, &lastTop);
		itemsUpdate(&a, lastIndex, lastTop);
	}
	

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "选择了 " << a.index << endl;

	itemFree(a.items);
	return 0;

}

int charGame()
{
	char fileName[fileNameLen];
	int status;
	//char *errorStr;
	ifstream f;
	Sudoku s;
	while (true)
	{
		status = charSelFile(fileName);
		if (status == -1)
			return -1;
		f.open(fileName, ios::in);
		if (!f.is_open())
		{
			cout << "打开文件失败。请检查 " << fileName << " 是否存在。" << endl;
			continue;
		}
		initSudoku(&s, -1, 0);
		status = inputSudoku(&s, &f);
		if (status == -2)
		{
			cout << "该文件格式不正确。请重试。" << endl;
			continue;
		}
		break;
	}

	charSudoku(&s);

	
	return 0;
}

int main()
{
	int status = 0;
	status = charGame();
	if (status == -1)
		return -1;
	return 0;
}