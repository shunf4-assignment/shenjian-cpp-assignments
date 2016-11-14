/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>
using namespace std;

int fac(int n)
{
	int r = 1;
	while (n > 1)
	{
		r *= n--;
	}
	return r;
}

int getDigit(int n, int digit, int allDigit = -1)
{
	if (allDigit == -1)
	{
		allDigit = (int)log10(n) + 1;
	}

	return n / (int)pow(10, allDigit - 1 - digit) % 10;
}

int fullArrangement(int digitNum, int seqNum)
{
	if (digitNum == 1)
		return 1;

	int prevNum, keyTenPow, toInsertDigit, nowNum;
	prevNum = fullArrangement(digitNum - 1, seqNum / digitNum);
	toInsertDigit = seqNum % digitNum;
	keyTenPow = (int)pow(10, toInsertDigit);
	nowNum = (prevNum / keyTenPow * 10 + digitNum) * keyTenPow + prevNum % keyTenPow;

	return nowNum;
}

int main()
{
	//REINPUT:
	int n;
	bool valid;

	do
	{
		valid = true;
		cout << "请输入：";
		cin >> n;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (n <= 0)
		{
			valid = false;
			cout << "输入超出范围，请重新输入。" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

	} while (!valid);
	//cout << fac(n);
	for (int x = 0; x < fac(n); x++)
	{
		int thisFullArr = fullArrangement(n, x);
		for (int j = 0; j < n; j++)
		{
			(j != 0) && (cout << " ");
			cout << getDigit(thisFullArr, j, n);
		}
		cout << endl;
	}
	
	//goto REINPUT;
	return 0;
}
