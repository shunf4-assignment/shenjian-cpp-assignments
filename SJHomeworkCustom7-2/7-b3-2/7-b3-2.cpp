/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

const int namelen = 9;

struct student
{
	int no;
	char name[9];
	int score;
	struct student *next;
};


void printStudent(const student * const head)
{
	const student *p = head;
	cout << "\tID Num\t\tName    \tScore" << endl;
	cout << "===============================================" << endl;
	while (true)
	{
		cout << "\t" << p->no << "\t\t" << p->name << setw(namelen - 1 - strlen(p->name)) << "" << "\t" << p->score << endl;
		if (!p->next)
			break;
		p = p->next;
	}
}

void cleanUp(ifstream &f, student * const head)
{
	student * q = head, *p = q;
	if (f.is_open())
		f.close();
	while (p)
	{
		q = p->next;
		if (p)
			delete p;
		p = q;
	}
	return;
}

int main()
{
	//REINPUT:
	ifstream f;
	int nowNo = 0;
	student *head = NULL, *p = NULL, *q = NULL;
	bool first = true;

	f.open("list.txt", ios::in);
	if (f.is_open() == 0)
	{
		cout << "�� list.txt ʧ�ܡ�������ļ��Ƿ��ڹ���Ŀ¼�ڡ�" << endl;
		return -1;
	}

	while (true)
	{
		f >> nowNo;
		if (nowNo != 9999999)
		{
			q = new(nothrow) student;
			if (!q)
			{
				cout << "ϵͳ�ڴ�û�пռ����������ݡ��������ڴ�ռ䣬Ȼ���������б�����" << endl;
				cleanUp(f, head);
				return -2;
			}
			if (first)
			{
				first = false;
				p = head = q;
			}
			else
			{
				p->next = q;
				p = q;
			}
			p->no = nowNo;
			f >> p->name;
			f >> p->score;
			p->next = NULL;
		}
		else
		{
			break;
		}
	}

	//��ʼ���
	cout << "ѧ���������£�" << endl;

	printStudent(head);

	cout << endl;
	cleanUp(f, head);
	//goto REINPUT;
	return 0;
}
