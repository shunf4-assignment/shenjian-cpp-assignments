/* 1652270 计算机2班 冯舜 */
/*90-b2-main.cpp*/
#include "90-b2.h"

void part1PrintArray()
{
	bool emergeSuc = false;
	int gameMap[CL_MAXGRID + 2][CL_MAXGRID + 2];
	int w=9, h=9;
	setfontsize(hout, L"新宋体", 30);

	system("cls");
	srand((unsigned int)time(0) + 2);
	inputThing(&w, "请输入游戏区域的宽(7-9)：", "输入非法！", "输入超过限制！", 7, 9, true);
	inputThing(&h, "请输入游戏区域的高(7-9)：", "输入非法！", "输入超过限制！", 7, 9, true);

	initializeMap(gameMap, w, h);
	emergeSuc = randomEmerge(gameMap, 5);
	printArray(gameMap);
	//Sleep(1000);
	cout << endl << (emergeSuc ? "生成彩球成功" : "生成彩球失败") << endl;
	pressEnterToContinue();
	
}

void part2FindMove()
{
	int gameMap[CL_MAXGRID + 2][CL_MAXGRID + 2];
	int pathMap[CL_MAXGRID + 2][CL_MAXGRID + 2] = {0};
	int w = 9, h = 9;
	int *path;
	char input[2][3] = { 0 };
	int source, dest;
	//地址可以编码为一个int，即行号*10+列号。

	system("cls");
	setfontsize(hout, L"新宋体", 30);
	inputWidthHeight(w, h);

	initializeMap(gameMap, w, h);
	initializeMap(pathMap, w, h, -1, 0);
	randomEmerge(gameMap, (int)floor(w*h*0.6));
	printArray(gameMap);

	if (!inputMove(gameMap, source, dest))
	{
		pressEnterToContinue();
		return;
	}
	
	path = staticPath(gameMap, source, dest);
	if (*path == 0)
	{
		//No path.
		cout << "找不到路。" << endl;
	}
	else
	{
		drawPathOnMap(pathMap, gameMap, path);
		printArray(pathMap, false, -1, 0);
		printArray(gameMap, false, 1, 0, pathMap);
	}
	pressEnterToContinue();
}

void part3FullFunction()
{
	const int nextBallNum = 3;
	int gameMap[CL_MAXGRID + 2][CL_MAXGRID + 2];
	int pathMap[CL_MAXGRID + 2][CL_MAXGRID + 2] = { 0 };
	int w = 9, h = 9;
	int *path;
	char input[2][3] = { 0 };
	int nextBalls[nextBallNum] = { 0,0,0 };
	int source, dest, x,y;
	int score = 0, thisScore = 0, thisBallCount = 0;
	bool exitFlag = false;
	//地址可以编码为一个int，即行号*10+列号。
	setfontsize(hout, L"新宋体", 30);
	inputWidthHeight(w, h);

	initializeMap(gameMap, w, h);
	randomEmerge(gameMap, 5, true);
	do
	{
		score += thisScore;
		if (thisBallCount==0)
			regenBalls(nextBalls);
		thisBallCount = 0;
		system("cls");
		printArray(gameMap, true, 1, 0, pathMap);
		cout << "本轮得分：" << thisScore << " 总分：" << score << endl;
		cout << "出球预告： ";
		for (int i = 0; i < nextBallNum; i++)
		{
			cout << " " << nextBalls[i] + 2;
		}
		cout << endl;
		thisScore = 0;

		initializeMap(pathMap, w, h, -1, 0);
		getxy(hout, x, y);

		while (true)
		{
			gotoxy(hout, x, y);
			if (!inputMove(gameMap, source, dest))
			{
				exitFlag = true;
				break;
			}
				
			path = staticPath(gameMap, source, dest);

			if (*path == 0)
			{
				//No path.
				cout << "找不到路。" << endl;
			}
			else
			{
				ballMove(gameMap, source, dest);
				drawPathOnMap(pathMap, gameMap, path, false);
				thisBallCount = checkIAR(gameMap,dest, &thisScore, true, NULL, 0, NULL);
				break;
			}
		}
		if (exitFlag)
		{
			break;
		}
	} while (thisBallCount==0 && randomEmerge(gameMap, 3, true, nextBalls) || thisBallCount!=0);
	system("cls");
	printArray(gameMap, true, 1, 0, pathMap);
	cout << "游戏结束，你的得分是：" << score << endl;
	pressEnterToContinue();
}

