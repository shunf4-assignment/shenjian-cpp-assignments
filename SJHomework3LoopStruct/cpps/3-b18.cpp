/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <windows.h>
using namespace std;

int main()
{
	int userNum, currMaximumOwner, i;
	double money, moneyCopy, moneyThisPerson, randomX, randomY, randomZ, randomA, currMaximum = 0;

	cout << "拼手气红包" << endl;
	cout << "请输入人数：";
	cin >> userNum;
	cout << "请输入金额：";
	cin >> money;
	cout << "请输入支付密码：jj520" << endl;
	cout << endl;

	srand((unsigned int)(time(0)));
start:


	LARGE_INTEGER tick, fc_begin, fc_end;

	QueryPerformanceFrequency(&tick);
	QueryPerformanceCounter(&fc_begin);

	moneyCopy = money;
	currMaximum = 0;
	
	cout << setiosflags(ios::fixed) << setprecision(2);

	for (i = 0; i < userNum; i++)
	{
		randomX = (rand() * 1. / 32767);
		randomY = (rand() * 1. / 32767);
		randomZ = (rand() * 1. / 32767);
		randomA = (rand() * 1. / 32767);
		moneyThisPerson = moneyCopy * randomX * 2 / (userNum - i);
		if (randomA <= ((1 - randomY) / sqrt(userNum - i +1) / sqrt(userNum)))
			moneyThisPerson = moneyCopy * randomY;
		moneyThisPerson = int(moneyThisPerson * 100 + 0.5) * 1. / 100; //舍去第二位小数的后面

		if (i == userNum - 1)
			moneyThisPerson = moneyCopy;
		
		if (moneyThisPerson < 0.01)
			moneyThisPerson = 0.01;

		if ((userNum - (i + 1)) != 0 && fabs((moneyCopy - moneyThisPerson) / (userNum - (i + 1))) < 0.01)
			moneyThisPerson = moneyCopy - (userNum - (i + 1)) * 0.01;

		moneyCopy -= moneyThisPerson;
		//moneyCopy = int(moneyCopy * 100 + 0.5) * 1. / 100;

		if (moneyThisPerson > currMaximum)
		{
			currMaximumOwner = i;
			currMaximum = moneyThisPerson;
		}

		if (i <= 5)
		{
			if (i == 0)
				cout << "沈坚";
			if (i == 1)
				cout << "1652270-计2-冯舜";
			if (i == 2)
				cout << "常♂竣♂勃"; 
			if (i == 3)
				cout << "梅语冰";
			if (i == 4)
				cout << "哲源♂王";
			if (i == 5)
				cout << "石海林大佬";

		}
		else
			cout << "玩家 " << i + 1;
		cout << "   抢到了 ￥" << moneyThisPerson;
		cout << " 还剩 " << moneyCopy;
		cout << endl;

		
	}

	cout << endl;

	QueryPerformanceCounter(&fc_end);
	cout << "你的红包 ";
	cout << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "秒";
	cout << "被抢完，";

	i = currMaximumOwner;
	if (i <= 5)
	{
		if (i == 0)
			cout << "沈坚";
		if (i == 1)
			cout << "1652270-计2-冯舜";
		if (i == 2)
			cout << "常♂竣♂勃";
		if (i == 3)
			cout << "梅语冰";
		if (i == 4)
			cout << "哲源♂王";
		if (i == 5)
			cout << "石海林大佬";

	}
	else
		cout << "玩家 " << i + 1;

	cout << " 是手气王，TA抢到了 ￥";
	cout << setiosflags(ios::fixed) << setprecision(2) << currMaximum << endl;

	return 0;
}

