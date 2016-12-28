/* 1652270 计算机2班 冯舜 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
using namespace std;
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max())

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

int main()
{
	//REINPUT:
	char *(monthName[13]) = {"None", "January", "Feburary","March","April","May","June","July","August","September","October","November","December" };
	int m;
	inputThing(&m, "请输入月份，用阿拉伯数字表示：", "输入非法！", "invalid", 1, 12, true);
	cout << *(monthName+m) << endl;
	//goto REINPUT;
	return 0;
}
