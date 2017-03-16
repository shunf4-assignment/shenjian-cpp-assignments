/*姓名 孟令琛 学号 1652308  班级 3班*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

struct student {
	int *no;
	char *name;
	int *score;
	struct student *next;
};
void output_student(struct student *head);
void release(struct student *head);
int main()
{
	ifstream fin;
	fin.open("list.txt", ios::in);
	if (fin.is_open() == 0)
	{
		cout << "打开文件失败" << endl;
		return -1;
	}

	student *p = NULL, *q = NULL, *head = NULL;
	while (1)
	{
		if (p != NULL)
			q = p;
		p = (student *)malloc(sizeof(struct student));
		if (p == NULL)
		{
			cout << "无法申请到空间" << endl;
			return -1;

		}
		if (q == NULL)
			head = p;
		else
			q->next = p;
		p->no = (int *)malloc(sizeof(int));
		p->score = (int *)malloc(sizeof(int));
		p->name = (char *)malloc(6 * sizeof(char));

		if (p->no == NULL || p->score == NULL || p->name == NULL)
		{
			cout << "无法申请到空间" << endl;
			return -1;
		}
		fin >> *p->no;
		if (*p->no == 9999999)
		{
			q->next = NULL;
			break;
		}
		fin >> p->name >> *p->score;
		p->next = NULL;
	}

	output_student(head);
	release(head);

	return 1;

}
void output_student(student *head)
{
	student *p = head;
	cout << setiosflags(ios::left);
	cout << setw(10) << "学号" << setw(10) << "姓名" << setw(4) << "分数" << endl;
	while (p != NULL)
	{
		cout << setw(10) << *p->no << setw(10) << p->name << setw(4) << *p->score << endl;
		p = p->next;
	}
	return;
}
void release(student *head)
{
	struct student *p, *q;
	p = head;
	while (p != NULL)
	{
		q = p->next;
		free (p->no);
		free (p->score);
		free(p->name);
		free(p);
		p = q;
	}
	return;
}