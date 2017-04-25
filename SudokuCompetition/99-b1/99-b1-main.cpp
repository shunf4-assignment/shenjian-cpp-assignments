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
  函数名称：
  功    能：从配置文件中读取超时值（秒）
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static int read_timeout_from_cfgfile(void)
{
	int second = DEFAULT_TOMEOUT_SECOND;

	ifstream cfgfile(CONF_FILENAME, ios::in);

	/* 无法打开配置文件则返回缺省值 */
	if (cfgfile.is_open() == 0)
		return second;

	/* 从配置文件中读取 */
	cfgfile >> second;
	if (!cfgfile.good())
		cfgfile.clear();
	cfgfile.close();

	/* 超出合理值则置缺省值 */
	if (second < 1 || second>180)
		second = DEFAULT_TOMEOUT_SECOND;

	return second;
}

/***************************************************************************
  函数名称：
  功    能：定时器处理函数，每3分钟执行一次
  输入参数：
  返 回 值：
  说    明：发送心跳包
***************************************************************************/
static void CALLBACK timer_process(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	output_used_time();
	cout << "本题超时" << endl;
	exit(-5);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static int start_timer(MMRESULT &timer_id, u_long second)
{
	timer_id = timeSetEvent(second*1000, 100, timer_process, 0, TIME_PERIODIC);
	if (timer_id == NULL)
		return -1;

	return 0;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static void stop_timer(MMRESULT timer_id)
{
	timeKillEvent(timer_id);
	return;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
static void output_used_time(void)
{
	QueryPerformanceCounter(&fc_end);//获得终止硬件定时器计数
	cout << setiosflags(ios::fixed) << setprecision(3);
	cout << "时钟频率：" << double(tick.QuadPart) / 1024 / 1024 << "GHz" << endl;
	cout << setprecision(0);
	cout << "时钟计数  ：" << double(fc_end.QuadPart - fc_begin.QuadPart) << endl;
	cout << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "秒" << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	MMRESULT timer_id;
	int timeout_second;
	int sudoku[9][9];
	int row, col;
	int ret;

	timeout_second = read_timeout_from_cfgfile();

	/* 读入（重定向方式） */
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
			cin >> sudoku[row][col];

	/* 输出初始值 */
	cout << "Begin" << endl;
	for (row = 0; row < 9; row++) {
		for (col = 0; col < 9; col++)
			cout << sudoku[row][col] << ' ';
		cout << endl;
	}
	cout << "End" << endl;

    /* 启动定时器 */
	if (start_timer(timer_id, timeout_second) < 0) {//启动定时器
		cout << "启动定时器错误" << endl;
		return -1;
		}

	QueryPerformanceFrequency(&tick);	//获得时钟频率
	QueryPerformanceCounter(&fc_begin);	//获得初始硬件定时器计数

	ret = solving_sudoku(sudoku);

	/* 输出使用时间 */
	output_used_time();

	/* 正常结束停止定时器 */
	stop_timer(timer_id);

	/* 有解则输出解 */
	switch (ret) {
		case 0:
			for (row = 0; row < 9; row++) {
				for (col = 0; col < 9; col++)
					cout << sudoku[row][col] << ' ';
				cout << endl;
			}
			break;

		case -1:
			cout << "本题初始数据有非法值" << endl;
			break;

		case -2:
			cout << "本题初始数据有冲突" << endl;
			break;

		case -3:
			cout << "本题无解" << endl;
			break;

		case -4:
		default:
			cout << "本题有其它错误" << endl;
			break;
		} //end of switch

	return 0;
}
