/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

//int totalMove = 0;

void Move(char from, char to, int num)
{
	cout << "�� " << num << " ��Բ�̴� " << from << " ���Ƶ� " << to << " ��" << endl;
	//totalMove += 1;
}

void HanoiStep(char origin, char dest, int totalNum)
{
	//���Լ��Ľⷨ
	//����������һ�鶯��Ϊ����ŵ���衱
	char intermediate;

	if (totalNum == 1)
	{
		Move(origin, dest, 1);
		return;
	}
	intermediate = 'A' + 'B' + 'C' - origin - dest;
	//cout << "  ���Խ�" << origin << "���ϵ�" << totalNum - 1 << " ��Բ���ƶ���" << intermediate << "��" << endl;
	HanoiStep(origin, intermediate, totalNum - 1);
	Move(origin, dest, totalNum);
	//cout << "  ���Խ�" << intermediate << "i���ϵ�" << totalNum - 1 << " ��Բ���ƶ���" << dest << "��d" << endl;
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
		}

		if (n < 1)
			valid = false;
	} while (!valid);
	
	//totalMove = 0;
	HanoiStep('A', 'C', n);
	//cout << "�ܹ��ƶ� " << totalMove << " ����" << endl;
	return 0;
}
