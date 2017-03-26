/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
/*AWESOMESudokuSJProject - 90-b2-console.cpp*/
#include "90-b2.h"

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

int boxWaitInput(listbox *l, int *lastIndex, int* lastTop)
{
	INPUT_RECORD iRec;
	DWORD num;
	COORD crPos;
	*lastIndex = l->index;
	*lastTop = l->top;

	while (1)
	{
		ReadConsoleInput(hin, &iRec, 1, &num);
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

				return 1;
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
				}

				return 2;
			}
			if (iRec.Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
			{
				return 3;
			}
		}
		if (iRec.EventType == MOUSE_EVENT && iRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			crPos = iRec.Event.MouseEvent.dwMousePosition;
			int selectedOne = crPos.Y - l->pos.Y - 1;
			if (selectedOne >= 0 && selectedOne < l->h && crPos.X > l->pos.X + 1 && crPos.X < l->pos.X + 2 + l->w * 2)
			{
				l->index = l->top + selectedOne;
				return 3;
			}
		}
	}
}
