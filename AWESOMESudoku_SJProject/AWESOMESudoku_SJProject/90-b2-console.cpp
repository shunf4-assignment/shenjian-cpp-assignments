/* 1652270 计算机2班 冯舜 */
/*AWESOMESudokuSJProject - 90-b2-console.cpp*/
#include "90-b2.h"

//在start位置，以宽高wh画一个框
void drawBox(COORD start, short w, short h)
{
	gotoxy(hout, start.X, start.Y);
	//盖
	cout << box[0] << box[1];
	for (int i = 0; i < w; i++)
		cout << box[2] << box[3];
	cout << box[4] << box[5];
	//中
	for (int j = 0; j < h; j++)
	{
		gotoxy(hout, start.X, start.Y + j + 1);
		cout << box[6] << box[7];
		cout << setw(w * 2) << "";
		cout << box[6] << box[7];
	}
	//底
	gotoxy(hout, start.X, start.Y + h + 1);
	cout << box[8] << box[9];
	for (int i = 0; i < w; i++)
		cout << box[2] << box[3];
	cout << box[10] << box[11];
}
void drawBox(short w, short h)
{
	COORD currCoord;
	currCoord = getxy_(hout);
	drawBox(currCoord, w, h);
}

//画出listbox下的项
void itemsDraw(listbox *l)
{
	item *p;
	int tmpX, tmpY;

	restoreColor();
	gotoxy(hout, l->pos.X + 2, l->pos.Y + 1);
	p = l->items;
	p = itemNext(p, l->top);
	for (int i = 0; i < l->h && p; i++)
	{
		getxy(hout, tmpX, tmpY);
		if (l->top + i == l->index)
		{
			setcolor(hout, commonColor[1], commonColor[0]);
		}
		else
		{
			restoreColor();
		}
		cout << setw(l->w * 2) << "";
		gotoxy(hout, tmpX, tmpY);
		cout << p->text;
		p = p->next;
		gracefullyReturn(l->pos.X + 2);
	}
}

//更新listbox下的项
void itemsUpdate(listbox *l, int lastIndex, int lastTop)
{
	if (l->top != lastTop)
	{
		itemsDraw(l);
	}
	else
	{
		restoreColor();
		gotoxy(hout, l->pos.X + 2, l->pos.Y + 1 + lastIndex - lastTop);
		cout << setw(l->w * 2) << "";
		gotoxy(hout, l->pos.X + 2, l->pos.Y + 1 + lastIndex - lastTop);
		cout << itemNext(l->items, lastIndex)->text;

		setcolor(hout, commonColor[1], commonColor[0]);
		gotoxy(hout, l->pos.X + 2, l->pos.Y + 1 + l->index - l->top);
		cout << setw(l->w * 2) << "";
		gotoxy(hout, l->pos.X + 2, l->pos.Y + 1 + l->index - l->top);
		cout << itemNext(l->items, l->index)->text;
	}
}

//画出listbox，包括边框
int boxDraw(listbox *l)
{
	restoreColor();
	SetConsoleCursorPosition(hout, l->pos);
	cout << box[0] << box[1];
	for (int i = 0; i < l->w; i++)
		cout << box[2] << box[3];
	cout << box[4] << box[5];
	for (int i = 0; i < l->h; i++)
	{
		gracefullyReturn(l->pos.X);
		cout << box[6] << box[7];
		for (int j = 0; j < l->w; j++)
			cout << setw(2) << "";
		cout << box[6] << box[7];
	}
	gracefullyReturn(l->pos.X);
	cout << box[8] << box[9];
	for (int i = 0; i < l->w; i++)
		cout << box[2] << box[3];
	cout << box[10] << box[11];

	itemsUpdate(l, -1, -1);
	return 0;
}



//更新Board 中的某个格子
void updateGrid(Board *b, Coord c)
{
	updateGrid(b, c, -1, -1);
}

