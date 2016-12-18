/* 1652270 �����2�� ��˴ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
using namespace std;
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max())
#define FS_STUDENT 4
#define FS_CLASS 5

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

double getFirstLessonScore(double (*p)[FS_CLASS])
{
	double SUM = 0;
	for (int i = 0; i < FS_STUDENT; i++)
	{
		SUM += *(*(p + i));
	}
	return SUM / FS_STUDENT;
}

void failStudent(double(*p)[FS_CLASS])
{
	int thisStudentFails;
	bool anyOutput = false;
	for (int i = 0; i < FS_STUDENT; i++)
	{
		thisStudentFails = 0;
		for (double *p2 = *(p + i); p2 - *(p + i) < FS_CLASS; p2++)
		{
			if (*p2 < 60.0)
				thisStudentFails++;
		}
		if (thisStudentFails > 2)
		{
			anyOutput = true;
			cout << "�� " << i + 1 << " ��ͬѧ��" << endl;
			for (double *p2 = *(p + i); p2 - *(p + i) < FS_CLASS; p2++)
			{
				cout << "\t�� " << p2 - *(p + i) + 1 << " �ſγɼ�Ϊ " << *p2 << " ��" << endl;
			}
		}
	}
	if (!anyOutput)
		cout << "û�з���������ѧ����" << endl;
}

void excelStudent(double(*p)[FS_CLASS])
{
	double thisStudentAvg;
	int thisStudentExcel;
	bool anyOutput = false;
	for (int i = 0; i < FS_STUDENT; i++)
	{
		thisStudentExcel = 0;
		thisStudentAvg = 0;
		for (double *p2 = *(p + i); p2 - *(p + i) < FS_CLASS; p2++)
		{
			thisStudentAvg += *p2;
			if (*p2 > 85.0)
				thisStudentExcel++;
		}
		thisStudentAvg /= FS_CLASS;
		if (thisStudentAvg > 90. || thisStudentExcel == 5)
		{
			anyOutput = true;
			cout << "�� " << i + 1 << " ��ͬѧ" << endl;
		}
	}
	if (!anyOutput)
		cout << "û�з���������ѧ����" << endl;
}

int main()
{
	//REINPUT:
	//freopen("Text.txt", "r", stdin);

	cout << "����������ÿ��ѧ��ÿ�ſεĳɼ�������һ��ѧ�������гɼ�����������һ��ѧ���ĳɼ���" << endl;
	double data[FS_STUDENT][FS_CLASS] = { 0 };
	for (int i = 0; i < FS_STUDENT; i++)
	{
		for (double*p2 = *(data + i); p2 - *(data + i) < FS_CLASS; p2++)
			inputThing(p2, "", "����Ƿ���", "���볬����Χ��", 0., 100., false);
	}
	cout << "��һ�ſε�ƽ���ɼ���" << getFirstLessonScore(data) << endl<<endl;
	cout << "�������ϲ������ѧ����" << endl;
	failStudent(data);

	cout << endl << "ƽ��90�����ϻ�ȫ��85���ϵ�ѧ����" << endl;
	excelStudent(data);
	cout << endl;
	//goto REINPUT;
	return 0;
}
