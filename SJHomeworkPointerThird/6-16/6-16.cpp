/* 1652270 �����2�� ��˴ */
#include <iostream>

using namespace std;
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max())
#define FS_STR_MAX 10

void displayArr(int * p, int n, bool bracket)
{
	if(bracket)
		cout << "{";
	int *pCopy = p;
	for (; pCopy < p + n; pCopy++)
	{
		cout << " " << *(pCopy) << ((pCopy < p + n - 1) ? "," : "");
	}
	if(bracket)
		cout << " }";
}



int main()
{
	//REINPUT:
	//freopen("Text.txt", "r", stdin);

	char c ;
	int numArr[FS_STR_MAX], thisNum = 0, *p=numArr;
	bool a = false;
	while (c = getchar())
	{
		if (c < '0' || c >'9')
		{
			if (a)
			{
				*(p++) = thisNum;
				thisNum = 0;
				a = false;
			}
			
		}
		else
		{
			a = true;
			thisNum = thisNum * 10 + c - '0';
		}
		if (c == '\n' || p-numArr>=10)
		{
			if (p - numArr >= 10 && a)
				cout << "����̫���ˣ�" << endl;
			break;
		}
	}
	cout << "��ͳ�Ƶ� " << int(p - numArr) << " �����������Ƿֱ�Ϊ��\n";
	displayArr(&numArr[0], p - numArr, false);
	cout << endl;
	//goto REINPUT;
	return 0;
}
