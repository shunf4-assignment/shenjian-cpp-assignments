/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;
#define out0 cout << "零"
#define nout cout << ""
#define outthis (toOut == 1) ? (cout << "壹") : (nout),(toOut == 2) ? (cout << "贰") : (nout),(toOut == 3) ? (cout << "叁") : (nout),(toOut == 4) ? (cout << "肆") : (nout),(toOut == 5) ? (cout << "伍") : (nout),(toOut == 6) ? (cout << "陆") : (nout),(toOut == 7) ? (cout << "柒") : (nout),(toOut == 8) ? (cout << "捌") : (nout),(toOut == 9) ? (cout << "玖") : (nout),(toOut == 0) ? (cout << "零") : (nout)

#define groupOutput ((!p1) ? ((!zeroPut && (p2 + p3 + p4)) ? (zeroPut = true, out0, z) : z) : (toOut = p1, outthis, cout << "仟", zeroPut = false, z), ((!p2) ? ((!zeroPut && (p3 + p4)) ? (zeroPut = true, out0, z) : z) : (toOut = p2, outthis, cout << "佰", zeroPut = false, z)), ((!p3) ? ((!zeroPut && (p4)) ? (zeroPut = true, out0, z) : z) : (toOut = p3, outthis, cout << "拾", zeroPut = false, z)), ((!p4) ? (z) : (toOut = p4, outthis, zeroPut = false, z)))

int main()
{
	double inputNum, inputNumCopy;
	int d10, d9, d8, d7, d6, d5, d4, d3, d2, d1, dm1, dm2, p1, p2, p3, p4, toOut;
	bool zeroPut = true, z = 0, hasYuan = false;  //zeroPut的初始值置为true是因为避免出现 “零十亿”

	cout << "请输入待转换的金额数：(0.01到100亿) ";
	cin >> inputNum;
	inputNumCopy = inputNum;

	(((((((((inputNumCopy -= (d10 = (int)(inputNumCopy / 1e9)) * 1e9) -= (d9 = (int)(inputNumCopy / 1e8)) * 1e8) -= (d8 = (int)(inputNumCopy / 1e7)) * 1e7) -= (d7 = (int)(inputNumCopy / 1e6)) * 1e6) -= (d6 = (int)(inputNumCopy / 1e5)) * 1e5) -= (d5 = (int)(inputNumCopy / 1e4)) * 1e4) -= (d4 = (int)(inputNumCopy / 1e3)) * 1e3) -= (d3 = (int)(inputNumCopy / 1e2)) * 1e2) -= (d2 = (int)(inputNumCopy / 1e1)) * 1e1) -= (d1 = (int)(inputNumCopy));  //整数部分

	inputNumCopy = (int)(inputNumCopy * 100 + 0.5);  //小数部分
	(inputNumCopy -= (dm1 = (int)(inputNumCopy / 10)) * 10) -= (dm2 = (int)(inputNumCopy));

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
	cout << "\t  个位： " << d1 << endl;
	cout << "\t十分位： " << dm1 << endl;
	cout << "\t百分位： " << dm2 << endl;
	
	cout << "大写：";

	hasYuan = !!(d10 + d9 + d8 + d7 + d6 + d5 + d4 + d3 + d2 + d1);
	p1 = 0, p2 = 0, p3 = d10, p4 = d9, groupOutput, (p1 + p2 + p3 + p4) && (cout << "亿");  //用&&相当于用if，因为短路运算
	p1 = d8, p2 = d7, p3 = d6, p4 = d5, groupOutput, (p1 + p2 + p3 + p4) && (cout << "万");
	p1 = d4, p2 = d3, p3 = d2, p4 = d1, groupOutput, hasYuan && (cout << "圆");

	(!dm1) ? ((hasYuan && dm2) ? (out0) : (nout)) : (toOut = dm1, outthis, cout << "角"), (!dm2) ? (!!(inputNum) && (cout << "整"), z) : (toOut = dm2, outthis, cout << "分", z);

	(!(inputNum)) && (cout << "零圆整");

	cout << endl << "程序运行结束。" << endl;

	return 0;
}