/* 1652270 �����2�� ��˴ */
/*HYPERBejeweled_SJProject - 90-b1-main.cpp*/
#include "90-b1.h"

void part1_()
{
	Map gameMap = { 0 };
	Map overMap = { 0 };


	inputThing(&(gameMap.w), "��������Ϸ����Ŀ�(5-9)��", "����Ƿ���", "���볬�����ƣ�", 5, MAXGRID, true);
	inputThing(&(gameMap.h), "��������Ϸ����ĸ�(5-9)��", "����Ƿ���", "���볬�����ƣ�", 5, MAXGRID, true);

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
			pressEnterToContinue("��ʾ�������̣����س���ʾ�������򡭡�");

			//checkHint(&gameMap, &overMap);
			printMap(&gameMap, &overMap, true);
			cout << "�ɵ� " << score << " ��" << endl;
			cout << endl;
		}
		else
		{
			cout << "�Ѿ�û�п������������ˡ�" << endl;
		}

		pressEnterToContinue("���س��������˵�����");
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
				pressEnterToContinue("��ʾ�������̣����س���ʾ�������򡭡�");
				//checkHint(&gameMap, &overMap);
				printMap(&gameMap, &overMap, true);
				cout << endl;
				if (mode >= 2)
				{
					pressEnterToContinue("���س���ʾ����������顭��");
					cout << endl;
					eliminateIAR(&gameMap, &overMap, &subsMap);
					printMap(&gameMap, NULL, true);

					cout << endl;
					pressEnterToContinue("���س���ʾ���������顭��");
					cout << endl;

					enterNew(&gameMap, &subsMap);
					printMap(&gameMap, NULL, true);
				}
				cout << "�ɵ� " << score << " ��" << endl;
				cout << endl;
				if (mode == 1)
				{
					break;
				}
			}
			else
			{
				cout << "�Ѿ�û�п������������ˡ�" << endl;
				break;
			}
		}
		if (mode >= 3)
		{
			initializeMap(&overMap, -1, 0);
			checkHint(&gameMap, &overMap);
			pressEnterToContinue("���س���ʾ��������ʾ����");
			printMap(&gameMap, &overMap, true);
			cout << endl;
		}
		
		
		pressEnterToContinue("���س��������˵�����");
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
			cout << "��ʼ���飺" << endl;
			printMap(&gameMap, NULL, true);
			cout << endl;
			cout << endl << "���潫��ʾͼ�Ρ�" << endl;
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
					pressEnterToContinue("���س�����               ");
					eliminateIARGraph(&board, &gameMap, &overMap);
					eliminateIAR(&gameMap, &overMap, &subsMap);
					pressEnterToContinue("���س�����               ");
					enterNewMoveDown(&board, &gameMap, &subsMap);
					graphicTable(&board, false, NULL);
				}
				else
				{
					cout << "�Ѿ�û�п������������ˡ�" << endl;
					break;
				}
			}
			initializeMap(&overMap, -1, 0);
			checkHint(&gameMap, &overMap);
			pressEnterToContinue("���س���ʾ��������ʾ����");
			graphicTable(&board, true, &overMap);
			
		}
		else
		{
			pressEnterToContinue();
		}

		pressEnterToContinue("���س��������˵�����");
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

		cout << "\n            ���������� by ˳��\n\n\
	-------------------------------------------------------\n\
		1.�ڲ����飬���ɳ�ʼ״̬��Ѱ���Ƿ��г�ʼ��������\n\
		2.�ڲ����飬������ʼ����������0�����䲢��0���\n\
		3.�ڲ����飬������ʼ������������������ʾ\n\
		4.n*n�Ŀ��(�޷ָ���)����ʾ��ʼ״̬\n\
		5.n*n�Ŀ��(�зָ���)����ʾ��ʼ״̬\n\
		6.n*n�Ŀ��(�зָ���)����ʾ��ʼ״̬����ʼ��������\n\
		7.n*n�Ŀ��(�зָ���)��������ʼ�����������ʾ������ʾ\n\
		8.cmdͼ�ν���������\n\
		0.�˳�\n\
	-------------------------------------------------------\n\
		[��ѡ��0 - 9]";

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
				setfontsize(hout, L"������", 24);
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
