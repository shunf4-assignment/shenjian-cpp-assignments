/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

bool debug = false;

//int fac(int n)
//int getDigit(int n, int digit, int allDigit = -1)
//int fullArrangement(int digitNum, int seqNum)
//int getWhichOne(int a, int b, int c, int d, int whichOne)
//int calc24(int a, int b, int c, int d)

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

	count = calc24InCertainArrangement(a, b, c, d);
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