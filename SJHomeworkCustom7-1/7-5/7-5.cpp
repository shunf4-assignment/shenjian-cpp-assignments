/* 1652270 计算机2班 冯舜 */
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
	char ungood[] = "输入第    个学生的       时出错。请从该处重新开始输入。";
	cout << "依次输入 " << n << " 个学生的学号、姓名、以及三门课成绩：";
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		ungood[8] = '0' + i;

		strncpy(&ungood[18], " 学号  ", 7);
		inputThing(&(students[i].no), "", ungood, ungood, 0, INT_MAX, false);

		strncpy(&ungood[18], " 姓名  ", 7);
		cin >> students[i].name;

		for (int j = 0; j < subjects; j++)
		{
			strncpy(&ungood[18], "成绩   ", 7);
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

		cout << "第 " << i << " 位学生：学号 " << students[i].no << ", 姓名 " << students[i].name << ", 三门课成绩 ";

		for (int s = 0; s < subjects; s++)
		{
			sum += students[i].score[s];
			cout << students[i].score[s];
			if (s != subjects - 1)
				cout << " ";
		}
		students[i].avgscore = sum / subjects;

		cout << ", 平均成绩 " << students[i].avgscore << endl;
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
			cout << "第 " << i << " 位学生：学号 " << students[i].no << ", 姓名 " << students[i].name << ", 三门课成绩 ";
			for (int s = 0; s < subjects; s++)
			{
				cout << students[i].score[s];
				if (s != subjects - 1)
					cout << " ";
			}

			cout << ", 平均成绩 " << students[i].avgscore << endl;
		}
	}
}

int main()
{
	//REINPUT:
	//freopen("Text.txt", "r", stdin);
	Student students[n];
	inputStudents(students);
	cout << "输入完成。学生的成绩数据如下：" << endl;
	
	calAvg(students);
	cout << "最高成绩者的数据：" << endl;

	highest(students);

	//goto REINPUT;
	return 0;
}
