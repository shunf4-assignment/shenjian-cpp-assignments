/* 1652270 计算机2班 冯舜 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

const int len = 25;

struct student
{
	char *id;
	char *name;
	char *school;
	struct student *next;
};

void cleanUp(ifstream &f1, ofstream &f2, student * const head)
{
	student * q = head, *p = q;
	if (f1.is_open())
		f1.close();
	if (f2.is_open())
		f2.close();
	while (p)
	{
		q = p->next;
		if (p)
		{
			if (p->id)
				delete (p->id);
			if (p->name)
				delete (p->name);
			if (p->school)
				delete (p->school);
			delete (p);
		}
		p = q;
	}
	return;
}

int readInData(ifstream &fi, ofstream &fo, int &numerator, int &denominator, student * &head)
{
	int count = 0;
	bool first = true;
	char tmpId[len];
	char tmpName[len];
	char tmpSchool[len];
	student *p = NULL, *q = NULL;

	fi >> numerator;
	fi >> denominator;

	while (count < denominator)
	{
		fi >> tmpId;
		q = new(nothrow) student;
		if (!q)
		{
			cout << "系统内存没有空间存放所需数据。请清理内存空间，然后重新运行本程序。" << endl;
			cleanUp(fi, fo, head);
			return -2;
		}
		q->id = q->school = q->name = NULL;
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

		p->id = new char[strlen(tmpId) + 1];
		if (!p->id)
		{
			cout << "系统内存没有空间存放所需数据。请清理内存空间，然后重新运行本程序。" << endl;
			cleanUp(fi, fo, head);
			return -2;
		}
		strcpy(p->id, tmpId);

		fi >> tmpName;
		p->name = new char[strlen(tmpName) + 1];
		if (!p->name)
		{
			cout << "系统内存没有空间存放所需数据。请清理内存空间，然后重新运行本程序。" << endl;
			cleanUp(fi, fo, head);
			return -2;
		}
		strcpy(p->name, tmpName);

		fi >> tmpSchool;
		p->school = new char[strlen(tmpSchool) + 1];
		if (!p->school)
		{
			cout << "系统内存没有空间存放所需数据。请清理内存空间，然后重新运行本程序。" << endl;
			cleanUp(fi, fo, head);
			return -2;
		}
		strcpy(p->school, tmpSchool);

		p->next = NULL;
		count++;
	}
	return 0;
}

void outputStudent(const student * const p, ofstream &fo)
{
	fo << p->id << "\t" << p->name << "\t" << p->school << endl;
}

void pickUp(student * head, int numerator, int denominator, ofstream &fo)
{
	int count = 0;
	int thisRand;
	student *p, *q;
	
	for (; count < numerator; count++)
	{
		thisRand = rand() % denominator;
		p = q = head;
		for (int i = 0; i < thisRand; i++)
		{
			if (i < thisRand - 1)
				q = q->next;
			p = p->next;
		}
		outputStudent(p, fo);
		if (q != head || p != head)
		{
			q->next = p->next;
		}
		delete (p->id);
		delete (p->name);
		delete (p->school);
		delete (p);
		denominator--;
	}
	

}

int main()
{
	//REINPUT:
	ifstream fi;
	ofstream fo;
	int numerator = 0; //分子
	int denominator = 0; //分母
	int readSuc;
	student * head = NULL;
	
	srand((unsigned)time(0));

	fi.open("stulist.txt", ios::in);
	if (fi.is_open() == 0)
	{
		cout << "打开 stulist.txt 失败。请检查该文件是否在工作目录内。" << endl;
		return -1;
	}

	fo.open("result.txt", ios::out);
	if (fo.is_open() == 0)
	{
		cout << "打开 result.txt 失败。请检查该文件是否可被写入。" << endl;
		return -1;
	}
	cout << "读取名单文件中..." << endl;
	if (readSuc = readInData(fi, fo, numerator, denominator, head))
	{
		return readSuc;
	}
	cout << "名单有 " << denominator << " 人，正在随机挑选..." << endl;
	pickUp(head, numerator, denominator, fo);
	cout << "成功挑选 " << numerator << " 人，已经存入 result.txt。" << endl;
	cleanUp(fi, fo, head);
	//goto REINPUT;
	return 0;
}
