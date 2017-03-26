/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
/*AWESOMESudokuSJProject - 90-b2-base.cpp*/
#include "90-b2.h"

int itemAppend(item *&i, const char * const p, listbox *l)
{
	item **lastP = &i;
	while (*lastP)
	{
		lastP = &((*lastP)->next);
	}
	item *j = new(nothrow) item;
	char *k = new(nothrow) char[strlen(p) + 1];
	if (!j || !k)
	{
		if (j)
			delete j;
		if (k)
			delete[]k;
		return -1;
	}
	j->text = k;
	j->next = NULL;
	strcpy(j->text, p);
	(*lastP) = j;
	if (l)
		l->itemLen++;
	return 0;
}

item* itemNext(item * const p, int n)
{
	item *q = p;
	for (; n > 0; n--)
	{
		q = q->next;
	}
	return q;
}

int itemFree(item *head)
{
	item *p, *q;
	p = head;
	while (p)
	{
		q = p->next;
		delete[] p->text;
		//delete p->next;
		delete p;
		p = q;
	}

	return 0;
}

int itemPrint(item *head)
{
	item *p, *q;
	int count = 0;
	p = head;
	while (p)
	{
		q = p->next;
		cout << setiosflags(ios::left) << setw(25) << p->text << "";
		if (count % 3 == 2)
		{
			cout << endl;
		}
		count++;
		p = q;
	}

	return 0;
}

int getFileList(item *&items, listbox *l)
{
	HANDLE file;
	WIN32_FIND_DATA fileData;
	int appendStatus;
	file = FindFirstFile(".\\*.*", &fileData);
	if (INVALID_HANDLE_VALUE == file)
	{
		return -2;
	}
	FindNextFile(file, &fileData);
	while (FindNextFile(file, &fileData))
	{
		if (strstr((char *)fileData.cFileName, "sudoku"))
		{
			appendStatus = itemAppend(items, fileData.cFileName, l);
			if (appendStatus == -1)
			{
				return -1;
			}
		}
	}
	return 0;
}

void initSudoku(Sudoku *s, int wallElement, int spaceElement)
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (i == 0 || j == 0 || i > 9  || j > 9)
				s->t[j][i] = wallElement;
			else
				s->t[j][i] = spaceElement;
		}
	}
}

int inputSudoku(Sudoku *s, ifstream *f)
{
	for (int j = 1; j <= 9; j++)
	{
		for (int i = 1; i <= 9; i++)
		{
			*f >> s->t[j][i];
			if (f->bad())
			{
				f->clear();
				f->close();
				return -2;
			}
		}
	}
	return 0;
}

int charSudoku(Sudoku *s)
{
	int X, Y;

	getxy(hout, X, Y);
	restoreColor();
	cout << "-+-a-b-c-+-d-e-f-+-g-h-i-+";
	cout << setiosflags(ios::right);
	gracefullyReturn(X);

	for (int j = 1; j <= 9; j++)
	{
		restoreColor();
		cout << j << "|";
		for (int i = 1; i <= 9; i++)
		{
			if (s->t[j][i] == 0)
			{
				setcolor(hout, commonColor[0], commonColor[3]);
			}
			else
			{
				setcolor(hout, commonColor[0], commonColor[2]);
			}
			cout << setw(2) << s->t[j][i];
			if (i % 3 == 0)
			{
				restoreColor();
				cout << setw(2) << "|";
			}
		}
		gracefullyReturn(X);
		if (j % 3 == 0)
		{
			restoreColor();
			cout << "-+-------+-------+-------+";
			gracefullyReturn(X);

		}
	}
	return 0;
}