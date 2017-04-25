#include <iostream>
using namespace std;



struct Sudoku
{
	short t[11][11];
};

struct SudokuValue
{
	short t[11][11];
};
int lengthOfValueSquare(short s, int *theOnly);
int gridEliminate(SudokuValue *v, int j, int i, int d);
int squareAssign(SudokuValue *v, int j, int i, int d);
int parseGrid(int sudoku[11][11], SudokuValue *v);
void shuffleArr(int * arrange, int len);
int depthSearch(SudokuValue *v);

int solving_sudoku(int sudoku[9][9])
{
	int status, theOnly = 0;
	int sudokuExp[11][11];
	SudokuValue v;
	for (int j = 1; j <= 9; j++)
	{
		for (int i = 1; i <= 9; i++)
		{
			sudokuExp[j][i] = sudoku[j - 1][i - 1];
		}
	}

	status = parseGrid(sudokuExp, &v);
	if (status == -1)
	{
		return 0;
	}
	else
	{
		status = depthSearch(&v);
		if (status == -1)
		{
			//memory not enough
			return 0;
		}
		else if (status == -2)
		{
			//no solution
			return 0;
		}
		else
		{
			for (int j = 1; j <= 9; j++)
			{
				for (int i = 1; i <= 9; i++)
				{
					if (lengthOfValueSquare(v.t[j][i], &theOnly) == 1)
					{
						sudoku[j-1][i-1] = theOnly;
					}
					else
						sudoku[j-1][i-1] = 0;
				}
			}
			return 1;
		}
	}
}

//返回某个SudokuValue元素有多少位是1。（可填入）
int lengthOfValueSquare(short s, int *theOnly)
{
	int len = 0;
	for (int i = 1; i <= 9; i++)
	{
		if (s & (1 << i))
		{
			len++;
			if (theOnly)
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
			for (jp = 1; jp <= 9 && status != -2; jp++)
			{
				if (jp != j)
					status = gridEliminate(v, jp, i, theOnly);
			}
			//列
			for (ip = 1; ip <= 9 && status != -2; ip++)
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

int parseGrid(int sudoku[11][11], SudokuValue *v)
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
			if (sudoku[j][i] != 0)
			{
				status = squareAssign(v, j, i, sudoku[j][i]);
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

int depthSearch(SudokuValue *v)
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
			status = depthSearch(vp);
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