/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

int outer_function(int param)
{
	return param;
}

int main()
{
	//REINPUT:
	char a[] = "˳��˳��˳��˳��";
	cout << a << endl;
	cout << ((char *)((int)a + 1));
	cout << endl;
	//goto REINPUT;
	return 0;
}