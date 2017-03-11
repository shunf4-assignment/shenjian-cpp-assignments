/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>
using namespace std;


int main()
{
	double x1, y1, x2, y2, x3, y3;
	double vectorProduct, S;

	cout << "请依次输入三个点的x,y坐标，共输入6个实数，用空格隔开（如2.0 3.0 3.0 4.0 4.0 5.0 表示(2,3)、(3,4)、(4,5)）" << endl;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	
	vectorProduct = (x2 - x1)*(y2 - y3) - (y2 - y1)*(x2 - x3); //叉积
	if (fabs(vectorProduct) < 1e-8) {
		//数学方法，两组向量若平行，等价于三点不能构成三角形
		cout << "这三个点不能构成三角形！" << endl;
	}
	else
	{
		S = fabs(vectorProduct) / 2;
		cout << "三个点构成三角形的面积 S = " << S << endl;
	}

	cout << "程序结束。" << endl;
	return 0;
}