/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <iomanip>
using namespace std;

void Move(char from, char to, int num, int moveNum)
{
	cout << "�� " << setw(5) << setfill('0') << moveNum << " ������ " << num << " ��Բ�̴� " << from << " ���Ƶ� " << to << " ��" << endl;
	//totalMove += 1;
}

int HanoiStep(char origin, char dest, int totalNum, bool firstTime = true)
{
	//����������һ�鶯��Ϊ����ŵ���衱
	char intermediate;
	static int totalMove = 0;

	if (firstTime) {
		totalMove = 0;
	}

	if (totalNum == 1)
	{
		totalMove += 1;
		Move(origin, dest, 1, totalMove);
		return totalMove;
	}
	intermediate = 'A' + 'B' + 'C' - origin - dest;
	HanoiStep(origin, intermediate, totalNum - 1, false);
	totalMove += 1;
	Move(origin, dest, totalNum, totalMove);
	HanoiStep(intermediate, dest, totalNum - 1, false);
	return totalMove;
}

int main()
{
	int n;
	int moveNum;
	bool valid;

	do
	{
		valid = true;
		cout << "��ʼ A ���ж��ٲ�Բ�̣�";
		cin >> n;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (n < 1)
		{
			valid = false;
			cout << "���볬����Χ�����������롣" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
	} while (!valid);

	moveNum = HanoiStep('A', 'C', n);
	cout << "�ܹ��ƶ� " << moveNum << " ����" << endl;
	return 0;
}
