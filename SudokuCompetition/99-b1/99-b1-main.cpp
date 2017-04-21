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

	/* ���루�ض���ʽ�� */
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			cin >> sudoku[row][col];

	/* �����ʼֵ */
	for (row = 0; row < 9; row++) {
		for (col = 0; col < 9; col++)
			cout << sudoku[row][col] << ' ';
		cout << endl;
	}

	QueryPerformanceFrequency(&tick);	//���ʱ��Ƶ��
	QueryPerformanceCounter(&fc_begin);	//��ó�ʼӲ����ʱ������

	result = solving_sudoku(sudoku);

	QueryPerformanceCounter(&fc_end);//�����ֹӲ����ʱ������
	cout << setiosflags(ios::fixed) << setprecision(3);
	cout << "ʱ��Ƶ�ʣ�" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
	cout << setprecision(0);
	cout << "ʱ�Ӽ���  ��" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
	cout << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "��" << endl;

	/* �н�������� */
	if (result) {
		for (row = 0; row < 9; row++) {
			for (col = 0; col < 9; col++)
				cout << sudoku[row][col] << ' ';
			cout << endl;
		}
	}
	else
		cout << "�����޽�" << endl;


	return 0;
}
