#include <iostream>
using namespace std;


int main()
{
	double change, changeFloatPart;
	int changeIntPart;
	int totalNote;
	int note50, note20, note10, note5, note1, note5j, note1j, note5f, note2f, note1f;

	cout << "����������Ľ������λС����(0.01-100) ";
	cin >> change;

	//��һ�� ��������ȡ��С��
	changeIntPart = (int)change;
	changeFloatPart = change - changeIntPart;

	//�ڶ��� ������������
	totalNote = 0;

	changeIntPart -= ((totalNote += (note50 = changeIntPart / 50)), note50 * 50);
	changeIntPart -= ((totalNote += (note20 = changeIntPart / 20)), note20 * 20);
	changeIntPart -= ((totalNote += (note10 = changeIntPart / 10)), note10 * 10);
	changeIntPart -= ((totalNote += (note5 = changeIntPart / 5)), note5 * 5);
	changeIntPart -= ((totalNote += (note1 = changeIntPart / 1)), note1 * 1);

	//������ ����С������
	changeFloatPart = int(changeFloatPart * 100 + 0.5);
	changeFloatPart -= ((totalNote += (note5j = (int)changeFloatPart / 50)), note5j * 50);
	changeFloatPart -= ((totalNote += (note1j = (int)changeFloatPart / 10)), note1j * 10);
	changeFloatPart -= ((totalNote += (note5f = (int)changeFloatPart / 5)), note5f * 5);
	changeFloatPart -= ((totalNote += (note2f = (int)changeFloatPart / 2)), note2f * 2);
	changeFloatPart -= ((totalNote += (note1f = (int)changeFloatPart / 1)), note1f * 1);

	//���Ĳ� ���
	cout << "���ܹ�������Ҫ���� " << totalNote << " �ų�Ʊ�����У�" << endl;
	(note50) ? (cout << "\t50Ԫ x " << note50 << endl) : (cout << "");
	(note20) ? (cout << "\t20Ԫ x " << note20 << endl) : (cout << "");
	(note10) ? (cout << "\t10Ԫ x " << note10 << endl) : (cout << "");
	(note5) ? (cout << "\t 5Ԫ x " << note5 << endl) : (cout << "");
	(note1) ? (cout << "\t 1Ԫ x " << note1 << endl) : (cout << "");
	(note5j) ? (cout << "\t 5�� x " << note5j << endl) : (cout << "");
	(note1j) ? (cout << "\t 1�� x " << note1j << endl) : (cout << "");
	(note5f) ? (cout << "\t 5�� x " << note5f << endl) : (cout << "");
	(note2f) ? (cout << "\t 2�� x " << note2f << endl) : (cout << "");
	(note1f) ? (cout << "\t 1�� x " << note1f << endl) : (cout << "");

	cout << endl;
	cout << "�������н�����" << endl;
	return 0;
}