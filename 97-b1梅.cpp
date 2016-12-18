/*梅语冰 1652311 计科3班*/
#include<iostream>
#include<iomanip>
#include <cstdio>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "cmd_console_tools.h"
using namespace std;


void shuruzhuzi(int *l, char *i, char *j, char *k, int xuanze, int *delay);
void fun(int n, char qishi, char jieshu, char zhongjian, int xuanze, int delay,int s);
int a[10] = { 0 }, b[10] = { 0 }, c[10] = { 0 }, topa, topb, topc;
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
void yanchi(int delay, int xuanze);
void shuchu0(int topa, int topb, int topc, int delay, int xuanze);
void shuchu1(int topa, int topb, int topc, int delay, int xuanze);
void move(char qishi, char jieshu, int xuanze, int delay);
void zhuzi(int xuanze);
void panzi(int n,int xuanze);
void image_move(int xuanze, char qishi, char jieshu, int s);

int main()
{
	int X, Y;
	char qishi, jieshu, zhongjian;
	int n, *l = &n,s;
	int delay = 0;
	char *i = &qishi, *j = &jieshu, *k = &zhongjian;

	cout << "---------------------------------------" << endl;
	cout << "1.基本解" << endl;
	cout << "2.基本解（步数记录）" << endl;
	cout << "3.内部数组显示（横向）" << endl;
	cout << "4.内部数组显示（横向+纵向）" << endl;
	cout << "5.图形解-预备-画三个圆柱" << endl;
	cout << "6.图形解-预备-在起始柱上画n个盘子" << endl;
	cout << "7.图形解-预备-第一次移动" << endl;
	cout << "8.图形解-自动移动版本" << endl;
	cout << "9.图形解-游戏版" << endl;
	cout << "0.退出" << endl;
	cout << "---------------------------------------" << endl;
	cout << "请选择（0-9）：";

	int xuanze;
	while (1) {
		cin >> xuanze;
		if (!cin.good()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请重新输入：";
		}
		else if (xuanze >= 10 || xuanze < 0) {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请重新输入：";
		}
		else
			break;
	}    //输入菜单的正确性判断


	if (xuanze == 0)
		return 0;

	else if (xuanze == 1) {
		shuruzhuzi(&n, &qishi, &jieshu, &zhongjian, xuanze, &delay);
		s = n;
		fun(n, qishi, jieshu, zhongjian, xuanze, delay,s);

	}

	else if (xuanze == 2) {
		shuruzhuzi(&n, &qishi, &jieshu, &zhongjian, xuanze, &delay);
		s = n;
		fun(n, qishi, jieshu, zhongjian, xuanze, delay,s);
	}

	else if (xuanze == 3) {
		shuruzhuzi(&n, &qishi, &jieshu, &zhongjian, xuanze, &delay);
		cout << "初始:" << setw(10) << " ";
		shuchu1(topa, topb, topc, delay, xuanze);
		cout << endl;
		s = n;
		fun(n, qishi, jieshu, zhongjian, xuanze, delay,s);
	}

	else if (xuanze == 4) {
		shuruzhuzi(&n, &qishi, &jieshu, &zhongjian, xuanze, &delay);
		system("cls");
		cout << "从" << qishi << "移动到" << jieshu << "，共" << n << "层" << ",延时设置为" << delay;
		X = 0, Y = 18;
		gotoxy(hout, X, Y);
		cout << "初始:" << setw(10) << " ";
		shuchu1(topa, topb, topc, delay, xuanze);
		s = n;
		fun(n, qishi, jieshu, zhongjian, xuanze, delay,s);
	}

	else if (xuanze == 5) {
		system("cls");
		zhuzi(xuanze);
		gotoxy(hout, 0, 18);
		setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	}

	else if (xuanze == 6) {
		shuruzhuzi(&n, &qishi, &jieshu, &zhongjian, xuanze, &delay);
		system("cls");
		cout << "从" << qishi << "移动到" << jieshu << "，共" << n << "层";
		zhuzi(xuanze);
		panzi(n,xuanze);
		gotoxy(hout, 0, 18);
		setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	}

	else if (xuanze == 7) {
		shuruzhuzi(&n, &qishi, &jieshu, &zhongjian, xuanze, &delay);
		s = n;
		system("cls");
		cout << "从" << qishi << "移动到" << jieshu << "，共" << n << "层";
		zhuzi(xuanze);
		panzi(n,xuanze);
		s = n;
		fun(n, qishi, jieshu, zhongjian, xuanze, delay,s);
		gotoxy(hout, 0, 18);
		setcolor(hout, COLOR_BLACK, COLOR_WHITE);

	}

	else if (xuanze == 8) {
		shuruzhuzi(&n, &qishi, &jieshu, &zhongjian, xuanze, &delay);
		s = n;
		setconsoleborder(hout, 100, 40);
		cout << "新窗口的宽度与高度" << endl;
		system("cls");
		cout << "从" << qishi << "移动到" << jieshu << "，共" << n << "层" << ",延时设置为" << delay;
		zhuzi(xuanze);
		panzi(n, xuanze);
		s = n;
		fun(n, qishi, jieshu, zhongjian, xuanze, delay,s);
		gotoxy(hout, 0, 32);
		cout << "初始:" << setw(10) << " ";
		shuchu1(topa, topb, topc, delay, xuanze);
	}
}

