/* 1652270 计算机2班 冯舜 */
/*HYPERBejeweled_SJProject - 90-b1-main.cpp*/
#include "90-b1.h"

void part1_()
{
	Map gameMap = { 0 };
	Map overMap = { 0 };


	inputThing(&(gameMap.w), "请输入游戏区域的宽(5-9)：", "输入非法！", "输入超过限制！", 5, MAXGRID, true);
	inputThing(&(gameMap.h), "请输入游戏区域的高(5-9)：", "输入非法！", "输入超过限制！", 5, MAXGRID, true);

	if (1) {
		partInit(1);
		int score = 0;


		overMap.w = gameMap.w;
		overMap.h = gameMap.h;
		initializeMap(&gameMap, -1, 0);
		

		initEmerge(&gameMap);
		printMap(&gameMap, NULL, true);
		cout << endl;

		initializeMap(&overMap, -1, 0);
		checkInARowWithScore(&gameMap, &overMap, &score);

		if (!isMapEmpty(&overMap))
		{
			pressEnterToContinue("显示完了棋盘，按回车显示可消的球……");

			//checkHint(&gameMap, &overMap);
			printMap(&gameMap, &overMap, true);
			cout << "可得 " << score << " 分" << endl;
			cout << endl;
		}
		else
		{
			cout << "已经没有可以消除的球了。" << endl;
		}

		pressEnterToContinue("按回车键回主菜单……");
	}
}

void arrayModes(int mode)
{
	Map gameMap = { 0 };
	Map overMap = { 0 };
	SMap subsMap = { 0 };

	inputWidthHeight(gameMap.w, gameMap.h);

	if (1) {
		partInit(1);
		int score = 0;


		overMap.w = gameMap.w;
		overMap.h = gameMap.h;
		subsMap.w = gameMap.w;
		subsMap.h = gameMap.h;

		initializeMap(&gameMap, -1, 0);
		
		initializeMap(&subsMap, -1, 0);

		initEmerge(&gameMap);
		printMap(&gameMap, NULL, true);
		cout << endl;

		while (1)
		{
			score = 0;
			initializeMap(&overMap, -1, 0);
			checkInARowWithScore(&gameMap, &overMap, &score);

			if (!isMapEmpty(&overMap))
			{
				pressEnterToContinue("显示完了棋盘，按回车显示可消的球……");
				//checkHint(&gameMap, &overMap);
				printMap(&gameMap, &overMap, true);
				cout << endl;
				if (mode >= 2)
				{
					pressEnterToContinue("按回车显示消除后的数组……");
					cout << endl;
					eliminateIAR(&gameMap, &overMap, &subsMap);
					printMap(&gameMap, NULL, true);

					cout << endl;
					pressEnterToContinue("按回车显示下落后的数组……");
					cout << endl;

					enterNew(&gameMap, &subsMap);
					printMap(&gameMap, NULL, true);
				}
				cout << "可得 " << score << " 分" << endl;
				cout << endl;
				if (mode == 1)
				{
					break;
				}
			}
			else
			{
				cout << "已经没有可以消除的球了。" << endl;
				break;
			}
		}
		if (mode >= 3)
		{
			initializeMap(&overMap, -1, 0);
			checkHint(&gameMap, &overMap);
			pressEnterToContinue("按回车显示可消除提示……");
			printMap(&gameMap, &overMap, true);
			cout << endl;
		}
		
		
		pressEnterToContinue("按回车键回主菜单……");
	}
}

