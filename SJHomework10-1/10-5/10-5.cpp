/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <iomanip>
using namespace std;

class matrix {
private:
	int value[2][3];
public:
	matrix operator+(matrix &b);
	/* ----根据需要添加其它成员函数的定义---- */
	matrix();
	friend istream& operator >> (istream &in, matrix &m);
	friend ostream& operator << (ostream &out, matrix &m);
};

/* ----给出类成员函数的体外实现---- */
matrix matrix::operator+(matrix &b)
{
	matrix result;
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < 3; i++)
		{
			result.value[j][i] = value[j][i] + b.value[j][i];
		}
	return result;
}

matrix::matrix()
{
	memset(value, 0, (sizeof(int)) * 2 * 3);
}

istream& operator >> (istream &in, matrix &m)
{
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < 3; i++)
		{
			in >> m.value[j][i];
		}
	return in;
}

ostream& operator << (ostream &out, matrix &m)
{
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			cout << m.value[j][i] << "  ";
		}
		cout << endl;
	}
	return out;
}

/* ----main函数不准动---- */
int main()
{
	matrix m1, m2, m3;

	cout << "请输入矩阵m1的值(共2行3列，按先行后列的顺序输入)" << endl;
	cin >> m1;
	cout << "请输入矩阵m2的值(共2行3列，按先行后列的顺序输入)" << endl;
	cin >> m2;

	cout << "初始矩阵m1的值：" << endl;
	cout << m1 << endl;
	cout << "初始矩阵m2的值：" << endl;
	cout << m2 << endl;
	cout << "相加后矩阵m3的值：" << endl;
	cout << (m3 = m1 + m2) << endl;

	return 0;
}