void shuruzhuzi(int *l, char *i, char *j, char *k, int xuanze, int *delay) {

	cout << "输入层数（1—10）：";
	while (1) {
		cin >> *l;
		if (!cin.good()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请重新输入:";
		}

		else if (*l >= 11) {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请重新输入：";
		}
		else
			break;
	}

	cout << "请输入起始圆柱名（A-C）：";
	while (1) {
		cin >> *i;
		if (*i != 'A' && *i != 'B' && *i != 'C' && *i != 'a' && *i != 'b' && *i != 'c') {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请重新输入起始柱（A-C):";
		}
		else
			break;
	}

	cout << "请输入结束圆柱名(A-C)：";
	while (1) {
		cin >> *j;
		if (*j != 'A' && *j != 'B' && *j != 'C' && *j != 'a' && *j != 'b' && *j != 'c' || *i == *j) {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请重新输入结束柱（A-C):";
		}
		else
			break;
	}   //输入一开始的层数，起始圆柱，结束圆柱

	if (xuanze == 4 && xuanze == 8) {
		cout << "请输入移动速度（0-5//0-按回车单步显示 1-延时最长 5-延时最短）：";
		cin >> *delay;
	}

	if ((*i == 'a' || *i == 'A') && (*j == 'c' || *j == 'C')) {
		*i = 'A';
		*k = 'B';
		*j = 'C';
	}

	else if ((*i == 'a' || *i == 'A') && (*j == 'b' || *j == 'B')) {
		*i = 'A';
		*k = 'C';
		*j = 'B';
	}

	else if ((*i == 'b' || *i == 'B') && (*j == 'a' || *j == 'A')) {
		*i = 'B';
		*k = 'C';
		*j = 'A';
	}

	else if ((*i == 'b' || *i == 'B') && (*j == 'c' || *j == 'C')) {
		*i = 'B';
		*k = 'A';
		*j = 'C';
	}

	else if ((*i == 'c' || *i == 'C') && (*j == 'a' || *j == 'A')) {
		*i = 'C';
		*k = 'B';
		*j = 'A';
	}

	else if ((*i == 'c' || *i == 'C') && (*j == 'b' || *j == 'B')) {
		*i = 'C';
		*k = 'A';
		*j = 'B';
	}

	//输入圆柱名的大小写全部转为大写，并确定中间圆柱
	int m;
	if (xuanze >= 3) {


		if (*i == 'A') {
			for (m = 0; m <= *l - 1; m++) {
				if (xuanze >= 4) {
					static int X = 13, Y = 12;
					gotoxy(hout, X, Y--);
				}
				if (a[m] == 0) {
					cout << " ";
				}
				else
					cout << a[m];
			}
		}

		if (*i == 'B') {
			for (m = 0; m <= *l - 1; m++) {
				if (xuanze >= 4) {
					static int X = 23, Y = 12;
					gotoxy(hout, X, Y--);
				}
				if (b[m] == 0) {
					cout << " ";
				}
				else
					cout << b[m];
			}
		}

		if (*i == 'C') {
			for (m = 0; m <= *l - 1; m++) {
				if (xuanze >= 4) {
					static int X = 33, Y = 12;
					gotoxy(hout, X, Y--);
				}
				if (b[m] == 0) {
					cout << " ";
				}
				else
					cout << c[m];
			}
		}
	}


	if (*i == 'A') {
		for (m = 0; m < *l; m++) {
			a[m] = *l - m;
		}
		topa = *l;
		topb = 0;
		topc = 0;
	}

	if (*i == 'B') {
		for (m = 0; m < *l; m++) {
			b[m] = *l - m;
		}
		topb = *l;
		topa = 0;
		topc = 0;
	}

	if (*i == 'C') {
		for (m = 0; m < *l; m++) {
			c[m] = *l - m;
		}
		topc = *l;
		topa = 0;
		topb = 0;
	}

}

