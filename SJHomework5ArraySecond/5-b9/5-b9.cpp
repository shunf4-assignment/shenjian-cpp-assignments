/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <fstream>
using namespace std;

bool check(int matrix[9][9], int mode)
{
	int checkSingle;
	int twoPower[] = { 1,2,4,8,16,32,64,128,256 };
	int thisNum;
	bool partValid = true;

	for (int i = 0; i < 9; i++)
	{
		checkSingle = 0;
		for (int j = 0; j < 9; j++)
		{
			if(mode == 0)
				thisNum = matrix[i][j];
			else if(mode == 1)
				thisNum = matrix[j][i];
			else
				thisNum = matrix[i % 3 * 3 + j % 3][i / 3 * 3 + j / 3];
			if (checkSingle / twoPower[thisNum - 1] % 2)
			{
				cout << "�� " << i+1;
				if (mode == 0)
					cout << " ��";
				else if (mode == 1)
					cout << " ��";
				else
					cout << " ���Ź���";
				cout << "�� " << j + 1;
				if (mode == 0)
					cout << " �е���";
				else if (mode == 1)
					cout << " �е���";
				else
					cout << " ����";
				cout << "�������ظ��� " << thisNum << endl;
				partValid = false;
			}
			else
				checkSingle += twoPower[thisNum - 1];
		}
	}
	return partValid;
}

int main()
{
	ifstream f;
	int matrix[9][9], currNum;
	bool sudokuValid = true;

	f.open("shudu.txt", ios::in);
	if (f.is_open() == 0)
	{
		cout << "���ļ�ʧ�ܡ�" << endl;
		return -1;
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			f >> currNum;
			matrix[i][j] = currNum;
			if (!f.good())
			{
				cout << "��������ʧЧ�����shudu.txt��" << endl;
				return -1;
			}
			if (currNum > 10 || currNum < 1)
			{
				cout << "�������ݳ�����Χ�����shudu.txt��" << endl;
				return -1;
			}
		}
	}

	//�����С����š��Ź����Ƿ����Ҫ��
	for (int mode = 0; mode < 3; mode++)
		if (!check(matrix, mode))
		{
			sudokuValid = false;
		}
	if (sudokuValid)
		cout << "�����������Ҫ��" << endl;
	else
		cout << "�������������Ҫ��" << endl;
	return 0;
}
