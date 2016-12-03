/* 1652270 计算机2班 冯舜 */
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

	cout << "请输入 " << studentNum << " 位学生的 姓名 学号 分数 信息，空格隔开:" << endl;
	for (int n = 0; n < studentNum; n++)
	{
		
		while (1) {
			if (n != 0 && getchar() == '\n')
			{
				cout << "请接着输入第" << n + 1 << "个学生的信息：";
			}
			cin >> studentName[n];
			cin >> studentID[n];
			cin >> studentScore[n];
			if (!cin.good() || studentScore[n] < 0)
			{
				cout << "您输入的数据中有错误，请检查后从头重新输入。"
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

	cout << "不及格学生信息如下：" << endl;
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
		cout << "所有人均及格！" << endl;
	}
}

void studentOutput(char name[], char id[], double score)
{
	cout << name << " " << id << " " << score << endl;
}
