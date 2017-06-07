/*1652270 计算机2班 冯舜*/
#include <iostream>
#include <string>
using namespace std;

class Student
{
public:
	void get_value()
	{
		cin >> num >> name >> sex;
	}
	void display()
	{
		cout << "num : " << num << endl;
		cout << "name : " << name << endl;
		cout << "sex : " << sex << endl;
	}

private:
	int num;
	string name;
	char sex;
};

class Student1 : public Student
{
public:
	void get_value_1()
	{
		cin >> age >> addr;
	}
	void display_1()
	{
		/*cout << "num : " << num << endl;
		cout << "name : " << name << endl;
		cout << "sex : " << sex << endl;*/
		cout << "age : " << age << endl;
		cout << "address : " << addr << endl;
	}
private:
	int age;
	string addr;
};

void input(Student1 &s);

int main()
{
	Student1 s;
	input(s);
	s.display();
	s.display_1();
	return 0;
}

void input(Student1 &s)
{
	cout << "请依次输入学号 姓名 性别：";
	s.get_value();
	cout << "请依次输入年龄 地址：";
	s.get_value_1();
}