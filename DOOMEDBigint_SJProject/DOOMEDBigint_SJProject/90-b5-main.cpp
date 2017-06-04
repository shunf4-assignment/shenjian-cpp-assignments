/* 1652270 �����2�� ��˴ */
/* DOOMEDBigint_SJProject 90-b5-main.cpp */
#include "90-b5.h"

int main()
{
	try
	{
		int testStep = 5;
		bool allTest = 0;
		if (testStep == 1 || allTest)
		{
			cout << "���Դ��� bigint" << endl;
			bigint b1;

			cout << "�޲ι���� b1��������� 0��ʵ�������\t\t";
			cout << b1 << endl;

			cout << "���ַ������� 0��������� 0��ʵ�������\t\t";
			bigint b2 = "0";
			cout << b2 << endl;

			cout << "���ַ�����ֵ -0��������� 0��ʵ�������\t";
			b1 = "-0";
			cout << b1 << endl;


			cout << "���ַ�����ʼ�� -123456789\n\t������� -123456789��ʵ�������\t\t";
			bigint b3 = "-123456789";
			cout << b3 << endl;


			cout << "���ַ�����ʼ�� 1230000000012300\n\t������� 1230000000012300��ʵ�������\t";
			bigint b4 = "1230000000012300";
			cout << b4 << endl;

			cout << "��int��ֵ 12300��������� 12300��ʵ�������\t";
			b1 = 12300;
			cout << b1 << endl;

			cout << "�� b4 == 1230000000012300 ��ֵ b1\n\t������� 1230000000012300��ʵ�������\t";
			b1 = b4;
			cout << b4 << endl;
		}
		if (testStep == 2 || allTest)
		{
			bigint a = "-72371626000514826365485330891017761326969912546873932263032307886126369713540461421192023396317290185";
			bigint b = "85071710656031275995862754692395358960735888973429618282131145669509492965176110735633615775481331112";
			bigint c = 7919376479651642;
			a.print();
			cout << endl;
			b.print();
			cout << endl;
			cout << (a + b) << endl;
			cout << (b - a) << endl;
			cout << endl;
			cout << (b * c) << endl;
		}
		if (testStep == 3 || allTest)
		{
			bigint a = "-0";
			bigint x = "-654650460274952057652017016752178115761568787978079580780178950712851075078";
			bigint b = "-7";
			bigint c;
			bigint d;

			__int64 dividendInit = 7919376479651642;
			__int64 divisorInit = 209820526280;
			for (int i = 0; i < 4; i++)
			{
				__int64 dividend = i & 1 ? -dividendInit : dividendInit;
				__int64 divisor = i & 2 ? -divisorInit : divisorInit;
				cout << dividend << " / " << divisor << " ";
				d.equalsDiv(dividend, divisor, c);
				cout << "������������ " << dividend / divisor << ", ʵ���� " << d << endl;
				cout << "������������ " << dividend % divisor << ", ʵ���� " << c << endl;
			}

		}
		if (testStep == 4 || allTest)
		{
			bigint c, d;
			cin >> c >> d;
			bigint e = c / d;
			cout << e << endl;
		}
		if (testStep == 5 || allTest)
		{
			bigint A, B, C;
			cin >> A >> B >> C;
			cout << A + B << endl;
			cout << A - B << endl;
			cout << A * B << endl;
			cout << A / C << endl;
		}

	}
	catch (bad_alloc &exp)
	{
		cerr << exp.what() << endl;
		return STAT_OVERFLOW;
	}
	return 0;
}