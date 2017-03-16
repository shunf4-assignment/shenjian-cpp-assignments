/* 1652270 �����2�� ��˴ */
/*HYPERBejeweled_SJProject - 90-b1-main.cpp*/
#include "90-b1.h"


void readMap()
{
	
	Map gameMap = { 0 };
	Map overMap1 = { 0 };
	Map overMap2 = { 0 };
	char input[11] = { 0 };
	char filename[25] = { 0 };
	char filenameans[25] = { 0 };
	int tmp;
	bool broken = false, consistent = true, jumpout, tmp1, tmp2;
	partInit(0);
	while (true)
	{
		ifstream f, fa;
		broken = false;
		consistent = true;
		strcpy_s(filename, "test\\");
		strcpy_s(filenameans, "test\\");
		cout << "������Ҫ�򿪵�ѧ�ţ����10���ַ�����������1652270��./test/1652270.dat���˳�����q����";
		
		cin.get(input, 11);
		
		cin.ignore(FS_MAX_LENGTH, '\n');
		cin.putback('\1');
		cin.ignore(FS_MAX_LENGTH, '\1');

		if (!strcmp(input, "q"))
		{
			break;
		}
		strcat_s(filename, input);
		strcat_s(filenameans, input);
		strcat_s(filename, ".dat");
		strcat_s(filenameans, ".ans");

		f.open(filename, ios::in);
		fa.open(filenameans, ios::in);
		if (!f.is_open() || !fa.is_open())
		{
			cout << "���ļ�ʧ�ܡ����� " << filename << " �� " << filenameans <<" �Ƿ���ڡ�" << endl;
			continue;
		}
		f >> gameMap.w;
		f >> gameMap.h;
		if (f.fail())
		{
			cout << "��������ʧЧ�������¶����ļ���" << endl;
			continue;
		}
		overMap2.w = overMap1.w = gameMap.w;
		overMap2.h = overMap1.h = gameMap.h;
		initializeMap(&gameMap, -1, 0);
		initializeMap(&overMap1, -1, 0);
		initializeMap(&overMap2, -1, 0);
		
		for (int j = 1; j <= gameMap.h; j++)
		{
			for (int i = 1; i <= gameMap.w; i++)
			{
				f >> gameMap.mapArray[j][i];
				fa >> tmp;
				tmp1 = f.fail();
				tmp2 = fa.fail();
				if ((tmp != gameMap.mapArray[j][i] && tmp - 90 != gameMap.mapArray[j][i]) || tmp1 || tmp2)
				{
					cout << "��������ʧЧ�������¶����ļ���" << endl;
					broken = true;
					break;
				}
				if (tmp >= 90)
				{
					overMap2.mapArray[j][i] = 1;
				}
			}
			if (broken)
				break;
		}
		if (broken)
			continue;
		partInit(0);

		checkHint(&gameMap, &overMap1);
		cout << "ԭʼ���̣�" << endl<< endl;
		printMap(&gameMap, NULL, true);
		cout <<  endl;

		cout << "�ҵ��㷨����Ŀ������" << endl<<endl;
		printMap(&gameMap, &overMap1, true);
		cout << endl;

		cout << "���ļ��еĿ������" << endl << endl;
		printMap(&gameMap, &overMap2, true);
		
		jumpout = false;
		for (int j = 1; j <= gameMap.h; j++)
		{
			for (int i = 1; i <= gameMap.w; i++)
			{
				if (overMap1.mapArray[j][i] != overMap2.mapArray[j][i])
				{
					consistent = false;
					jumpout = true;
					break;
				}
			}
			if (jumpout)
				break;
		}
		if (consistent)
		{
			cout << "�������������ʾһ�¡�" << endl;
		}
		else
		{
			cout << "�������������ʾ��һ�£��㷨���ļ����������⡣" << endl;
		}
		pressEnterToContinue();
		f.close();
		fa.close();
		break;
	}
	
}

