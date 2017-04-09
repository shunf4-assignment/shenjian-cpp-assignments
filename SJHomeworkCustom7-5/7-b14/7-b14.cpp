/*1652270 计算机2班 冯舜*/
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#define UNIT 16			//每行的字节数
#define UNITGAP 8		//隔多少个字节打一个"-"
#define ADDRLEN 8		//左侧的当前地址长度
#define INPUTLEN 200	//输入文件名的最长长度

int main(int argc, char **argv)
{
	char *fileName;
	char fileNameBuffer[INPUTLEN + 1];		//存储输入的文件名
	unsigned char currLine[UNIT + 1] = { 0 };		//存储每行的字节
	//system("chcp 437");
	if (argc == 2)
	{
		fileName = argv[1];
	}
	else
	{
		cout << "请输入文件路径（只取前 " << INPUTLEN << " 个字符）：";
		cin.getline(fileNameBuffer, INPUTLEN + 1);
		fileName = fileNameBuffer;
	}

	ifstream fin;
	int jumpOut;		//文件在某一行的第 jumpOut 个字节处结束
	fin.open(fileName, ios::in | ios::binary);
	if (!fin.is_open())
	{
		cout << "文件 " << fileName << " 打开失败！" << endl;
		return 1;
	}
	cout << "[ " << fileName << " ]" << endl;
	cout << setw(ADDRLEN + 1) << "";

	//表头 a - f
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
		cout << setw(ADDRLEN) << fin.tellg() << ": ";		//打印当前地址
		
		for (int i = 0; i < UNIT; i++)						//读入当前行的每一个字节
		{
			jumpOut = -1;									//若文件没有结束，jumpOut默认置为-1
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

			cout << setw(2) << (unsigned int)currLine[i]  ;
		}

		cout << "   ";

		for (int i = 0; i < UNIT; i++)						//打印存储在currLine中的原样字节
		{
			if (i == jumpOut)
				break;
			if (currLine[i] >= 33 && currLine[i] <= 126)
				cout << currLine[i];
			else
				cout << '.';
		}
		cout << endl;
		fin.peek();		//重要。若文件在某一行结尾恰好结束，此时eof不为true。但peek一下会将eof置为true。
	}
	fin.close();
	cout << endl;
	if (!(argc == 2))
	{
		system("pause");
	}
	return 0;
}