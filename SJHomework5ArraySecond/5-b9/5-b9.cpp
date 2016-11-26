/* 1652270 计算机2班 冯舜 */
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
				cout << "第 " << i+1;
				if (mode == 0)
					cout << " 行";
				else if (mode == 1)
					cout << " 列";
				else
					cout << " 个九宫格";
				cout << "第 " << j + 1;
				if (mode == 0)
					cout << " 列的数";
				else if (mode == 1)
					cout << " 行的数";
				else
					cout << " 个数";
				cout << "出现了重复的 " << thisNum << endl;
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
		cout << "打开文件失败。" << endl;
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
				cout << "输入数据失效。检查shudu.txt。" << endl;
				return -1;
			}
			if (currNum > 10 || currNum < 1)
			{
				cout << "输入数据超出范围。检查shudu.txt。" << endl;
				return -1;
			}
		}
	}

	//检查横行、纵排、九宫格是否符合要求
	for (int mode = 0; mode < 3; mode++)
		if (!check(matrix, mode))
		{
			sudokuValid = false;
		}
	if (sudokuValid)
		cout << "这个数独符合要求。" << endl;
	else
		cout << "这个数独不符合要求！" << endl;
	return 0;
}