int waitMouse(Board *b)
{
	bool loop = true;
	bool dragEnd, everDrag;
	INPUT_RECORD    mouseRec;
	DWORD           res;
	COORD           stPos, nwPos, edPos, tmp1, tmp2;
	Coord			source, dest, tmpC, tmpD = {0,0};
	int				xD, yD;
	short * dimenToChange;
	int * dimenToChange2, tmps1, tmps2;
	int * dimenToComp;
	int returnFlag = 0;
	//0 - fail to do anything, 1 - swap with a success, 2 - exit
	Map overMap = { 0 };

	enable_mouse(hin);
	
	overMap.w = b->map->w;
	overMap.h = b->map->h;
	initializeMap(&overMap, -1, 0);

	while (loop) {

		ReadConsoleInput(hin, &mouseRec, 1, &res);
		if (mouseRec.EventType != MOUSE_EVENT)
			continue;
		if (mouseRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
		{
			tmp1 = mouseRec.Event.MouseEvent.dwMousePosition;
			tmpC = getCoordonBoard(b, &tmp1);
			if(tmpC.x && tmpC.y && (tmpC.x != tmpD.x || tmpC.y != tmpD.y))
				printCoord(b, getCoordonBoard(b, &tmp1));
			tmpD = tmpC;
		}
		if (mouseRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			dragEnd = false;
			everDrag = false;
			stPos = mouseRec.Event.MouseEvent.dwMousePosition;
			source = getCoordonBoard(b, &stPos);
			
			if (source.x == 0)
			{
				continue;
			}
			nwPos = stPos;
			b->currPos = source;
			addGraphicalBall(b, -1, 1, { 0,0 });
			tmp1 = { 0,0 };
			while (dragEnd == false)
			{
				ReadConsoleInput(hin, &mouseRec, 1, &res);
				if (mouseRec.EventType != MOUSE_EVENT)
					continue;
				if (mouseRec.Event.MouseEvent.dwButtonState == 0 && mouseRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
					dragEnd = true;
				else if (mouseRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
				{
					if (nwPos.X != mouseRec.Event.MouseEvent.dwMousePosition.X || nwPos.Y != mouseRec.Event.MouseEvent.dwMousePosition.Y)
					{
						everDrag = true;
						nwPos = mouseRec.Event.MouseEvent.dwMousePosition;
						xD = (nwPos.X - b->sc.X) / 2 - (stPos.X - b->sc.X) / 2;
						yD = nwPos.Y - stPos.Y;
						tmp2 = tmp1;
						dimenToChange = &(tmp1.X);
						dimenToComp = &(yD);

						if ((source.y == 1 && yD < 0 || source.y == b->map->h && yD > 0) || !(abs(xD) < abs(yD) || (source.x == 1 && xD < 0 || source.x == b->map->w && xD > 0)))
						{
							dimenToChange = &(tmp1.X);
							dimenToComp = &(xD);
							tmp1.Y = 0;

						}
						else
						{
							dimenToChange = &(tmp1.Y);
							dimenToComp = &(yD);
							tmp1.X = 0;
						}

						if (*dimenToComp < -1)
						{

							*dimenToChange = -2;
						}
						else if (*dimenToComp < 0)
						{
							*dimenToChange = -1;
						}
						else if (*dimenToComp > 1)
						{
							*dimenToChange = 2;
						}
						else if (*dimenToComp > 0)
						{
							*dimenToChange = 1;
						}
						else
						{
							*dimenToChange = 0;
						}

						if (tmp1.X != tmp2.X || tmp1.Y != tmp2.Y)
						{
							tmp2.X = sgn(tmp2.X);
							tmp2.Y = sgn(tmp2.Y);

							b->currPos = { source.x + tmp2.X, source.y + tmp2.Y };
							if (b->currPos.x < 1 || b->currPos.y < 1 || b->currPos.x > b->map->w || b->currPos.y > b->map->h)
								;
							else
								addGraphicalBall(b, -1, 0, { 0,0 });

							b->currPos = source;
							addGraphicalBall(b, 0, 0, tmp2);
							if (b->currPos.x == 1 && tmp1.X < 0 || b->currPos.x == b->map->w && tmp1.X > 0 || b->currPos.y == 1 && tmp1.Y < 0 || b->currPos.y == b->map->h && tmp1.Y > 0)
								continue;


							addGraphicalBall(b, 0, 0, { 0,0 });
							addGraphicalBall(b, getGrid(b->map, source), 1, tmp1);
							if (abs(tmp1.X + tmp1.Y) == 2)
							{
								addGraphicalBall(b, getGrid(b->map, { source.x + tmp1.X / 2, source.y + tmp1.Y / 2 }), 0, { 0,0 });


							}
						}
					}

				}
			}

			if (everDrag)
			{
				b->currPos = source;
				addGraphicalBall(b, 0, 0, { 0,-1 });
				addGraphicalBall(b, 0, 0, { -1,0 });
				addGraphicalBall(b, 0, 0, { 0,1 });
				addGraphicalBall(b, 0, 0, { 1,0 });

				edPos = mouseRec.Event.MouseEvent.dwMousePosition;
				dest = source;
				xD = (nwPos.X - b->sc.X) / 2 - (stPos.X - b->sc.X) / 2;
				yD = nwPos.Y - stPos.Y;

				if ((source.y == 1 && yD < 0 || source.y == b->map->h && yD > 0) || !(abs(xD) < abs(yD) || (source.x == 1 && xD < 0 || source.x == b->map->w && xD > 0)))

				{
					dimenToChange2 = &(dest.x);
					dimenToComp = &(xD);

				}
				else
				{
					dimenToChange2 = &(dest.y);
					dimenToComp = &(yD);


				}
				if (*dimenToComp < -1)
				{

					(*dimenToChange2)--;
				}
				else if (*dimenToComp > 1)
				{
					(*dimenToChange2)++;
				}



				if (dest.x < 1 || dest.x > b->map->w || dest.y < 1 || dest.y > b->map->h || dest.x == source.x && dest.y == source.y)
				{
					b->currPos = source;
					addGraphicalBall(b, -1, 0, { 0,0 });
				}
				else
				{
					tmps1 = getGrid(b->map, source);
					tmps2 = getGrid(b->map, dest);
					b->currPos = dest;
					addGraphicalBall(b, tmps1, 0, { 0,0 });
					b->currPos = source;
					addGraphicalBall(b, tmps2, 0, { 0,0 });
					*getGridPointer(b->map, source) = tmps2;
					*getGridPointer(b->map, dest) = tmps1;
					checkInARow(b->map, &overMap);
					if (isMapEmpty(&overMap))
					{
						*getGridPointer(b->map, source) = tmps1;
						*getGridPointer(b->map, dest) = tmps2;

						Sleep(swapInvalidInterval);
						b->currPos = source;
						tmp1.X = (dest.x - source.x) * 2;
						tmp1.Y = (dest.y - source.y) * 2;
						addGraphicalBall(b, 0, 0, tmp1);
						addGraphicalBall(b, 0, 0, { 0,0 });
						tmp1.X = dest.x - source.x;
						tmp1.Y = dest.y - source.y;
						addGraphicalBall(b, tmps1, 1, tmp1);
						Sleep(swapInvalidInterval);
						addGraphicalBall(b, 0, 0, tmp1);

						b->currPos = dest;
						addGraphicalBall(b, tmps2, 0, { 0,0 });
						b->currPos = source;
						addGraphicalBall(b, tmps1, 0, { 0,0 });
					}
					else
					{
						loop = false;
						returnFlag = 1;
						break;
					}
					//graphicTable(b, true, NULL);

				}

			}
			else
			{
				while (true)
				{
					COORD_ c1;
					COORD c1_, t1;
					//Coord tmpC;
					int mouseStatus;
					mouseStatus = read_mouse(hin, c1.X, c1.Y, 1);

					if (mouseStatus == MOUSE_ONLY_MOVED)
					{
						c1_.X = c1.X;
						c1_.Y = c1.Y;
						tmpC = getCoordonBoard(b, &c1_);
						if (tmpC.x && tmpC.y && (tmpC.x != tmpD.x || tmpC.y != tmpD.y))
							printCoord(b, tmpC);
						tmpD = tmpC;
					}
					if (mouseStatus == MOUSE_RIGHT_BUTTON_CLICK)
					{
						returnFlag = 2;
						loop = false;
						break;

					}
					else if (mouseStatus != MOUSE_LEFT_BUTTON_CLICK)
						continue;

					c1_.X = c1.X;
					c1_.Y = c1.Y;
					dest = getCoordonBoard(b, &c1_);
					
					if (dest.x == 0)
					{
						continue;
					}
					if (dest.x == source.x && dest.y == source.y)
					{
						b->currPos = source;
						addGraphicalBall(b, -1, 0, { 0,0 });
						break;
					}
					t1.X = dest.x - source.x;
					t1.Y = dest.y - source.y;
					if (abs(t1.X) + abs(t1.Y) != 1)
					{
						b->currPos = source;
						addGraphicalBall(b, -1, 0, { 0,0 });
						source = dest;
						b->currPos = source;
						addGraphicalBall(b, -1, 1, { 0,0 });

						continue;
					}
					tmps1 = getGrid(b->map, source);
					tmps2 = getGrid(b->map, dest);
					Sleep(swapInvalidInterval);
					b->currPos = dest;
					addGraphicalBall(b, 0, 0, { 0,0 });
					b->currPos = source;
					addGraphicalBall(b, 0, 0, { 0,0 });
					addGraphicalBall(b, -1, 1, t1);
					Sleep(swapInvalidInterval);
					addGraphicalBall(b, 0, 0, t1);
					b->currPos = dest;
					addGraphicalBall(b, tmps1, 0, { 0,0 });
					b->currPos = source;
					addGraphicalBall(b, tmps2, 0, { 0,0 });
					*getGridPointer(b->map, source) = tmps2;
					*getGridPointer(b->map, dest) = tmps1;
					checkInARow(b->map, &overMap);
					if (isMapEmpty(&overMap))
					{
						*getGridPointer(b->map, source) = tmps1;
						*getGridPointer(b->map, dest) = tmps2;

						Sleep(swapInvalidInterval);
						b->currPos = source;
						tmp1.X = (dest.x - source.x) * 2;
						tmp1.Y = (dest.y - source.y) * 2;
						addGraphicalBall(b, 0, 0, tmp1);
						addGraphicalBall(b, 0, 0, { 0,0 });
						tmp1.X = dest.x - source.x;
						tmp1.Y = dest.y - source.y;
						addGraphicalBall(b, tmps1, 1, tmp1);
						Sleep(swapInvalidInterval);
						addGraphicalBall(b, 0, 0, tmp1);

						b->currPos = dest;
						addGraphicalBall(b, tmps2, 0, { 0,0 });
						b->currPos = source;
						addGraphicalBall(b, tmps1, 0, { 0,0 });
					}
					else
					{
						loop = false;
						returnFlag = 1;
						break;
					}
					break;
				}
			}
		}
		if (mouseRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			returnFlag = 2;
			loop = false;
		}
	}
	return returnFlag;
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
			if (mode >= 6)
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
		clearLines(2);
		pressEnterToContinue("���س��������˵�����");
	}
}

void fullGame(bool extra)
{
	Map gameMap = { 0 };
	Map overMap = { 0 };
	SMap subsMap = { 0 };
	Board board = {};
	COORD_ boardWH;
	COORD_ windowWH;
	COORD_ startXY;
	int thisTurnMouse, combo;
	char userOpt;
	bool restart = false, sel = false;
	int X, Y;

	board.bgColor = commonColor[0];
	board.frameColor = commonColor[1];
	board.highBgColor = commonColor[2];
	board.map = &gameMap;

	partInit(1);
	inputWidthHeight(gameMap.w, gameMap.h);
	boardWH = boardUIWH(&gameMap, true);
	windowWH = windowWHCal(&gameMap, boardWH, 8);
	startXY = startXYCal(boardWH, 8);
	while (1) {
		int score = 0, thisScore = 0, lastScore = 0, total = 0, lastTotal = 0;
		bool firstTime = true;
		restart = false;
		combo = 0;

		overMap.w = gameMap.w;
		overMap.h = gameMap.h;
		subsMap.w = gameMap.w;
		subsMap.h = gameMap.h;


		initializeMap(&gameMap, -1, 0);
		initializeMap(&overMap, -1, 0);
		initializeMap(&subsMap, -1, 0);

		initEmerge(&gameMap);

		partInit(4, windowWH.X, windowWH.Y, windowWH.Y);
		board.sc = startXY;
		gotoxy(hout, board.sc.X, board.sc.Y);

		graphicTable(&board, true, &overMap);

		while (1)
		{
			total = 0;
			lastScore = score;
			initializeMap(&overMap, -1, 0);
			if (firstTime)
				total = checkInARowWithScore(&gameMap, &overMap, NULL, combo);
			else
				total = checkInARowWithScore(&gameMap, &overMap, &score, combo);
			if (score - lastScore != 0)
				thisScore = score - lastScore;
			if (total != 0)
				lastTotal = total;

			gotoEndOfBoard(&board);
			cout << setw(6) << "";
			getxy(hout, X, Y);
			clearLines(2);
			restoreColor();
			cout << "��ǰ�÷֣�" << score << ", ���ֵ÷֣�" << thisScore << ", ������ȥ������" << lastTotal;
			gracefullyReturn(X);
			cout << "Combo��" << combo;

			lastTotal = total;


			if (!isMapEmpty(&overMap))
			{
				combo++;
				eliminateIARGraph(&board, &gameMap, &overMap);
				eliminateIAR(&gameMap, &overMap, &subsMap);
				enterNewMoveDown(&board, &gameMap, &subsMap);
				graphicTable(&board, false, NULL);
				continue;
			}
			else
			{
				if (firstTime)
					firstTime = false;
				combo = 0;
			}
			initializeMap(&overMap, -1, 0);
			checkHint(&gameMap, &overMap);
			graphicTable(&board, false, &overMap);

			if (isMapEmpty(&overMap))
			{
				int X, Y;
				gotoEndOfBoard(&board);
				cout << setw(6) << "";
				getxy(hout, X, Y);
				gracefullyReturn();
				clearLines(2);
				cout << "���ޣ�û�п����ƶ������ˣ����֡�";
				gracefullyReturn(X);
				break;
			}

			thisTurnMouse = waitMouse(&board);
			if (thisTurnMouse == 2)
				break;
		}
		gotoEndOfBoard(&board);
		cout << endl << endl;

		getxy(hout, X, Y);
		clearLines(2);
		restoreColor();
		cout << "��Ҫ����һ����(y/n)";
		sel = false;

		do {
			userOpt = _getch();
			switch (userOpt)
			{
				case 'y':
				case 'Y':
					restart = true;
					sel = true;
					break;
				case 'n':
				case 'N':
					restart = false;
					sel = true;
					break;

			}
		} while (!sel);
		if (!restart)
			break;
	}
	gotoEndOfBoard(&board);
	clearLines(4);

	pressEnterToContinue("���س��������˵�����");

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
		9.���ļ��ж�ȡ��������֤����������ʾ���㷨����ȷ��\n\
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
			{
				CloseHandle(hout);	// �رձ�׼�����豸���
				CloseHandle(hin);	// �رձ�׼�����豸���
				return 0;
			}
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
			case 8:
				fullGame(false);
				break;
			case 9:
				readMap();
				break;
		}
	}
	return 0;
}
