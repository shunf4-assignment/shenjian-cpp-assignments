/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int y, m, dayForThisMonth, leapYear, w, weekLoop, dayLoop;
	bool valid;
	valid = false;  //初值置为false，是为了在下一步进入循环

	while (!valid)
	{
		cout << "请依次输入年(2000-2030)和月份(1-12)，空格隔开：";
		cin >> y >> m;


		valid = true;
		if (y < 2000 || y > 2030)
		{
			cout << "年份非法，请重新输入" << endl;
			valid = false;
		}
		else
		{
			leapYear = ((y % 400 == 0) || (y % 100 != 0 && y % 4 == 0));
			dayForThisMonth = 30;
			if (m > 7 && m <= 12)
			{
				dayForThisMonth += ((m + 1) % 2);
			}
			else if (m >= 1 && m <= 7 && m != 2)
			{
				dayForThisMonth += (m % 2);
			}
			else if (m == 2)
			{
				dayForThisMonth -= 1;
				dayForThisMonth -= !leapYear;  //使该月的日子数等于29或28
			}
			else
			{
				cout << "月份非法，请重新输入。" << endl;
				valid = false;
			}
		}
	}

	valid = false;
	while (!valid)
	{
		cout << "请输入该月第一天的星期（0-6，其中0表示星期天）" << endl;
		cin >> w;
		valid = true;
		if (w < 0 || w > 6)
		{
			cout << "星期填写无效，请重新填写" << endl;
			valid = false;
		}
	}

	cout << "该月的月历如下：" << endl;
	cout << "日  一  二  三  四  五  六" << endl;

	dayLoop = 1 - w;  //第一天不是周日的时候，要输出空格，那么在循环中需要对应处理，需要输出空格的标志即为dayLoop非正数
	weekLoop = 0;  //在循环中记录当前输出日期（或空白）对应的星期

	while (dayLoop <= dayForThisMonth)
	{
		if (weekLoop != 0)
			cout << "  ";
		if (dayLoop > 0)
		{
			cout << setw(2) << dayLoop;
		}
		else
		{
			cout << "  ";
		}

		if (weekLoop == 6)
			cout << endl;
		
		weekLoop = (weekLoop + 1) % 7;
		dayLoop += 1;
	}
	cout << endl;
	
	return 0;
}