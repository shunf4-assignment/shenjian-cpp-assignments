/* 1652270 计算机2班 冯舜 */
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
			cout << "第 " << i + 1 << " 号同学，" << endl;
			for (double *p2 = *(p + i); p2 - *(p + i) < FS_CLASS; p2++)
			{
				cout << "\t第 " << p2 - *(p + i) + 1 << " 门课成绩为 " << *p2 << " 分" << endl;
			}
		}
	}
	if (!anyOutput)
		cout << "没有符合条件的学生。" << endl;
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
			cout << "第 " << i + 1 << " 号同学" << endl;
		}
	}
	if (!anyOutput)
		cout << "没有符合条件的学生。" << endl;
}

int main()
{
	//REINPUT:
	//freopen("Text.txt", "r", stdin);

	cout << "请依次输入每个学生每门课的成绩，输入一个学生的所有成绩后再输入下一个学生的成绩。" << endl;
	double data[FS_STUDENT][FS_CLASS] = { 0 };
	for (int i = 0; i < FS_STUDENT; i++)
	{
		for (double*p2 = *(data + i); p2 - *(data + i) < FS_CLASS; p2++)
			inputThing(p2, "", "输入非法。", "输入超出范围。", 0., 100., false);
	}
	cout << "第一门课的平均成绩：" << getFirstLessonScore(data) << endl<<endl;
	cout << "两门以上不及格的学生：" << endl;
	failStudent(data);

	cout << endl << "平均90分以上或全部85以上的学生：" << endl;
	excelStudent(data);
	cout << endl;
	//goto REINPUT;
	return 0;
}
