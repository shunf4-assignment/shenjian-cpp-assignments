/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

bool debug = false;

int fac(int n)
{
	int r = 1;
	while (n > 1)
		r *= n--;
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

double elementaryCalc(double num1, double num2, int opType)
{
	switch (opType)
	{
		case 0:
			debug && (cout << num1 << '+' << num2 << "=" << num1 + num2 << endl);
			return num1 + num2;
		case 4:
			debug && (cout << num2 << '-' << num1 << "=" << num2 - num1 << endl);
			return num2 - num1;
		case 1:
			debug && (cout << num1 << '-' << num2 << "=" << num1 - num2 << endl);
			return num1 - num2;
		case 2:
			debug && (cout << num1 << '*' << num2 << "=" << (num1 * num2) << endl);
			return num1 * num2;
		case 5:
			debug && (cout << num2 << '/' << num1 << "=" << num2 / num1 << endl);
			return num2 / num1;
		case 3:
			debug && (cout << num1 << '/' << num2 << "=" << num1 / num2  << endl);
			return num1 / num2;
	}
	return 0;
}


char operationChar(int opType)
{
	//0加，1减，2乘，3除以，4反减，5反除以
	switch (opType)
	{
		case 0:
			return '+';
		case 4:
		case 1:
			return '-';
		case 2:
			return '*';
		case 5:
		case 3:
			return '/';
	}
	return '?';
}

void outputInOrder(int a, int b, int c, int d, int op1, int op2, int op3, int order)
{
	switch (order)
	{
		case 0:
			printf("((%i%c%i)%c%i)%c%i", a, operationChar(op1), b, operationChar(op2), c, operationChar(op3), d);
			return;
		case 1:
			printf("(%i%c(%i%c%i))%c%i", a, operationChar(op1), b, operationChar(op2), c, operationChar(op3), d);
			return;
		case 2:
			printf("%i%c((%i%c%i)%c%i)", a, operationChar(op1), b, operationChar(op2), c, operationChar(op3), d);
			return;
		case 3:
			printf("%i%c(%i%c(%i%c%i))", a, operationChar(op1), b, operationChar(op2), c, operationChar(op3), d);
			return;
		case 4:
			printf("(%i%c%i)%c(%i%c%i)", a, operationChar(op1), b, operationChar(op2), c, operationChar(op3), d);
			return;
	}
}

int calc24InCertainArrangement(int a, int b, int c, int d)
{
	int op1, op2, op3, order, count = 0;
	double expressionResult;
	for (op1 = 0; op1 <= 3; op1++)
	{
		for (op2 = 0; op2 <= 3; op2++)
		{
			for (op3 = 0; op3 <= 3; op3++)
			{
				for (order = 0; order <= 4; order++)
				{
					switch (order)
					{
						case 0:
							expressionResult = elementaryCalc((double)a, (double)b, op1);
							expressionResult = elementaryCalc(expressionResult, (double)c, op2);
							expressionResult = elementaryCalc(expressionResult, (double)d, op3);
							break;
						case 1:
							expressionResult = elementaryCalc((double)b, (double)c, op2);
							expressionResult = elementaryCalc((double)a, expressionResult, op1);
							expressionResult = elementaryCalc(expressionResult, (double)d, op3);
							break;
						case 2:
							expressionResult = elementaryCalc((double)b, (double)c, op2);
							expressionResult = elementaryCalc(expressionResult, (double)d, op3);
							expressionResult = elementaryCalc((double)a, expressionResult, op1);
							break;
						case 3:
							expressionResult = elementaryCalc((double)c, (double)d, op3);
							expressionResult = elementaryCalc((double)b, expressionResult, op2);
							expressionResult = elementaryCalc((double)a, expressionResult, op1);
							break;
						case 4:
							expressionResult = elementaryCalc(elementaryCalc((double)a, (double)b, op1), elementaryCalc((double)c, (double)d, op3), op2);
							break;
					}
					if (fabs(expressionResult - 24) < 1e-6)
					{
						outputInOrder(a, b, c, d, op1, op2, op3, order);
						cout << "=24" << endl;
						count += 1;
					}
				}

			}
		}
	}

	return count;
}

int getWhichOne(int a, int b, int c, int d, int whichOne)
{
	switch (whichOne)
	{
		case 0:
			return a;
		case 1:
			return b;
		case 2:
			return c;
		case 3:
			return d;
		default:
			return 0;
	}
}

int calc24(int a, int b, int c, int d)
{
	int arrangementMap, count = 0, thisCount;
	for (int i = 0; i < 24; i++)
	{
		bool jumpOut = false;
		arrangementMap = fullArrangement(4, i);
		debug && (cout << arrangementMap << endl);
		for (int k = 0; k < 4; k++ && !jumpOut)
		{
			for (int l = k + 1; l < 4; l++ && !jumpOut)
			{
				if (getWhichOne(a, b, c, d, getDigit(arrangementMap, k, 4) - 1) == getWhichOne(a, b, c, d, getDigit(arrangementMap, l, 4) - 1) && getDigit(arrangementMap, l, 4) > getDigit(arrangementMap, k, 4))
				{
					jumpOut = true;
				}
			}
		}
		if (jumpOut)
			continue;
		
		thisCount = calc24InCertainArrangement(getWhichOne(a, b, c, d, getDigit(arrangementMap, 0, 4) - 1), getWhichOne(a, b, c, d, getDigit(arrangementMap, 1, 4) - 1), getWhichOne(a, b, c, d, getDigit(arrangementMap, 2, 4) - 1), getWhichOne(a, b, c, d, getDigit(arrangementMap, 3, 4) - 1));
		count += thisCount;
		if (thisCount)
			cout << endl;
	}
	return count;
}


int main()
{
	//REINPUT:
	int a, b, c, d, count;
	bool valid;

	do
	{
		valid = true;
		cout << "请输入四个1~10的整数：";
		cin >> a >> b >> c >> d;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (a <= 0 || b <= 0 || c <= 0 || c <= 0 || a > 10 || b > 10 || c > 10 || c > 10)
		{
			valid = false;
			cout << "输入超出范围，请重新输入。" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

	} while (!valid);

	count = calc24(a, b, c, d);
	if (!count)
	{
		cout << "无解" << endl;
	}
	else
	{
		cout << "共有 " << count << " 种算法。" << endl;
	}
	//goto REINPUT;
	return 0;
}