/* 1652270 计算机2班 冯舜 */
/*90-b2-tools.cpp*/
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
	//如函数名
	cout << "按Enter按键继续……" << endl;
	while (_getch() != '\r')
		;
	return;
}

//处理输入检查
/*
由于要用到函数模板，这个函数放到头文件里了
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
	inputThing(&w, "请输入游戏区域的宽(7-9)：", "输入非法！", "输入超过限制！", 7, 9, true);
	inputThing(&h, "请输入游戏区域的高(7-9)：", "输入非法！", "输入超过限制！", 7, 9, true);
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

			cout << "请输入" << (i == 0 ? "移出球的" : "目标") << "位置（如A1，输入q退出游戏）：";

			getxy(hout, inputx, inputy);
			cout << "_________";
			gotoxy(hout, inputx, inputy);

			inputCertainLen(input[i], 3);
			input[i][0] -= (input[i][0] >= 'a' && input[i][0] <= 'z') ? ('a' - 'A') : 0;

			if (input[i][0] == 'Q')
				return false;

			if (input[i][0] < 'A' || input[i][0] > 'Z' || input[i][1] < '0' || input[i][1] > '9')
			{
				cout << "输入非法。" << setw(80) << "" << endl;
				continue;
			}

			if (i == 1)
			{
				if (strcmp(input[0], input[1]) == 0)
				{
					cout << "这个格子和移出球的位置相同！" << setw(80) << "" << endl;
					continue;
				}

				if (tmp = gameMap[input[1][0] - 'A' + 1][input[1][1] - '0'], tmp != 0)
				{
					cout << "这个格子不能放球！" << setw(80) << "" << endl;
					continue;
				}
				dest = (input[1][0] - 'A' + 1)*(CL_MAXGRID + 1) + input[1][1] - '0';
				cout << "移入格：" << input[1][0] << "行" << input[1][1] << "列 " << setw(50) << "" << endl;
			}
			else
			{
				if (tmp = gameMap[input[0][0] - 'A' + 1][input[0][1] - '0'], tmp < 2)
				{
					cout << "移出的格子上没有球！" << setw(80) << "" << endl;
					continue;
				}
				source = (input[0][0] - 'A' + 1)*(CL_MAXGRID + 1) + input[0][1] - '0';
				cout << "移出球：" << input[0][0] << "行" << input[0][1] << "列，球号 " << gameMap[(input[0][0] - 'A' + 1)][input[0][1] - '0'] << setw(50) << "" << endl;
			}
			break;
		}
		i++;
	}
	
	return true;
}

int inputMoveByMouse(int(*gameMap)[CL_MAXGRID + 2], int &source, int&dest, int tableStartX, int tableStartY, int promptX, int promptY,int prompt2X, int prompt2Y, int quitX, int quitY, int menuX, int menuY, bool keyBoard)
{
	int currPos, i=0, w,h;
	int actionRet = 0;
	getMapWidthHeight(gameMap, w, h);
	while (i < 2)
	{
		while (true)
		{
			restoreColor();
			actionRet = mouseActions(tableStartX, tableStartY, promptX, promptY, 0, 0, &currPos, w, h, keyBoard);
			gotoxy(hout, prompt2X, prompt2Y);
			if (actionRet >= 0x72 && actionRet <= 0x74)
			{
				//fn按键
				return actionRet;
			}
			if (currPos == -1)
			{
				return -1; //右键退出
			}
			if (i == 1)
			{
				if (source == currPos)
				{
					cout << "这个格子和移出球的位置相同！" << setw(10) << "" << endl;
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
						cout << "移出球：" << numToLetter[currPos / (CL_MAXGRID + 1)] << "行" << currPos % (CL_MAXGRID + 1) << "列，球号 " << *getGridPointer(gameMap, currPos) << setw(10) << "" << endl;
						addGraphicalBall(tableStartX, tableStartY, currPos, *getGridPointer(gameMap, currPos), colorList[CL_BALLNUM+2]);
					}
					else
					{
						cout << "这个格子不能放球！" << setw(10) << "" << endl;
					}
					continue;
				}
				dest = currPos;

				cout << "移入格：" << numToLetter[currPos/(CL_MAXGRID+1)] << "行" << currPos % (CL_MAXGRID + 1) << "列 " << setw(10) << "" << endl;
			}
			else
			{
				if (*getGridPointer(gameMap, currPos) < 2)
				{
					cout << "移出的格子上没有球！" << setw(10) << "" << endl;
					continue;
				}
				source = currPos;
				cout << "移出球：" << numToLetter[currPos / (CL_MAXGRID + 1)] << "行" << currPos % (CL_MAXGRID + 1) << "列，球号 " << *getGridPointer(gameMap, currPos) << setw(10) << "" << endl;

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

int read_mouse_and_key(const HANDLE hin, int &X, int &Y, const int enable_read_mouse_moved)
{
	INPUT_RECORD    mouseRec;
	DWORD           res;
	COORD           crPos;
	WORD				keyCode;

	while (1) {
		/* 从hin中读输入状态（包括鼠标、键盘等） */
		ReadConsoleInput(hin, &mouseRec, 1, &res);
		/* 忽略所有非鼠标事件，包括键盘 */
		if (mouseRec.EventType != MOUSE_EVENT)
		{
			if (mouseRec.Event.KeyEvent.bKeyDown == 1) { //键盘按了键

				keyCode = mouseRec.Event.KeyEvent.wVirtualKeyCode;
				switch (keyCode)
				{
					case 0x72:
						return 0x72;
					case 0x73:
						return 0x73;
					case 0x74:
						return 0x74;
					default:
						continue;
				}
				return keyCode;
			}
		}

		/* 从返回中读鼠标指针当前的坐标 */
		crPos = mouseRec.Event.MouseEvent.dwMousePosition;
		X = crPos.X;
		Y = crPos.Y;

		if (enable_read_mouse_moved && mouseRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
			return MOUSE_ONLY_MOVED;

		if (mouseRec.Event.MouseEvent.dwButtonState == (FROM_LEFT_1ST_BUTTON_PRESSED | RIGHTMOST_BUTTON_PRESSED)) { //同时按下左右键
			return MOUSE_LEFTRIGHT_BUTTON_CLICK;
		}
		else if (mouseRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) { //按下左键
			if (mouseRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
				return MOUSE_LEFT_BUTTON_DOUBLE_CLICK;
			else
				return MOUSE_LEFT_BUTTON_CLICK;
		}
		else if (mouseRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) { //按下右键
			if (mouseRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
				return MOUSE_RIGHT_BUTTON_DOUBLE_CLICK;
			else
				return MOUSE_RIGHT_BUTTON_CLICK;
		}
		else //忽略其它按键操作（如果需要滚轮，则判断 FROM_LEFT_2ND_BUTTON_PRESSED）
			;
	} //end of while(1)

	return MOUSE_NO_ACTION; //此句应该执行不到，为避免某些编译器报不完全分支错误，加
}
