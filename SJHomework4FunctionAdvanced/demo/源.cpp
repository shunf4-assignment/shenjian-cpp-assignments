/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

int main()
{
	void f();
	int a(int x);
	cout << a(5) << endl;
	f();
	return 0;
}

int a(int x)
{
	cout << x << "+";
	return 1;
}

void f() {
	cout << a(2) << endl;
}