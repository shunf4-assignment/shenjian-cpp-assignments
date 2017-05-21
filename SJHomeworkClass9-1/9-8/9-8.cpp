/* 1652270 计算机2班 冯舜 */
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
程序结果：
显示了修改前和修改后的学生数据：
101 78.5
101 80.5
*/