void part4Frame()
{
	int gameMap[CL_MAXGRID + 2][CL_MAXGRID + 2];
	int w = 9, h = 9,x,y;

	inputWidthHeight(w, h);

	initializeMap(gameMap, w, h);
	randomEmerge(gameMap, 5, true);

	cout << "初始数组：" << endl;
	printArray(gameMap);
	cout << endl << "下面将显示图形。" << endl;
	pressEnterToContinue();
	system("cls");
	getxy(hout, x, y);
	graphicNoInsideBorder(gameMap, x, y);
	pressEnterToContinue();
}

void part5Table()
{
	int gameMap[CL_MAXGRID + 2][CL_MAXGRID + 2];
	int w = 9, h = 9, x, y;

	inputWidthHeight(w, h);

	initializeMap(gameMap, w, h);
	randomEmerge(gameMap, 5, true);

	cout << "初始数组：" << endl;
	printArray(gameMap);
	cout << endl << "下面将显示图形。" << endl;
	pressEnterToContinue();
	system("cls");

	getxy(hout, x, y);
	graphicTable(gameMap, x, y, true);
	pressEnterToContinue();
}

void part6OnceMove()
{
	int gameMap[CL_MAXGRID + 2][CL_MAXGRID + 2];
	int pathMap[CL_MAXGRID + 2][CL_MAXGRID + 2] = { 0 };
	int w = 9, h = 9, x, y;
	int windowWidth, windowHeight, tableWidth, tableHeight, tableStartX, tableStartY;
	int source, dest;
	int *path;

	inputWidthHeight(w, h);

	initializeMap(gameMap, w, h);
	initializeMap(pathMap, w, h, -1, 0);

	randomEmerge(gameMap, (int)floor(w*h*0.6), true);
	tableWidth = w * 4 + 2;
	tableHeight = h * 2 + 1 + 3;
	tableStartX = tableWidth / 4;
	tableStartY = tableHeight / 4;
	windowWidth = tableStartX * 2 + tableWidth;
	windowHeight = tableHeight + tableStartY * 2;

	setconsoleborder(hout, windowWidth, windowHeight);
	restoreColor();
	system("cls");

	graphicTable(gameMap, tableStartX, tableStartY, true);
	getxy(hout, x, y);
	if (inputMoveByMouse(gameMap, source, dest, tableStartX, tableStartY, x, y, x, y + 1, -1, -1, -1, -1, false) != -1)
	{
		path = staticPath(gameMap, source, dest);

		gotoxy(hout, x, y + 2);
		restoreColor();

		if (*path == 0)
		{
			//No path.
			cout << "找不到路。" << endl;
		}
		else
		{
			graphicRoute(gameMap, path, tableStartX, tableStartY, *getGridPointer(gameMap, source));
			gotoxy(hout, x, y + 2);
			restoreColor();
			cout << "移动成功。" << endl;
		}
	}
	gotoxy(hout, x, y + 3);
	setcursor(hout, CURSOR_VISIBLE_NORMAL);
	pressEnterToContinue();
}

