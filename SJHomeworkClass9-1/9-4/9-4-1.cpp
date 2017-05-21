/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

class student {
private:
	int num;
	float score;
public:
	void display();   //输出学号和成绩
					  /* 给出需要的其它成员函数的定义，数量不限 */
	student(void);
	student(int, float);
	void setNo(int);
	void setGrade(float);
};

/* 在此给出类成员函数的实现（体外方式） */
student::student(void)
{
	setNo(0);
	setGrade(100);
}

student::student(int newno, float newgrade)
{
	setNo(newno);
	setGrade(newgrade);
}

void student::display()
{
	cout << "学号: " << num << ", 成绩: " << score << endl;
}

void student::setNo(int newno)
{
	num = newno;
}

void student::setGrade(float newgrade)
{
	score = newgrade;
}


int main()
{
	student *p, s[5] = { student(1001, 78.5),
		student(1002, 63.5),
		student(1003, 87.5),
		student(1004, 52.5),
		student(1005, 34.5) };
	/* 下面输出 1001、1003、1005三个人的信息
	【注意：】不允许再定义任何类型的变量 */
	p = s;
	(p)->display();
	(p + 2)->display();
	(p + 4)->display();

	return 0;
}