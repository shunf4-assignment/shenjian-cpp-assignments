/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <iomanip>
using namespace std;

class matrix {
private:
	int value[2][3];
public:
	matrix(int(*p)[3]);  //构造函数，用数组初始化矩阵
	void display();       //输出该矩阵
	friend matrix operator+(matrix &a, matrix &b);
	/* ----根据需要添加其它成员函数的定义---- */
	matrix();
};

/* ----给出类成员函数的体外实现---- */
matrix::matrix(int(*p)[3])
{
	memcpy_s(value, (sizeof(int)) * 2 * 3, p, (sizeof(int)) * 2 * 3);
}

matrix::matrix()
{
	memset(value, 0, (sizeof(int)) * 2 * 3);
}

matrix operator+(matrix &a, matrix &b)
{
	matrix result;
	for(int j = 0; j < 2; j++)
		for (int i = 0; i < 3; i++)
		{
			result.value[j][i] = a.value[j][i] + b.value[j][i];
		}
	return result;
}

void matrix::display()
{
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			cout << value[j][i] << "  ";
		}
		cout << endl;
	}
}

/* ----main函数不准动---- */
int main()
{
	int a[2][3] = { { 1,2,3 },{ 4,5,6 } };
	int b[2][3] = { { 1,2,3 },{ 4,5,6 } };
	matrix m1(a), m2(b), m3;

	cout << "初始矩阵m1的值：" << endl;
	m1.display();
	cout << "初始矩阵m2的值：" << endl;
	m2.display();
	m3 = m1 + m2;
	cout << "相加后矩阵m3的值：" << endl;
	m3.display();

	return 0;
}