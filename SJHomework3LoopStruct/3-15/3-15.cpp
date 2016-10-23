/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;


int main()
{
	unsigned int m, n, tempVar, greatestCommonDivisor, leastCommonMultiple, leftNum, rightNum;

	m = 0, n = 0, leftNum = 0, rightNum = 0, tempVar = 0;

	//开始输入m和n。
	cout << "请依次输入两个正整数 m 和 n，可以用空格或回车隔开：";
	cin >> m >> n;

	leftNum = m;
	rightNum = n;
	//欧几里得算法（辗转相除法）
	while (leftNum != 0)
	{
		tempVar = rightNum % leftNum;
		rightNum = leftNum;
		leftNum = tempVar;
	}

	//此时rightNum即为最大公约数
	greatestCommonDivisor = rightNum;

	//最小公倍数非常好求
	if (greatestCommonDivisor != 0 && m*n != 0)
	{
		leastCommonMultiple = m * n / greatestCommonDivisor;
		cout << "计算结果：" << endl;
		cout << "\t最大公约数： " << greatestCommonDivisor << endl;
		cout << "\t最小公倍数： " << leastCommonMultiple << endl;
	}
	else
	{
		cout << "您的输入可能包括0！结果异常！" << endl;
		leastCommonMultiple = 0;
	}
		
	return 0;
}