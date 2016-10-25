/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;


int main()
{
	double upperLimit = 1, lowerLimit = 0, mediumX, upperValue, lowerValue, mediumValue, precision;

	cout << "方程 2x^3-9x^2+12x-3=0 在 (0,1) 的解如下：" << endl;
	
	mediumX = (upperLimit + lowerLimit) / 2;
	do
	{
		upperValue = 2 * upperLimit * upperLimit * upperLimit - 9 * upperLimit *upperLimit + 12 * upperLimit - 3;
		lowerValue = 2 * lowerLimit * lowerLimit * lowerLimit - 9 * lowerLimit *lowerLimit + 12 * lowerLimit - 3;
		mediumValue = 2 * mediumX * mediumX * mediumX - 9 * mediumX *mediumX + 12 * mediumX - 3;

		if (mediumValue * upperValue > 1e-12)
		{
			upperLimit = mediumX;
		}
		else if (mediumValue * upperValue < -1e-12)
		{
			lowerLimit = mediumX;
		}
		else
		{
			break;
		}
		precision = fabs(upperLimit - lowerLimit);
		mediumX = (upperLimit + lowerLimit) / 2;
	} while (precision >= 1e-5);

	cout << "x = " << setiosflags(ios::fixed) << setprecision(7) << mediumX;
	cout << "，误差不大于 " << precision << endl;

	return 0;
}