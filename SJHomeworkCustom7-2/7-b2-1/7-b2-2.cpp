/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

const int namelen = 9;
struct Student
{
	int no;
	char name[namelen];
	int score;
	int rank;
};

void selectionSort(Student  * const s, int stuNum)
{
	Student * max, tmpS;
	bool b;
	int uniqRank, actualRank;
	for (Student * p = s; p - s < stuNum; p++)
	{
		max = p;
		for (Student *q = p + 1; q - s < stuNum; q++)
		{
			b = false;
			b = q->score > max->score;
			if (b)
			{
				max = q;
			}
		}
		tmpS = *p;
		*p = *max;
		*max = tmpS;

		uniqRank = p - s + 1;
		p->rank = uniqRank;
		if (p != s && (*p).score == (*(p - 1)).score)
		{
			actualRank = (*(p - 1)).rank;
			p->rank = actualRank;

			Student *r = p - 1;
			while (r >= s && r->score == p->score)
			{
				if (r->no < p->no)
				{
					break;
				}
				r--;
			}
			r++;
			tmpS = *p;
			for (Student *t = p; t > r; t--)
			{
				*t = *(t - 1);
			}
			*r = tmpS;
		}
			

	}
}

void printStudent(const Student  * const s, int stuNum)
{
	cout << "\tID Num\t\tName    \tScore\tRank" << endl;
	cout << "=========================================================" << endl;
	for (const Student * p = s; p - s < stuNum; p++)
	{
		cout << "\t" << p->no << "\t\t" << p->name << setw(namelen - 1 - strlen(p->name)) << "" << "\t" << p->score << "\t" << p->rank << endl;
	}
}

int main()
{
	//REINPUT:
	ifstream f;
	int stuNum = 0;
	Student *s, *p;

	f.open("student.txt", ios::in);
	if (f.is_open() == 0)
	{
		cout << "打开 student.txt 失败。请检查该文件是否在工作目录内。" << endl;
		return -1;
	}

	f >> stuNum;
	s = new(nothrow) Student[stuNum];

	if (!s)
	{
		cout << "系统内存没有连续空间存放所需数据。请清理内存空间，然后重新运行本程序。" << endl;
		f.close();
		return -2;
	}

	for (p = s; p - s < stuNum; p++)
	{
		f >> p->no;
		f >> p->name;
		f >> p->score;
		if (f.fail())
		{
			cout << "读取文件出错。请检查文件内的数据。" << endl;
			f.close();
			delete[] s;
			return -3;
		}
	}

	//开始排序
	selectionSort(s, stuNum);

	//开始输出
	cout << "学生数据如下：" << endl;

	printStudent(s, stuNum);

	cout << endl;
	delete[] s;
	f.close();

	//goto REINPUT;
	return 0;
}