void updateGrid(Board *b, Coord c, int fore, int back)
{
	int boxFore, numFore, currBack;
	int j = c.y;
	int i = c.x;
	short tmpX;
	int currNum;

	boxFore = numFore = commonColor[2];
	currBack = commonColor[0];
	currNum = *getGridPointer(b->s, c);

	

	if (b->initial && b->initial->t[j][i] == 0)
	{
		boxFore = numFore = commonColor[3];
	}
	if (b->o && (b->o->t[j][i] & 7))
	{
		numFore = commonColor[4];
	}

	if (b->o && (b->o->t[j][i] >> 4 & 1))
	{
		currBack = commonColor[6];
	}

	

	if (fore >= 0)
		boxFore = numFore = fore;
	if (back >= 0)
		currBack = back;

	setcolor(hout, currBack, boxFore);

	tmpX = b->start.X + 6 * i - 6;
	gotoxy(hout, tmpX, b->start.Y + 3 * j - 3);
	for (int k = 0; k < 6; k++)
		cout << box[k];
	gracefullyReturn(tmpX);
	cout << box[6] << box[7];
	setcolor(hout, currBack, numFore);
	if (currNum == 0)
	{
		cout << setw(2) << "";
	}
	else
	{
		cout << setw(2) << currNum;
	}
	setcolor(hout, currBack, boxFore);
	cout << box[6] << box[7];
	gracefullyReturn(tmpX);
	cout << box[8] << box[9] << box[2] << box[3] << box[10] << box[11];
	cout << endl;
	restoreColor();
}

void updateGrid(Board *b, Coord c, short value)
{
	int boxFore, numFore, currBack;
	int j = c.y;
	int i = c.x;
	short tmpX;
	int theOnly;
	int currNum;

	boxFore = numFore = commonColor[2];
	currBack = commonColor[0];

	if (lengthOfValueSquare(value, &theOnly) == 1)
	{
		currNum = theOnly;
	}
	else
		currNum = 0;

	if (b->initial && b->initial->t[j][i] == 0)
	{
		boxFore = numFore = commonColor[3];
	}

	if (b->sel.x == i && b->sel.y == j)
	{
		currBack = commonColor[5];
	}


	setcolor(hout, currBack, boxFore);

	tmpX = b->start.X + 6 * i - 6;
	gotoxy(hout, tmpX, b->start.Y + 3 * j - 3);
	for (int k = 0; k < 6; k++)
		cout << box[k];
	gracefullyReturn(tmpX);
	cout << box[6] << box[7];
	setcolor(hout, currBack, numFore);
	if (currNum == 0)
	{
		cout << setw(2) << "";
	}
	else
	{
		cout << setw(2) << currNum;
	}
	setcolor(hout, currBack, boxFore);
	cout << box[6] << box[7];
	gracefullyReturn(tmpX);
	cout << box[8] << box[9] << box[2] << box[3] << box[10] << box[11];
	cout << endl;
	restoreColor();
}

//画出Board，其实就是循环updateGrid
void printBoard(Board *b)
{
	gotoxy(hout, b->start.X - 2, b->start.Y - 1);
	for (int i = 0; i <= 8; i++)
	{
		cout << setw(6) << char('a' + i);
	}
	Coord c;

	for (int j = 1; j <= 9; j++)
	{
		restoreColor();
		gotoxy(hout, b->start.X - 2, b->start.Y + 3 * j - 2);
		cout << setw(2) << j;
		for (int i = 1; i <= 9; i++)
		{
			c.x = i;
			c.y = j;
			updateGrid(b, c);
		}
	}
	restoreColor();

}
//autoGame自动解数独时刷新Board
void updateBoardAuto(Board *b, SudokuValue *vp, int* args)
{
	Coord c;
	for (int j = 1; j <= 9; j++)
	{
		restoreColor();
		for (int i = 1; i <= 9; i++)
		{
			c.x = i;
			c.y = j;
			updateGrid(b, c, vp->t[j][i]);
		}
	}
	printDFSProgress(args, b->bulletin);
	Sleep(sleepTime);
}

