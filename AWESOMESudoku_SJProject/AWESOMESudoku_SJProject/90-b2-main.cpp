/* 1652270 �����2�� ��˴ */
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
		cout << "�ڴ治�������ͷ��ڴ档\n���򼴽��˳���" << endl;
		itemFree(a.items);
		return -1;
	}
	
	//itemAppend(a.items, "��1", &a);

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
	cout << "ѡ���� " << a.index << endl;

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
			cout << "���ļ�ʧ�ܡ����� " << fileName << " �Ƿ���ڡ�" << endl;
			continue;
		}
		initSudoku(&s, -1, 0);
		status = inputSudoku(&s, &f);
		if (status == -2)
		{
			cout << "���ļ���ʽ����ȷ�������ԡ�" << endl;
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