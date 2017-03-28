/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max)()

void printLight(short light, const int lightnum)
{
	short mask = 0x0001;
	short result;
	const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	for (int i = 0; i < lightnum; i++)
	{
		cout << setw(4) << letters[i];
	}
	cout << endl;
	for (int i = 0; i < lightnum; i++)
	{
		result = light & mask;
		cout << setw(4) << (result ? "ON" : "OFF");
		light >>= 1;
	}
	cout << endl;
}


int main()
{
	const int len = 10;
	const int lightnum = 10;
	char input[len] = { 0 };
	short light = 0x0, lastLight = 0x0;
	int lightCurr;
	int lightToBe;
	short lightOperand;

	cout << "初始开关状态：" << endl;
	printLight(light, lightnum);
	cout << endl;

	for (;;)
	{
		lightCurr = -1;
		lightToBe = -1;
		cout << "请输入对灯光的操作，如a on：";
		cin.get(input, 6);
		cin.clear();
		cin.ignore(FS_MAX_LENGTH, '\n');

		_strlwr_s(input);  //Compability

		if (!strcmp(input, "end"))
		{
			break;
		}
		
		if (input[0] < 'a' || input[0] > 'a' + lightnum - 1)
		{
			cout << "灯号错误。" << endl;
			continue;
		}

		lightCurr = input[0] - 'a';

		if (strcmp(&input[2], "on") == 0)
			lightToBe = 1;
		if (strcmp(&input[2], "off") == 0)
			lightToBe = 0;

		if (lightToBe == -1 || input[1] != ' ')
		{
			cout << "操作错误。" << endl;
			continue;
		}

		lightOperand = 0x0001;
		lightOperand <<= lightCurr;
		

		if (lightToBe)
		{
			light |= lightOperand;
		}
		else
		{
			light &= ~lightOperand;
		}
		cout << endl << "short数据：";
		cout << "0x" << hex << setfill('0') << setw(4) << light << setfill(' ') << endl;

		if (lastLight == light)
		{
			cout << "开关的状态没有改变。" << endl;
		}
		else
		{
			printLight(light, lightnum);
		}

		lastLight = light;
		cout << endl;
		//break;
	}
	return 0;
}
//