
#include "90-b2.h"



void arrayShift(int * arr, int lastPos, int removePos)
{
	for (int *p = arr + removePos; p < arr + lastPos; p++)
	{
		*p = *(p + 1);
	}
}

void arrayPush(int * arr, int lastPos, int toPush)
{
	;
}

void restoreColor()
{
	setcolor(hout, colorList[0], colorList[1]);
}

void pressEnterToContinue()
{
	//�纯����
	cout << "��Enter������������" << endl;
	while (_getch() != '\r')
		;
	return;
}

//����������
/*
����Ҫ�õ�����ģ�壬��������ŵ�ͷ�ļ�����
template <typename T>
void inputThing(T* p, const char * promptText, const char * cinUngoodText, const char * outLimitText, T lowerLimit, T upperLimit, bool clearBuffer)*/

void inputCertainLen(char * _Str, int _Count)
{
	cin.get(_Str, _Count, '\n');
	cin.clear();
	cin.ignore(FS_MAX_LENGTH, '\n');
}

void inputWidthHeight(int &w, int &h)
{
	inputThing(&w, "��������Ϸ����Ŀ�(7-9)��", "����Ƿ���", "���볬�����ƣ�", 7, 9, true);
	inputThing(&h, "��������Ϸ����ĸ�(7-9)��", "����Ƿ���", "���볬�����ƣ�", 7, 9, true);
}

bool inputMove(int (*gameMap)[CL_MAXGRID + 2], int &source, int&dest)
{
	int promptx, prompty;
	int tmp;
	int inputx, inputy;
	int i = 0;
	char input[2][3] = { 0 };
	getxy(hout, promptx, prompty);

	while (i < 2)
	{
		getxy(hout, promptx, prompty);
		while (true)
		{
			gotoxy(hout, promptx, prompty);

			cout << "������" << (i == 0 ? "�Ƴ����" : "Ŀ��") << "λ�ã���A1������q�˳���Ϸ����";

			getxy(hout, inputx, inputy);
			cout << "_________";
			gotoxy(hout, inputx, inputy);

			inputCertainLen(input[i], 3);
			input[i][0] -= (input[i][0] >= 'a' && input[i][0] <= 'z') ? ('a' - 'A') : 0;

			if (input[i][0] == 'Q')
				return false;

			if (input[i][0] < 'A' || input[i][0] > 'Z' || input[i][1] < '0' || input[i][1] > '9')
			{
				cout << "����Ƿ���" << setw(80) << "" << endl;
				continue;
			}

			if (i == 1)
			{
				if (strcmp(input[0], input[1]) == 0)
				{
					cout << "������Ӻ��Ƴ����λ����ͬ��" << setw(80) << "" << endl;
					continue;
				}

				if (tmp = gameMap[input[1][0] - 'A' + 1][input[1][1] - '0'], tmp != 0)
				{
					cout << "������Ӳ��ܷ���" << setw(80) << "" << endl;
					continue;
				}
				dest = (input[1][0] - 'A' + 1)*(CL_MAXGRID + 1) + input[1][1] - '0';
				cout << "�����" << input[1][0] << "��" << input[1][1] << "�� " << setw(50) << "" << endl;
			}
			else
			{
				if (tmp = gameMap[input[0][0] - 'A' + 1][input[0][1] - '0'], tmp < 2)
				{
					cout << "�Ƴ��ĸ�����û����" << setw(80) << "" << endl;
					continue;
				}
				source = (input[0][0] - 'A' + 1)*(CL_MAXGRID + 1) + input[0][1] - '0';
				cout << "�Ƴ���" << input[0][0] << "��" << input[0][1] << "�У���� " << gameMap[(input[0][0] - 'A' + 1)][input[0][1] - '0'] << setw(50) << "" << endl;
			}
			break;
		}
		i++;
	}
	
	return true;
}

