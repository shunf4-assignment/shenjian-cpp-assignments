/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>  //由于程序要用到数学函数sqrt，故应包含头文件cmath
using namespace std;

int zeller(int year, int month, int day)
{
	int c, w;
	(month < 3) && (year = year - 1, month = month + 12);
	c = year / 100, year = year % 100;
	w = year + year / 4 + c / 4 - 2 * c + 13 * (month + 1) / 5 + day - 1;
	return (w % 7);
}


int main()
{
	int y, m, d;
	while (1) {
		cout << "请依次输入年 月 日，空格隔开：";
		cin >> y >> m >> d;

		if (!(cin.rdstate() != ios_base::failbit))
		{
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		

	}
	cout << zeller(y, m, d) << endl;
	return 0;
}