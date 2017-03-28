/* 1652270 计算机2班 冯舜 */
/*AWESOMESudokuSJProject - 90-b2-base.cpp*/
#include "90-b2.h"

int compAppend(composition *&i, const Sudoku &c)
{
	composition **lastP = &i;
	composition *lastNode = i;
	while (lastNode && lastNode->next)
	{
		lastNode = lastNode->next;
	}
	while (*lastP)
	{
		lastP = &((*lastP)->next);
	}
	composition *j = new(nothrow) composition;
	if (!j)
	{
		return -1;
	}
	j->c = c;
	j->next = NULL;
	j->prev = lastNode;

	(*lastP) = j;

	return 0;
}

composition* compNext(composition * const p, int n)
{
	composition *q = p;
	for (; n > 0; n--)
	{
		q = q->next;
	}
	return q;
}

composition* compPrev(composition * const p, int n)
{
	composition *q = p;
	for (; n > 0; n--)
	{
		q = q->prev;
	}
	return q;
}

int compFree(composition *head)
{
	composition *p, *q;
	p = head;
	while (p)
	{
		q = p->next;
		delete p;
		p = q;
	}

	return 0;
}

int compCount(composition *head)
{
	composition *q = head;
	int count = 0;
	for (; q; count++)
	{
		q = q->next;
	}
	return count;
}

int compCount(composition *head, composition *p)
{
	composition *q = head;
	int count = 0;
	for (; q && q != p; count++)
	{
		q = q->next;
	}
	return count;
}

int compDropTail(composition *&head, int n)
{
	//抛弃该节点以后的所有节点，包括自身，传引用过去的指针置NULL
	composition *p = head;
	p = compNext(p, n);
	compFree(p);
	head = NULL;

	return 0;
}

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

bool isSudokuFull(Sudoku *s)
{
	bool result = true;
	for (int i = 0; i < 11 && result; i++)
	{
		for (int j = 0; j < 11 && result; j++)
		{
			if (s->t[j][i] == 0)
			{
				result = false;
				break;
			}
		}
	}
	return result;
}

void initSudoku(Sudoku *s, Sudoku *o )
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			s->t[j][i] = o->t[j][i];
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
			if (f->fail())
			{
				f->clear();
				f->close();
				return -2;
			}
		}
	}
	return 0;
}

int charSudoku(Sudoku *s, Sudoku *initial, Sudoku *o)
{
	int X, Y;
	int currFore, currBack;

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
			currFore = commonColor[2];
			currBack = commonColor[0];

			if (initial->t[j][i] == 0)
			{
				currFore =  commonColor[3];
			}

			if (o && (o->t[j][i] >> 4 & 1))
			{
				currBack = commonColor[1];
			}

			if (o && (o->t[j][i] & 7))
			{
				currFore = commonColor[4];
			}

			setcolor(hout, currBack, currFore);

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

int decExtract(int dec, int n)
{
	for (int i = 0; i < n; i++)
	{
		dec /= 10;
	}
	return dec % 10;
}

void decSet(int *dec, int digit, int numToSet)
{
	int decMeta = 1;
	for (int i = 0; i < digit; i++)
	{
		decMeta *= 10;
	}
	*dec -= decExtract(*dec, digit) * decMeta;
	*dec += numToSet * decMeta;
}

int validSudoku(Sudoku *s, Sudoku *overMap)
{
	//检查数独的正确性
	//overMap中每个格为一个bitmap，次高位->低位: 行-列-宫 是否冲突；最高位：是否反白
	//返回-2表示有非法数字，返回1表示数独冲突


	int result = 0, thisResult;
	int currNum;
	int currNonu;	//用以位运算(10进制)操作查重
	int posOccu;

	//行、列查重
	for (int m = 0; m < 2 && result >= 0; m++)
	{
		for (int j = 1; j <= 9 && result >= 0; j++)
		{
			currNonu = 0x0;
			thisResult = 0;
			for (int i = 1; i <= 9 && result >= 0; i++)
			{
				currNum = m == 0 ? (s->t[j][i]) : (s->t[i][j]);
				if (m == 0 && (currNum < 0 || currNum > 9))
				{
					result = -2;
					break;
				}
				if (currNum == 0)
					continue;
				if (posOccu = decExtract(currNonu, currNum - 1))
				{
					result++;
					thisResult = 1;
					if (overMap)
					{
						if (m == 0)
						{
							overMap->t[j][i] |= 0x01 << 2;
							overMap->t[j][posOccu] |= 0x01 << 2;
						}
						else
						{
							overMap->t[i][j] |= 0x01 << 1;
							overMap->t[posOccu][j] |= 0x01 << 1;
						}
					}

				}
				else
				{
					decSet(&currNonu, currNum - 1, i);
				}

			}
			if (thisResult)
			{
				if (overMap)
					for (int i = 1; i <= 9 && result >= 0; i++)
					{
						if (m == 0)
						{
							overMap->t[j][i] |= 0x01 << 4;
						}
						else
						{
							overMap->t[i][j] |= 0x01 << 4;
						}
					}
			}
		}
	}
	
	if (result < 0)
		return result;

	//宫查重
	for (int j = 1; j <= 9 && result >= 0; j++)  //宫号
	{
		currNonu = 0x0;
		thisResult = 0;
		for (int i = 1; i <= 9 && result >= 0; i++)  //格号
		{
			int translatedJ = (j - 1) / 3 * 3 + 1 + (i - 1) / 3;
			int translatedI = (j - 1) % 3 * 3 + 1 + (i - 1) % 3;
			currNum = s->t[translatedJ][translatedI];

			if (currNum == 0)
				continue;

			if (posOccu = decExtract(currNonu, currNum - 1))
			{
				result++;
				thisResult = 1;
				if (overMap)
				{
					overMap->t[translatedJ][translatedI] |= 0x01;
					overMap->t[(j - 1) / 3 * 3 + 1 + (posOccu - 1) / 3][(j - 1) % 3 * 3 + 1 + (posOccu - 1) % 3] |= 0x01;
				}

			}
			else
			{
				decSet(&currNonu, currNum - 1, i);
			}

		}
		if (thisResult)
		{
			if (overMap)
				for (int i = 1; i <= 9 && result >= 0; i++)
				{
					int translatedJ = (j - 1) / 3 * 3 + 1 + (i - 1) / 3;
					int translatedI = (j - 1) % 3 * 3 + 1 + (i - 1) % 3;
					overMap->t[translatedJ][translatedI] |= 0x01 << 4;
				}
		}
	}
	return result;
}