/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <windows.h> //ȡϵͳʱ��
using namespace std;


int main()
{
	LARGE_INTEGER tick, fc_begin, fc_end;

	QueryPerformanceFrequency(&tick);	//���ʱ��Ƶ��
	QueryPerformanceCounter(&fc_begin);	//��ó�ʼӲ����ʱ������

	/* �˴�����ĳ���ʼ */
	double a, b, c;
	a = -6, b = 0;
	c = a / 0;
	cout << c << endl;
	/* �˴�����ĳ������ */

	QueryPerformanceCounter(&fc_end);//�����ֹӲ����ʱ������
	cout << setiosflags(ios::fixed) << setprecision(3);
	cout << "ʱ��Ƶ�ʣ�" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
	cout << setprecision(0);
	cout << "ʱ�Ӽ�����" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
	cout << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "��" << endl;

	return 0;
}