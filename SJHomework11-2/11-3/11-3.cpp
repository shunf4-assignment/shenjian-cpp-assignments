/*1652270 计算机2班 冯舜*/
#include <iostream>
#include <string>
using namespace std;

class Student
{
public:
protected:
	int num;
	string name;
	char sex;
};

class Student1 : protected Student
{
public:
	void get_value_1();
	void display_1();
private:
	int age;
	string addr;
};

void Student1::get_value_1()
{
	cin >> num >> name >> sex;
	cin >> age >> addr;
}
void Student1::display_1()
{
	cout << "num : " << num << endl;
	cout << "name : " << name << endl;
	cout << "sex : " << sex << endl;
	cout << "age : " << age << endl;
	cout << "address : " << addr << endl;
}

void input(Student1 &s);

int main()
{
	Student1 s;
	input(s);
	//s.display();
	s.display_1();
	return 0;
}

void input(Student1 &s)
{
	cout << "请依次输入学号 姓名 性别 年龄 地址：";
	//s.get_value();
	//cout << "请依次输入：";
	s.get_value_1();
}