void graphModes(int mode)
{
	Map gameMap = { 0 };
	Map overMap = { 0 };
	SMap subsMap = { 0 };
	Board board = {};
	COORD_ boardWH;
	COORD_ windowWH;
	COORD_ startXY;
	board.bgColor = commonColor[0];
	board.frameColor = commonColor[1];
	board.highBgColor = commonColor[2];
	board.map = &gameMap;

	partInit(1);
	inputWidthHeight(gameMap.w, gameMap.h);
	boardWH = boardUIWH(&gameMap, mode != 4);
	windowWH = windowWHCal(&gameMap, boardWH, mode);
	startXY = startXYCal(boardWH, mode);
	if (1) {
		int score = 0;


		overMap.w = gameMap.w;
		overMap.h = gameMap.h;
		subsMap.w = gameMap.w;
		subsMap.h = gameMap.h;
		

		initializeMap(&gameMap, -1, 0);
		initializeMap(&overMap, -1, 0);
		initializeMap(&subsMap, -1, 0);

		initEmerge(&gameMap);

		if (mode < 8)
		{
			cout << "初始数组：" << endl;
			printMap(&gameMap, NULL, true);
			cout << endl;
			cout << endl << "下面将显示图形。" << endl;
			pressEnterToContinue();
		}
		
		
		partInit(4, windowWH.X, windowWH.Y, windowWH.Y);
		board.sc = startXY;
		gotoxy(hout, board.sc.X, board.sc.Y);
		if (mode == 4)
			graphicNoInsideBorder(&board, NULL);
		else
		{
			if(mode >= 6)
				checkInARowWithScore(&gameMap, &overMap, &score);
			graphicTable(&board, true, &overMap);

		}
		if (mode == 7)
		{
			while (1)
			{
				score = 0;
				initializeMap(&overMap, -1, 0);
				checkInARowWithScore(&gameMap, &overMap, &score);
				graphicTable(&board, true, &overMap);

				if (!isMapEmpty(&overMap))
				{
					pressEnterToContinue("按回车消除               ");
					eliminateIARGraph(&board, &gameMap, &overMap);
					eliminateIAR(&gameMap, &overMap, &subsMap);
					pressEnterToContinue("按回车下落               ");
					enterNewMoveDown(&board, &gameMap, &subsMap);
					graphicTable(&board, false, NULL);
				}
				else
				{
					cout << "已经没有可以消除的球了。" << endl;
					break;
				}
			}
			initializeMap(&overMap, -1, 0);
			checkHint(&gameMap, &overMap);
			pressEnterToContinue("按回车显示可消除提示……");
			graphicTable(&board, true, &overMap);
			
		}
		else
		{
			pressEnterToContinue();
		}

		pressEnterToContinue("按回车键回主菜单……");
	}
}

int main()
{
	int mode;
	char userOpt;
	startInit();
	
	while (true)
	{
		mode = 1;
		partInit(0);

		cout << "\n            彩球消消乐 by 顺子\n\n\
	-------------------------------------------------------\n\
		1.内部数组，生成初始状态，寻找是否有初始可消除项\n\
		2.内部数组，消除初始可消除项后非0项下落并用0填充\n\
		3.内部数组，消除初始可消除项后查找消除提示\n\
		4.n*n的框架(无分隔线)，显示初始状态\n\
		5.n*n的框架(有分隔线)，显示初始状态\n\
		6.n*n的框架(有分隔线)，显示初始状态及初始可消除项\n\
		7.n*n的框架(有分隔线)，消除初始可消除项后显示消除提示\n\
		8.cmd图形界面完整版\n\
		0.退出\n\
	-------------------------------------------------------\n\
		[请选择0 - 9]";

		do {
			userOpt = _getch();
		} while (!(userOpt >= '0' && userOpt <= '9'));
		cout << userOpt << endl;
		mode = userOpt - '0';

		switch (mode)
		{
			case 0:
				return 0;
			case 1:
				arrayModes(1);
				break;
			case 2:
				arrayModes(2);
				break;
			case 3:
				arrayModes(3);
				break;
			case 4:
				graphModes(4);
				break;
			case 5:
				graphModes(5);
				break;
			case 6:
				graphModes(6);
				break;
			case 7:
				graphModes(7);
				break;
				/*case 8:
				setfontsize(hout, L"新宋体", 24);
				part7GraphicFull(true);
				break;
			case 9:
				part9();
				break;
			*/
		}
	}
	return 0;
}
