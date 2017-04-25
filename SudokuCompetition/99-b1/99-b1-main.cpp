#include <iostream>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")
using namespace std;

#define CONF_FILENAME				"99-b1-timeout.cfg"
#define DEFAULT_TOMEOUT_SECOND		30
static LARGE_INTEGER tick, fc_begin, fc_end;

extern int solving_sudoku(int sudoku[9][9]);

static int read_timeout_from_cfgfile(void);
static void CALLBACK timer_process(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
static void start_timer(u_long second);
static void output_used_time(void);
/***************************************************************************
  �������ƣ�
  ��    �ܣ��������ļ��ж�ȡ��ʱֵ���룩
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static int read_timeout_from_cfgfile(void)
{
	int second = DEFAULT_TOMEOUT_SECOND;

	ifstream cfgfile(CONF_FILENAME, ios::in);

	/* �޷��������ļ��򷵻�ȱʡֵ */
	if (cfgfile.is_open() == 0)
		return second;

	/* �������ļ��ж�ȡ */
	cfgfile >> second;
	if (!cfgfile.good())
		cfgfile.clear();
	cfgfile.close();

	/* ��������ֵ����ȱʡֵ */
	if (second < 1 || second>180)
		second = DEFAULT_TOMEOUT_SECOND;

	return second;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʱ����������ÿ3����ִ��һ��
  ���������
  �� �� ֵ��
  ˵    ��������������
***************************************************************************/
static void CALLBACK timer_process(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	output_used_time();
	cout << "���ⳬʱ" << endl;
	exit(-5);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static int start_timer(MMRESULT &timer_id, u_long second)
{
	timer_id = timeSetEvent(second*1000, 100, timer_process, 0, TIME_PERIODIC);
	if (timer_id == NULL)
		return -1;

	return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void stop_timer(MMRESULT timer_id)
{
	timeKillEvent(timer_id);
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
static void output_used_time(void)
{
	QueryPerformanceCounter(&fc_end);//�����ֹӲ����ʱ������
	cout << setiosflags(ios::fixed) << setprecision(3);
	cout << "ʱ��Ƶ�ʣ�" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
	cout << setprecision(0);
	cout << "ʱ�Ӽ���  ��" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
	cout << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "��" << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int main()
{
	MMRESULT timer_id;
	int timeout_second;
	int sudoku[9][9];
	int row, col;
	int ret;

	timeout_second = read_timeout_from_cfgfile();

	/* ���루�ض���ʽ�� */
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			cin >> sudoku[row][col];

	/* �����ʼֵ */
	cout << "Begin" << endl;
	for (row = 0; row < 9; row++) {
		for (col = 0; col < 9; col++)
			cout << sudoku[row][col] << ' ';
		cout << endl;
	}
	cout << "End" << endl;

    /* ������ʱ�� */
	if (start_timer(timer_id, timeout_second) < 0) {//������ʱ��
		cout << "������ʱ������" << endl;
		return -1;
		}

	QueryPerformanceFrequency(&tick);	//���ʱ��Ƶ��
	QueryPerformanceCounter(&fc_begin);	//��ó�ʼӲ����ʱ������

	ret = solving_sudoku(sudoku);

	/* ���ʹ��ʱ�� */
	output_used_time();

	/* ��������ֹͣ��ʱ�� */
	stop_timer(timer_id);

	/* �н�������� */
	switch (ret) {
		case 0:
			for (row = 0; row < 9; row++) {
				for (col = 0; col < 9; col++)
					cout << sudoku[row][col] << ' ';
				cout << endl;
			}
			break;

		case -1:
			cout << "�����ʼ�����зǷ�ֵ" << endl;
			break;

		case -2:
			cout << "�����ʼ�����г�ͻ" << endl;
			break;

		case -3:
			cout << "�����޽�" << endl;
			break;

		case -4:
		default:
			cout << "��������������" << endl;
			break;
		} //end of switch

	return 0;
}