void part7GraphicFull(bool keyBoard)
{
	int w = 9, h = 9;
	int windowWidth, windowHeight, tableWidth, tableHeight, tableStartX, tableStartY;
	bool  nextBallsVisible = true, gameStatsVisible = true;
	inputWidthHeight(w, h);
	tableWidth = w * 4 + 2;
	tableHeight = h * 2 + 1 + 3;
	tableStartX = tableWidth *5 /7;
	tableStartY = 7;
	windowWidth = tableStartX * 2 + tableWidth + 26;
	windowHeight = tableHeight + tableStartY * 2 + 1;
	setconsoleborder(hout, windowWidth, windowHeight);
	while (true) {
		const int nextBallNum = 3;
		int gameMap[CL_MAXGRID + 2][CL_MAXGRID + 2];
		int pathMap[CL_MAXGRID + 2][CL_MAXGRID + 2] = { 0 };
		
		
		int menuX, menuY, KingX = 0, KingY = 0, PretenderX = 0, PretenderY = 0, scoreKX, scoreKY, nextBallsX, nextBallsY, scorePX, scorePY, promptX, promptY, statX, statY;
		int *path;
		int nextBalls[nextBallNum + 1] = { 0,0,0 };
		int source, dest = -1;
		int score = 0, kingScore = 100, thisScore = 0, thisBallCount = 0;
		bool exitFlag = false, fnFlag = false, restartFlag = false, defeatSJ = false, firstTime = true;
		int gameStats[] = { 0,0,0,0,0,0,0,0,0 };
		int gameStatsBallDel[] = { 0,0,0,0,0,0,0,0,0 };
		int actionRet;

		initializeMap(gameMap, w, h);
		randomEmerge(gameMap, 5, true);
		
		menuX = 0, menuY = 0;
		KingX = tableStartX / 2 - 4;
		PretenderX = tableStartX * 3 / 2 - 4 + tableWidth;
		nextBallsX = tableStartX + tableWidth / 2 - 7;
		scoreKX = tableStartX / 2 - 4;
		scorePX = tableWidth + tableStartX * 3 / 2 - 5;
		nextBallsY = scoreKY = scorePY = 3;
		promptX = tableStartX + 2;
		promptY = tableStartY + tableHeight + 1;
		statX = tableStartX * 2 + tableWidth + 1;
		statY = tableStartY;

		KingY = PretenderY = 9;
		restoreColor();
		system("cls");

		drawInitUI(tableWidth, tableHeight, tableStartX, tableStartY, menuX, menuY, KingX, PretenderX, KingY, PretenderY, nextBallsX, nextBallsY, scoreKX, scoreKY, scorePX, scorePY, gameMap, windowWidth, statX, statY, nextBallsVisible, gameStatsVisible, score, kingScore);
		graphicTable(gameMap, tableStartX, tableStartY, true);

		do
		{
			score += thisScore;
			if (thisBallCount == 0 && !fnFlag)
				regenBalls(nextBalls);
			updateScore(score, scorePX, scorePY);
			updateKingPret(score, kingScore, KingX, KingY, PretenderX, PretenderY, firstTime);
			firstTime = false;
			if (!defeatSJ && score > kingScore)
			{
				gotoxy(hout, promptX, promptY + 2);
				cout << "你打倒了沈坚！！" << endl;
			}
			updateNextBalls(nextBalls, nextBallsX, nextBallsY, nextBallsVisible, false, true);
			updateStats(gameMap, gameStats, gameStatsBallDel, statX, statY, tableHeight, gameStatsVisible, false, true);

			graphicTable(gameMap, tableStartX, tableStartY, thisBallCount>0);

			thisScore = 0;
			thisBallCount = false;
			fnFlag = false;

			initializeMap(pathMap, w, h, -1, 0);

			while (true)
			{
				actionRet = inputMoveByMouse(gameMap, source, dest, tableStartX, tableStartY, promptX, promptY, promptX, promptY + 2, -1, -1, -1, -1, keyBoard);
				if (actionRet == -1)
				{
					exitFlag = true;
					break;
				}
				if (actionRet >= 0x72 && actionRet <= 0x74)
				{
					if(actionRet == 0x73)
					{
						restartFlag = true;
					}
					else if (actionRet == 0x72)
					{
						nextBallsVisible = !nextBallsVisible;
						updateNextBalls(nextBalls, nextBallsX, nextBallsY, nextBallsVisible, true, false);
						fnFlag = true;
					}
					else if (actionRet == 0x74)
					{
						gameStatsVisible = !gameStatsVisible;
						updateStats(gameMap, gameStats, gameStatsBallDel, statX, statY, tableHeight, gameStatsVisible, true, false);
						fnFlag = true;
					}
					break;
				}

				path = staticPath(gameMap, source, dest);

				restoreColor();
				gotoxy(hout, promptX, promptY + 3);

				if (*path == 0)
				{
					//No path.
					printf("\a");
					cout << "找不到路。" << endl;
				}
				else
				{
					graphicRoute(gameMap, path, tableStartX, tableStartY, *getGridPointer(gameMap, source));
					ballMove(gameMap, source, dest);
					thisBallCount = checkIAR(gameMap, dest, &thisScore, true, NULL, 0, gameStatsBallDel);
					gotoxy(hout, promptX, promptY + 3);
					restoreColor();
					cout << "移动成功。" << endl;
					break;
				}
			}
			if (exitFlag)
			{
				break;
			}
			if (restartFlag)
			{
				break;
			}
			if (fnFlag)
			{
				continue;
			}
		} while (thisBallCount == 0 && !fnFlag && randomEmerge(gameMap, 3, true, nextBalls) || thisBallCount != 0 || fnFlag);
		if (restartFlag)
		{
			restartFlag = false;
			continue;
		}
		graphicTable(gameMap, tableStartX, tableStartY, false);
		gotoxy(hout, promptX, promptY + 2);
		setcursor(hout, CURSOR_VISIBLE_NORMAL);
		cout << "游戏结束，你的得分是：" << score << endl;
		pressEnterToContinue();
		return;
	}
	
}

