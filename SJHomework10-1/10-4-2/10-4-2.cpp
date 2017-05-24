/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <iomanip>
using namespace std;

class matrix {
private:
	int value[2][3];
public:
	matrix(int(*p)[3]);  //���캯�����������ʼ������
	void display();       //����þ���
	friend matrix operator+(matrix &a, matrix &b);
	/* ----������Ҫ���������Ա�����Ķ���---- */
	matrix();
};

/* ----�������Ա����������ʵ��---- */
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

/* ----main������׼��---- */
int main()
{
	int a[2][3] = { { 1,2,3 },{ 4,5,6 } };
	int b[2][3] = { { 1,2,3 },{ 4,5,6 } };
	matrix m1(a), m2(b), m3;

	cout << "��ʼ����m1��ֵ��" << endl;
	m1.display();
	cout << "��ʼ����m2��ֵ��" << endl;
	m2.display();
	m3 = m1 + m2;
	cout << "��Ӻ����m3��ֵ��" << endl;
	m3.display();

	return 0;
}