/*1652272 计算机1班 许至清*/
#include <iostream>
#include<iomanip>
using namespace std;

#define SIZE 10
int A[SIZE] = { 0 }, B[SIZE] = { 0 }, C[SIZE] = { 0 };
int A_top = 0, B_top = 0, C_top = 0;
int i = 0;
void hanoi(int n, char c1, char c2);
void initialize(int n, char c1);
void print(void);
int main()
{
	int n;
	char c1, c2;
	system("cls");
	system("mode con cols=100 lines=30"); // cols 为列 即宽 lines 为行 即高

	cout << "请输入层数(1-10) ";
	cin >> n;
	while (!cin.good() || n < 1 || n>10) {
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "输入不合法，请重新输入" << endl;
		cout << "请输入层数(1-10) ";
		cin >> n;
	}
	cin.ignore(1024, '\n');
	cout << "请输入起始圆柱名(A-C) ";
	cin >> c1;
	while (!cin.good() || (c1 != 'A'&&c1 != 'B'&&c1 != 'C'&&c1 != 'a'&&c1 != 'b'&&c1 != 'c')) {
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "输入不合法，请重新输入" << endl;
		cout << "请输入起始圆柱名(A-C) ";
		cin >> c1;
	}
	cin.ignore(1024, '\n');
	cout << "请输入结束圆柱名(A-C) ";
	cin >> c2;
	while (!cin.good() || (c2 != 'A'&&c2 != 'B'&&c2 != 'C'&&c2 != 'a'&&c2 != 'b'&&c2 != 'c') || c1 == c2 || c1 == c2 + 32 || c1 == c2 - 32) {
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "输入不合法，请重新输入" << endl;
		cout << "请输入结束圆柱名(A-C) ";
		cin >> c2;
	}
	c1 = char(toupper(c1));
	c2 = char(toupper(c2));
	initialize(n, c1);
	cout << "初始：               ";
	print();
	cout << endl;

	hanoi(n, c1, c2);

	return 0;
}
void print(void) {
	cout << "A:";
	for (int i = 0; i < A_top; i++) {
		if (A[i])
			cout << " " << A[i];
		else
			cout << "  ";
	}
	for (int i = A_top; i < SIZE; i++)
		cout << "  ";
	cout << " ";
	cout << "B:";
	for (int i = 0; i < B_top; i++) {
		if (B[i])
			cout << " " << B[i];
		else
			cout << "  ";
	}
	for (int i = B_top; i < SIZE; i++)
		cout << "  ";
	cout << " ";
	cout << "C:";
	for (int i = 0; i < C_top; i++) {
		if (C[i])
			cout << " " << C[i];
		else
			cout << "  ";
	}
	for (int i = C_top; i < SIZE; i++)
		cout << "  ";
}
void initialize(int n, char c1) {
	switch (c1) {
		case 'A':
			for (int i = n; i >= 1; i--) {
				A[A_top++] = i;
			}
			break;
		case 'B':
			for (int i = n; i >= 1; i--) {
				B[B_top++] = i;
			}
			break;
		case 'C':
			for (int i = n; i >= 1; i--) {
				C[C_top++] = i;
			}
			break;
	}
}
void hanoi(int n, char c1, char c2) {
	int temp;
	if (n == 1) {
		cout << "第" << setw(4) << ++i << " 步(" << n << "):" << c1 << "---->" << c2 << " ";
		switch (c1) {
			case 'A':
				temp = A[--A_top];
				break;
			case 'B':
				temp = B[--B_top];
				break;
			case 'C':
				temp = C[--C_top];
				break;
		}
		switch (c2) {
			case 'A':
				A[A_top++] = temp;
				break;
			case 'B':
				B[B_top++] = temp;
				break;
			case 'C':
				C[C_top++] = temp;
				break;
		}
		print();
		cout << endl;
	}
	else {
		hanoi(n - 1, c1, 'A' + 'B' + 'C' - c1 - c2);
		cout << "第" << setw(4) << ++i << " 步(" << n << "):" << c1 << "---->" << c2 << " ";
		switch (c1) {
			case 'A':
				temp = A[--A_top];
				break;
			case 'B':
				temp = B[--B_top];
				break;
			case 'C':
				temp = C[--C_top];
				break;
		}
		switch (c2) {
			case 'A':
				A[A_top++] = temp;
				break;
			case 'B':
				B[B_top++] = temp;
				break;
			case 'C':
				C[C_top++] = temp;
				break;
		}
		print();
		cout << endl;
		hanoi(n - 1, 'A' + 'B' + 'C' - c1 - c2, c2);
	}
}