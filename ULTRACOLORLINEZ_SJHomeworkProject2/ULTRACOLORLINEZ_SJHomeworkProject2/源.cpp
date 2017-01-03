#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
#include "90-b2.h"
#include <conio.h>
using namespace std;

int read_mouse_(const HANDLE hin, int &X, int &Y, const int enable_read_mouse_moved)
{
	INPUT_RECORD    mouseRec;
	DWORD           res;
	COORD           crPos;

	while (1) {
		/* 从hin中读输入状态（包括鼠标、键盘等） */
		ReadConsoleInput(hin, &mouseRec, 1, &res);
		/* 忽略所有非鼠标事件，包括键盘 */

		

		/* 从返回中读鼠标指针当前的坐标 */
		if (mouseRec.EventType == MOUSE_EVENT)
		{
			crPos = mouseRec.Event.MouseEvent.dwMousePosition;
			X = crPos.X;
			Y = crPos.Y;
		}
		else
		{
			X = 3;
			Y = 3;
		}
		

		gotoxy(hout, X, Y);
		cout << hex << (int)mouseRec.EventType << " " << mouseRec.Event.MouseEvent.dwEventFlags << " " << mouseRec.Event.KeyEvent.bKeyDown << " " << mouseRec.Event.KeyEvent.wVirtualKeyCode << "*";

		//if (enable_read_mouse_moved && mouseRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
		//	return MOUSE_ONLY_MOVED;

		//if (mouseRec.Event.MouseEvent.dwButtonState == (FROM_LEFT_1ST_BUTTON_PRESSED | RIGHTMOST_BUTTON_PRESSED)) { //同时按下左右键
		//	return MOUSE_LEFTRIGHT_BUTTON_CLICK;
		//}
		//else if (mouseRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) { //按下左键
		//	if (mouseRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
		//		return MOUSE_LEFT_BUTTON_DOUBLE_CLICK;
		//	else
		//		return MOUSE_LEFT_BUTTON_CLICK;
		//}
		//else if (mouseRec.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) { //按下右键
		//	if (mouseRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
		//		return MOUSE_RIGHT_BUTTON_DOUBLE_CLICK;
		//	else
		//		return MOUSE_RIGHT_BUTTON_CLICK;
		//}
		//else //忽略其它按键操作（如果需要滚轮，则判断 FROM_LEFT_2ND_BUTTON_PRESSED）
		//	;
		//_getch();
		//Sleep(2000);
	} //end of while(1)

	return MOUSE_NO_ACTION; //此句应该执行不到，为避免某些编译器报不完全分支错误，加
}

int main()
{
	int X, Y;
	read_mouse_(hin, X,Y,true);
	return 0;
}