void fun(int n, char qishi, char jieshu, char zhongjian, int xuanze, int delay,int s)
{
	static int i = 0;
	int X, Y;
	if (n == 1) {
		if (xuanze != 7) {
			if (xuanze != 1) {
				if (xuanze >= 3)
					move(qishi, jieshu, xuanze, delay);
				i++;
				if (xuanze == 4) {
					X = 0, Y = 18;
					gotoxy(hout, X, Y);
				}
				cout << "第" << setw(4) << i << "步：";
			}
			cout << n << "# " << qishi << "--->" << jieshu;
		}
		if (xuanze == 7) {
			image_move(xuanze, qishi, jieshu, s);
			return;
		}
		if (xuanze == 8) {
			image_move(xuanze, qishi, jieshu, s);
		}
		else if (xuanze >= 3)
			shuchu1(topa, topb, topc, delay, xuanze);
		cout << endl;
	}

	else {
		fun(n - 1, qishi, zhongjian, jieshu, xuanze, delay,s);
		if (xuanze >= 3)
			move(qishi, jieshu, xuanze, delay);
		if (xuanze == 4) {
			X = 0, Y = 18;
			gotoxy(hout, X, Y);
		}
		else if (xuanze == 8) {
			X = 0, Y = 25;
		}
		if (xuanze != 7) {
			if (xuanze != 1) {
				i++;
				cout << "第" << setw(4) << i << "步：";
			}
			cout << n << "# " << qishi << "--->" << jieshu;
		}
		if (xuanze == 7) {
			image_move(xuanze, qishi, jieshu, s);
		}
		else if (xuanze >= 3) {
			shuchu1(topa, topb, topc, delay, xuanze);
		}
		cout << endl;
		fun(n - 1, zhongjian, jieshu, qishi, xuanze, delay,s);
	}
}


void move(char qishi, char jieshu, int xuanze, int delay)
{

	if (qishi == 'A') {
		--topa;
		if (jieshu == 'B') {
			topb++;
			b[topb - 1] = a[topa];
			a[topa] = 0;
		}
		else {
			topc++;
			c[topc - 1] = a[topa];
			a[topa] = 0;
		}
		if (xuanze >= 4) {
			shuchu0(topa, topb, topc, delay, xuanze);
			cout << endl;
		}
	}

	if (qishi == 'B') {
		--topb;
		if (jieshu == 'A') {
			topa++;
			a[topa - 1] = b[topb];
			b[topb] = 0;
		}
		else {
			topc++;
			c[topc - 1] = b[topb];
			b[topb] = 0;
		}
	}


	if (qishi == 'C') {
		--topc;
		if (jieshu == 'A') {
			topa++;
			a[topa - 1] = c[topc];
			c[topc] = 0;
		}
		else {
			topb++;
			b[topb - 1] = c[topc];
			c[topc] = 0;
		}
	}


	if (xuanze >= 4) {
		shuchu0(topa, topb, topc, delay, xuanze);
		cout << endl;
	}
}
//top移动

void shuchu1(int topa, int topb, int topc, int delay, int xuanze)
{
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);

	int m;
	cout << setw(5) << "A:";
	for (m = 0; m < 10; m++) {
		if (a[m] == 0) {
			cout << setw(2) << " ";
		}
		else
			cout << setw(2) << a[m];
	}

	cout << setw(10) << "B:";
	for (m = 0; m < 10; m++) {
		if (b[m] == 0) {
			cout << setw(2) << " ";
		}
		else
			cout << setw(2) << b[m];
	}
	cout << setw(10) << "C:";
	for (m = 0; m < 10; m++) {
		if (c[m] == 0) {
			cout << setw(2) << " ";
		}
		else
			cout << setw(2) << c[m];
	}

	if (xuanze == 4) {
		yanchi(delay, xuanze);
	}
}
//输出横版


