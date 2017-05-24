/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <iomanip>
using namespace std;

class matrix {
private:
	int value[2][3];
public:
	matrix operator+(matrix &b);
	/* ----������Ҫ���������Ա�����Ķ���---- */
	matrix();
	friend istream& operator >> (istream &in, matrix &m);
	friend ostream& operator << (ostream &out, matrix &m);
};

/* ----�������Ա����������ʵ��---- */
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

/* ----main������׼��---- */
int main()
{
	matrix m1, m2, m3;

	cout << "���������m1��ֵ(��2��3�У������к��е�˳������)" << endl;
	cin >> m1;
	cout << "���������m2��ֵ(��2��3�У������к��е�˳������)" << endl;
	cin >> m2;

	cout << "��ʼ����m1��ֵ��" << endl;
	cout << m1 << endl;
	cout << "��ʼ����m2��ֵ��" << endl;
	cout << m2 << endl;
	cout << "��Ӻ����m3��ֵ��" << endl;
	cout << (m3 = m1 + m2) << endl;

	return 0;
}
