/* 1652270 �����2�� ��˴ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
using namespace std;
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max())
#define FS_ARR_MAXLEN 20


template <typename T>
void inputThing(T* p, const char * promptText, const char * cinUngoodText, const char * outLimitText, T lowerLimit, T upperLimit, bool clearBuffer = false)
{
	bool valid;
	do
	{
		valid = true;
		cout << promptText;
		cin >> *p;

		if (!cin.good())
		{
			valid = false;
			cout << cinUngoodText << endl;
		}
		else if (*p > upperLimit || *p < lowerLimit)
		{
			valid = false;
			cout << outLimitText << endl;
		}

		if (!valid)
		{
			cin.clear();
			cin.ignore(FS_MAX_LENGTH, '\n');
		}

	} while (!valid);
	if (clearBuffer)
		cin.ignore(FS_MAX_LENGTH, '\n');
}

void standardInput(int* p, int pLen, const char * varName, int lowerLimit = 0, int upperLimit = 1048576, bool clearBuffer = false, bool displayPrompt = true)
{
	char promptText[80] = { '\0' };
	sprintf(promptText, "������ %s ��ֵ(%d-%d)��", varName, lowerLimit, upperLimit);
	for (int *p2 = p; p2 - p<pLen; p2++)
		inputThing(p2, displayPrompt ? promptText : "", "�������ʹ������������롣", "���볬����Χ������������", lowerLimit, upperLimit, clearBuffer);
}

void standardInput(double* p, int pLen, const char * varName, double lowerLimit = 0, double upperLimit = INFINITY, bool clearBuffer = false, bool displayPrompt = true)
{
	char promptText[80] = { '\0' };
	sprintf(promptText, "������ %s ��ֵ(%lf-%lf)��", varName, lowerLimit, upperLimit);
	for (double *p2 = p; p2 - p<pLen; p2++)
		inputThing(p, displayPrompt ? promptText : "", "�������ʹ������������롣", "���볬����Χ������������", lowerLimit, upperLimit, clearBuffer);
}

template <typename T, typename T2>
void standardInput(T *p, int pLen, const char * varName, T2 lowerLimit = 0, T2 upperLimit = 0, bool clearBuffer = false, bool displayPrompt = false)
{
	char promptText[80] = { '\0' };
	sprintf(promptText, "������ %s ��ֵ��", varName);
	//for(T p2 = *p;p2 - *p < pLen; p2++)
	for (T* p2 = p; p2 - p < pLen; p2++)
		standardInput(*p2, sizeof(*p) / sizeof(**p), varName, lowerLimit, upperLimit, clearBuffer, false);
}

void displayArr(int * p, int n = 1, bool bracket = false)
{
	cout << "{";
	int *pCopy = p;
	for (; pCopy < p + n; pCopy++)
	{
		cout << " " << *(pCopy) << ((pCopy < p + n - 1) ? "," : "");
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

void loopMove(int *p, int n, int m)
{
	for (int *p2 = p + n - 1; p2 >= p; p2--)
	{
		*(p2 + m) = *p2;
	}
	for (int *p2 = p; p2 < p+m; p2++)
	{
		*p2 = *(p2+n);
	}
}


int main()
{
	//REINPUT:
	int m, n;
	int arr[FS_ARR_MAXLEN * 2];
	//freopen("Text.txt", "r", stdin);
	do {
		standardInput(&m,1, "m", 0, FS_ARR_MAXLEN);
		standardInput(&n,1, "n", 0, FS_ARR_MAXLEN);
		if (m >= n)
			cout << "m >= n�����������롣" << endl;
	} while (m >= n);
	
	cout << "���������� " << n << " ������" << endl;
	for (int *p = arr; p - arr < n; p++)
	{
		inputThing(p, "", "�������ʹ�����Ӹ�����ʼ�������롣", "������Χ����Ӹ�����ʼ�������롣", INT_MIN, INT_MAX, false);
	}
	cout << "ԭ���飺\t\t";
	displayArr(arr, n);
	cout << endl;

	loopMove(arr, n, m);
	cout << "�䶯�������飺\t\t";
	displayArr(arr, n);
	cout << endl;

	//goto REINPUT;
	return 0;
}
