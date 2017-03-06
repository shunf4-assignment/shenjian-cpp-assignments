/* 1652270 �����2�� ��˴ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max())

const int subjects = 3;
const int namelen = 9;
const int n = 10;

struct Student
{
	int no;
	char name[namelen];
	float score[subjects];
	float avgscore;
};

template <typename T>
void inputThing(T* p, const char * promptText, const char * cinUngoodText, const char * outLimitText, T lowerLimit, T upperLimit, bool clearBuffer = false)
{
	bool valid;
	do
	{
		valid = true;
		cout << promptText;
		cin >> *p;

		if (!cin.good())
		{
			valid = false;
			cout << cinUngoodText << endl;
		}
		else if (*p > upperLimit || *p < lowerLimit)
		{
			valid = false;
			cout << outLimitText << endl;
		}

		if (!valid)
		{
			cin.clear();
			cin.ignore(FS_MAX_LENGTH, '\n');
		}

	} while (!valid);
	if (clearBuffer)
		cin.ignore(FS_MAX_LENGTH, '\n');
}

void inputStudents(Student *students)
{
	char ungood[] = "�����    ��ѧ����       ʱ������Ӹô����¿�ʼ���롣";
	cout << "�������� " << n << " ��ѧ����ѧ�š��������Լ����ſγɼ���";
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		ungood[8] = '0' + i;

		strncpy(&ungood[18], " ѧ��  ", 7);
		inputThing(&(students[i].no), "", ungood, ungood, 0, INT_MAX, false);

		strncpy(&ungood[18], " ����  ", 7);
		cin >> students[i].name;

		for (int j = 0; j < subjects; j++)
		{
			strncpy(&ungood[18], "�ɼ�   ", 7);
			ungood[23] = '0' + j + 1;
			inputThing(&(students[i].score[j]), "", ungood, ungood, -0.01f, 100.0f, false);
		}
	}
}

void calAvg(Student *students)
{
	for (int i = 0; i < n; i++)
	{
		float sum;
		sum = 0;

		cout << "�� " << i << " λѧ����ѧ�� " << students[i].no << ", ���� " << students[i].name << ", ���ſγɼ� ";

		for (int s = 0; s < subjects; s++)
		{
			sum += students[i].score[s];
			cout << students[i].score[s];
			if (s != subjects - 1)
				cout << " ";
		}
		students[i].avgscore = sum / subjects;

		cout << ", ƽ���ɼ� " << students[i].avgscore << endl;
	}
}

void highest(Student *students)
{
	float highest = -1.0f;
	for (int i = 0; i < n; i++)
	{
		if (students[i].avgscore > highest)
			highest = students[i].avgscore;
	}
	for (int i = 0; i < n; i++)
	{
		if (fabs(students[i].avgscore - highest) < 1e-6)
		{
			cout << "�� " << i << " λѧ����ѧ�� " << students[i].no << ", ���� " << students[i].name << ", ���ſγɼ� ";
			for (int s = 0; s < subjects; s++)
			{
				cout << students[i].score[s];
				if (s != subjects - 1)
					cout << " ";
			}

			cout << ", ƽ���ɼ� " << students[i].avgscore << endl;
		}
	}
}

int main()
{
	//REINPUT:
	//freopen("Text.txt", "r", stdin);
	Student students[n];
	inputStudents(students);
	cout << "������ɡ�ѧ���ĳɼ��������£�" << endl;
	
	calAvg(students);
	cout << "��߳ɼ��ߵ����ݣ�" << endl;

	highest(students);

	//goto REINPUT;
	return 0;
}
