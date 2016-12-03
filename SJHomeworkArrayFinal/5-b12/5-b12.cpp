/* 1652270 计算机2班 冯舜 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define maxLen 30
#define strToCom 3

int outer_function(int param)
{
	return param;
}

int main()
{
	//REINPUT:
	char stringS[strToCom][maxLen] = {'\0'};
	char tmpStr[maxLen] = { '\0' };
	bool valid;

	cout << "请依次输入 " << strToCom << " 个字符串进行比较，每个不超 " << maxLen - 1 << " 个字符，空格隔开：";
	for (int i = 0; i < strToCom; i++)
	{
		do
		{
			valid = true;
			cin >> stringS[i];

			if (!cin.good()) {
				valid = false;
				cout << "输入非法，请从第 " << i+1 << " 个字符串开始输入。" << endl;
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
		} while (!valid);

	} 

	if (strcmp(stringS[1], stringS[2]) > 0)
	{
		strcpy(tmpStr, stringS[2]);
		strcpy(stringS[2], stringS[1]);
		strcpy(stringS[1], tmpStr);
	}

	if (strcmp(stringS[0], stringS[1]) < 0)
	{
		cout << stringS[0] << " " << stringS[1] << " " << stringS[2] << endl;
	}
	else
	{
		cout << stringS[1] << " " << stringS[0] << " " << stringS[2] << endl;
	}
	
	return 0;
}
