/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

void daxie(int num, int flag_of_zero)
{
	switch (num) {
	case 0:
		if (flag_of_zero)	//�˱��ʲô��˼������˼��
			cout << "��";
		break;
	case 1:
		cout << "Ҽ";
		break;
	case 2:
		cout << "��";
		break;
	case 3:
		cout << "��";
		break;
	case 4:
		cout << "��";
		break;
	case 5:
		cout << "��";
		break;
	case 6:
		cout << "½";
		break;
	case 7:
		cout << "��";
		break;
	case 8:
		cout << "��";
		break;
	case 9:
		cout << "��";
		break;
	default:
		cout << "error";
		break;
	}
}

int main()
{
	double inputNum, inputNumCopy;
	int d10, d9, d8, d7, d6, d5, d4, d3, d2, d1, dm1, dm2;

//REINPUT:
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
	cout << "��д��";

	//����ʮ��λ����λ
	if (d10)
	{
		daxie(d10, false);
		cout << "ʰ";
		startToPrintOut = true;
	}
	if (d9)
	{
		daxie(d9, false);
		startToPrintOut = true;
	}
	if (d10 != 0 || d9 != 0)
	{
		cout << "��";
	}

	//������
	daxie(d8, (d7 != 0 || d6 != 0 || d5 != 0) && startToPrintOut);
	if (d8)
	{
		cout << "Ǫ";
		startToPrintOut = true;
	}

	daxie(d7, ((d6 != 0 || d5 != 0) && (d8 != 0)) && startToPrintOut);
	if (d7)
	{
		cout << "��";
		startToPrintOut = true;
	}

	daxie(d6, ((d5 != 0) && (d7 != 0)) && startToPrintOut);
	if (d6)
	{
		cout << "ʰ";
		startToPrintOut = true;
	}

	daxie(d5, false);
	if (d5)
	{
		startToPrintOut = true;
	}
	if (d8 != 0 || d7 != 0 || d6 != 0 || d5 != 0)
	{
		cout << "��";
	}

	//����Բ��
	daxie(d4, ((d3 != 0 || d2 != 0 || d1 != 0) && startToPrintOut));
	if (d4)
	{
		cout << "Ǫ";
		startToPrintOut = true;
	}

	daxie(d3, (((d2 != 0 || d1 != 0) && (d4 != 0)) && startToPrintOut));
	if (d3)
	{
		cout << "��";
		startToPrintOut = true;
	}

	daxie(d2, (((d1 != 0) && (d3 != 0)) && startToPrintOut));
	if (d2)
	{
		cout << "ʰ";
		startToPrintOut = true;
	}

	daxie(d1, !(inputNum));
	if (d1)
	{
		startToPrintOut = true;
	}
	if (d10 || d9 || d8 || d7 || d6 || d5 || d4 || d3 || d2 || d1)
		cout << "Բ";

	//����Ǻͷ�
	//����û�У�Ҫ����������ֵĳ�Ҫ�����ǣ���Ϊ0��������������Ϊ0.
	daxie(dm1, (((d10 || d9 || d8 || d7 || d6 || d5 || d4 || d3 || d2 || d1) && dm2) && startToPrintOut));
	if (dm1)
	{
		cout << "��";
		startToPrintOut = true;
	}

	daxie(dm2, false);
	if (dm2)
	{
		cout << "��";
		startToPrintOut = true;
	}
	else
	{
		if (inputNum)
			cout << "��";
	}

	if (!(inputNum))
		cout << "Բ��";

	cout << endl;

	//goto REINPUT;

	return 0;
}