void part9()
{
	if (1) {
		int X = 0, Y = 0;
		int action;
		int loop = 1;
		int a = 1;
		int b = 1;
		int bothClicked = -1;
		int onceClicked = -1;
		bool x = false;
		DWORD lastTick = GetTickCount();
		DWORD currTick = GetTickCount();
		restoreColor();
		system("cls");
		enable_mouse(hin);

		/* 打印初始光标位置[0,0] */
		setcursor(hout, CURSOR_INVISIBLE);	//关闭光标
		cout << "可测试左键单/双击,右键单/双击,左右键同时单击五种，其中右键双击结束鼠标测试" << endl;
		cout << "[当前鼠标位置] X:0  Y:0"; //打印初始鼠标位置
		
		while (loop) {
			/* 读鼠标，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
			action = read_mouse(hin, X, Y, 1);
			
			lastTick = currTick;
			/* 转到第1行进行打印 */
			gotoxy(hout, 0, 1);
			cout << "[当前光标位置] X:" << setw(2) << X << " Y:" << setw(2) << Y << " 操作:";
			


			switch (action) {
				case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
					cout << "按下左键      " << endl;
					gotoxy(hout, 0, 1);
					cout << "[当前光标位置] X:" << setw(2) << X << " Y:" << setw(2) << Y << " 操作:";
					if ((a = read_mouse(hin, X, Y, 1)) == 6 &&( b = read_mouse(hin, X, Y, 1)) == 2)
					{
						cout << "双击左键      " << endl;
						showch(hout, X, Y, '2', colorList[0], colorList[1]);			//在鼠标指针位置显示2
						break;
					}
					else
					{
						if (a == 5 || b == 5)
						{
							cout << "同时按下左右键" << endl;
							showch(hout, X, Y, '5', colorList[0], colorList[1]);			//在鼠标指针位置显示5
							read_mouse(hin, X, Y, 1);
							read_mouse(hin, X, Y, 1);
							break;
						}
					}
					showch(hout, X, Y, '1', colorList[0], colorList[1]);			//在鼠标指针位置显示1
					break;
				case MOUSE_LEFT_BUTTON_DOUBLE_CLICK:	//双击左键
					cout << "双击左键      " << endl;
					showch(hout, X, Y, '2', colorList[0], colorList[1]);			//在鼠标指针位置显示2
					break;
				case MOUSE_RIGHT_BUTTON_CLICK:			//按下右键
					cout << "按下右键      " << endl;
					gotoxy(hout, 0, 1);
					cout << "[当前光标位置] X:" << setw(2) << X << " Y:" << setw(2) << Y << " 操作:";
					if ((a = read_mouse(hin, X, Y, 1)) == 6 && (b = read_mouse(hin, X, Y, 1)) == 2)
					{
						cout << "双击右键      " << endl;
						showch(hout, X, Y, '4', colorList[0], colorList[1]);			//在鼠标指针位置显示2
						break;
					}
					else
					{
						if (a == 5 || b == 5)
						{
							cout << "同时按下左右键" << endl;
							read_mouse(hin, X, Y, 1);
							read_mouse(hin, X, Y, 1);
							showch(hout, X, Y, '5', colorList[0], colorList[1]);			//在鼠标指针位置显示5
							break;
						}
					}
					cout << "按下右键      " << endl;
					showch(hout, X, Y, '3', colorList[0], colorList[1]);			//在鼠标指针位置显示3
					break;
				case MOUSE_RIGHT_BUTTON_DOUBLE_CLICK:	//双击右键
					cout << "双击右键      " << endl;
					showch(hout, X, Y, '4', colorList[0], colorList[1]);			//在鼠标指针位置显示4
					loop = 0;
					break;
				case MOUSE_LEFTRIGHT_BUTTON_CLICK:		//同时按下左右键
					cout << "同时按下左右键" << endl;
					showch(hout, X, Y, '5', colorList[0], colorList[1]);			//在鼠标指针位置显示5
					read_mouse(hin, X, Y, 1);
					break;
				case MOUSE_ONLY_MOVED:
					cout << "移动          " << endl;
					//showch(hout, X, Y, '*');不打印任何内容
					break;
				case MOUSE_NO_ACTION:
				default:
					cout << "其它操作" << endl;
					showch(hout, X, Y, '0', colorList[0], colorList[1]);			//在鼠标指针位置显示0
					break;
			} //end of switch
		} //end of while(1)

		setcursor(hout, CURSOR_VISIBLE_NORMAL);	//打开光标
		pressEnterToContinue();
	}
}

