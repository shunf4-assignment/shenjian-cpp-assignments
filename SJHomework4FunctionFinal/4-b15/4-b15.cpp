/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

bool debug = false;

double elementaryCalc(double num1, double num2, int opType, bool reversed = false)
{
	//0加，1减，2乘，3除以，4反减，5反除以
	switch (opType)
	{
		case 0:
			debug && (cout << num1 << '+' << num2 << "=" << num1 + num2 << endl);
			return num1 + num2;
		case 4:
			reversed = !reversed;
			debug && (cout << "(rev)" << endl);
		case 1:
			debug && (cout << num1 << '-' << num2 << "=" << (!reversed ? num1 - num2 : num2 - num1) << endl);
			return !reversed ? num1 - num2 : num2 - num1;
		case 2:
			debug && (cout << num1 << '*' << num2 << "=" << (num1 * num2) << endl);
			return num1 * num2;
		case 5:
			reversed = !reversed;
			debug && (cout << "(rev)" << endl);
		case 3:
			debug && (cout << num1 << '/' << num2 << "=" << (!reversed ? num1 / num2 : num2 / num1) << endl);
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
	if (order == 1 || order == 4)
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
	if (order == 0 || order == 4)
	{
		cout << ")";
	}
	cout << operationChar(op2);
	if (order == 3 || order == 4)
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
	if (order == 2 || order == 4)
	{
		cout << ")";
	}
	if (order == 3)
	{
		cout << "))";
	}
}

bool searchInCertainOrder(int a_, int b_, int c_, int d_, int order)
{
	//固定运算顺序a-b-c-d，遍历三个符号，搜索值为24的值，成功返回1，否则0
	double a, b, c, d;
	int op1, op2, op3;
	double expressionResult = 0;
	double depth1Result = 0;
	double depth2Result = 0;
	double depth3Result = 0;
	bool solutionExist = false;

	switch (order)
	{
		case 0:
			a = (double)a_;
			b = (double)b_;
			c = (double)c_;
			d = (double)d_;
			break;
		case 1:
			a = (double)b_;
			b = (double)c_;
			c = (double)a_;
			d = (double)d_;
			break;
		case 2:
			a = (double)b_;
			b = (double)c_;
			c = (double)d_;
			d = (double)a_;
			break;
		case 3:
			a = (double)c_;
			b = (double)d_;
			c = (double)b_;
			d = (double)a_;
			break;
		case 4:
			a = (double)a_;
			b = (double)b_;
			c = (double)c_;
			d = (double)d_;
			break;
	}

	for (int op1_ = 0; op1_ <= 3; op1_++)
	{
		depth1Result = elementaryCalc(a, b, op1_);
		if (debug)
		{
			cout << "order: " << order << endl;
			cout << "  1)" << depth1Result << endl;
		}
		for (int op2_ = 0; op2_ <= 3; op2_++)
		{
			if (order == 4)
				depth2Result = elementaryCalc(c, d, op2_);
			else if (order == 1 || order == 3)
				depth2Result = elementaryCalc(c, depth1Result, op2_);
			else
				depth2Result = elementaryCalc(depth1Result, c, op2_);
			
			if (debug)
			{
				cout << "    2)" << depth2Result << endl;
			}
			for (int op3_ = 0; op3_ <= 3; op3_++)
			{
				if (order == 4)
					depth3Result = elementaryCalc(depth1Result, depth2Result, op3_);
				else if (order == 2 || order == 3)
					depth3Result = elementaryCalc(d, depth2Result, op3_);
				else
					depth3Result = elementaryCalc(depth2Result, d, op3_);
				
				switch (order)
				{
					case 0:
						op1 = op1_;
						op2 = op2_;
						op3 = op3_;
						break;
					case 1:
						op1 = op2_;
						op2 = op1_;
						op3 = op3_;
						break;
					case 2:
						op1 = op3_;
						op2 = op1_;
						op3 = op2_;
						break;
					case 3:
						op1 = op3_;
						op2 = op2_;
						op3 = op1_;
						break;
					case 4:
						op1 = op1_;
						op2 = op3_;
						op3 = op2_;
						break;
				}
				if (debug)
				{
					cout << "      3)" << depth3Result << endl;
					cout << "        f)";
					outputInOrder(a_, b_, c_, d_, op1, op2, op3, order);
					cout << " = " << depth3Result << endl;
				}
				

				if (fabs(depth3Result - 24) < 1e-6)
				{
					outputInOrder(a_, b_, c_, d_, op1, op2, op3, order);
					(!solutionExist) && (solutionExist = true);
					cout << "=24" << endl;
				}
			}
		}
	}

	return solutionExist;
}

bool calc24(int a, int b, int c, int d)
{
	bool solutionExist = false;
	for (int order = 0; order <= 4; order++)
	{
		solutionExist = searchInCertainOrder(a, b, c, d, order) || solutionExist;
	}
	return solutionExist;
}

int main()
{
	//REINPUT:
	int a, b, c, d;
	bool valid, solutionExist;

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

	solutionExist = calc24(a, b, c, d);
	if (!solutionExist)
	{
		cout << "无解" << endl;
	}

	//goto REINPUT;
	return 0;
}