//画出inputBox
void drawInputBox(COORD inputPos)
{
	gotoxy(hout, inputPos.X, inputPos.Y);
	cout << box[0] << box[1] << box[2] << box[3] << boxIn[0] << boxIn[1] << box[2] << box[3] << boxIn[0] << boxIn[1] << box[2] << box[3] << box[4] << box[5];
	gotoxy(hout, inputPos.X, inputPos.Y + 1);
	cout << box[6] << box[7] << setw(2) << "" << box[6] << box[7] << setw(2) << "" << box[6] << box[7] << setw(2) << "" << box[6] << box[7];
	gotoxy(hout, inputPos.X, inputPos.Y + 2);
	cout << box[8] << box[9] << box[2] << box[3] << boxIn[8] << boxIn[9] << box[2] << box[3] << boxIn[8] << boxIn[9] << box[2] << box[3] << box[10] << box[11];
}
//画出前进后退对应的两个按钮和退出按钮
void drawBkFw(COORD bkfwStart, COORD bkfwWH)
{
	drawBox(bkfwStart, (bkfwWH.X / 2 - 4) / 2, bkfwWH.Y);
	drawBox(coordPlus( bkfwStart , bkfwWH.X / 2, 0), (bkfwWH.X / 2 - 4) / 2, bkfwWH.Y);
	gotoxy(hout, bkfwWH.X / 2 / 2 - 1  + bkfwStart.X, bkfwStart.Y + bkfwWH.Y / 2 + 1 );
	cout << "←";
	gotoxy(hout, bkfwWH.X / 2 / 2 * 3 - 1 + bkfwStart.X, bkfwStart.Y + bkfwWH.Y / 2 + 1);
	cout << "→";
	gotoxy(hout, bkfwStart.X, bkfwStart.Y + bkfwWH.Y + 2);
	drawBox((bkfwWH.X - 4) / 2, 1);
	gotoxy(hout, bkfwWH.X / 2 - 2 + bkfwStart.X, bkfwStart.Y + bkfwWH.Y  + 3);
	cout << "退出";
}

void cleanInputBox(COORD inputPos)
{
	for (int inputPoint = 0; inputPoint < 3; inputPoint++)
	{
		gotoxy(hout, inputPos.X + 2 + 4 * (inputPoint), inputPos.Y + 1);
		cout << setw(2) << "";
	}

}

void updateInputBox(COORD inputPos, const char * const str)
{
	bool strEnd = false;
	for (int inputPoint = 0; inputPoint < 3; inputPoint++)
	{
		if (!strEnd && str[inputPoint] == '\0')
			strEnd = true;
		gotoxy(hout, inputPos.X + 2 + 4 * (inputPoint), inputPos.Y + 1);
		if (strEnd)
		{
			cout << setw(2) << "";
		}
		else
		{
			cout << setw(2) << (char)(str[inputPoint] >= 'a' && str[inputPoint] <= 'z' ? str[inputPoint] + 'A' - 'a' : str[inputPoint]);

		}
	}

}

//操作所有Clickable，在有clickable可以相应键盘鼠标操作时调用***Trig
int inputTrig(Clickable **clist)
{
	INPUT_RECORD iRec;
	DWORD num;
	COORD crPos;


	int status = 0;

	enable_mouse(hin);

	while (1)
	{
		ReadConsoleInput(hin, &iRec, 1, &num);
		if (iRec.EventType == KEY_EVENT)
		{
			for (Clickable **p = clist; *p; p++)
			{
				if ((*p)->keyTrig)
				{
					status = (*p)->trigFunc(iRec, (*p)->args);
					if (status)
						break;
				}
			}
		}
		else if (iRec.EventType == MOUSE_EVENT)
		{
			crPos = iRec.Event.MouseEvent.dwMousePosition;
			for (Clickable **p = clist; *p; p++)
			{
				if (crPos.X >= (*p)->rectTop1.X && crPos.X < (*p)->rectTop2.X && crPos.Y >= (*p)->rectTop1.Y && crPos.Y < (*p)->rectTop2.Y)
				{
					if ((iRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED || iRec.Event.MouseEvent.dwEventFlags == MOUSE_WHEELED || iRec.Event.MouseEvent.dwEventFlags == MOUSE_HWHEELED) && (*p)->moveTrig)
					{
						status = (*p)->trigFunc(iRec, (*p)->args);
						if (status)
							break;
					}
					else if ((iRec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) || (iRec.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED))
					{
						status = (*p)->trigFunc(iRec, (*p)->args);
						if (status)
							break;

					}
				}

			}

		}
		if (status == -10)
		{
			//跳出
			break;
		}
	}
	return status;
}

