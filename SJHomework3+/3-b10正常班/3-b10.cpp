/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

int main()
{
	double inputNum, inputNumCopy;
	int d10, d9, d8, d7, d6, d5, d4, d3, d2, d1, dm1, dm2, toOut;
	bool startToPrintOut = false;  //����ָʾ������û�п�ʼ����ˣ�û������Ļ������"10"�ᵱ��ǰ���ж��������������ʰ��

	cout << "�������ת���Ľ������(0.01��100��) ";
	cin >> inputNum;
	inputNumCopy = inputNum;

	inputNumCopy -= (d10 = (int)(inputNumCopy / 1e9)) * 1e9;
	inputNumCopy -= (d9 = (int)(inputNumCopy / 1e8)) * 1e8;
	inputNumCopy -= (d8 = (int)(inputNumCopy / 1e7)) * 1e7;
	inputNumCopy -= (d7 = (int)(inputNumCopy / 1e6)) * 1e6;
	inputNumCopy -= (d6 = (int)(inputNumCopy / 1e5)) * 1e5;
	inputNumCopy -= (d5 = (int)(inputNumCopy / 1e4)) * 1e4;
	inputNumCopy -= (d4 = (int)(inputNumCopy / 1e3)) * 1e3;
	inputNumCopy -= (d3 = (int)(inputNumCopy / 1e2)) * 1e2;
	inputNumCopy -= (d2 = (int)(inputNumCopy / 1e1)) * 1e1;
	inputNumCopy -= (d1 = (int)(inputNumCopy));

	inputNumCopy = (int)(inputNumCopy * 100 + 0.5);
	inputNumCopy -= (dm1 = (int)(inputNumCopy / 10)) * 10;
	inputNumCopy -= (dm2 = (int)(inputNumCopy));

	cout << "�ֽ�����" << endl;
	cout << "\tʮ��λ�� " << d10 << endl;
	cout << "\t  ��λ�� " << d9 << endl;
	cout << "\tǧ��λ�� " << d8 << endl;
	cout << "\t����λ�� " << d7 << endl;
	cout << "\tʮ��λ�� " << d6 << endl;
	cout << "\t  ��λ�� " << d5 << endl;
	cout << "\t  ǧλ�� " << d4 << endl;
	cout << "\t  ��λ�� " << d3 << endl;
	cout << "\t  ʮλ�� " << d2 << endl;
	cout << "\t    Բ�� " << d1 << endl;
	cout << "\t    �ǣ� " << dm1 << endl;
	cout << "\t    �֣� " << dm2 << endl;
	cout << "��д��" ;

	//����ʮ��λ����λ
	if (d10)
	{
		toOut = d10;
		if (toOut == 1)
			cout << "Ҽ";
		if (toOut == 2)
			cout << "��";
		if (toOut == 3)
			cout << "��";
		if (toOut == 4)
			cout << "��";
		if (toOut == 5)
			cout << "��";
		if (toOut == 6)
			cout << "½";
		if (toOut == 7)
			cout << "��";
		if (toOut == 8)
			cout << "��";
		if (toOut == 9)
			cout << "��";
		cout << "ʰ";
		startToPrintOut = true;
	}
	if (d9)
	{
		toOut = d9;
		if (toOut == 1)
			cout << "Ҽ";
		if (toOut == 2)
			cout << "��";
		if (toOut == 3)
			cout << "��";
		if (toOut == 4)
			cout << "��";
		if (toOut == 5)
			cout << "��";
		if (toOut == 6)
			cout << "½";
		if (toOut == 7)
			cout << "��";
		if (toOut == 8)
			cout << "��";
		if (toOut == 9)
			cout << "��";
		startToPrintOut = true;
	}
	if (d10 != 0 || d9 != 0)
	{
		cout << "��";
	}

	//������
	if (d8)
	{
		toOut = d8;
		if (toOut == 1)
			cout << "Ҽ";
		if (toOut == 2)
			cout << "��";
		if (toOut == 3)
			cout << "��";
		if (toOut == 4)
			cout << "��";
		if (toOut == 5)
			cout << "��";
		if (toOut == 6)
			cout << "½";
		if (toOut == 7)
			cout << "��";
		if (toOut == 8)
			cout << "��";
		if (toOut == 9)
			cout << "��";
		cout << "Ǫ";
		startToPrintOut = true;
	}
	else
	{
		if (d7 != 0 || d6 != 0 || d5 != 0)
		{
			if(startToPrintOut)
				cout << "��";
		}
	}

	if (d7)
	{
		toOut = d7;
		if (toOut == 1)
			cout << "Ҽ";
		if (toOut == 2)
			cout << "��";
		if (toOut == 3)
			cout << "��";
		if (toOut == 4)
			cout << "��";
		if (toOut == 5)
			cout << "��";
		if (toOut == 6)
			cout << "½";
		if (toOut == 7)
			cout << "��";
		if (toOut == 8)
			cout << "��";
		if (toOut == 9)
			cout << "��";
		cout << "��";
		startToPrintOut = true;
	}
	else
	{
		if ((d6 != 0 || d5 != 0) && (d8 != 0))
		{
			if (startToPrintOut)
				cout << "��";
		}
	}

	if (d6)
	{
		toOut = d6;
		if (toOut == 1)
			cout << "Ҽ";
		if (toOut == 2)
			cout << "��";
		if (toOut == 3)
			cout << "��";
		if (toOut == 4)
			cout << "��";
		if (toOut == 5)
			cout << "��";
		if (toOut == 6)
			cout << "½";
		if (toOut == 7)
			cout << "��";
		if (toOut == 8)
			cout << "��";
		if (toOut == 9)
			cout << "��";
		cout << "ʰ";
		startToPrintOut = true;
	}
	else
	{
		if ((d5 != 0) && (d7 != 0))
		{
			if (startToPrintOut)
				cout << "��";
		}
	}

	if (d5)
	{
		toOut = d5;
		if (toOut == 1)
			cout << "Ҽ";
		if (toOut == 2)
			cout << "��";
		if (toOut == 3)
			cout << "��";
		if (toOut == 4)
			cout << "��";
		if (toOut == 5)
			cout << "��";
		if (toOut == 6)
			cout << "½";
		if (toOut == 7)
			cout << "��";
		if (toOut == 8)
			cout << "��";
		if (toOut == 9)
			cout << "��";
		startToPrintOut = true;
	}
	if (d8 != 0 || d7 != 0 || d6 != 0 || d5 != 0)
	{
		startToPrintOut = true;
		cout << "��";
	}

	//����Բ��
	if (d4)
	{
		toOut = d4;
		if (toOut == 1)
			cout << "Ҽ";
		if (toOut == 2)
			cout << "��";
		if (toOut == 3)
			cout << "��";
		if (toOut == 4)
			cout << "��";
		if (toOut == 5)
			cout << "��";
		if (toOut == 6)
			cout << "½";
		if (toOut == 7)
			cout << "��";
		if (toOut == 8)
			cout << "��";
		if (toOut == 9)
			cout << "��";
		cout << "Ǫ";
		startToPrintOut = true;
	}
	else
	{
		if (d3 != 0 || d2 != 0 || d1 != 0)
		{
			if (startToPrintOut)
				cout << "��";
		}
	}

	if (d3)
	{
		toOut = d3;
		if (toOut == 1)
			cout << "Ҽ";
		if (toOut == 2)
			cout << "��";
		if (toOut == 3)
			cout << "��";
		if (toOut == 4)
			cout << "��";
		if (toOut == 5)
			cout << "��";
		if (toOut == 6)
			cout << "½";
		if (toOut == 7)
			cout << "��";
		if (toOut == 8)
			cout << "��";
		if (toOut == 9)
			cout << "��";
		cout << "��";
		startToPrintOut = true;
	}
	else
	{
		if ((d2 != 0 || d1 != 0) && (d4 != 0))
		{
			if (startToPrintOut)
				cout << "��";
		}
	}

	if (d2)
	{
		toOut = d2;
		if (toOut == 1)
			cout << "Ҽ";
		if (toOut == 2)
			cout << "��";
		if (toOut == 3)
			cout << "��";
		if (toOut == 4)
			cout << "��";
		if (toOut == 5)
			cout << "��";
		if (toOut == 6)
			cout << "½";
		if (toOut == 7)
			cout << "��";
		if (toOut == 8)
			cout << "��";
		if (toOut == 9)
			cout << "��";
		cout << "ʰ";
		startToPrintOut = true;
	}
	else
	{
		if ((d1 != 0) && (d3 != 0))
		{
			if (startToPrintOut)
				cout << "��";
		}
	}

	if (d1)
	{
		toOut = d1;
		if (toOut == 1)
			cout << "Ҽ";
		if (toOut == 2)
			cout << "��";
		if (toOut == 3)
			cout << "��";
		if (toOut == 4)
			cout << "��";
		if (toOut == 5)
			cout << "��";
		if (toOut == 6)
			cout << "½";
		if (toOut == 7)
			cout << "��";
		if (toOut == 8)
			cout << "��";
		if (toOut == 9)
			cout << "��";
		startToPrintOut = true;
	}
	if (d10 || d9 || d8 || d7 || d6 || d5 || d4 || d3 || d2 || d1)
		cout << "Բ";

	//����Ǻͷ�
	//����û�У�Ҫ����������ֵĳ�Ҫ�����ǣ���Ϊ0��������������Ϊ0.
	if (dm1)
	{
		toOut = dm1;
		if (toOut == 1)
			cout << "Ҽ";
		if (toOut == 2)
			cout << "��";
		if (toOut == 3)
			cout << "��";
		if (toOut == 4)
			cout << "��";
		if (toOut == 5)
			cout << "��";
		if (toOut == 6)
			cout << "½";
		if (toOut == 7)
			cout << "��";
		if (toOut == 8)
			cout << "��";
		if (toOut == 9)
			cout << "��";
		cout << "��";
		startToPrintOut = true;
	}
	else
	{
		if ((d10 || d9 || d8 || d7 || d6 || d5 || d4 || d3 || d2 || d1) && dm2)
			if (startToPrintOut)
				cout << "��";
	}

	if (dm2)
	{
		toOut = dm2;
		if (toOut == 1)
			cout << "Ҽ";
		if (toOut == 2)
			cout << "��";
		if (toOut == 3)
			cout << "��";
		if (toOut == 4)
			cout << "��";
		if (toOut == 5)
			cout << "��";
		if (toOut == 6)
			cout << "½";
		if (toOut == 7)
			cout << "��";
		if (toOut == 8)
			cout << "��";
		if (toOut == 9)
			cout << "��";
		cout << "��";
		startToPrintOut = true;
	}
	else
	{
		if (inputNum)
			cout << "��";
	}

	if (!(inputNum))
		cout << "��Բ��";

	cout << endl;
	return 0;
}