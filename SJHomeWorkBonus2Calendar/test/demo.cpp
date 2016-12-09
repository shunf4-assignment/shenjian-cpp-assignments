/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

int outer_function(int param)
{
	return param;
}

int main()
{
	//REINPUT:
	char a[] = "顺子顺子顺子顺子";
	cout << a << endl;
	cout << ((char *)((int)a + 1));
	cout << endl;
	//goto REINPUT;
	return 0;
}