/* 1652270 �����2�� ��˴ */
#include "4-b12.h"  //Ҫ�ø���������negativeZeroToZero�����Ժ���Դ�ļ�Ҳ����ͷ�ļ�

void linearEquation(double b, double c)
{
	cout << "�ⲻ��һ��һԪ���η��̡�" << endl;
	if (fabs(b) < 1e-8)
	{
		cout << "����Ҳ����һ��һ�η��̡�";
		if (fabs(c) >= 1e-8)
		{
			cout << "��û�и���" << endl;
		}
		else
		{
			cout << "����ʵ���������ĸ���" << endl;
		}
	}
	else
		cout << "�����Կ�������ĸ�Ϊ x = " << negativeZeroToZero(-c / b) << endl;
}
