/*1652270 �����2�� ��˴*/
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#define UNIT 16			//ÿ�е��ֽ���
#define UNITGAP 8		//�����ٸ��ֽڴ�һ��"-"
#define ADDRLEN 8		//���ĵ�ǰ��ַ����
#define INPUTLEN 200	//�����ļ����������

int main(int argc, char **argv)
{
	char *fileName;
	char fileNameBuffer[INPUTLEN + 1];		//�洢������ļ���
	unsigned char currLine[UNIT + 1] = { 0 };		//�洢ÿ�е��ֽ�
	//system("chcp 437");
	if (argc == 2)
	{
		fileName = argv[1];
	}
	else
	{
		cout << "�������ļ�·����ֻȡǰ " << INPUTLEN << " ���ַ�����";
		cin.getline(fileNameBuffer, INPUTLEN + 1);
		fileName = fileNameBuffer;
	}

	ifstream fin;
	int jumpOut;		//�ļ���ĳһ�еĵ� jumpOut ���ֽڴ�����
	fin.open(fileName, ios::in | ios::binary);
	if (!fin.is_open())
	{
		cout << "�ļ� " << fileName << " ��ʧ�ܣ�" << endl;
		return 1;
	}
	cout << "[ " << fileName << " ]" << endl;
	cout << setw(ADDRLEN + 1) << "";

	//��ͷ a - f
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
		cout << setw(ADDRLEN) << fin.tellg() << ": ";		//��ӡ��ǰ��ַ
		
		for (int i = 0; i < UNIT; i++)						//���뵱ǰ�е�ÿһ���ֽ�
		{
			jumpOut = -1;									//���ļ�û�н�����jumpOutĬ����Ϊ-1
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

		for (int i = 0; i < UNIT; i++)						//��ӡ�洢��currLine�е�ԭ���ֽ�
		{
			if (i == jumpOut)
				break;
			if (currLine[i] >= 33 && currLine[i] <= 126)
				cout << currLine[i];
			else
				cout << '.';
		}
		cout << endl;
		fin.peek();		//��Ҫ�����ļ���ĳһ�н�βǡ�ý�������ʱeof��Ϊtrue����peekһ�»Ὣeof��Ϊtrue��
	}
	fin.close();
	cout << endl;
	if (!(argc == 2))
	{
		system("pause");
	}
	return 0;
}