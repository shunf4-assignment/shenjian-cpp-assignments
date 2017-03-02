#include <iostream>
using namespace std;

int fun(int * p)
{
	return 1;
}
void fun2(int (*p)[3])
{
	return;
}
void fun3(int &a)
{
	a = 2;
	return;
}

int main()
{
	int i = 0;
	int arr[2][3] = { 1,2,3,4,5,6 };
	int(*p1)[3] = arr;
	char *p2 = "China";
	int (*p3)(int *) = fun;
	int *p4[2] = { &arr[1][1], &arr[0][2] };
	char **p5 = &p2;

	char str[10];
	char *p6 = str;
	int *p7 = &arr[1][3];

	fun(arr[0]);
	fun2(arr);
	fun3(i);

	return 0;

}
