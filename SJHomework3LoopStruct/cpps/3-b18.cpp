/* 1652270 �����2�� ��˴ */
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

	cout << "ƴ�������" << endl;
	cout << "������������";
	cin >> userNum;
	cout << "�������";
	cin >> money;
	cout << "������֧�����룺jj520" << endl;
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
		moneyThisPerson = int(moneyThisPerson * 100 + 0.5) * 1. / 100; //��ȥ�ڶ�λС���ĺ���

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
				cout << "���";
			if (i == 1)
				cout << "1652270-��2-��˴";
			if (i == 2)
				cout << "���ῢ�Ც"; 
			if (i == 3)
				cout << "÷���";
			if (i == 4)
				cout << "��Դ����";
			if (i == 5)
				cout << "ʯ���ִ���";

		}
		else
			cout << "��� " << i + 1;
		cout << "   ������ ��" << moneyThisPerson;
		cout << " ��ʣ " << moneyCopy;
		cout << endl;

		
	}

	cout << endl;

	QueryPerformanceCounter(&fc_end);
	cout << "��ĺ�� ";
	cout << setprecision(6) << double(fc_end.QuadPart - fc_begin.QuadPart) / double(tick.QuadPart) << "��";
	cout << "�����꣬";

	i = currMaximumOwner;
	if (i <= 5)
	{
		if (i == 0)
			cout << "���";
		if (i == 1)
			cout << "1652270-��2-��˴";
		if (i == 2)
			cout << "���ῢ�Ც";
		if (i == 3)
			cout << "÷���";
		if (i == 4)
			cout << "��Դ����";
		if (i == 5)
			cout << "ʯ���ִ���";

	}
	else
		cout << "��� " << i + 1;

	cout << " ����������TA������ ��";
	cout << setiosflags(ios::fixed) << setprecision(2) << currMaximum << endl;

	return 0;
}

