/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

int main()
{
	int i1, i2, i3, i4;
	int tmp;  //中间变量，用来交换变量用
	int intlabel, minimum;  //记号变量

	cout << "输入四个整数，依次用空格隔开，或是用回车隔开输入四次。" << endl << "请输入：";
	cin >> i1 >> i2 >> i3 >> i4;
	cout << endl;

	intlabel = 1;
	minimum = i1;
	intlabel = (minimum > i2) ? (minimum = i2, 2) : (intlabel);
	intlabel = (minimum > i3) ? (minimum = i3, 3) : (intlabel);
	intlabel = (minimum > i4) ? (minimum = i4, 4) : (intlabel);  //将minimum与数字逐个比较，选出最小值，并且将最小值对应的序号赋值给intlabel

	//将最小的数字和i1做一个交换
	tmp = i1;
	i1 = minimum;
	(intlabel == 2) ? (i2 = tmp) : (i2);
	(intlabel == 3) ? (i3 = tmp) : (i3);
	(intlabel == 4) ? (i4 = tmp) : (i4);

	//接下来只需要对i2 i3 i4排序即可
	if (i2 > i3)
	{
		tmp = i2;
		i2 = i3;
		i3 = tmp;
	}

	if (i4 < i2)
	{
		tmp = i2;
		i2 = i4;
		i4 = i3;
		i3 = tmp;
	}
	else if (i4 >= i2 && i4 < i3)
	{
		tmp = i4;
		i4 = i3;
		i3 = tmp;
	}

	cout << "排序后结果：";
	cout << i1 << ", " << i2 << ", " << i3 << ", " << i4 << endl;

	return 0;
}