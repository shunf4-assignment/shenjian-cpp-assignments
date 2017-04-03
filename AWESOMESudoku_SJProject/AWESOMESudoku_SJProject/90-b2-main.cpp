/* 1652270 计算机2班 冯舜 */
/*AWESOMESudokuSJProject - 90-b2-main.cpp*/
#include "90-b2.h"

int graphOpenFile(Sudoku *initial, COORD bulletin, COORD filePos, COORD fileWH)
{
	char fileName[fileNameLen];
	int status;
	ifstream f;

	listbox fileList;
	Clickable boxClick;
	Clickable *clickable[2] = { &boxClick, NULL };
	int lastIndex, lastTop, inputStatus = -1;
	void * args[4] = { &fileList, &lastIndex, &lastTop, NULL };

	fileList.h = fileWH.Y;
	fileList.w = fileWH.X;
	fileList.index = 0;
	fileList.top = 0;
	fileList.itemLen = 0;
	fileList.pos = filePos;
	fileList.items = NULL;

	boxClick.trigFunc = &boxTrig;
	boxClick.args = args;
	boxClick.keyTrig = true;
	boxClick.moveTrig = false;
	boxClick.rectTop1 = fileList.pos;
	boxClick.rectTop2.X = fileList.pos.X + fileList.w * 2 +2;
	boxClick.rectTop2.Y = fileList.pos.Y + fileList.h + 1;

	while (true)
	{
		itemFree(fileList.items);
		fileList.items = NULL;
		fileList.index = 0;
		fileList.top = 0;
		fileList.itemLen = 0;
		f.close();

		status = listSelFile(fileName, &fileList, clickable);
		restoreColor();
		gotoxy(hout, bulletin.X, bulletin.Y);
		clearLines(1);

		if (status == -2)
		{
			//Empty Directory
			clearLines(1);
			cout << "当前文件夹内没有sudoku*数据文件。请放入数据文件，然后重新进入。" << endl;
			break;
		}

		if (status == -1)
			return -1;
		f.open(fileName, ios::in);
		if (!f.is_open())
		{
			cout << "打开文件" << "[" << fileName << "] " << "失败。请检查 " << fileName << " 是否存在。" << endl;
			continue;
		}
		initSudoku(initial, -1, 0);
		status = inputSudoku(initial, &f);
		if (status == -2)
		{
			cout << "[" << fileName << "] " << "该文件格式不正确。请重试。" << endl;
			continue;
		}
		status = validSudoku(initial, NULL);
		if (status == -2)
		{
			cout << "该数独" << "[" << fileName << "] " << "存在非法数字。请重试。" << endl;
			continue;
		}
		break;
	}
	f.close();
	itemFree(fileList.items);

	clearLines(1, 56);
	cout << "[" << fileName << "]" << " 中数据已经读入。" << endl;

	return status;
}