void shuchu0(int topa, int topb, int topc, int delay, int xuanze)
{
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);

		int X, Y;
		int m;
		if (xuanze == 4) {
			X = 10, Y = 13;
		}
		else if (xuanze == 8) {
			X = 10, Y = 29;
		}
		gotoxy(hout, X, Y);
		cout << "=========================" << endl;
		gotoxy(hout, X, Y + 1);
		cout << "   A         B         C" << endl;

		if (xuanze == 4) {
			X = 13, Y = 12;
		}
		else if (xuanze == 8) {
			X = 13, Y = 28;
		}
		for (m = 0; m < 10; m++, Y--) {
			if (a[m] == 0) {
				gotoxy(hout, X, Y);
				cout << " ";
			}
			else {
				gotoxy(hout, X, Y);
				cout << a[m];
			}
		}

		if (xuanze == 4) {
			X = 23, Y = 12;
		}
		else if (xuanze == 8) {
			X = 23, Y =28;
		}
		for (m = 0; m < 10; m++, Y--) {
			if (b[m] == 0) {
				gotoxy(hout, X, Y);
				cout << " ";
			}
			else {
				gotoxy(hout, X, Y);
				cout << b[m];
			}
		}

		if (xuanze == 4) {
			X = 33, Y = 12;
		}
		else if (xuanze == 8) {
			X = 33, Y = 28;
		}
		for (m = 0; m < 10; m++, Y--) {
			if (c[m] == 0) {
				gotoxy(hout, X, Y);
				cout << " ";
			}
			else {
				gotoxy(hout, X, Y);
				cout << c[m];
			}
		}
		yanchi(delay, xuanze);
}
//输出竖版

void yanchi(int delay, int xuanze)
{
	if (xuanze == 4) {
		switch (delay) {
		case 0: {
			if (_getch() == 10)
				break;
		}
		case 1: {
			Sleep(500);
			break;
		}
		case 2: {
			Sleep(400);
			break;
		}
		case 3: {
			Sleep(300);
			break;
		}
		case 4: {
			Sleep(200);
			break;
		}
		case 5: {
			Sleep(100);
			break;
		}
		}
	}

}

void zhuzi(int xuanze)
{
	if (1) {
		const int Y = 16;
		const int bg_color = COLOR_HYELLOW;	//背景为亮黄色
		const int fg_color = COLOR_HBLUE;	//前景为亮蓝色
		const char ch = ' ';        //字符为*(注意：如果是空格，则前景色无法显示)
		const int LENGTH = 1;
		int x;

		for (x = 4; x < 28; x++) {
			showch(hout, x, Y, ch, bg_color, fg_color, LENGTH);
			Sleep(50);
		}
		
		for (x = 36; x < 60; x++) {
			showch(hout, x, Y, ch, bg_color, fg_color, LENGTH);
			Sleep(50);		
		}

		for (x = 68; x < 92; x++) {
			showch(hout, x, Y, ch, bg_color, fg_color, LENGTH);
			Sleep(50);
		}
	}
	//横柱子

	if (1) {
		const int MAX_Y = 16;
		const int X = 16;
		const int bg_color = COLOR_HYELLOW;	//背景为亮黄色
		const int fg_color = COLOR_HBLUE;	//前景为亮蓝色
		const char ch = ' ';        //字符为*(注意：如果是空格，则前景色无法显示)
		const int LENGTH = 1;
		int y;

		for (y = 3; y < MAX_Y; y++) {
			showch(hout, X, y, ch, bg_color, fg_color, LENGTH);
			Sleep(100);
			
		}


		for (y = 3; y < MAX_Y; y++) {
			showch(hout, X + 32, y, ch, bg_color, fg_color, LENGTH);
			Sleep(100);		
		}

		for (y = 3; y < MAX_Y; y++) {
			showch(hout, X + 64, y, ch, bg_color, fg_color, LENGTH);
			Sleep(100);
		}
	}
	//竖着的
}
//画出三个柱子

