/* 1652270 计算机2班 冯舜 */
/*AWESOMESudokuSJProject - 90-b2-base.cpp*/
#include "90-b2.h"

//添加一个composition节点，将链表的末尾指针赋值为新节点的地址。
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

//等价于数组中的取composition[n]。
composition* compNext(composition * const p, int n)
{
	composition *q = p;
	for (; n > 0; n--)
	{
		q = q->next;
	}
	return q;
}

//等价于数组中的取composition[-n]。
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

//返回节点数目。
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

//返回head到p之间的节点数目。
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

//把head及之后的节点全部释放，抛弃。
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

int itemCount(item *head)
{
	item *q = head;
	int count = 0;
	for (; q; count++)
	{
		q = q->next;
	}
	return count;
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
	cout << setiosflags(ios::left);
	while (p)
	{
		q = p->next;
		cout << setw(25) << p->text << "";
		if (count % 3 == 2)
		{
			cout << endl;
		}
		count++;
		p = q;
	}
	cout << resetiosflags(ios::left);

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

//Sudoku棋盘区域置零。
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

//打印数独的字符模式。
int charSudoku(Sudoku *s, Sudoku *initial, Sudoku *o)
{
	int X, Y;
	int currFore, currBack;

	getxy(hout, X, Y);
	restoreColor();
	cout << "-+-a-b-c-+-d-e-f-+-g-h-i-+";
	//cout << setiosflags(ios::right);
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
				currBack = commonColor[6];
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
	restoreColor();
	return 0;
}

//取出某十进制位模式数的右第n位。
int decExtract(int dec, int n)
{
	for (int i = 0; i < n; i++)
	{
		dec /= 10;
	}
	return dec % 10;
}

//设置某十进制位模式数的右第n位。
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
	//overMap中每个格为一个bitmap，次高位->低位: 行-列-宫 是否冲突；最高位：是否将底色标记为冲突
	//返回-2表示有非法数字，返回1及以上表示数独冲突


	int result = 0, thisResult, lastResult;
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
			lastResult = result;
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
					//position Ocuupied, Conflict Exist
					thisResult = 1;
					result = lastResult + thisResult;
					if (overMap)
					{
						//mark the conflict on the overlay map on bit << 2
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
					//position not Ocuupied, so Occupy it
					decSet(&currNonu, currNum - 1, i);
				}

			}
			if (thisResult)
			{
				if (overMap)  //mark this column/line with bit << 4 = 1 to display the entire column/line in red background
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
		lastResult = result;
		for (int i = 1; i <= 9 && result >= 0; i++)  //格号
		{
			int translatedJ = (j - 1) / 3 * 3 + 1 + (i - 1) / 3;
			int translatedI = (j - 1) % 3 * 3 + 1 + (i - 1) % 3;
			currNum = s->t[translatedJ][translatedI];

			if (currNum == 0)
				continue;

			if (posOccu = decExtract(currNonu, currNum - 1))
			{
				thisResult = 1;
				result = lastResult + thisResult;
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

int *getGridPointer(Sudoku *s, const Coord c)
{
	return &(s->t[c.y][c.x]);
}

int *getInputAble(Board *b)
{
	//返回一个数组头指针，展示b->sel处可以填入的数字，以0做结束
	short occupied = 0x0;
	short mask = 0x1;
	static int inputAble[10] = { 0 };
	int n, *p = inputAble;
	//判断行
	for (int j = 1; j <= 9; j++)
	{
		if(j != b->sel.y)
			occupied |= (mask << b->s->t[j][b->sel.x]);
	}
	//判断列
	for (int i = 1; i <= 9; i++)
	{
		if(i != b->sel.x)
			occupied |= (mask << b->s->t[b->sel.y][i]);
	}
	//判断宫
	for (int k = 0; k < 9; k++)
	{
		if((b->sel.y - 1) / 3 * 3 + 1 + k / 3 != b->sel.y && (b->sel.x - 1) / 3 * 3 + 1 + k % 3 != b->sel.x)
			occupied |= (mask << b->s->t[(b->sel.y - 1) / 3 * 3 + 1 + k / 3][(b->sel.x - 1) / 3 * 3 + 1 + k % 3]);
	}
	for (n = 1; n <= 9; n++)
	{
		if ((occupied & (mask << n)) == 0)
		{
			*p++ = n;
		}
	}
	*p = 0;
	return inputAble;
}

/*
以下是约束-扩展Constraint Propagation + DFS算法算数独的相关函数。
请参考：http://norvig.com/sudoku.html
*/
//返回某个SudokuValue元素有多少位是1。（可填入）
int lengthOfValueSquare(short s, int *theOnly)
{
	int len = 0;
	for (int i = 1; i <= 9; i++)
	{
		if (s & (1 << i))
		{
			len++;
			if(theOnly)
				*theOnly = i;
		}
	}
	return len;
}

int gridEliminate(SudokuValue *v, int j, int i, int d)
{
	int theOnly, jp, ip, theOnlyJ, theOnlyI;
	int status = 0, count = 0;
	short onlyMask = 1 << d;
	if ((v->t[j][i] & onlyMask))
	{
		v->t[j][i] &= ~onlyMask;
		if (!v->t[j][i])
			return -2;
		else if (lengthOfValueSquare(v->t[j][i], &theOnly) == 1)
		{
			status = 0;
			//Eliminate From Peers
			//行
			for ( jp = 1; jp <= 9 && status != -2; jp++)
			{
				if (jp != j)
					status = gridEliminate(v, jp, i, theOnly);
			}
			//列
			for ( ip = 1; ip <= 9 && status != -2; ip++)
			{
				if (ip != i)
					status = gridEliminate(v, j, ip, theOnly);
			}
			//宫
			for (int k = 0; k < 9 && status != -2; k++)
			{
				jp = (j - 1) / 3 * 3 + 1 + k / 3;
				ip = (i - 1) / 3 * 3 + 1 + k % 3;
				if (jp != j && ip != i)
					status = gridEliminate(v, jp, ip, theOnly);
			}
			if (status == -2)
				return -2;
		}

		//See if a place in a unit can only put 1 digit
		//行
		count = 0;
		for (jp = 1; jp <= 9 && status != -2; jp++)
		{
			if (v->t[jp][i] & onlyMask)
			{
				count++;
				theOnlyJ = jp;
			}
		}
		if (count == 0)
			return -2;
		else if (count == 1)
		{
			status = squareAssign(v, theOnlyJ, i, d);
			if (status == -2)
				return -2;
		}
		//列
		count = 0;
		for (ip = 1; ip <= 9 && status != -2; ip++)
		{
			if (v->t[j][ip] & onlyMask)
			{
				count++;
				theOnlyI = ip;
			}
		}
		if (count == 0)
			return -2;
		else if (count == 1)
		{
			status = squareAssign(v, j, theOnlyI, d);
			if (status == -2)
				return -2;
		}
		//宫
		count = 0;
		for (int k = 0; k < 9 && status != -2; k++)
		{
			jp = (j - 1) / 3 * 3 + 1 + k / 3;
			ip = (i - 1) / 3 * 3 + 1 + k % 3;
			
			if (v->t[jp][ip] & onlyMask)
			{
				count++;
				theOnlyI = ip;
				theOnlyJ = jp;
			}
		}
		if (count == 0)
			return -2;
		else if (count == 1)
		{
			status = squareAssign(v, theOnlyJ, theOnlyI, d);
			if (status == -2)
				return -2;
		}
	}
	return 0;
}

int squareAssign(SudokuValue *v, int j, int i, int d)
{
	int status;
	for (int dc = 1; dc <= 9; dc++)
	{
		if (dc == d || !(v->t[j][i] & (1 << dc)))
			continue;
		status = gridEliminate(v, j, i, dc);
		if (status == -2)
			return -2;
	}
	return 0;
}

int parseGrid(Sudoku *s, SudokuValue *v)
{
	int status;
	for (int j = 1; j <= 9; j++)
	{
		for (int i = 1; i <= 9; i++)
		{
			v->t[j][i] = 0x0;
			for (int d = 1; d <= 9; d++)
				v->t[j][i] |= (1 << d);
		}
	}

	for (int j = 1; j <= 9; j++)
	{
		for (int i = 1; i <= 9; i++)
		{
			if (s->t[j][i] != 0)
			{
				status = squareAssign(v, j, i, s->t[j][i]);
				if (status == -2)
					return -2;
			}
		}
	}
	return 0;
}

void shuffleArr(int * arrange, int len)
{
	int swapTo, tmpVar;
	for (int i = 1; i < len; i++)
	{
		swapTo = rand() % (len - i);
		tmpVar = arrange[len - i];
		arrange[len - i] = arrange[swapTo];
		arrange[swapTo] = tmpVar;
	}
}

int depthSearch(SudokuValue *v, int *dfsArgs, Board *b)
{
	int minLen = 10, currLen, status;
	int minJ, minI;
	SudokuValue *vp;
	bool win = true;
	int arrange[] = { 1,2,3,4,5,6,7,8,9 };
	int d;

	shuffleArr(arrange, 9);

	for (int j = 1; j <= 9 && win; j++)
	{
		for (int i = 1; i <= 9 && win; i++)
		{
			if (lengthOfValueSquare(v->t[j][i], NULL) != 1)
			{
				win = false;
			}
		}
	}

	if (win)
	{
		return 0;
	}

	for (int j = 1; j <= 9; j++)
	{
		for (int i = 1; i <= 9; i++)
		{
			currLen = lengthOfValueSquare(v->t[j][i], NULL);
			if (currLen < minLen && currLen != 1)
			{
				minLen = currLen;
				minJ = j;
				minI = i;
			}
		}
	}
	
	for (int dx = 1; dx <= 9; dx++)
	{
		d = arrange[dx - 1];
		if (v->t[minJ][minI] & (1 << d))
		{
			vp = new(nothrow) SudokuValue;
			if (!vp)
				return -1;
			*vp = *v;
			status = squareAssign(vp, minJ, minI, d);
			if (status == -2)
			{
				delete vp;
				continue;
			}
			(dfsArgs[1])++;
			b->sel.x = minI;
			b->sel.y = minJ;
			if (dfsArgs[0] && dfsArgs[1] % dfsArgs[0] == 0)
			{
				updateBoardAuto(b, vp, dfsArgs);
				if (debug)
					getchar();
			}
			if (dfsArgs[4])
			{
				printDFSProgress(dfsArgs, b->bulletin);
			}
			dfsArgs[2]++;
			if (dfsArgs[2] > dfsArgs[3])
				dfsArgs[3] = dfsArgs[2];
			status = depthSearch(vp, dfsArgs, b);
			dfsArgs[2]--;
			if (status == -1)
			{
				delete vp;
				return -1;
			}
			if (status != -2)
			{
				*v = *vp;
				delete vp;
				return 0;
			}
			delete vp;
		}
	}
	return -2;
}