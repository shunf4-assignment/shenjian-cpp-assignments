/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;


int main()
{
	unsigned int a = 0, n = 0, sum = 0, tempVar = 0;

	//��ʼ����a��n��
	cout << "���������������� a �� n�������ÿո��س�������";
	cin >> a >> n;
	 
	//�ۼ�
	for (int i = 0; i < n; i++)
	{
		tempVar = tempVar * 10 + a;
		sum = sum + tempVar;
	}

	cout << "Sn = " << sum << endl;

	return 0;
}