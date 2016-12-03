/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <time.h>
using namespace std;
#define maxLen 16

int main()
{
	void generatePW(char result[], int digit);
	void insertArray(char ar[], char el, int insertPos, int lastPos);
	char result[maxLen + 1] = { '\0' };
	time_t t;
	time(&t);
	srand((unsigned int)t);
	int d;

	while (true)
	{
		cout << "请输入要生成的密码位数(12-16): ";
		cin >> d;
		if (!cin.good() || d < 12 || d > maxLen)
		{
			cout << "输入非法或超出范围，请重新输入。" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else
		{
			break;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		generatePW(result, d);
		cout << result << endl;
	}
		
	return 0;
}

template <typename T>
void insertArray(T ar[], T el, int insertPos, int lastPos)
{
	for (int i = lastPos; i >= insertPos; i--)
	{
		ar[i + 1] = ar[i];
	}
	ar[insertPos] = el;
}

void generatePW(char result[], int digit)
{
	char thisChar;
	char lastChar;
	int currDigit = digit - 8;

	for (int i = 0; i < digit - 8; i++)
	{
		thisChar = char(rand() / 32676. * (126 + 1 - 33) + 33);
		result[i] = thisChar;
	}
	char classList[] = { 'Z','A','z','a','9','0' };
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 2; i++)
		{
			thisChar = char(rand() / 32676. * (classList[j * 2] + 1 - i - classList[j * 2 + 1]) + classList[j * 2 + 1]);
			thisChar += (i != 0) && (thisChar >= lastChar);
			insertArray(result, thisChar, int(rand() / 32676. * (currDigit)), currDigit - 1);
			currDigit++;
			lastChar = thisChar;
		}
	}
	for (int i = 0; i < 2; i++)
	{
		thisChar = char(rand() / 32676. * (126 - 33 + 1 - 26 - 26 - 10) + 33);
		thisChar += (i != 0) && (thisChar >= lastChar);
		lastChar = thisChar;
		thisChar += (thisChar >= '0') ? 10 : 0;
		thisChar += (thisChar >= 'A') ? 26 : 0;
		thisChar += (thisChar >= 'a') ? 26 : 0;
		insertArray(result, thisChar, int(rand() / 32676. * (currDigit)), currDigit - 1);
		currDigit++;
	}
	result[currDigit] = '\0';
}

