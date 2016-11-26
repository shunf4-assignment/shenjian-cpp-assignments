/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>
using namespace std;

double triArea(double x1, double y1, double x2, double y2, double x3, double y3)
{
	double vectorProduct = (x2 - x1)*(y2 - y3) - (y2 - y1)*(x2 - x3); //叉积
	double S;
	if (fabs(vectorProduct) < 1e-8) {
		//数学方法，两组向量若平行，等价于三点不能构成三角形
		return 0;
	}
	else
	{
		S = fabs(vectorProduct) / 2;
		return S;
	}
}

double polyArea(double polyCoord[][2], int coordNum)
{
	double totalS = 0;
	for (int i = 1; i < coordNum - 1; i++)
	{
		totalS += triArea(polyCoord[0][0], polyCoord[0][1], polyCoord[i][0], polyCoord[i][1], polyCoord[i + 1][0], polyCoord[i + 1][1]);
		//cout << totalS << endl;
	}
	return totalS;
}

void notPolygon(int i)
{
	cout << "这不是一个 " << i << " 边形！" << endl;
	return;
}

void concavePoly(int i)
{
	cout << "这是一个凹 " << i << " 边形。" << endl;
	return;
}

int main()
{
	//REINPUT:
	int coordNum;
	const int maxCoordNum = 7;
	double coord[maxCoordNum][2];
	double thisVectorProduct, polyA;
	bool valid, thisPositive, polyValid = true;

	do
	{
		valid = true;
		cout << "几对直角坐标？(4-" << maxCoordNum << ")";
		cin >> coordNum;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (coordNum < 4 || coordNum > maxCoordNum)
		{
			valid = false;
			cout << "输入超出范围，请重新输入。" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

	} while (!valid);
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	do
	{
		valid = true;
		cout << "按顺/逆时针输入坐标 x1 y1 x2 y2 x3 y3 ... ，共输入 " << coordNum << " 对， "<< coordNum *2 << " 个实数：";
		
		for (int i = 0; i < coordNum; i++)
		{
			cin >> coord[i][0];
			cin >> coord[i][1];
			if (!cin.good())
			{
				break;
			}
		}

		if (!cin.good())
		{
			valid = false;
			cout << endl << "输入类型错误，请从头开始输入坐标。" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
	} while (!valid);
	
	for (int i = 0; i < coordNum - 2; i++)
	{
		double vector1[] = { coord[(i + 1) % coordNum][0] - coord[i][0], coord[(i + 1) % coordNum][1] - coord[i][1] };
		double vector2[] = { coord[(i + 2) % coordNum][0] - coord[(i + 1) % coordNum][0], coord[(i + 2) % coordNum][1] - coord[(i + 1) % coordNum][1] };
		thisVectorProduct = vector1[0] * vector2[1] - vector2[0] * vector1[1];
		//thisDotProduct = vector1[0] * vector2[1] - vector2[0] * vector1[1];
		if (fabs(thisVectorProduct) < 1e-8)
		{
			notPolygon(coordNum);
			polyValid = false;
			break;
		}
		if (i == 0)
		{
			if (thisVectorProduct > 0)
			{
				//cout << "Positive" << endl;
				thisPositive = true;
			}
			else
			{
				//cout << "Negative" << endl;
				thisPositive = false;
			}
		}
		else
		{
			/*if (thisVectorProduct > 0)
			{
				cout << "Positive" << endl;
			}
			else
			{
				cout << "Negative" << endl;
			}*/
			if (thisPositive ^ (thisVectorProduct > 0))
			{
				concavePoly(coordNum);
				polyValid = false;
				break;
			}
		}
	}

	if (polyValid)
	{
		polyA = polyArea(coord, coordNum);
		cout << "这是一个凸 " << coordNum << " 边形。\n它的面积 S = " << polyA << endl;
	}

	//goto REINPUT;
	return 0;
}
