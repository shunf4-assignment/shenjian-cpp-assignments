/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <cmath>
#include <iomanip>
#include <windows.h>

using namespace std;

//�˳����ڼ��㸺����ʱ�򾫶Ⱥܲ��������ֵԽ��Խ����ȷ
int main()
{
	double x, loopVar, loopTerm, sum; //loopVar��ʾѭ��������Ҳ��ΪloopTermѭ����x/loopVar��������loopTerm��e^x̩��չ���еĵ�loopVar+1��
	long t1, t2; //��ʼʱ������ʱ��

	cout << "����Ҫ����e^x���Ա��� x = ";
	cin >> x;

	loopVar = 0;
	loopTerm = 1;
	sum = 0;

	//��ʼ��ʱ
	t1 = GetTickCount();
	while (fabs(loopTerm) >= 1e-5)
	{
		sum += loopTerm;
		//cout << loopTerm << endl;
		loopVar += 1;
		loopTerm = loopTerm * x / loopVar;
	}

	//������ʱ
	t2 = GetTickCount();

	cout << "e^x = " << setiosflags(ios::fixed) << setprecision (15) << sum << endl;

	//cout << t1 << " " << t2;
	//cout << "������ʱ" << setprecision(12) << (t2 - t1) / 1000. << "�롣";
	
	return 0;
}