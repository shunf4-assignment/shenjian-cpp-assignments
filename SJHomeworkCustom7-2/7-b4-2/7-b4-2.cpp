/* 1652270 �����2�� ��˴ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

const int namelen = 9;

struct student
{
	int *no;
	char *name;
	int *score;
	struct student *next;
};


void printStudent(const student * const head)
{
	const student *p = head;
	cout << "\tID Num\t\tName    \tScore" << endl;
	cout << "===============================================" << endl;
	while (true)
	{
		cout << "\t" << *(p->no) << "\t\t" << (p->name) << "     \t" << *(p->score) << endl;
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
		{
			if (p->no)
				delete (p->no);
			if (p->name)
				delete (p->name);
			if (p->score)
				delete (p->score);
			delete (p);
		}
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
	char tmpName[namelen];

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
			q->no = q->score = NULL;
			q->name = NULL;
			q->next = NULL;
			if (first)
			{
				first = false;
				head = q;
			}
			else
			{
				p->next = q;
			}
			p = q;

			p->no = new int;
			if (!p->no)
			{
				cout << "ϵͳ�ڴ�û�пռ����������ݡ��������ڴ�ռ䣬Ȼ���������б�����" << endl;
				cleanUp(f, head);
				return -2;
			}
			*(p->no) = nowNo;

			f >> tmpName;
			p->name = new char[strlen(tmpName) + 1];
			if (!p->name)
			{
				cout << "ϵͳ�ڴ�û�пռ����������ݡ��������ڴ�ռ䣬Ȼ���������б�����" << endl;
				cleanUp(f, head);
				return -2;
			}
			strcpy(p->name, tmpName);

			p->score = new int;
			if (!p->score)
			{
				cout << "ϵͳ�ڴ�û�пռ����������ݡ��������ڴ�ռ䣬Ȼ���������б�����" << endl;
				cleanUp(f, head);
				return -2;
			}
			f >> *(p->score);

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
