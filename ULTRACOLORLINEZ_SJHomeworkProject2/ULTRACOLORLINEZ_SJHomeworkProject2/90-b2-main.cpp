/* 1652270 �����2�� ��˴ */
/*90-b2-main.cpp*/
#include "90-b2.h"

void part1PrintArray()
{
	bool emergeSuc = false;
	int gameMap[CL_MAXGRID + 2][CL_MAXGRID + 2];
	int w=9, h=9;

	srand((unsigned int)time(0) + 2);
	inputThing(&w, "��������Ϸ����Ŀ�(7-9)��", "����Ƿ���", "���볬�����ƣ�", 7, 9, true);
	inputThing(&h, "��������Ϸ����ĸ�(7-9)��", "����Ƿ���", "���볬�����ƣ�", 7, 9, true);

	initializeMap(gameMap, w, h);
	emergeSuc = randomEmerge(gameMap, 5);
	printArray(gameMap);
	//Sleep(1000);
	cout << endl << (emergeSuc ? "���ɲ���ɹ�" : "���ɲ���ʧ��") << endl;
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
	//��ַ���Ա���Ϊһ��int�����к�*10+�кš�

	inputWidthHeight(w, h);

	initializeMap(gameMap, w, h);
	initializeMap(pathMap, w, h, -1, 0);
	randomEmerge(gameMap, (int)floor(w*h*0.6));
	printArray(gameMap);

	inputMove(gameMap, source, dest);
	
	path = staticPath(gameMap, source, dest);
	if (*path == 0)
	{
		//No path.
		cout << "�Ҳ���·��" << endl;
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
	//��ַ���Ա���Ϊһ��int�����к�*10+�кš�

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
		cout << "���ֵ÷֣�" << thisScore << " �ܷ֣�" << score << endl;
		cout << "����Ԥ�棺 ";
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
				cout << "�Ҳ���·��" << endl;
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
	cout << "��Ϸ��������ĵ÷��ǣ�" << score << endl;
	pressEnterToContinue();
}

void part4Frame()
{
	int gameMap[CL_MAXGRID + 2][CL_MAXGRID + 2];
	int w = 9, h = 9,x,y;

	inputWidthHeight(w, h);

	initializeMap(gameMap, w, h);
	randomEmerge(gameMap, 5, true);

	cout << "��ʼ���飺" << endl;
	printArray(gameMap);
	cout << endl << "���潫��ʾͼ�Ρ�" << endl;
	pressEnterToContinue();
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

	cout << "��ʼ���飺" << endl;
	printArray(gameMap);
	cout << endl << "���潫��ʾͼ�Ρ�" << endl;
	pressEnterToContinue();
	getxy(hout, x, y);
	graphicTable(gameMap, x, y);
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

	graphicTable(gameMap, tableStartX, tableStartY);
	getxy(hout, x, y);
	if (inputMoveByMouse(gameMap, source, dest, tableStartX, tableStartY, x, y, x, y + 1, -1, -1, -1, -1) != -1)
	{
		path = staticPath(gameMap, source, dest);

		gotoxy(hout, x, y + 2);
		restoreColor();

		if (*path == 0)
		{
			//No path.
			cout << "�Ҳ���·��" << endl;
		}
		else
		{
			graphicRoute(gameMap, path, tableStartX, tableStartY, *getGridPointer(gameMap, source));
			gotoxy(hout, x, y + 2);
			restoreColor();
			cout << "�ƶ��ɹ���" << endl;
		}
	}
	gotoxy(hout, x, y + 3);
	setcursor(hout, CURSOR_VISIBLE_NORMAL);
	pressEnterToContinue();
}

void part7GraphicFull()
{
	const int nextBallNum = 3;
	int gameMap[CL_MAXGRID + 2][CL_MAXGRID + 2];
	int pathMap[CL_MAXGRID + 2][CL_MAXGRID + 2] = { 0 };
	int w = 9, h = 9;
	int windowWidth, windowHeight, tableWidth, tableHeight, tableStartX, tableStartY;
	int menuX, menuY, KingX = 0, KingY = 0, PretenderX = 0, PretenderY = 0, scoreKX, scoreKY, nextBallsX, nextBallsY, scorePX, scorePY, promptX, promptY, statX, statY;
	int *path;
	int nextBalls[nextBallNum + 1] = { 0,0,0 };
	int source, dest;
	int score = 0, thisScore = 0, kingScore = 100, thisBallCount = 0;
	bool exitFlag = false;
	int gameStats[] = { 0,0,0,0,0,0,0,0,0 };
	int gameStatsBallDel[] = { 0,0,0,0,0,0,0,0,0 };

	inputWidthHeight(w, h);

	initializeMap(gameMap, w, h);
	randomEmerge(gameMap, 5, true);
	tableWidth = w * 4 + 2;
	tableHeight = h * 2 + 1 + 3;
	tableStartX = tableWidth / 2;
	tableStartY = 7;
	windowWidth = tableStartX * 2 + tableWidth + 26;
	windowHeight = tableHeight + tableStartY * 2 +1;
	menuX = 0, menuY = 0;
	KingX = tableStartX / 2 - 4;
	PretenderX = tableStartX * 3 / 2 - 4 + tableWidth;
	nextBallsX = tableStartX + tableWidth / 2 - 7;
	scoreKX = tableStartX / 2 - 3;
	scorePX = tableWidth + tableStartX *3 /2 - 3;
	nextBallsY = scoreKY = scorePY = 3;
	promptX = tableStartX + 2;
	promptY = tableStartY + tableHeight + 1;
	statX = tableStartX * 2 + tableWidth + 1;
	statY = tableStartY;



	//KingY = calY(kingScore, score);
	//PretenderY = calY(score);

	setconsoleborder(hout, windowWidth, windowHeight);
	restoreColor();
	system("cls");

	drawInitUI(tableWidth, tableHeight, tableStartX, tableStartY, menuX, menuY, KingX, PretenderX, KingY, PretenderY, nextBallsX, nextBallsY, scoreKX, scoreKY, scorePX, scorePY, gameMap, windowWidth, statX, statY);

	

	do
	{
		score += thisScore;
		if(thisBallCount==0)
			regenBalls(nextBalls);
		updateScore(score, scorePX, scorePY);
		updateNextBalls(nextBalls, nextBallsX, nextBallsY);
		updateStats(gameMap, gameStats, gameStatsBallDel, statX, statY);

		graphicTable(gameMap, tableStartX, tableStartY);

		thisScore = 0;
		thisBallCount = false;

		initializeMap(pathMap, w, h, -1, 0);

		while (true)
		{
			if (inputMoveByMouse(gameMap, source, dest, tableStartX, tableStartY, promptX, promptY, promptX, promptY + 2, -1, -1, -1, -1) == -1)
			{
				exitFlag = true;
				break;
			}

			path = staticPath(gameMap, source, dest);

			restoreColor();
			gotoxy(hout, promptX, promptY + 3);

			if (*path == 0)
			{
				//No path.
				cout << "�Ҳ���·��" << endl;
			}
			else
			{
				graphicRoute(gameMap, path, tableStartX, tableStartY, *getGridPointer(gameMap, source));
				ballMove(gameMap, source, dest);
				thisBallCount = checkIAR(gameMap, dest, &thisScore, true, NULL, 0, gameStatsBallDel);
				gotoxy(hout, promptX, promptY + 3);
				restoreColor();
				cout << "�ƶ��ɹ���" << endl;
				break;
			}
		}
		if (exitFlag)
		{
			break;
		}
	} while (thisBallCount==0 && randomEmerge(gameMap, 3, true, nextBalls) || thisBallCount!=0);
	graphicTable(gameMap, tableStartX, tableStartY);
	gotoxy(hout, promptX, promptY + 2);
	setcursor(hout, CURSOR_VISIBLE_NORMAL);
	cout << "��Ϸ��������ĵ÷��ǣ�" << score << endl;
	pressEnterToContinue();
}

int main()
{
	int mode;
	char opt;

	srand(unsigned int(time(0)));

	while (true)
	{
		mode = 1;
		setconsoleborder(hout, 80, 25);
		restoreColor();
		system("cls");

		//freopen("in.txt", "r", stdin);

		cout << "	---------------------------------------------\n\
	1.�ڲ����飬������ɳ�ʼ5����\n\
	2.�ڲ����飬�������60%����Ѱ���ƶ�·��\n\
	3.�ڲ����飬������\n\
	4.����n*n�Ŀ�ܣ��޷ָ��ߣ��������ʾ5����\n\
	5.����n*n�Ŀ�ܣ��зָ��ߣ��������ʾ5����\n\
	6.n*n�Ŀ�ܣ�60%����֧����꣬���һ���ƶ�\n\
	7.cmdͼ�ν���������\n\
	8.cmdͼ�ν��������� - ֧��ͬʱ����������ӷ֣�\n\
	9.˫�������Ҽ�ͬʱ���²������ε���������ӷ֣�\n\
	0.�˳�\n\
	-------------------------------------------- -\n\
		[��ѡ��0 - 9]";

		do {
			opt = _getch();
		} while (!(opt >= '0' && opt <= '9'));
		cout << opt << endl;

		mode = opt - '0';
		if (mode == 0)
			return 0;

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
				part6OnceMove();
				break;
			case 7:
				part7GraphicFull();
				break;
		}

	}
	return 0;
}