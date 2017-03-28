/* 1652270 �����2�� ��˴ */
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

	cout << "��ʼ����״̬��" << endl;
	printLight(light, lightnum);
	cout << endl;

	for (;;)
	{
		lightCurr = -1;
		lightToBe = -1;
		cout << "������Եƹ�Ĳ�������a on��";
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
			cout << "�ƺŴ���" << endl;
			continue;
		}

		lightCurr = input[0] - 'a';

		if (strcmp(&input[2], "on") == 0)
			lightToBe = 1;
		if (strcmp(&input[2], "off") == 0)
			lightToBe = 0;

		if (lightToBe == -1 || input[1] != ' ')
		{
			cout << "��������" << endl;
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
		cout << endl << "short���ݣ�";
		cout << "0x" << hex << setfill('0') << setw(4) << light << setfill(' ') << endl;

		if (lastLight == light)
		{
			cout << "���ص�״̬û�иı䡣" << endl;
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