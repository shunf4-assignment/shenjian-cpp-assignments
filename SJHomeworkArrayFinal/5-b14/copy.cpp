/* 1652270 �����2�� ��˴ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
using namespace std;
#define maxDigit 50

static int daxie(int num, int flag_of_zero, char result[], short resultPin, const char unit[])
{
	char chistr[] = "��Ҽ��������½��ƾ�";


	if (num || flag_of_zero) {
		result[resultPin] = chistr[num * 2];
		result[resultPin + 1] = chistr[num * 2 + 1];
		resultPin += 2;
	}
	if (num)
	{
		strcat(&result[resultPin], unit);
		if (strcmp(unit, "") != 0)
			resultPin += 2;
	}
	return resultPin;
}

int main()
{
	double inputNum, inputNumCopy, tempNum = 1;
	int d[maxDigit + 4] = { 0 };
	short firstDigit = 0, resultPin = 0;
	char digitList[4][9] = { "", "ʰ", "��","Ǫ" };
	char classList[(maxDigit - 2) / 4 + 3][9] = { "��", "��" ,"Բ","��","��","��","��","��","��","�","��","��","��","��","��"};
	char result[256] = { '\0' };

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
			resultPin = daxie(d[i * 4 + 2 + j], (d[i * 4 + 2 + j - 1] != 0 && j != 0 && i * 4 + 2 + j <= firstDigit), result, resultPin, digitList[j]);
		}
		if (d[i * 4 + 2] || d[i * 4 + 2 + 1] || d[i * 4 + 2 + 2] || d[i * 4 + 2 + 3] || (firstDigit >= 2 && i == 0))
		{
			strcat(&result[resultPin], classList[i + 2]);
			resultPin += 2;
		}
	}

	if (firstDigit == 0 && d[0] == 0)
	{
		strcat(&result[resultPin], "��Բ");
		resultPin += 2;
	}

	resultPin = daxie(d[1], firstDigit > 1 && d[0], result, resultPin, classList[1]);
	resultPin = daxie(d[0], false, result, resultPin, classList[0]);
	if (!d[0])
	{
		strcat(&result[resultPin], "��");
		resultPin += 2;
	}

	cout << result << endl;
	return 0;
}