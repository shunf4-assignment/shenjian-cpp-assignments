/*1652340 计算机3班 刘毅韬*/
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <fstream>
#include "90-b5-adv.h"
bigint gcd(const bigint &a, const bigint &b)
{
	return b == 0 ? a : gcd(b, a % b);
}
bigint add(const bigint &a, const bigint &b)
{
	return const_cast<bigint &&>(a + b);
}
int main()
{	
	bigint a, b;
	bigint c[50];

	//freopen("90-b5-adv-data.txt", "r", stdin);
	//freopen("90-b5-adv-ans.txt", "w", stdout);

	for (int i = 1; i <= 3; ++i)
	{
		clog << "第" << i << "批次的测试ing" << endl;
		clog << "------------------------------------" << endl;


		clog << "【下面进行测试1】" << endl;
		/*-----------------------------------------------*/
		cout << "请输入数字a" << endl;
		cin >> a;
		c[0] = a;
		cout << "请输入数字b" << endl;
		cin >> b;
		c[1] = a % b;
		a /= b;
		cout << "a/=b的结果为 " << a << endl;
		cout << "原来的a模b的结果为 " << c[1] << endl;
		cout << "原来的a + b =" << add(c[0], b) << endl;
		bigint d = std::move(const_cast<bigint &&>(a * b));
		cout << "原来的a * (a / b) 的结果为 " << d << endl;

		cout << "由于a * (a / b) + (a % b) == a， 因此下面这项应该为true" << endl;
		cout << boolalpha << (d + c[1] == c[0]) << endl;
		/*-----------------------------------------------*/


		clog << "【下面进行测试2】" << endl;
		/*-----------------------------------------------*/
		cout << "请输入两个数c, d" << endl;
		cin >> c[1] >> c[0];
		cout << "c乘d结果为" << c[1] * c[0] << endl;
		/*-----------------------------------------------*/

		clog << "【下面进行测试3】" << endl;
		/*-----------------------------------------------*/
		cout << "请输入两个数e, f" << endl;

		cin >> c[0] >> c[1];
		cout << "e - f = " << c[0] - c[1] << endl;
		cout << "f--结果为" << endl;
		cout << c[1]-- << endl;
		cout << "++f结果为" << endl;
		cout << ++c[1] << endl;
		cout << "注意以上两项应该相等 都等于f" << endl;
		cout << "e += f 结果为" << endl;
		cout << (c[0] += c[1]) << endl;
		cout << "a * (a / b) = " << d << endl;
		cout << " a * (a / b) < f 值为 " << (d < c[1]) << endl;
		cout << " a * (a / b) == f 值为 " << (d == c[1]) << endl;
		cout << " a * (a / b) > f 值为 " << (d > c[1]) << endl;
		cout << " a * (a / b) <= f 值为 " << (d <= c[1]) << endl;
		cout << " a * (a / b) >= f 值为 " << (d >= c[1]) << endl;
		cout << " a * (a / b) != f 值为 " << (d != c[1]) << endl;
		/*----------------------------------------------*/
		clog << "第" << i << "批次的测试done" << endl;
		clog << "------------------------------------" << endl;
	}
	return 0;
}