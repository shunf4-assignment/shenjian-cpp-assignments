/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;
#define studentNameLength 11
#define studentIDLength 11
#define studentNum 10
#define passScore 60.0

int main()
{
	void checkFail(char[][studentNameLength], char[][studentIDLength], double[]);

	double studentScore[studentNum] = { 0 };
	char studentName[studentNum][11] = { '\0' };
	char studentID[studentNum][11] = { 0 };

	cout << "������ " << studentNum << " λѧ���� ���� ѧ�� ���� ��Ϣ���ո����:" << endl;
	for (int n = 0; n < studentNum; n++)
	{
		
		while (1) {
			if (n != 0 && getchar() == '\n')
			{
				cout << "����������" << n + 1 << "��ѧ������Ϣ��";
			}
			cin >> studentName[n];
			cin >> studentID[n];
			cin >> studentScore[n];
			if (!cin.good() || studentScore[n] < 0)
			{
				cout << "��������������д���������ͷ�������롣"
					<< endl;
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
			}
			else
			{
				break;
			}
		}
	}

	checkFail(studentName, studentID, studentScore);
	return 0;
}

void checkFail(char studentName[][studentNameLength], char studentID[][studentIDLength], double studentScore[])
{
	bool empty = true;
	void studentOutput(char name[], char id[], double score);

	cout << "������ѧ����Ϣ���£�" << endl;
	for (int i = 0; i < studentNum; i++)
	{
		if (studentScore[i] < passScore)
		{
			studentOutput(studentName[i], studentID[i], studentScore[i]);
			empty = false;
		}
	}
	if (empty)
	{
		cout << "�����˾�����" << endl;
	}
}

void studentOutput(char name[], char id[], double score)
{
	cout << name << " " << id << " " << score << endl;
}
