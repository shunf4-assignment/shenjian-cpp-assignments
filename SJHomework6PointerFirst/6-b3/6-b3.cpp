/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include <iostream>
using namespace std;
#define C_LAL 6
#define C_LBL 8
#define C_LCL C_LAL+C_LBL

void displayArr(int * p, int n = 1, bool bracket = false)
{
	cout << "{";
	int *pCopy = p;
	for (; pCopy < p + n && *pCopy != -1; pCopy++)
	{
		cout << " " << *(pCopy) << ((pCopy < p + n - 1 && *(pCopy+1) != -1) ? "," : "");
	}
	cout << " }";
}

template <typename T>
void displayArr(T * p, int n = 1, bool bracket = false)
{
	if (bracket)
		cout << "{";
	T *pCopy = p;
	for (; pCopy < p + n;)
	{
		cout << " ";
		displayArr(*pCopy, sizeof(*pCopy) / sizeof(**pCopy), true);
		if (pCopy < p + n - 1)
			cout << ",";
		*pCopy++;

	}
	if (bracket)
		cout << " }";
}

void merge(int *la, int *lb, int *lc)
{
	int *bigger;
	for (; *la != -1 || *lb != -1;)
	{
		if (*la != -1 && *lb != -1)
		{
			bigger = (*la > *lb) ? (la++) : ((*la == *lb) ? (la++, lb++) : (lb++));
			if (*(lc-1) != *bigger)
			{
				*(lc++) = *bigger;
			}
		}
		else
			*(lc++) = (*la == -1) ? (*(lb++)) : (*(la++));
	}
	*lc = -1;
}

int main()
{
	int la[C_LAL + 1] = { 22,22,18,16,5,4,-1 };
	int lb[C_LBL + 1] = { 20,18,15,10,9,8,7,6,-1 };
	int lc[C_LCL + 1] = { 0 };
	merge(la, lb, lc);
	cout << "list a = ";
	displayArr(&la);
	cout << endl;

	cout << "list b = ";
	displayArr(&lb);
	cout << endl;

	cout << "list c = ";
	displayArr(&lc);
	cout << endl;

	return 0;
}
