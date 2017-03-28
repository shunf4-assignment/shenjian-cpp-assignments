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
	Sudoku initial;
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
		initSudoku(&initial, -1, 0);
		status = inputSudoku(&initial, &f);
		if (status == -2)
		{
			cout << "该文件格式不正确。请重试。" << endl;
			continue;
		}
		status = validSudoku(&initial, NULL);
		if (status == -2)
		{
			cout << "该数独存在非法数字。请重试。" << endl;
			continue;
		}
		break;
	}
	cout << "[" << fileName << "]" << " 中数据已经读入。" << endl;

	Sudoku o;  //overlay
	Sudoku p;  //player
	char inputMove[4];
	int inputJ, inputI, inputToBe;
	COORD start;
	composition *comps = NULL;
	composition *currComp = NULL;

	
	initSudoku(&p, &initial);
	compAppend(comps, p);

	currComp = comps;

	start = getxy_(hout);
	
	while (true)
	{
		p = currComp->c;
		initSudoku(&o, -1, 0);
		status = validSudoku(&p, &o);
		

		gotoxy(hout, start.X, start.Y);
		clearLines(16);

		cout << "当前步骤记录：" << compCount(comps, currComp) + 1 << " / " << compCount(comps) << endl;

		charSudoku(&p, &initial, &o);
		if (status != 0)
		{
			cout << "检查后发现有 " << status << " 处冲突。";
		}
		else
		{
			if (isSudokuFull(&p))
			{
				clearLines(3);
				printLine("你胜利了！");
				break;
			}
		}
		cout << endl;
		cout << "请输入(5c9/bk/fw/end)：";


		cin.get(inputMove, 4);
		cin.clear();
		cin.ignore(FS_MAX_LENGTH, '\n');
		cin.sync();

		_strlwr(inputMove);
		if (strcmp(inputMove, "end") == 0)
		{
			break;
		}
		if (strcmp(inputMove, "bk") == 0)
		{
			clearLines(1);
			if(currComp->prev)
				currComp = currComp->prev;
			else
			{
				printLine("已经到了第一个步骤，无法再回退。");
			}
			continue;
		}
		if (strcmp(inputMove, "fw") == 0)
		{
			clearLines(1);

			if (currComp->next)
				currComp = currComp->next;
			else
			{
				printLine("已经到了最新的步骤，无法再前进。");
				
			}
			continue;
		}

		if (!(inputMove[0] >= '1' && inputMove[0] <= '9' && inputMove[1] >= 'a' && inputMove[1] <= 'i' && inputMove[2] >= '1'&& inputMove[2] <= '9'))
		{
			printLine("输入格式非法。请重新输入。");
			continue;
		}

		inputJ = inputMove[0] - '0';
		inputI = inputMove[1] - 'a' + 1;
		inputToBe = inputMove[2] - '0';

		if (initial.t[inputJ][inputI])
		{

			printLine("此为初始数字，不能更改。");
			continue;
		}

		p.t[inputJ][inputI] = inputToBe;

		clearLines(1);
		cout << inputMove << ": 成功。" << endl;
		compFree(currComp->next);
		currComp->next = NULL;
		compAppend(currComp, p);
		currComp = currComp->next;
	}

	compFree(comps);

	
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