/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;


int main()
{
	unsigned int m, n, tempVar, greatestCommonDivisor, leastCommonMultiple, leftNum, rightNum;

	m = 0, n = 0, leftNum = 0, rightNum = 0, tempVar = 0;

	//��ʼ����m��n��
	cout << "�������������������� m �� n�������ÿո��س�������";
	cin >> m >> n;

	leftNum = m;
	rightNum = n;
	//ŷ������㷨��շת�������
	while (leftNum != 0)
	{
		tempVar = rightNum % leftNum;
		rightNum = leftNum;
		leftNum = tempVar;
	}

	//��ʱrightNum��Ϊ���Լ��
	greatestCommonDivisor = rightNum;

	//��С�������ǳ�����
	if (greatestCommonDivisor != 0 && m*n != 0)
	{
		leastCommonMultiple = m * n / greatestCommonDivisor;
		cout << "��������" << endl;
		cout << "\t���Լ���� " << greatestCommonDivisor << endl;
		cout << "\t��С�������� " << leastCommonMultiple << endl;
	}
	else
	{
		cout << "����������ܰ���0������쳣��" << endl;
		leastCommonMultiple = 0;
	}
		
	return 0;
}