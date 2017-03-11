/* 1652270 �����2�� ��˴ */
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
		cout << "�� student.txt ʧ�ܡ�������ļ��Ƿ��ڹ���Ŀ¼�ڡ�" << endl;
		return -1;
	}

	f >> stuNum;
	s = new(nothrow) Student[stuNum];

	if (!s)
	{
		cout << "ϵͳ�ڴ�û�������ռ����������ݡ��������ڴ�ռ䣬Ȼ���������б�����" << endl;
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
			cout << "��ȡ�ļ����������ļ��ڵ����ݡ�" << endl;
			f.close();
			delete[] s;
			return -3;
		}
	}

	//��ʼ����
	selectionSort(s, stuNum);

	//��ʼ���
	cout << "ѧ���������£�" << endl;

	printStudent(s, stuNum);

	cout << endl;
	delete[] s;
	f.close();

	//goto REINPUT;
	return 0;
}