void panzi(int n, int xuanze) {
	const int fg_color = COLOR_HBLUE;	//前景为亮蓝色
	const char ch = ' ';
	const int LENGTH = 1;
	int x, i, y;

	for (i = 0, y = 15; i < n; i++, y--) {
		for (x = 16; x < 16 + a[i]; x++) {
			showch(hout, x, y, ch, i + 1, fg_color, LENGTH);
		}
		for (x = 16; x > (16 - a[i]); x--) {
			showch(hout, x, y, ch, i + 1, fg_color, LENGTH);
		}
			Sleep(30);
		
	}

	for (i = 0, y = 15; i < n; i++, y--) {
		for (x = 48; x < 48 + b[i]; x++) {
			showch(hout, x, y, ch, i + 1, fg_color, LENGTH);
		}
		for (x = 48; x > (48 - b[i]); x--) {
			showch(hout, x, y, ch, i + 1, fg_color, LENGTH);
		}
			Sleep(30);
		
	}

	for (i = 0, y = 15; i < n; i++, y--) {
		for (x = 80; x < 80 + c[i]; x++) {
			showch(hout, x, y, ch, i + 1, fg_color, LENGTH);
		}
		for (x = 80; x > (80 - c[i]); x--) {
			showch(hout, x, y, ch, i + 1, fg_color, LENGTH);
		}
			Sleep(30);
	}
}
//画出盘子

