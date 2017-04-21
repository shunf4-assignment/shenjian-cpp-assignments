#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;

extern int solving_sudoku(int sudoku[9][9]);

int main()
{
	LARGE_INTEGER tick, fc_begin, fc_end;

	int sudoku[9][9];
	int row, col;
	int result;

	/* 读入（重定向方式） */
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			cin >> sudoku[row][col];

	/* 输出初始值 */
	for (row = 0; row < 9; row++) {
		for (col = 0; col < 9; col++)
			cout << sudoku[row][col] << ' ';
		cout << endl;
	}

	QueryPerformanceFrequency(&tick);	//获得时钟频率
	QueryPerformanceCounter(&fc_begin);	//获得初始硬件定时器计数

	result = solving_sudoku(sudoku);

	QueryPerformanceCounter(&fc_end);//获得终止硬件定时器计数
	cout << setiosflags(ios::fixed) << setprecision(3);
	cout << "时钟频率：" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
	cout << setprecision(0);
	cout << "时钟计数  ：" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
	cout << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "秒" << endl;

	/* 有解则输出解 */
	if (result) {
		for (row = 0; row < 9; row++) {
			for (col = 0; col < 9; col++)
				cout << sudoku[row][col] << ' ';
			cout << endl;
		}
	}
	else
		cout << "本题无解" << endl;


	return 0;
}
