/*1652270 计算机2班 冯舜*/
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#define UNIT 16
#define UNITGAP 8
#define ADDRLEN 8
#define INPUTLEN 200
int main(int argc, char **argv)
{
	char *fileName;
	char fileNameBuffer[INPUTLEN + 1];
	char currLine[UNIT + 1] = { 0 };
	if (argc == 2)
	{
		fileName = argv[1];
	}
	else
	{
		cout << "请输入文件路径（只取前" << INPUTLEN << "个字符）：";
		cin.getline(fileNameBuffer, INPUTLEN + 1);
		fileName = fileNameBuffer;
	}

	ifstream fin;
	int jumpOut;
	fin.open(fileName, ios::in | ios::binary);
	if (!fin.is_open())
	{
		cout << "文件 " << fileName << " 打开失败！" << endl;
		return 1;
	}
	cout << "[ " << fileName << " ]" << endl;
	cout << setw(ADDRLEN + 1) << "";


	for (int i = 0; i < UNIT; i++)
	{
		if (i && i % UNITGAP == 0)
		{
			cout << setw(2) << "-";
		}
		cout << setw(3) << setiosflags(ios::uppercase) << hex << i;
	}
	cout << endl << setfill('0');
	while (!fin.eof())
	{
		cout << setw(ADDRLEN) << fin.tellg() << ": ";
		
		for (int i = 0; i < UNIT; i++)
		{
			jumpOut = -1;
			currLine[i] = fin.get();
			if (fin.eof())
			{
				jumpOut = i;
				cout << setfill(' ') << setw((UNIT - i) * 3 + 2 * ((UNIT - i) / UNITGAP)) << "";
				cout << setfill('0');
				break;
			}

			if (i && i % UNITGAP == 0)
			{
				cout << " -";
			}
			if(i)
				cout << " ";
			cout << setw(2) << (unsigned int)(unsigned char)currLine[i]  ;
		}
		cout << "   ";
		for (int i = 0; i < UNIT; i++)
		{
			if (i == jumpOut)
				break;
			if (currLine[i] >= 33 && currLine[i] <= 126)
				cout << currLine[i];
			else
				cout << '.';
		}
		cout << endl;
		fin.peek();
	}
	fin.close();
	cout << endl;
	if (!(argc == 2))
	{
		system("pause");
	}
	return 0;
}