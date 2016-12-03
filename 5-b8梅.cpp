/*梅语冰 1652311 计科3班*/
#include<iostream>
using namespace std;
int main()
{
	double a[7][2], b[7][2], judge1, judge2, flag = 0;
	int i, j, m, k;
	cout << "输入坐标点的个数(4-7）:";
	while (1) {
		cin >> m;
		if (!cin.good()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请重新输入：";
		}
		else if (m >= 8 || m <= 3) {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请重新输入：";
		}
		else
			break;
	}

	cout << "请按序输入4-7对直角坐标：";
	while (1) {
		for (j = 0; j <= m - 1; j++) {
			for (i = 0; i <= 1; i++) {
				cin >> a[j][i];
				if (!cin.good()) {
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "输入错误，请重新输入：";
				}
			}
		}
		break;
	}



	for (j = 0; j <= m - 1; j++) {
		for (k = 0; k <= m - 1; k++) {
			if (j <= m - 2) {
				b[k][0] = a[j][0] - a[j + 1][0];
				b[k][1] = a[k][1] - a[k][1];
			}
			else {
				b[k][0] = a[m - 1][0] - a[0][0];
				b[k][1] = a[m - 1][1] - a[0][1];
			}
		}
	}
	//将点的坐标转成向量


		judge1 = b[k][0] * b[k + 1][1] - b[k + 1][0] * b[k][1];
		judge2 = b[k - 1][0] * b[0][1] - b[0][0] * b[k - 1][1];
		//向量叉乘判断（x1y2-x2y1)

		for (k = 0; k <= m - 2; k++) {
			if (fabs(judge1) <= 1e-6 || fabs(judge2) <= 1e-6)
				flag++;
		}
		//判断有没有三点共线，如果有三点共线，flag就++

		if (flag > 0) {
			cout << "不是" << m << "边形"<<endl;
			return 0;
		}
		//如果flag>0了，有三点共线，不是m边形，直接return 0结束程序


		flag = 0;//不三点共线，将flag归0，进行新的判断
		for (k = 0; k <= m - 2; k++) {
			if (fabs(judge1) > 0 || fabs(judge2) > 0)
				flag++;
		}
		if (flag == m)
			cout << "是凸" << m << "边形"<<endl;//每个向量叉乘都大于0，是凸多边形
		else
			cout << "不是凸" << m << "边形"<<endl;//有向量叉乘小于0，不是凸多边形

		return 0;

	}

