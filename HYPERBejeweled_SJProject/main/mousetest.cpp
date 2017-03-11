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
�������ƣ�
��    �ܣ���ʾ��ʾ��Ϣ
���������
�� �� ֵ��
˵    ����
***************************************************************************/
void to_be_continued(const HANDLE hout, const char *prompt, const int X = 0, const int Y = 22)
{
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	gotoxy(hout, X, Y);

	if (prompt)
		cout << prompt << "�����س�������...";
	else
		cout << "���س�������...";

	while (_getch() != '\r')
		;

	system("cls"); //����ϵͳ���������Ļ
}

int record1()
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //ȡ��׼����豸��Ӧ�ľ��
	const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //ȡ��׼�����豸��Ӧ�ľ��
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

		setcursor(hout, CURSOR_VISIBLE_NORMAL);	//�򿪹��
		to_be_continued(hout, "��������ʾ1����ȡ����ƶ��¼������");
	}

	CloseHandle(hout);	// �رձ�׼�����豸���
	CloseHandle(hin);	// �رձ�׼�����豸���

	return 0;
}

int main()
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //ȡ��׼����豸��Ӧ�ľ��
	const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);  //ȡ��׼�����豸��Ӧ�ľ��
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
				//cout << "���� (" << stPos.X << "," << stPos.Y << ") ��ʼ�϶���" << endl;
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
							cout << "����϶����� (" << nwPos.X << "," << nwPos.Y << ")��" << endl;
						}

					}
				}
				edPos = mouseRec.Event.MouseEvent.dwMousePosition;
				if(everDrag)
					cout << "���� (" << stPos.X << "," << stPos.Y << ") �϶����� (" << edPos.X << "," << edPos.Y << ")��" << endl;
				else
				{
					cout << "�����(" << stPos.X << "," << stPos.Y << ") �����˵�����" << endl;
				}
			}

		}

		setcursor(hout, CURSOR_VISIBLE_NORMAL);	//�򿪹��
		to_be_continued(hout, "��������ʾ1����ȡ����ƶ��¼������");
	}

	CloseHandle(hout);	// �رձ�׼�����豸���
	CloseHandle(hin);	// �رձ�׼�����豸���

	return 0;
}
