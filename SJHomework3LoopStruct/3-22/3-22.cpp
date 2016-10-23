/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;


int main()
{
	int peachNum = 1; //第九天桃子数，也就等于第十天吃之前的桃子数。（这里讲的桃子数都是指第n天吃后的桃子数）
	int day = 9;  //现在是第十天，但是桃子数当第九天算

	//cout << "第 " << day + 1 << " 天，吃之前有 " << peachNum << " 个桃子，猴子一脸懵逼" << endl;

	for (; day >= 1; day--)  //时光倒流
	{
		//cout << "第 " << day << " 天，吃之前有 " << (peachNum + 1) * 2 << " 个桃子，吃了之后剩下 " << peachNum << " 个。" << endl;
		peachNum = (peachNum + 1) * 2;
	}
	
	cout << "第一天摘下了 " << peachNum << " 个桃子。" << endl;

	return 0;
}