//listbox 的鼠键操作触发函数
int boxTrig(INPUT_RECORD iRec, void **args)
{

	COORD crPos;
	listbox *l = (listbox *)(args[0]);
	int *lastIndex = (int *)(args[1]);
	int *lastTop = (int *)(args[2]);
	int result = 0;
	*lastIndex = l->index;
	*lastTop = l->top;
	if (l->itemLen == 0)
	{
		return 0;
	}

	if (iRec.EventType == KEY_EVENT && iRec.Event.KeyEvent.bKeyDown)
	{

		if (iRec.Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
		{
			if (l->index < l->itemLen - 1)
			{
				l->index++;
				if (l->index - l->top >= l->h)
					l->top = l->index - l->h + 1;
			}
			else
			{
				l->index = 0;
				l->top = 0;
			}

			result = 1;
		}
		if (iRec.Event.KeyEvent.wVirtualKeyCode == VK_UP)
		{
			if (l->index > 0)
			{
				l->index--;
				if (l->index - l->top < 0)
					l->top = l->index;
			}
			else
			{
				l->index = l->itemLen - 1;
				l->top = l->index - l->h + 1;
				if (l->top < 0)
					l->top = 0;
			}

			result = 2;
		}
		if (iRec.Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
		{
			result = -10;
		}
	}
	if (iRec.EventType == MOUSE_EVENT && (iRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED || iRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED))
	{
		crPos = iRec.Event.MouseEvent.dwMousePosition;
		int selectedOne = crPos.Y - l->pos.Y - 1;
		if (selectedOne >= 0 && selectedOne < l->h && crPos.X > l->pos.X + 1 && crPos.X < l->pos.X + 2 + l->w * 2 && l->top + selectedOne < l->itemLen)
		{
			l->index = l->top + selectedOne;
		}
		else
		{
			return -2;
		}
		if (iRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			result = -10;
		else
		{
			if (l->index == *lastIndex)
			{
				result = -1;
			}
			else
			{
				result = 1;
			}
		}
	}
	if (iRec.EventType == MOUSE_EVENT && (iRec.Event.MouseEvent.dwEventFlags == MOUSE_WHEELED || iRec.Event.MouseEvent.dwEventFlags == MOUSE_HWHEELED))
	{
		crPos = iRec.Event.MouseEvent.dwMousePosition;
		int selectedOne = crPos.Y - l->pos.Y - 1;
		if (selectedOne >= 0 && selectedOne < l->h && crPos.X > l->pos.X + 1 && crPos.X < l->pos.X + 2 + l->w * 2)
		{
			l->top++;
			if (l->top + l->h > l->itemLen)
			{
				l->top = l->itemLen - l->h;
			}

		}

	}
	if (result > 0 || result == -10)
	{
		itemsUpdate(l, *lastIndex, *lastTop);

	}
	return result;
}
//返回前进键的鼠标操作触发函数
int backTrig(INPUT_RECORD iRec, void **args)
{
	COORD clickPos = iRec.Event.MouseEvent.dwMousePosition;
	Board *b = (Board *)(args[0]);
	COORD bkfwStart = *(COORD *)(args[1]);
	COORD bkfwWH = *(COORD *)(args[2]);
	Coord &currHigh = b->sel;
	
	if (clickPos.Y > bkfwStart.Y + bkfwWH.Y + 1)
	{
		//END
		b->sel.x = -3;
		b->sel.y = -3;
		return -10;
	}
	else if (clickPos.X < bkfwStart.X + bkfwWH.X / 2)
	{
		//BACKWARD
		b->sel.x = -1;
		b->sel.y = -1;
		return -10;
	}
	else
	{
		//FORWARD
		b->sel.x = -2;
		b->sel.y = -2;
		return -10;
	}

}
//输入坐标、数字对应的键盘操作触发函数
int selTrig(INPUT_RECORD iRec, void**args)
{
	/*
	args[] = { (void *)&inputPos, (void *)&inputMove, (void *)&inputPoint, &b, NULL }
	*/
	WORD key;


	if (!(iRec.EventType == KEY_EVENT && iRec.Event.KeyEvent.bKeyDown))
		return 0;

	key = iRec.Event.KeyEvent.wVirtualKeyCode;
	int inputPoint = *(int *)args[2];
	char *inputMove = (char *)args[1];
	COORD inputPos = *(COORD *)args[0];
	Board *b = (Board *)(args[3]);
	Coord &currHigh = b->sel;
	COORD *bulletin = (COORD *)args[4];


	if (key >= 'A' && key <= 'I' || key == 'K' || key == 'W' || key == 'N' || key >= '0' && key <= '9')
	{

		if (inputPoint == 3)
			return 0;

		inputMove[inputPoint] = (key >= '0' && key <= '9') ? key : (key + 'a' - 'A');
		inputMove[inputPoint + 1] = 0;
		(*(int *)args[2])++;
		gotoxy(hout, inputPos.X + 2 + 4 * (inputPoint), inputPos.Y + 1);
		cout << setw(2) << (char)key;


		if (strcmp(inputMove, "fw") == 0)
		{
			b->sel.x = -2;
			b->sel.y = -2;
			return -10;
		}
		else if (strcmp(inputMove, "bk") == 0)
		{
			b->sel.x = -1;
			b->sel.y = -1;
			return -10;
		}
		else if (strcmp(inputMove, "end") == 0)
		{
			b->sel.x = -3;
			b->sel.y = -3;
			return -10;
		}
		else if ((*(int *)args[2]) == 3)
		{
			if (inputMove[0] > '0' && inputMove[0] <= '9' && inputMove[1] >= 'a' && inputMove[1] <= 'i' && inputMove[2] >= '0' && inputMove[2] <= '9')
			{
				b->sel.x = inputMove[1] - 'a' + 1;
				b->sel.y = inputMove[0] - '0';
				b->toInput = inputMove[2] - '0';
				return -10;
			}
			else
			{
				inputMove[0] = 0;
				(*(int *)args[2]) = 0;
				b->sel.x = 1;
				b->sel.y = 1;
				cout << '\a';
				cleanInputBox(inputPos);
				return -9;
			}
		}
		else if ((*(int *)args[2]) == 2)
		{
			if (inputMove[0] > '0' && inputMove[0] <= '9' && inputMove[1] >= 'a' && inputMove[1] <= 'i')
			{

				currHigh.x = inputMove[1] - 'a' + 1;
				currHigh.y = inputMove[0] - '0';
				updateGrid(b, currHigh, -1, commonColor[5]);
				updateInputAble(b, bulletin);
			}
		}

		return 0;
	}
	else if (key == VK_DELETE)
	{
		if (inputPoint != 0)
		{
			gotoxy(hout, inputPos.X + 2 + 4 * (inputPoint - 1), inputPos.Y + 1);
			cout << setw(2) << "";
			inputMove[inputPoint] = 0;
			(*(int *)args[2])--;

			if (inputPoint == 2)
			{
				updateGrid(b, currHigh, -1, -1);
			}
			return 1;
		}
		return 0;
	}
	else if (key == VK_UP || key == VK_DOWN || key == VK_LEFT || key == VK_RIGHT)
	{
		updateGrid(b, currHigh, -1, -1);
		switch (key)
		{
			case VK_UP:
				if (currHigh.y > 1)
					currHigh.y--;
				break;
			case VK_DOWN:
				if (currHigh.y < 9)
					currHigh.y++;
				break;
			case VK_LEFT:
				if (currHigh.x > 1)
					currHigh.x--;
				break;
			case VK_RIGHT:
				if (currHigh.x < 9)
					currHigh.x++;
				break;
			default:
				return 0;
		}
		updateGrid(b, currHigh, -1, commonColor[5]);
		(*(int *)args[2]) = 2;
		inputMove[0] = currHigh.y + '0';
		inputMove[1] = currHigh.x + 'a' - 1;
		inputMove[2] = 0;
		updateInputBox(inputPos, inputMove);
		updateInputAble(b, bulletin);
		return 2;
	}
	else if (key == VK_BACK)
	{
		cleanInputBox(inputPos);
		b->sel.x = -1;
		b->sel.y = -1;
		return -10;
	}
	else
		return 0;
}
//点击数独棋盘对应的鼠标操作触发函数
int boardTrig(INPUT_RECORD iRec, void **args)
{
	COORD clickPos = iRec.Event.MouseEvent.dwMousePosition;
	int inputPoint = *(int *)args[2];
	char *inputMove = (char *)args[1];
	COORD inputPos = *(COORD *)args[0];
	Board *b = (Board *)(args[3]);
	Coord clickGrid;
	Coord &currHigh = b->sel;
	COORD *bulletin = (COORD *)args[4];
	clickGrid.x = (clickPos.X - b->start.X) / 6 + 1;
	clickGrid.y = (clickPos.Y - b->start.Y) / 3 + 1;
	if (!(clickGrid.x >= 1 && clickGrid.y >= 1 && clickGrid.x <= 9 && clickGrid.y <= 9))
	{
		return -9;

	}
	updateGrid(b, currHigh, -1, -1);
	currHigh = clickGrid;
	updateGrid(b, currHigh, -1, commonColor[5]);
	(*(int *)args[2]) = 2;
	inputMove[0] = currHigh.y + '0';
	inputMove[1] = currHigh.x + 'a' - 1;
	inputMove[2] = 0;
	updateInputBox(inputPos, inputMove);
	updateInputAble(b, bulletin);
	return 2;

}

//打印出可以输入的数字
void updateInputAble(Board *b , COORD *bulletin)
{ 
	int *inputAble = getInputAble(b);
	gotoxy(hout, bulletin->X, bulletin->Y);
	clearLines(1, 56);
	cout << "(" << char(b->sel.y + '0') << ", " << char(b->sel.x + 'A' - 1) << ")";
	if (*inputAble)
	{
		cout << " 可以输入的数字有：";
		for (int *p = inputAble; *p; p++)
		{
			if (p != inputAble)
				cout << ", ";
			cout << *p;
		}
		cout << "。" << endl;
	}
	else
	{
		cout << " 无法输入任何数字。请考虑回退。";
	}
}

void printDFSProgress(int *args, COORD *bulletin)
{
	gotoxy(hout, bulletin->X + DFSlen1, bulletin->Y);
	clearLines(1, DFSlen2);
	cout << setw(DFSlen2) << args[1];
	gotoxy(hout, bulletin->X + DFSlen1 + DFSlen2 + DFSlen3, bulletin->Y);
	clearLines(1, DFSlen4);
	cout << setw(DFSlen4) << args[2];
	gotoxy(hout, bulletin->X + DFSlen1 + DFSlen2 + DFSlen3 + DFSlen4 + DFSlen5, bulletin->Y);
	clearLines(1, DFSlen6);
	cout << setw(DFSlen6) << args[3];
}