int charGame()
{
	char fileName[fileNameLen];
	int status;
	setconsoleborder(hout, 80, 25, 200);
	system("cls");
	//char *errorStr;
	ifstream f;
	Sudoku initial;
	while (true)
	{
		f.close();
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
	bool firstTime = true;

	
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
			if (firstTime)
			{
				cout << "数独文件存在开局冲突。请检查后重新游戏。" << endl;
				break;
			}
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

		if (firstTime)
			firstTime = false;
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

		if (!(inputMove[0] >= '1' && inputMove[0] <= '9' && inputMove[1] >= 'a' && inputMove[1] <= 'i' && inputMove[2] >= '0'&& inputMove[2] <= '9'))
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
	pressEnterToContinue("按 Enter 返回主菜单……");
	
	return 0;
}

int graphGame()
{
	int status;
	//char *errorStr;
	ifstream f;
	Sudoku initial;

	//定义坐标
	setconsoleborder(hout, 100, 39, 39);
	system("cls");
	COORD start;
	COORD bkfwStart;
	COORD bulletin = { 4, 31 };
	COORD inputPos = { 28, 32 };
	COORD bkfwWH = { 24 ,3 };
	bkfwStart.X = 64;
	bkfwStart.Y = 12;
	start.X = 5;
	start.Y = 3;
	COORD hintPos = { 64, 22 };
	COORD filePos = { 64,2 };
	COORD fileWH = { 10, 8 };

	status = graphOpenFile(&initial, bulletin, filePos, fileWH);

	if (status < 0)
	{
		pressEnterToContinue("按 Enter 键返回主菜单……");
		return status;
	}
	

	restoreColor();

	Sudoku o;  //overlay
	Sudoku p;  //player
	

	composition *comps = NULL;
	composition *currComp = NULL;
	Board b;
	char inputMove[4] = { 0 };
	int inputPoint = 0;
	int inputJ, inputI, inputToBe;
	bool firstTime = true;
	Clickable boardClick;
	Clickable inputClick;
	Clickable backClick;
	Clickable *gameClick[4] = { &boardClick, &inputClick, &backClick, NULL };
	void *boardArgs[] = { (void *)&inputPos, (void *)&inputMove, (void *)&inputPoint, (void *)&b, (void *)&bulletin, NULL };
	void *inputArgs[] = { (void *)&inputPos, (void *)&inputMove, (void *)&inputPoint, (void *)&b,(void *)&bulletin, NULL };
	void *backArgs[] = { (void *)&b, (void *)&bkfwStart, (void *)&bkfwWH, NULL };
	bool somethingOut = false;

	b.initial = &initial;
	b.s = &p;
	b.sel = { 1,1 };
	initSudoku(&p, &initial);
	compAppend(comps, p);

	currComp = comps;

	
	initSudoku(&o, -1, 0);
	b.o = &o;
	b.start = start;
	


	boardClick.args = boardArgs;
	boardClick.keyTrig = false;
	boardClick.moveTrig = false;
	boardClick.rectTop1 = b.start;
	boardClick.rectTop2 = coordPlus(b.start, 6*9, 3*9);
	boardClick.trigFunc = boardTrig;
	inputClick.args = inputArgs;
	inputClick.keyTrig = true;
	inputClick.moveTrig = false;
	inputClick.rectTop1 = {-1 ,-1 };
	inputClick.rectTop2 = { -1 ,-1 };
	inputClick.trigFunc = selTrig;
	backClick.args = backArgs;
	backClick.keyTrig = false;
	backClick.moveTrig = false;
	backClick.rectTop1 = bkfwStart;
	backClick.rectTop2 = coordPlus(bkfwStart, bkfwWH.X, bkfwWH.Y + 5);
	backClick.trigFunc = backTrig;

	

	drawBkFw(bkfwStart, bkfwWH);
	drawInputBox(inputPos);
	gotoxy(hout, hintPos.X, hintPos.Y);
	cout << "  【提示】";
	gracefullyReturn(hintPos.X);
	gracefullyReturn(hintPos.X);
	cout << "可用键盘输入坐标、用鼠标";
	gracefullyReturn(hintPos.X);
	cout << "点击后输入数字。点按←按钮";
	gracefullyReturn(hintPos.X);
	cout << "或按退格键，可以回到上一步，";
	gracefullyReturn(hintPos.X);
	cout << "按DELETE键删除已经输入的";
	gracefullyReturn(hintPos.X);
	cout << "字符。";
	gracefullyReturn(hintPos.X);
	gracefullyReturn(hintPos.X);
	cout << "输入xx0可以消除某格数字。";
	
	

	while (true)
	{
		p = currComp->c;
		//p.sel = { 1,1 };
		initSudoku(&o, -1, 0);
		status = validSudoku(&p, &o);

		inputMove[0] = 0;
		inputPoint = 0;
		cleanInputBox(inputPos);

		gotoxy(hout, start.X, start.Y - 2);
		clearLines(1);
		cout << "当前步骤记录：" << compCount(comps, currComp) + 1 << " / " << compCount(comps) << endl;

		printBoard(&b);

		gotoxy(hout, bulletin.X, bulletin.Y);
		
		if (status != 0 && !somethingOut)
		{
			clearLines(1, 56);
			cout << "检查后发现有 " << status << " 处冲突。";
			if (firstTime)
			{
				cout << "数独文件存在开局冲突。请检查后重新游戏。" << endl;
				break;
			}
		}
		else
		{
			if (isSudokuFull(&p))
			{
				printLine("你胜利了！");
				break;
			}
		}

		if(firstTime)
			firstTime = false;
		somethingOut = false;
		
		gotoxy(hout, 0, inputPos.Y + 1);
		cout << "请输入(5c9/bk/fw/end)：";

		inputTrig(gameClick);

		gotoxy(hout, bulletin.X, bulletin.Y);

		if (b.sel.x == -3 && b.sel.y == -3)
		{
			break;
		}
		if (b.sel.x == -1 && b.sel.y == -1)
		{
			clearLines(1);
			if (currComp->prev)
				currComp = currComp->prev;
			else
			{
				printLine("已经到了第一个步骤，无法再回退。");
				somethingOut = true;
			}
			b.sel = { 1,1 };
			continue;
		}
		if (b.sel.x == -2 && b.sel.y == -2)
		{
			clearLines(1);

			if (currComp->next)
				currComp = currComp->next;
			else
			{
				printLine("已经到了最新的步骤，无法再前进。");
				somethingOut = true;
			}
			b.sel = { 1,1 };

			continue;

		}

		inputJ = b.sel.y;
		inputI = b.sel.x;
		inputToBe = b.toInput;

		if (initial.t[inputJ][inputI])
		{

			printLine("此为初始数字，不能更改。");
			somethingOut = true;
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
	gotoxy(hout, bulletin.X, bulletin.Y + 5);
	clearLines(1, 56);
	pressEnterToContinue("按 Enter 返回主菜单……");

	return 0;
}



int autoGame(int mode, bool refreshEvery)
{
	int status;
	//char *errorStr;
	ifstream f;
	Sudoku initial;

	//定义坐标
	setconsoleborder(hout, 100, 39, 39);
	system("cls");
	COORD start;
	COORD bkfwStart;
	COORD bulletin = { 4, 31 };
	COORD inputPos = { 28, 32 };
	COORD bkfwWH = { 24 ,3 };
	COORD filePos = { 64,2 };
	COORD fileWH = { 10,26 };
	bkfwStart.X = 64;
	bkfwStart.Y = 12;
	start.X = 5;
	start.Y = 3;
	COORD hintPos = { 64, 22 };
	int dfsArgs[] = {0,0,0,0,refreshEvery }; //CountCycle, CurrCount, CurrDepth, MaxDepth

	status = graphOpenFile(&initial, bulletin, filePos, fileWH);

	if (status < 0)
	{
		pressEnterToContinue("按 Enter 键返回主菜单……");
		return status;
	}

	restoreColor();

	SudokuValue v;

	Board b;
	dfsArgs[0] = 1;
	if (mode == 0)
		dfsArgs[0] = 0;
	if (mode == 2)
		dfsArgs[0] = 1000;

	b.initial = &initial;
	b.s = &initial;
	b.o = NULL;
	b.bulletin = &bulletin;
	b.start = start;

	printBoard(&b);

	status = parseGrid(&initial, &v);
	if (status == -2)
	{
		gotoxy(hout, bulletin.X, bulletin.Y);
		clearLines(1, 56);
		cout << "数独无解！";
	}
	else
	{
		updateBoardAuto(&b, &v, dfsArgs);
		if(debug)
			getchar();
		gotoxy(hout, bulletin.X, bulletin.Y);
		clearLines(1, 56);
		cout << DFSStr1 << setw(DFSlen2) << dfsArgs[1] << DFSStr2 << setw(DFSlen4) << dfsArgs[2] << DFSStr3 << setw(DFSlen6) << dfsArgs[3] << DFSStr4;
		if (!dfsArgs[4])
			cout << endl << "请等待计算完毕……" << endl;
		status = depthSearch(&v, dfsArgs, &b);
		if (!dfsArgs[4])
		{
			gotoxy(hout, bulletin.X, bulletin.Y);
			cout << endl;
			clearLines(1, 56);
		}
		if (status == -2)
		{
			gotoxy(hout, bulletin.X, bulletin.Y);
			clearLines(1, 56);
			cout << "数独无解！";
			cout << DFSStr1 << setw(DFSlen2) << dfsArgs[1] << DFSStr2 << setw(DFSlen4) << dfsArgs[2] << DFSStr3 << setw(DFSlen6) << dfsArgs[3] << DFSStr4;
		}
		else
		{
			updateBoardAuto(&b, &v, dfsArgs);
			printDFSProgress(dfsArgs, &bulletin);
		}
	}

	gotoxy(hout, bulletin.X, bulletin.Y + 5);
	clearLines(1, 56);
	pressEnterToContinue("按 Enter 返回主菜单……");

	return 0;
}


int main()
{
	int mode;
	int status = 0, appendStatus;
	char userOpt;
	listbox selList;
	Clickable boxClick;
	Clickable *clist[2] = { &boxClick, NULL };
	int lastIndex, lastTop;
	void * args[4] = { &selList, &lastIndex, &lastTop, NULL };
	COORD selWH = { 20, 8 };
	COORD selPos = { 14, 6 };
	char *menuItems[] = { "字符游戏" ,"图形游戏" ,"图形自动解（瞬解，刷新计算次数）","图形自动解（瞬解，不刷新计算次数）", "图形自动解（带延时）", "图形自动解（每1000次显示一次）", "退出", NULL };

	selList.h = selWH.Y;
	selList.w = selWH.X;
	selList.index = 0;
	selList.top = 0;
	selList.itemLen = 0;
	selList.pos = selPos;
	selList.items = NULL;

	boxClick.trigFunc = &boxTrig;
	boxClick.args = args;
	boxClick.keyTrig = true;
	boxClick.moveTrig = true;
	boxClick.rectTop1 = selList.pos;
	boxClick.rectTop2.X = selList.pos.X + selList.w * 2+2;
	boxClick.rectTop2.Y = selList.pos.Y + selList.h + 1;

	for (char **p = menuItems; *p; p++)
	{
		appendStatus = itemAppend(selList.items, *p, &selList);
		if (appendStatus == -1)
		{
			cout << "内存不够，请释放内存。\n程序即将退出。" << endl;
			itemFree(selList.items);
			return -1;
		}
	}
	

	startInit();
	while (true)
	{
		system("cls");
		setconsoleborder(hout, 80, 25, 25);

		mode = 1;

		cout << "\n            数独游戏 by 顺子\n\n                请用键盘或鼠标选择一项。";

		boxDraw(&selList);
		inputTrig(clist);
		restoreColor();

		cout << endl;
		cout << endl;

		userOpt = selList.index;

		mode = userOpt;

		switch (mode)
		{
			case 6:
			{
				gotoxy(hout, 0, 23);
				CloseHandle(hout);	// 关闭标准输入设备句柄
				CloseHandle(hin);	// 关闭标准输入设备句柄
				break;
			}
			case 0:
				status = charGame();
				break;
			case 1:
				status = graphGame();
				break;
			case 2:
				status = autoGame(0, true);
				break;
			case 3:
				status = autoGame(0, false);
				break;
			case 4:
				status = autoGame(1, true);
				break;
			case 5:
				status = autoGame(2, true);
				break;
		}
		if (status == -1)
			return -1;
		if (mode == 6)
		{
			break;
		}

	}
	itemFree(selList.items);
	return 0;
}