int inputMoveByMouse(int(*gameMap)[CL_MAXGRID + 2], int &source, int&dest, int tableStartX, int tableStartY, int promptX, int promptY,int prompt2X, int prompt2Y, int quitX, int quitY, int menuX, int menuY)
{
	int currPos, i=0, w,h;
	getMapWidthHeight(gameMap, w, h);
	while (i < 2)
	{
		while (true)
		{
			restoreColor();
			mouseActions(tableStartX, tableStartY, promptX, promptY, 0, 0, &currPos, w, h);
			gotoxy(hout, prompt2X, prompt2Y);
			if (currPos == -1)
			{
				return -1;
			}
			if (i == 1)
			{
				if (source == currPos)
				{
					cout << "������Ӻ��Ƴ����λ����ͬ��" << setw(10) << "" << endl;
					continue;
				}

				if (*getGridPointer(gameMap, currPos) != 0)
				{
					if (*getGridPointer(gameMap, currPos) >= 2)
					{
						addGraphicalBall(tableStartX, tableStartY, source, *getGridPointer(gameMap, source), colorList[0]);
						source = currPos;
						restoreColor();
						gotoxy(hout, prompt2X, prompt2Y);
						cout << "�Ƴ���" << numToLetter[currPos / (CL_MAXGRID + 1)] << "��" << currPos % (CL_MAXGRID + 1) << "�У���� " << *getGridPointer(gameMap, currPos) << setw(10) << "" << endl;
						addGraphicalBall(tableStartX, tableStartY, currPos, *getGridPointer(gameMap, currPos), colorList[CL_BALLNUM+2]);
					}
					else
					{
						cout << "������Ӳ��ܷ���" << setw(10) << "" << endl;
					}
					continue;
				}
				dest = currPos;

				cout << "�����" << numToLetter[currPos/(CL_MAXGRID+1)] << "��" << currPos % (CL_MAXGRID + 1) << "�� " << setw(10) << "" << endl;
			}
			else
			{
				if (*getGridPointer(gameMap, currPos) < 2)
				{
					cout << "�Ƴ��ĸ�����û����" << setw(10) << "" << endl;
					continue;
				}
				source = currPos;
				cout << "�Ƴ���" << numToLetter[currPos / (CL_MAXGRID + 1)] << "��" << currPos % (CL_MAXGRID + 1) << "�У���� " << *getGridPointer(gameMap, currPos) << setw(10) << "" << endl;

				addGraphicalBall(tableStartX, tableStartY, currPos, *getGridPointer(gameMap, currPos), colorList[CL_BALLNUM + 2]);
			}
			
			break;
		}
		i++;
	}
	addGraphicalBall(tableStartX, tableStartY, source, *getGridPointer(gameMap, source), colorList[0]);
	addGraphicalBall(tableStartX, tableStartY, dest, *getGridPointer(gameMap, dest), colorList[0]);
	return 0;
}

void graphicRoute(int(*gameMap)[CL_MAXGRID + 2], int *path, int tableStartX, int tableStartY, int ballType)
{
	int pathCount = 1;
	int x0, y0, x1, y1;
	path--;
	while (*path)
	{
		decodePos_(*path, y1, x1);
		decodePos_(*(path+1), y0, x0);

		
		addGraphicalBall(tableStartX, tableStartY, *(path + 1), 0, colorList[0]);
		addGraphicalBall(tableStartX, tableStartY, *(path + 1), ballType, colorList[0], (x1 - x0 + 1) + 3 * (y1 - y0 + 1));
		Sleep(sleepTime1/2);

		addGraphicalBall(tableStartX, tableStartY, *path, ballType, colorList[0]);
		addGraphicalBall(tableStartX, tableStartY, *(path + 1), 0, colorList[0], (x1 - x0 + 1) + 3 * (y1 - y0 + 1));
		
		Sleep(sleepTime1/2);

		pathCount++;
		path--;
	}
}