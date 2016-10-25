/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;


int main()
{
	unsigned int a = 0, n = 0, sum = 0, tempVar = 0;

	//开始输入a和n。
	cout << "请依次输入正整数 a 和 n，可以用空格或回车隔开：";
	cin >> a >> n;
	 
	//累加
	for (int i = 0; i < n; i++)
	{
		tempVar = tempVar * 10 + a;
		sum = sum + tempVar;
	}

	cout << "Sn = " << sum << endl;

	return 0;
}