/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cmath>
using namespace std;

double elementaryCalc(double num1, double num2, int opType, bool reversed = false)
{
	//0加，1减，2乘，3除以，4反减，5反除以
	switch (opType)
	{
		case 0:
			return num1 + num2;
		case 4:
			reversed = !reversed;
		case 1:
			return !reversed ? num1 - num2 : num2 - num1;
		case 2:
			return num1 * num2;
		case 5:
			reversed = !reversed;
		case 3:
			return !reversed ? num1 / num2 : num2 / num1;
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
	if (order == 0)
	{
		cout << "((";
	}
	if (order == 1)
	{
		cout << "(";
	}
	cout << a;
	cout << operationChar(op1);
	if (order == 1 || order == 3)
	{
		cout << "(";
	}
	if (order == 2)
	{
		cout << "((";
	}
	cout << b;
	if (order == 0)
	{
		cout << ")";
	}
	cout << operationChar(op2);
	if (order == 3)
	{
		cout << "(";
	}
	cout << c;
	if (order == 0 || order == 2)
	{
		cout << ")";
	}
	if (order == 1)
	{
		cout << "))";
	}
	cout << operationChar(op3);
	cout << d;
	if (order == 2)
	{
		cout << ")";
	}
	if (order == 3)
	{
		cout << "))";
	}
}


/*
order:
0: 0 1 2
1: 1 0 2
2: 1 2 0
3: 2 1 0
*/
bool searchInCertainOrder(int a_, int b_, int c_, int d_, int order)
{
	//固定运算顺序a-b-c-d，遍历三个符号，搜索值为24的值，成功返回1，否则0
	/*//注意，此时减运算和除运算的顺序没有确定，即输入1 2 3 4的时候
	//	在加法上只会测试(1+2)...
	//	而减法上会测试(1-2)...和(2-1)...*/
	double a, b, c, d;
	double expressionResult = 0;
	double depth1Result = 0;
	double depth2Result = 0;
	double depth3Result = 0;
	bool solutionExist = false;

	switch (order)
	{
		case 0:
			a = a_;
			b = b_;
			c = c_;
			d = d_;
		case 1:
			a = b_;
			b = c_;
			c = a_;
			d = d_;
		case 2:
			a = a_;
			b = b_;
			c = c_;
			d = d_;
	}

	for (int op1 = 0; op1 <= 3; op1++)
	{
		expressionResult = (double)a;
		expressionResult = elementaryCalc(expressionResult, (double)b, op1);
		depth1Result = expressionResult;
		cout << "  1)" << depth1Result << endl;
		for (int op2 = 0; op2 <= 3; op2++)
		{
			expressionResult = elementaryCalc(depth1Result, (double)c, op2);
			depth2Result = expressionResult;
			cout << "    2)" << depth2Result << endl;
			for (int op3 = 0; op3 <= 3; op3++)
			{
				expressionResult = elementaryCalc(depth2Result, (double)d, op3);
				depth3Result = expressionResult;
				cout << "      3)" << depth3Result << endl;
				cout << "        f)";
				outputInOrder(a, b, c, d, op1, op2, op3, order);
				cout << " = " << expressionResult << endl;
				
				if (fabs(expressionResult - 24) < 1e-6)
				{
					outputInOrder(a, b, c, d, op1, op2, op3, order);
					(!solutionExist) && (solutionExist = true);
					cout << "=24"  << endl;
				}
			}
		}
	}

	return solutionExist;
}

bool calc24(int a, int b, int c, int d)
{
	bool solutionExist = false;
	for (int order = 0; order <= 3; order++)
	{
			solutionExist = searchInCertainOrder(a, b, c, d, order) || solutionExist;
	}
	return solutionExist;
}

int main()
{
	//REINPUT:
	int a, b, c, d;
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

	calc24(a, b, c, d);
	cout << endl;
	//goto REINPUT;
	return 0;
}
