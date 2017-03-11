#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include "cmd_console_tools.h"
using namespace std;

/***************************************************************************
函数名称：
功    能：显示提示信息
输入参数：
返 回 值：
说    明：
***************************************************************************/
void to_be_continued(const HANDLE hout, const char *prompt, const int X = 0, const int Y = 22)
{
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	gotoxy(hout, X, Y);

	if (prompt)
		cout << prompt << "，按回车键继续...";
	else
		cout << "按回车键继续...";

	while (_getch() != '\r')
		;

	system("cls"); //调用系统命令清除屏幕
}

int record1()
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
	const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄
	INPUT_RECORD    mouseRec;
	DWORD           res;
	COORD           crPos;
	setconsoleborder(hout, 140, 40, 1000);

	if (1) {
		int X = 0, Y = 0;
		int action;
		int loop = 1;

		enable_mouse(hin);
		cout << "[ CLS ]";

		while (loop) {
			

			ReadConsoleInput(hin, &mouseRec, 1, &res);
			cout << "" << mouseRec.EventType << ", ";
			cout << "" << mouseRec.Event.MouseEvent.dwButtonState << ", ";
			cout << "" << mouseRec.Event.MouseEvent.dwControlKeyState << ", ";
			cout << "" << mouseRec.Event.MouseEvent.dwEventFlags << "| ";
			crPos = mouseRec.Event.MouseEvent.dwMousePosition;
			X = crPos.X;
			Y = crPos.Y;

			if (mouseRec.Event.MouseEvent.dwEventFlags != MOUSE_MOVED && mouseRec.EventType == MOUSE_EVENT && X >= 0 && X <= 6 && Y == 0)
			{
				system("cls");
				enable_mouse(hin);
				cout << "[ CLS ]";
			}
			
		} //end of while(1)

		setcursor(hout, CURSOR_VISIBLE_NORMAL);	//打开光标
		to_be_continued(hout, "鼠标操作演示1（读取鼠标移动事件）完成");
	}

	CloseHandle(hout);	// 关闭标准输入设备句柄
	CloseHandle(hin);	// 关闭标准输入设备句柄

	return 0;
}

int main()
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄
	const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //取标准输入设备对应的句柄
	INPUT_RECORD    mouseRec;
	DWORD           res;
	COORD           crPos, stPos, nwPos, edPos;
	bool dragEnd, everDrag;
	setconsoleborder(hout, 140, 40, 40);

	if (1) {
		int X = 0, Y = 0;
		int action;
		int loop = 1;

		enable_mouse(hin);

		while (loop) {


			ReadConsoleInput(hin, &mouseRec, 1, &res);
			if(mouseRec.EventType != MOUSE_EVENT)
				continue;

			if (mouseRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				dragEnd = false;
				everDrag = false;
				stPos = mouseRec.Event.MouseEvent.dwMousePosition;
				//cout << "鼠标从 (" << stPos.X << "," << stPos.Y << ") 开始拖动。" << endl;
				nwPos = stPos;
				while (dragEnd == false)
				{
					ReadConsoleInput(hin, &mouseRec, 1, &res);
					if (mouseRec.EventType != MOUSE_EVENT)
						continue;
					if (mouseRec.Event.MouseEvent.dwButtonState == 0 && mouseRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
						dragEnd = true;
					else if (mouseRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
					{
						everDrag = true;
						if (nwPos.X != mouseRec.Event.MouseEvent.dwMousePosition.X || nwPos.Y != mouseRec.Event.MouseEvent.dwMousePosition.Y)
						{
							nwPos = mouseRec.Event.MouseEvent.dwMousePosition;
							cout << "鼠标拖动到了 (" << nwPos.X << "," << nwPos.Y << ")。" << endl;
						}

					}
				}
				edPos = mouseRec.Event.MouseEvent.dwMousePosition;
				if(everDrag)
					cout << "鼠标从 (" << stPos.X << "," << stPos.Y << ") 拖动到了 (" << edPos.X << "," << edPos.Y << ")。" << endl;
				else
				{
					cout << "鼠标在(" << stPos.X << "," << stPos.Y << ") 进行了单击。" << endl;
				}
			}

		}

		setcursor(hout, CURSOR_VISIBLE_NORMAL);	//打开光标
		to_be_continued(hout, "鼠标操作演示1（读取鼠标移动事件）完成");
	}

	CloseHandle(hout);	// 关闭标准输入设备句柄
	CloseHandle(hin);	// 关闭标准输入设备句柄

	return 0;
}
