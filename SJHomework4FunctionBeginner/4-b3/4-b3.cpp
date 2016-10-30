/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

void daxie(int num, int flag_of_zero)
{
	switch (num) {
	case 0:
		if (flag_of_zero)	//此标记什么意思请自行思考
			cout << "零";
		break;
	case 1:
		cout << "壹";
		break;
	case 2:
		cout << "贰";
		break;
	case 3:
		cout << "叁";
		break;
	case 4:
		cout << "肆";
		break;
	case 5:
		cout << "伍";
		break;
	case 6:
		cout << "陆";
		break;
	case 7:
		cout << "柒";
		break;
	case 8:
		cout << "捌";
		break;
	case 9:
		cout << "玖";
		break;
	default:
		cout << "error";
		break;
	}
}

int main()
{
	double inputNum, inputNumCopy;
	int d10, d9, d8, d7, d6, d5, d4, d3, d2, d1, dm1, dm2;

//REINPUT:
	bool startToPrintOut = false;  //用来指示程序有没有开始输出了，没有这个的话，输出"10"会当作前面有东西进而输出“零拾”

	cout << "请输入待转换的金额数：(0.01到100亿) ";
	cin >> inputNum;
	inputNumCopy = inputNum;

	inputNumCopy -= (d10 = (int)(inputNumCopy / 1e9)) * 1e9;
	inputNumCopy -= (d9 = (int)(inputNumCopy / 1e8)) * 1e8;
	inputNumCopy -= (d8 = (int)(inputNumCopy / 1e7)) * 1e7;
	inputNumCopy -= (d7 = (int)(inputNumCopy / 1e6)) * 1e6;
	inputNumCopy -= (d6 = (int)(inputNumCopy / 1e5)) * 1e5;
	inputNumCopy -= (d5 = (int)(inputNumCopy / 1e4)) * 1e4;
	inputNumCopy -= (d4 = (int)(inputNumCopy / 1e3)) * 1e3;
	inputNumCopy -= (d3 = (int)(inputNumCopy / 1e2)) * 1e2;
	inputNumCopy -= (d2 = (int)(inputNumCopy / 1e1)) * 1e1;
	inputNumCopy -= (d1 = (int)(inputNumCopy));

	inputNumCopy = (int)(inputNumCopy * 100 + 0.5);
	inputNumCopy -= (dm1 = (int)(inputNumCopy / 10)) * 10;
	inputNumCopy -= (dm2 = (int)(inputNumCopy));

	cout << "分解结果：" << endl;
	cout << "\t十亿位： " << d10 << endl;
	cout << "\t  亿位： " << d9 << endl;
	cout << "\t千万位： " << d8 << endl;
	cout << "\t百万位： " << d7 << endl;
	cout << "\t十万位： " << d6 << endl;
	cout << "\t  万位： " << d5 << endl;
	cout << "\t  千位： " << d4 << endl;
	cout << "\t  百位： " << d3 << endl;
	cout << "\t  十位： " << d2 << endl;
	cout << "\t    圆： " << d1 << endl;
	cout << "\t    角： " << dm1 << endl;
	cout << "\t    分： " << dm2 << endl;
	cout << "大写：";

	//处理十亿位和亿位
	if (d10)
	{
		daxie(d10, false);
		cout << "拾";
		startToPrintOut = true;
	}
	if (d9)
	{
		daxie(d9, false);
		startToPrintOut = true;
	}
	if (d10 != 0 || d9 != 0)
	{
		cout << "亿";
	}

	//处理“万”
	daxie(d8, (d7 != 0 || d6 != 0 || d5 != 0) && startToPrintOut);
	if (d8)
	{
		cout << "仟";
		startToPrintOut = true;
	}

	daxie(d7, ((d6 != 0 || d5 != 0) && (d8 != 0)) && startToPrintOut);
	if (d7)
	{
		cout << "佰";
		startToPrintOut = true;
	}

	daxie(d6, ((d5 != 0) && (d7 != 0)) && startToPrintOut);
	if (d6)
	{
		cout << "拾";
		startToPrintOut = true;
	}

	daxie(d5, false);
	if (d5)
	{
		startToPrintOut = true;
	}
	if (d8 != 0 || d7 != 0 || d6 != 0 || d5 != 0)
	{
		cout << "万";
	}

	//处理“圆”
	daxie(d4, ((d3 != 0 || d2 != 0 || d1 != 0) && startToPrintOut));
	if (d4)
	{
		cout << "仟";
		startToPrintOut = true;
	}

	daxie(d3, (((d2 != 0 || d1 != 0) && (d4 != 0)) && startToPrintOut));
	if (d3)
	{
		cout << "佰";
		startToPrintOut = true;
	}

	daxie(d2, (((d1 != 0) && (d3 != 0)) && startToPrintOut));
	if (d2)
	{
		cout << "拾";
		startToPrintOut = true;
	}

	daxie(d1, !(inputNum));
	if (d1)
	{
		startToPrintOut = true;
	}
	if (d10 || d9 || d8 || d7 || d6 || d5 || d4 || d3 || d2 || d1)
		cout << "圆";

	//处理角和分
	//发现没有，要输出“整”字的充要条件是：分为0，并且整个数不为0.
	daxie(dm1, (((d10 || d9 || d8 || d7 || d6 || d5 || d4 || d3 || d2 || d1) && dm2) && startToPrintOut));
	if (dm1)
	{
		cout << "角";
		startToPrintOut = true;
	}

	daxie(dm2, false);
	if (dm2)
	{
		cout << "分";
		startToPrintOut = true;
	}
	else
	{
		if (inputNum)
			cout << "整";
	}

	if (!(inputNum))
		cout << "圆整";

	cout << endl;

	//goto REINPUT;

	return 0;
}