void image_move(int xuanze, char qishi, char jieshu, int s) {
	const int bg_color = COLOR_HYELLOW;	//背景为亮黄色
	const int fg_color = COLOR_HBLUE;	//前景为亮蓝色
	const char ch = ' ';        //字符为*(注意：如果是空格，则前景色无法显示)
	const int LENGTH = 1;
	int y, x, X;

	if (qishi == 'A') {
		_getch();
		for (y = 16 - topa; y >= 3; y--) {
			_getch();
			for (x = 16; x <= 16 + s-topa; x++) {
				showch(hout, x, y, ch, 0, fg_color, LENGTH);
			}
			_getch();
			for (x = 16; x >=(16 -(s- topa)); x--) {
				showch(hout, x, y, ch, 0, fg_color, LENGTH);
			}
			_getch();
			for (x = 16; x <= 16 +s- topa; x++) {
				showch(hout, x, y-1, ch, topa, fg_color, LENGTH);
			}
			_getch();
			for (x = 16; x >=(16 - (s - topa)); x--) {
				showch(hout, x, y-1, ch, topa, fg_color, LENGTH);
			}	
			_getch();
			showch(hout, 16, y, ch, bg_color, fg_color, LENGTH);

			Sleep(30);
		}

		showch(hout, 16, 3, ch, bg_color, fg_color, LENGTH);

		if (jieshu == 'B') {
			for (x = 16; x <= 48; x++) {
				for (X = x; X <= x + s-topa; X++) {
					showch(hout, X - 1, y, ch, 0, fg_color, LENGTH);
				}
				_getch();

				for (X = x; X >=(x -(s- topa)); X--) {
					showch(hout, X - 1, y, ch, 0, fg_color, LENGTH);
				}
				_getch();

				for (X = x; X <= x + s-topa; X++) {
					showch(hout, X, y, ch, topa, fg_color, LENGTH);
				}
				_getch();

				for (X = x; X >=(x -( s- topa)); X--) {
					showch(hout, X, y, ch, topa, fg_color, LENGTH);
				}				
				Sleep(30);
			}
			_getch();

			for (y = 3; y < 16 - topb; y++) {
				for (X = 48; X <= 48 + s-topa; X++) {
					showch(hout, X, y-1, ch, 0, fg_color, LENGTH);
				}
				_getch();

				for (X = 48; X >=(48 - (s-topa)); X--) {
					showch(hout, X, y-1, ch, 0, fg_color, LENGTH);
				}
				_getch();

				for (X = 48;X <= 48 +(s-topa); X++) {
					showch(hout,X, y, ch, topa, fg_color, LENGTH);
				}
				_getch();

				for (X = 48; X >=(48 -(s- topa)); X--) {
					showch(hout, X, y, ch, topa, fg_color, LENGTH);
				}
				_getch();
				showch(hout, 48, y - 1, ch, bg_color, fg_color, LENGTH);
				Sleep(30);
			}
			_getch();
		}

		else if (jieshu == 'C') {
			for (x = 16; x <= 80; x++) {
				for (X = x; X <= x + (s - topa); X++) {
					showch(hout, X - 1, y, ch, 0, fg_color, LENGTH);
				}
				for (X = x; X >= (x - (s - topa)); X--) {
					showch(hout, X - 1, y, ch, 0, fg_color, LENGTH);
				}
				for (X = x; X <= x + (s - topa); X++) {
					showch(hout, X, y, ch, topa, fg_color, LENGTH);
				}
				for (X = x; X >= (x - (s - topa)); X--) {
					showch(hout, X, y, ch, topa, fg_color, LENGTH);
				}
				Sleep(30);
			}
		}

		for (y = 3; y < 16 - topc; y++) {
				for (x = 80; x <= 80 + (s - topa); x++) {
					showch(hout, x, y - 1, ch, 0, fg_color, LENGTH);
				}
				for (x = 80; x >= (80 - (s - topa)); x--) {
					showch(hout, x, y - 1, ch, 0, fg_color, LENGTH);
				}
				for (x = 80; x <= 80 + (s - topa); x++) {
					showch(hout, x, y, ch, topa, fg_color, LENGTH);
				}
				for (x = 80; x >= (80 - (s - topa)); x--) {
					showch(hout, x, y, ch, topa, fg_color, LENGTH);
				}
				showch(hout, 80, y - 1, ch, bg_color, fg_color, LENGTH);
				Sleep(30);
			}
	}

	if (qishi == 'B') {
		for (y = 16 - topb; y >= 3; y--) {
			for (x = 48; x <= 48 + (s - topb); x++) {
				showch(hout, x, y, ch, 0, fg_color, LENGTH);
			}
			for (x = 48; x >= (48 - (s - topb)); x--) {
				showch(hout, x, y, ch, 0, fg_color, LENGTH);
			}
			for (x = 48; x <= 48 + (s - topb); x++) {
				showch(hout, x, y - 1, ch, topb, fg_color, LENGTH);
			}
			for (x = 48; x >= (48 - (s - topb)); x--) {
				showch(hout, x, y - 1, ch, topb, fg_color, LENGTH);
			}
			showch(hout, 48, y , ch, bg_color, fg_color, LENGTH);

			Sleep(30);
		}
		showch(hout, 48, 3, ch, bg_color, fg_color, LENGTH);

		if (jieshu == 'A') {
			for (x = 48; x >= 16; x--) {
				for (X = x; X <= x + (s - topb); X++) {
					showch(hout, X + 1, y, ch, 0, fg_color, LENGTH);
				}
				for (X = x; X >= (x - (s - topb)); X--) {
					showch(hout, X + 1, y, ch, 0, fg_color, LENGTH);
				}
				for (X = x; X <= x + (s - topb); X++) {
					showch(hout, X, y, ch, topb, fg_color, LENGTH);
				}
				for (X = x; X >= (x - (s - topb)); X--) {
					showch(hout, X, y, ch, topb, fg_color, LENGTH);
				}
				Sleep(30);
			}

			for (y = 3; y < 16 - topa; y++) {
				for (x = 16; x <= 16 + (s - topb); x++) {
					showch(hout, x, y - 1, ch, 0, fg_color, LENGTH);
				}
				for (x = 16; x >= (16 - (s - topb)); x--) {
					showch(hout, x, y - 1, ch, 0, fg_color, LENGTH);
				}
				for (x = 16; x <= 16 + (s - topb); x++) {
					showch(hout, x, y, ch, topb, fg_color, LENGTH);
				}
				for (x = 16; x >= (16 - (s - topb)); x--) {
					showch(hout, x, y, ch, topb, fg_color, LENGTH);
				}
				showch(hout, 16, y - 1, ch, bg_color, fg_color, LENGTH);
				Sleep(30);
			}
		}


		else if (jieshu == 'C') {
			for (x = 48; x <= 80; x++) {
				for (X = x; X <= x + (s - topb); X++) {
					showch(hout, X-1, y, ch, 0, fg_color, LENGTH);
				}
				for (X = x; X >=(x - (s - topb));X--) {
					showch(hout, X-1, y, ch, 0, fg_color, LENGTH);
				}
				for (X = x; X <= x + (s - topb); X++) {
					showch(hout, X, y, ch, topb, fg_color, LENGTH);
				}
				for (X = x; X >= (x - (s - topb)); X--) {
					showch(hout, X, y, ch, topb, fg_color, LENGTH);
				}
				Sleep(30);
			}

			for (y = 3; y < 16 - topc; y++) {
				for (X = 80; X <= 80 + (s - topb); X++) {
					showch(hout, X, y-1, ch, 0, fg_color, LENGTH);
				}
				for (X = 80; X >=(80 - (s - topb)); X--) {
					showch(hout, X, y-1, ch, 0, fg_color, LENGTH);
				}
				for (X = 80; X <= 80 + (s - topb); X++) {
					showch(hout, X, y, ch, topb, fg_color, LENGTH);
				}
				for (X = 80; X >=(80 - (s - topb)); X--) {
					showch(hout, X, y, ch, topb, fg_color, LENGTH);
				}
				showch(hout, 80, y - 1, ch, bg_color, fg_color, LENGTH);
				Sleep(30);
			}
		}

	}

	if (qishi == 'C') {
		for (y = 16 - topc; y >= 3; y--) {
			for (x = 80; x <= 80 + (s - topc); x++) {
				showch(hout, x, y, ch, 0, fg_color, LENGTH);
			}
			for (x = 80; x >= (80 - (s - topc)); x--) {
				showch(hout, x, y, ch, 0, fg_color, LENGTH);
			}
			for (x = 80; x <= 80 + (s - topc); x++) {
				showch(hout, x, y - 1, ch, topc, fg_color, LENGTH);
			}
			for (x = 80; x >= (80 - (s - topc)); x--) {
				showch(hout, x, y - 1, ch, topc, fg_color, LENGTH);
			}
			showch(hout, 80, y, ch, bg_color, fg_color, LENGTH);

			Sleep(30);
		}
			showch(hout, 80, 3, ch, bg_color, fg_color, LENGTH);
			_getch();

			if (jieshu == 'A') {
				for (x = 80; x >= 16; x--) {
					for (X = x; X <= x + (s - topc); X++) {
						showch(hout, X + 1, y, ch, 0, fg_color, LENGTH);
					}
					for (X = x; X >= (x - (s - topc)); X--) {
						showch(hout, X + 1, y, ch, 0, fg_color, LENGTH);
					}
					for (X = x; X <= x + (s - topc); X++) {
						showch(hout, X, y, ch, topc, fg_color, LENGTH);
					}
					for (X = x; X >= (x - (s - topc)); X--) {
						showch(hout, X, y, ch, topc, fg_color, LENGTH);
					}
					Sleep(30);
				}

				for (y = 3; y < 16 - topa; y++) {
					for (x = 16; x <= 16 + (s - topb); x++) {
						showch(hout, x, y - 1, ch, 0, fg_color, LENGTH);
					}
					for (x = 16; x >= (16 - (s - topb)); x--) {
						showch(hout, x, y - 1, ch, 0, fg_color, LENGTH);
					}
					for (x = 16; x <= 16 + (s - topb); x++) {
						showch(hout, x, y, ch, topc, fg_color, LENGTH);
					}
					for (x = 16; x >= (16 - (s - topb)); x--) {
						showch(hout, x, y, ch, topc, fg_color, LENGTH);
					}
					showch(hout, 16, y - 1, ch, bg_color, fg_color, LENGTH);
					Sleep(30);
				}
			}


		else if (jieshu == 'B') {
			for (x = 80; x >= 48; x--) {
				for (X = x; X <= x + (s - topc);X++) {
					showch(hout, X+1, y, ch, 0, fg_color, LENGTH);
				}
				for (X = x; X >=(x - (s - topc)); X--) {
					showch(hout, X+1, y , ch, 0, fg_color, LENGTH);
				}
				for (X = x; X <= x + (s - topc); X++) {
					showch(hout, X, y, ch, topc, fg_color, LENGTH);
				}
				for (X = x; X >=(x - (s - topc)); X--) {
					showch(hout, X, y, ch, topc, fg_color, LENGTH);
				}
				Sleep(30);
			}

			for (y = 3; y < 16 - topb; y++) {
				for (x = 48; x <= 48 + (s - topc); x++) {
					showch(hout, x, y-1, ch, 0, fg_color, LENGTH);
				}
				for (x = 48; x >=(48 - (s - topc)); x--) {
					showch(hout, x, y-1, ch, 0, fg_color, LENGTH);
				}
				for (x = 48; x <= 48 + (s - topc); x++) {
					showch(hout, x, y, ch, topc, fg_color, LENGTH);
				}
				for (x = 48; x >=(48 - (s - topc)); x--) {
					showch(hout, x, y, ch, topc, fg_color, LENGTH);
				}
				showch(hout, 48, y - 1, ch, bg_color, fg_color, LENGTH);
				Sleep(30);
			}
			_getch();
		}


	}
}
