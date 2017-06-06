#include <iostream>
#include <conio.h>
#include "11-b1-time.h"
#include "11-b1-datetime.h"
using namespace std;

void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

/* ----main函数不准动，也不需要提交，检查时会替换（细节可能有错，如果发现请及时提出）---- */
int main()
{
	if (1) {
		Time d1;             //2000.1.1
		Time d2(23, 54, 00);  //2017.5.18

		cout << "测试初始化，完全正确的赋值" << endl;

		cout << "d1应该是0.0.0， 实际为：";
		d1.show();
		cout << "d2应该是23.54.00，实际为：";
		d2.show();

		wait_for_enter();
	}

	if (1) {
		Time d1(-1, 3, 15);  //2000.3.15
		Time d2(24, 3, 4);   //2000.3.4
		Time d3(13, 65, 15); //2005.1.15
		Time d4(20, 5, 96);  //2017.5.1

		cout << "测试初始化，时分秒非法" << endl;

		cout << "d1应该是0.3.15，实际为：";
		d1.show();
		cout << "d2应该是0.3.4， 实际为：";
		d2.show();
		cout << "d3应该是13.0.15，实际为：";
		d3.show();
		cout << "d4应该是20.5.0， 实际为：";
		d4.show();

		wait_for_enter();
	}

	if (1) {
		Time d1, d2, d3; //都是2000.1.1

		cout << "测试set，带缺省值" << endl;
		d1.set(13, 5, 18);	//2017.5.18
		d2.set(13, 5);		//2017.5.1
		d3.set(13);		//2017.1.1

		cout << "d1应该是13.5.18，实际为：";
		d1.show();
		cout << "d2应该是13.5.0， 实际为：";
		d2.show();
		cout << "d3应该是13.0.0， 实际为：";
		d3.show();

		wait_for_enter();
	}

	if (1) {
		Time d1(17, 5, 18);
		int y, m, d;

		cout << "测试get" << endl;
		d1.get(y, m, d);

		cout << "应该y=17,m=5,d=18，实际为：";
		cout << "y=" << y << ",m=" << m << ",d=" << d << endl;

		wait_for_enter();
	}

	if (1) {
		Time d1(17, 5, 18);
		Time d2;

		cout << "测试cout" << endl;
		cout << "d1应该是17.5.18，实际为：" << d1 << endl;
		cout << "d2应该是0.0.0， 实际为：" << d2 << endl;

		wait_for_enter();
	}

	if (1) {
		Time d1;

		cout << "测试cin/cout" << endl;

		cout << "请输入17 5 18" << endl;
		cin >> d1;
		cout << "d1应该是17.5.18，实际为：" << d1 << endl;

		cout << "请输入16 2 29" << endl;
		cin >> d1;
		cout << "d1应该是16.2.29，实际为：" << d1 << endl;

		cout << "请输入17 2 76" << endl;
		cin >> d1;
		cout << "d1应该是17.2.0，实际为：" << d1 << endl;

		cout << "请输入-35 4 10" << endl;
		cin >> d1;
		cout << "d1应该是0.4.10，实际为：" << d1 << endl;

		cout << "请输入17 100 10" << endl;
		cin >> d1;
		cout << "d1应该是17.0.10，实际为：" << d1 << endl;

		cout << "请输入17 4 98" << endl;
		cin >> d1;
		cout << "d1应该是17.4.0，实际为：" << d1 << endl;

		cout << "请输入24 60 60" << endl;
		cin >> d1;
		cout << "d1应该是0.0.0，实际为：" << d1 << endl;

		wait_for_enter();
	}

	if (1) {
		Time d1(1);          //1900.1.1
		Time d2(86340);      //2099.12.31
							 //Date d3(-100);       //1900.1.1
							 //Date d4(80000);      //2099.12.31

		cout << "转换构造函数测试，包括合法及非法值" << endl;

		cout << "d1应该是0.0.1，  实际为：";
		d1.show();
		cout << "d2应该是23.59.00，实际为：";
		d2.show();
		/*cout << "d3应该是1900.1.1，  实际为：";
		d3.show();*/
		/*cout << "d4应该是2099.12.31，实际为：";
		d4.show();*/

		d1 = 36074;
		cout << "d1应该是10.1.4， 实际为：";
		d1.show();

		wait_for_enter();
	}

	if (1) {
		Time d0(0, 0, 0);
		Time d1(0, 0, 1);
		Time d2(23, 59, 59);
		Time d3(10, 2, 0);

		cout << "类型转换函数测试，包括合法及非法值" << endl;
		cout << "d0应该是0，     实际为：" << int(d0) << endl;
		cout << "d1应该是1，     实际为：" << int(d1) << endl;
		cout << "d2应该是86399， 实际为：" << int(d2) << endl;
		cout << "d3应该是36120， 实际为：" << int(d3) << endl;

		wait_for_enter();
	}

	if (1) {
		Time d1(15, 5, 18);
		Time d2;

		cout << "测试+/- n" << endl;

		d2 = d1 + 38;
		cout << "d2应该是15.5.56， 实际为：" << d2 << endl;

		d2 = 38 + d1;
		cout << "d2应该是15.5.56， 实际为：" << d2 << endl;

		d2 = d1 - 7;
		cout << "d2应该是15.5.11， 实际为：" << d2 << endl;

		d1.set(9, 59, 59);
		d2 = d1 + 5;
		cout << "d2应该是10.0.4，  实际为：" << d2 << endl;

		d1.set(10, 0, 2);
		d2 = d1 - 5;
		cout << "d2应该是9.59.57，实际为：" << d2 << endl;

		d1.set(3, 12, 31);
		d2 = d1 + 5403;
		cout << "d2应该是4.42.34，  实际为：" << d2 << endl;

		d2 = d1 - 1831;
		cout << "d2应该是2.42.0，实际为：" << d2 << endl;

		d1.set(0, 0, 1);
		d2 = d1 - 2;
		cout << "d2应该是23.59.59，  实际为：" << d2 << endl;

		d1.set(23, 59, 58);
		d2 = d1 + 5;
		cout << "d2应该是0.0.3，实际为：" << d2 << endl;

		d1.set(9, 4, 30);
		d2.set(2, 59, 58);
		cout << "d1-d2应该是21872，实际为：" << d1 - d2 << endl;

		d1.set(23, 59, 59);
		d2.set(0, 0, 0);
		cout << "d1-d2应该是86399，实际为：" << d1 - d2 << endl;

		cout << "d2-d1应该是-86399，实际为：" << d1 - d2 << endl;

		wait_for_enter();
	}

	if (1) {
		Time d1, d2;

		cout << "测试++/--" << endl;

		d1.set(17, 5, 18);
		d2 = d1++;
		cout << "d1应该是17.5.19，  实际为：" << d1 << endl;
		cout << "d2应该是17.5.18，  实际为：" << d2 << endl;

		d1.set(17, 5, 18);
		d2 = ++d1;
		cout << "d1应该是17.5.19，  实际为：" << d1 << endl;
		cout << "d2应该是17.5.19，  实际为：" << d2 << endl;

		d1.set(15, 5, 0);
		d2 = d1--;
		cout << "d1应该是15.4.59， 实际为：" << d1 << endl;
		cout << "d2应该是15.5.0，  实际为：" << d2 << endl;

		d1.set(15, 5, 0);
		d2 = --d1;
		cout << "d1应该是15.4.59， 实际为：" << d1 << endl;
		cout << "d2应该是15.4.59， 实际为：" << d2 << endl;

		d1.set(0, 0, 0);
		d2 = d1--;
		cout << "d1应该是23.59.59，实际为：" << d1 << endl;
		cout << "d2应该是0.0.0，  实际为：" << d2 << endl;

		d1.set(23, 59, 59);
		d2 = d1++;
		cout << "d1应该是0.0.0，实际为：" << d1 << endl;
		cout << "d2应该是23.59.59，实际为：" << d2 << endl;


		wait_for_enter();
	}


	if (1) {
		/* 测试比较运算符 */
		Time d1(17, 5, 18);
		Time d2(17, 5, 18);
		Time d3(16, 4, 27);

		cout << "测试比较运算符" << endl;

		cout << "比较结果应为0，实际为：" << (d1 >  d2) << endl;
		cout << "比较结果应为1，实际为：" << (d1 >= d2) << endl;
		cout << "比较结果应为0，实际为：" << (d1 <  d2) << endl;
		cout << "比较结果应为1，实际为：" << (d1 <= d2) << endl;
		cout << "比较结果应为1，实际为：" << (d1 == d2) << endl;
		cout << "比较结果应为0，实际为：" << (d1 != d2) << endl;

		cout << "比较结果应为1，实际为：" << (d1 >  d3) << endl;
		cout << "比较结果应为1，实际为：" << (d1 >= d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 <  d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 <= d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 == d3) << endl;
		cout << "比较结果应为1，实际为：" << (d1 != d3) << endl;

		wait_for_enter();
	}

	return 0;
}