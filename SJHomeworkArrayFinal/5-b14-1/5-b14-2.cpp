/* 1652270 �����2�� ��˴ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#define maxDigit 50

static string daxie(int num, int flag_of_zero, string result, const char unit[])
{
	char chistr[] = "��Ҽ��������½��ƾ�";


	if (num || flag_of_zero) {
		result += chistr[num * 2];
		result += chistr[num * 2 + 1];
	}
	if (num)
	{
		result += unit;
	}
	return result;
}

int main()
{
	double inputNum, inputNumCopy, tempNum = 1;
	int d[maxDigit + 4] = { 0 };
	short firstDigit = 0;
	char digitList[4][9] = { "", "ʰ", "��","Ǫ" };
	char classList[(maxDigit - 2) / 4 + 3][9] = { "��", "��" ,"Բ","��","��","��","��","��","��","�","��","��","��","��","��" };
	string result = "";

	for (int i = 0; i < maxDigit - 2 - 1; i++)
	{
		tempNum *= 10;
	}

	while (1) {
		cout << "�������ת���Ľ������(0.01��100��) ";
		cin >> inputNum;

		if (!cin.good() || inputNum < 0)
		{
			cout << "����Ƿ���" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			break;
	}

	inputNum += 0.00001;
	inputNumCopy = inputNum;

	for (int i = maxDigit - 1; i >= 0; i--)
	{
		d[i] = int(inputNumCopy / tempNum);
		if (d[i] && i > firstDigit)
			firstDigit = i;
		inputNumCopy -= d[i] * tempNum;
		tempNum /= 10;
	}

	cout << "�ֽ�����" << endl;
	for (int i = maxDigit - 1; i >= 0; i--)
	{
		if (i >= 2) {
			if (i < 12 || (d[i] != 0)) {
				cout << '\t' << setw(4) << digitList[(i - 2) % 4] << classList[(i - 2) / 4 + 2] << "λ��";
				cout << d[i] << endl;
			}
		}
		else
		{
			cout << '\t' << setw(4) << "" << classList[i] << "λ��";
			cout << d[i] << endl;
		}
	}
	cout << "��д��";

	for (int i = (maxDigit - 3) / 4; i >= 0; i--)
	{
		for (int j = 3; j >= 0; j--)
		{
			result = daxie(d[i * 4 + 2 + j], (d[i * 4 + 2 + j - 1] != 0 && j != 0 && i * 4 + 2 + j <= firstDigit), result, digitList[j]);
		}
		if (d[i * 4 + 2] || d[i * 4 + 2 + 1] || d[i * 4 + 2 + 2] || d[i * 4 + 2 + 3] || (firstDigit >= 2 && i == 0))
		{
			result += classList[i + 2];
		}
	}

	if (firstDigit == 0 && d[0] == 0)
	{
		result += "��Բ";
	}

	result = daxie(d[1], firstDigit > 1 && d[0], result, classList[1]);
	result = daxie(d[0], false, result, classList[0]);
	if (!d[0])
	{
		result += "��";
	}

	cout << result << endl;
	return 0;
}