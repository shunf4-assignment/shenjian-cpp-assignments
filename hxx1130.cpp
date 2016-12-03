/* 1652305 计算机3班 黄茜茜 */
#include <iostream>
#include<iomanip>
#include<windows.h>
using namespace std;
#define NUM 10
int a[NUM] = { 0 }, b[NUM] = { 0 }, c[NUM] = { 0 };
int t1 = 0, t2 = 0, t3 = 0;
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
/* 将光标移动到指定位置 */
void gotoxy(HANDLE hout, int X, int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}
/* 在指定位置处打印一个指定的字符 */
void showch0(HANDLE hout, int X, int Y, char ch)
{
	gotoxy(hout, X, Y);
	putchar(ch);
}
void showch(HANDLE hout, int p[NUM], int X, int Y, int i)
{
	gotoxy(hout, X, Y);
	cout << p[i];
}
void f() {
	gotoxy(hout, 23, 17);
	int i;
	cout << "A:";
	for (i = 0;i < NUM;i++) {
		if (a[i] > 0)
			cout << a[i] << " ";
		else cout << "  ";
	}
	cout << "B:";
	for (i = 0;i < NUM;i++) {
		if (b[i] > 0)
			cout << b[i] << " ";
		else cout << "  ";
	}
	cout << "C:";
	for (i = 0;i < NUM;i++) {
		if (c[i] > 0)
			cout << c[i] << " ";
		else cout << "  ";
	}
	cout << endl;
}
void shuzu(int xianshi, int s, char p) {
	cout << setiosflags(ios::left) << setw(7) << "初始：";
	int i;
	if (p == 'a' || p == 'A') {
		for (i = s;i > 0;i--)
			a[i - 1] = a[i] + 1;
	}
	else if (p == 'b' || p == 'B') {
		for (i = s;i > 0;i--)
			b[i - 1] = b[i] + 1;
	}
	else if (p == 'c' || p == 'C') {
		for (i = s;i > 0;i--)
			c[i - 1] = c[i] + 1;
	}
	if (xianshi == 1) {
		f();
	}
	if (p == 'a' || p == 'A') {
		for (i = 0;i < NUM;i++) {
			if (a[i] > 0)
				showch(hout, a, 9, 11 - i, i);
			else break;
		}
	}
	else if (p == 'b' || p == 'B') {
		for (i = 0;i < NUM;i++) {
			if (b[i] > 0)
				showch(hout, b, 19, 11 - i, i);
			else break;
		}
	}
	else if (p == 'c' || p == 'C') {
		for (i = 0;i < NUM;i++) {
			if (c[i] > 0)
				showch(hout, c, 29, 11 - i, i);
			else break;
		}
	}
}
void move(int v, int xianshi, int s, int n, char from, char to) {
	static int m = 1;
	if (v == 0) {
		if (getchar() == 10) {
			if ((from == 'A' || from == 'a')) {
				if ((to == 'b') || (to == 'B')) {
					b[t2] = a[t1 - 1];
					a[t1 - 1] = 0;
					showch0(hout, 9, 12 - t1, ' ');
					showch(hout, b, 19, 11 - t2, t2);
					t2++;
					t1--;
				}
				else if ((to == 'c') || (to == 'C')) {
					c[t3] = a[t1 - 1];
					a[t1 - 1] = 0;
					showch0(hout, 9, 12 - t1, ' ');
					showch(hout, c, 29, 11 - t3, t3);
					t3++;
					t1--;
				}
			}
			if ((from == 'B' || from == 'b')) {
				if ((to == 'a') || (to == 'A')) {
					a[t1] = b[t2 - 1];
					b[t2 - 1] = 0;
					showch0(hout, 19, 12 - t2, ' ');
					showch(hout, a, 9, 11 - t1, t1);
					t1++;
					t2--;
				}
				else if ((to == 'c') || (to == 'C')) {
					c[t3] = b[t2 - 1];
					b[t2 - 1] = 0;
					showch0(hout, 19, 12 - t2, ' ');
					showch(hout, c, 29, 11 - t3, t3);
					t3++;
					t2--;
				}
			}
			if ((from == 'C' || from == 'c')) {
				if ((to == 'a') || (to == 'A')) {
					a[t1] = c[t3 - 1];
					c[t3 - 1] = 0;
					showch0(hout, 29, 12 - t3, ' ');
					showch(hout, a, 9, 11 - t1, t1);
					t1++;
					t3--;
				}
				else if ((to == 'b') || (to == 'B')) {
					b[t2] = c[t3 - 1];
					c[t3 - 1] = 0;
					showch0(hout, 29, 12 - t3, ' ');
					showch(hout, b, 19, 11 - t2, t2);
					t2++;
					t3--;
				}
			}
			gotoxy(hout, 0, 17);
			cout << "第" << setiosflags(ios::right) << setw(4) << m++ << " 步" << "(" << n << "):" << from << " ----> " << to << " ";
			if (xianshi == 1) {
				f();
			}
		}
	}
	else if (v > 0) {
		Sleep(100 * (10 - v));
		if ((from == 'A' || from == 'a')) {
			if ((to == 'b') || (to == 'B')) {
				b[t2] = a[t1 - 1];
				a[t1 - 1] = 0;
				showch0(hout, 9, 12 - t1, ' ');
				showch(hout, b, 19, 11 - t2, t2);
				t2++;
				t1--;
			}
			else if ((to == 'c') || (to == 'C')) {
				c[t3] = a[t1 - 1];
				a[t1 - 1] = 0;
				showch0(hout, 9, 12 - t1, ' ');
				showch(hout, c, 29, 11 - t3, t3);
				t3++;
				t1--;
			}
		}
		if ((from == 'B' || from == 'b')) {
			if ((to == 'a') || (to == 'A')) {
				a[t1] = b[t2 - 1];
				b[t2 - 1] = 0;
				showch0(hout, 19, 12 - t2, ' ');
				showch(hout, a, 9, 11 - t1, t1);
				t1++;
				t2--;
			}
			else if ((to == 'c') || (to == 'C')) {
				c[t3] = b[t2 - 1];
				b[t2 - 1] = 0;
				showch0(hout, 19, 12 - t2, ' ');
				showch(hout, c, 29, 11 - t3, t3);
				t3++;
				t2--;
			}
		}
		if ((from == 'C' || from == 'c')) {
			if ((to == 'a') || (to == 'A')) {
				a[t1] = c[t3 - 1];
				c[t3 - 1] = 0;
				showch0(hout, 29, 12 - t3, ' ');
				showch(hout, a, 9, 11 - t1, t1);
				t1++;
				t3--;
			}
			else if ((to == 'b') || (to == 'B')) {
				b[t2] = c[t3 - 1];
				c[t3 - 1] = 0;
				showch0(hout, 29, 12 - t3, ' ');
				showch(hout, b, 19, 11 - t2, t2);
				t2++;
				t3--;
			}
		}
		gotoxy(hout, 0, 17);
		cout << "第" << setiosflags(ios::right) << setw(4) << m++ << " 步" << "(" << n << "):" << from << " ----> " << to << " ";
		if (xianshi == 1) {
			f();
		}
	}
}
void H(int v, int xianshi, int s, int n, char A, char B, char C) {
	if (n == 1) {
		move(xianshi, v, s, n, A, C);
	}
	else {
		H(v, xianshi, s, n - 1, A, C, B);
		move(xianshi, v, s, n, A, C);
		H(v, xianshi, s, n - 1, B, A, C);
	}
}
int main() {
	int s, v, xianshi, i;
	char x, y, z;
	while (true) {
		cout << "请输入塔层数（1-10）：";
		cin >> s;
		if ((!cin.good()) || s > 10 || s < 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请重新输入" << endl;
			continue;
		}
		else break;
	}
	while (true) {
		cout << "请输入起始圆柱名(A-C)：";
		cin >> x;
		if (x == 'A' || x == 'B' || x == 'C' || x == 'a' || x == 'b' || x == 'c')
			break;
		else if ((!cin.good()) || !(x == 'A' || x == 'B' || x == 'C' || x == 'a' || x == 'b' || x == 'c'))
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请重新输入" << endl;
			continue;
		}
	}
	while (true) {
		cout << "请输入结束圆柱名(A-C)：";
		cin >> y;
		if (y == 'A' || y == 'B' || y == 'C' || y == 'a' || y == 'b' || y == 'c') {
			if (int(x) == int(y) || (int(x) - int(y)) == 32 || (int(y) - int(x)) == 32) {
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "输入错误，请重新输入" << endl;
				continue;
			}
			else {
				if ((x == 'a' || x == 'A') && (y == 'b' || y == 'B'))
					z = 'C';
				else if ((x == 'a' || x == 'A') && (y == 'c' || y == 'C'))
					z = 'B';
				else if ((x == 'c' || x == 'C') && (y == 'b' || y == 'B'))
					z = 'A';
				else if ((x == 'b' || x == 'B') && (y == 'a' || y == 'A'))
					z = 'C';
				else if ((x == 'b' || x == 'B') && (y == 'c' || y == 'C'))
					z = 'A';
				else if ((x == 'c' || x == 'C') && (y == 'a' || y == 'A'))
					z = 'B';
				break;
			}
		}
		else if ((!cin.good()) || !(y == 'A' || y == 'B' || y == 'C' || y == 'a' || y == 'b' || y == 'c'))
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请重新输入" << endl;
			continue;
		}
	}
	while (true) {
		cout << "请输入移动速度(0-5：0-按回车单步演示 1-延时最长 5-延时最短)：";
		cin >> v;
		if (v == 0 || v == 1 || v == 2 || v == 3 || v == 4 || v == 5) {
			break;
		}
		else if ((!cin.good()) || !(v == 0 || v == 1 || v == 2 || v == 3 || v == 4 || v == 5))
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请重新输入" << endl;
			continue;
		}
	}
	while (true) {
		cout << "请输入是否显示内部数组值(0-不显示 1-显示)：";
		cin >> xianshi;
		if (xianshi == 0 || xianshi == 1) {
			system("cls");
			cout << "从 " << x << " 移动到 " << y << " ，共 " << s << " 层，延时设置为" << v << ",";
			if (xianshi == 0)
				cout << "不显示内部数组值";
			else if (xianshi == 1)
				cout << "显示内部数组值";
			cout << endl;
			for (i = 1;i < 12;i++) {
				cout << endl;
			}
			cout << "       =========================" << endl;
			cout << setw(10) << "A";
			cout << setw(10) << "B";
			cout << setw(10) << "C";
			for (i = 1;i < 5;i++) {
				cout << endl;
			}
			shuzu(xianshi, s, x);
			Sleep(100 * (10 - v));
			if (x == 'a' || x == 'A')
				t1 = t1 + s;
			else if (x == 'b' || x == 'B')
				t2 = t2 + s;
			else if (x == 'c' || x == 'C')
				t3 = t3 + s;
			if (v == 0) {
				if(getchar()==10)
					H(v, xianshi, s, s, x, z, y);
			}
			else if(v>0)
				H(v, xianshi, s, s, x, z, y);
			break;
		}
		else if ((!cin.good()) || !(xianshi == 0 || xianshi == 1))
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请重新输入" << endl;
			continue;
		}
	}
	cout << endl;
	return 0;
}