int main()
{
	int mode;
	char opt;
	srand(unsigned int(time(0)));
	system("color f0");
	while (true)
	{
		mode = 1;
		setconsoleborder(hout, 80, 25);
		restoreColor();
		system("cls");
		setfontsize(hout, L"新宋体", 20);
		//freopen("in.txt", "r", stdin);

		cout << "\n            控制台彩球游戏 by 顺子\n\n\
	---------------------------------------------\n\
	1.内部数组，随机生成初始5个球\n\
	2.内部数组，随机生成60%的球，寻找移动路径\n\
	3.内部数组，完整版\n\
	4.画出n*n的框架（无分隔线），随机显示5个球\n\
	5.画出n*n的框架（有分隔线），随机显示5个球\n\
	6.n*n的框架，60%的球，支持鼠标，完成一次移动\n\
	7.cmd图形界面完整版\n\
	8.cmd图形界面完整版 - 支持同时读键（额外加分）\n\
	9.双击及左右键同时按下操作屏蔽单击（额外加分）\n\
	0.退出\n\
	---------------------------------------------\n\
	[请选择0 - 9]";

		do {
			opt = _getch();
		} while (!(opt >= '0' && opt <= '9'));
		cout << opt << endl;

		mode = opt - '0';
		if (mode == 0)
			return 0;
		system("cls");
		switch (mode)
		{
			case 1:
				part1PrintArray();
				break;
			case 2:
				part2FindMove();
				break;
			case 3:
				part3FullFunction();
				break;
			case 4:
				part4Frame();
				break;
			case 5:
				part5Table();
				break;
			case 6:
				setfontsize(hout, L"新宋体", 24);
				part6OnceMove();
				break;
			case 7:
				setfontsize(hout, L"新宋体", 24);
				part7GraphicFull(false);
				break;
			case 8:
				setfontsize(hout, L"新宋体", 24);
				part7GraphicFull(true);
				break;
			case 9:
				part9();
				break;
		}

	}
	return 0;
}

