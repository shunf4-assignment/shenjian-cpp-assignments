/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

class Student
{
public:
	Student(int n, float s) : num(n), score(s)
	{

	}
	void change(int n, float s)
	{
		num = n;
		score = s;
	}
	void display()
	{
		cout << num << " " << score << endl;
	}
private:
	int num;
	float score;
};

void fun(Student &stud)
{
	stud.display();
	stud.change(101, 80.5);
	stud.display();
}

int main()
{
	Student stud(101, 78.5);
	fun(stud);
	return 0;
}

/*
��������
��ʾ���޸�ǰ���޸ĺ��ѧ�����ݣ�
101 78.5
101 80.5
*/