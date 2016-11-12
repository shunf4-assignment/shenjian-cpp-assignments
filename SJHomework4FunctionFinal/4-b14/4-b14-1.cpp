/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <iomanip>
using namespace std;

int totalMove = 0;

void Move(char from, char to, int num)
{
	cout << "�� " << setw(5) << setfill('0') << totalMove << " ������ " << num << " ��Բ�̴� " << from << " ���Ƶ� " << to << " ��" << endl;
	//totalMove += 1;
}

void HanoiStep(char origin, char dest, int totalNum)
{
	//����������һ�鶯��Ϊ����ŵ���衱
	char intermediate;

	if (totalNum == 1)
	{
		totalMove += 1;
		Move(origin, dest, 1);
		return;
	}
	intermediate = 'A' + 'B' + 'C' - origin - dest;
	HanoiStep(origin, intermediate, totalNum - 1);
	totalMove += 1;
	Move(origin, dest, totalNum);
	HanoiStep(intermediate, dest, totalNum - 1);
}

int main()
{
	int n;
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

	totalMove = 0;
	HanoiStep('A', 'C', n);
	cout << "�ܹ��ƶ� " << totalMove << " ����" << endl;
	return 0;
}
