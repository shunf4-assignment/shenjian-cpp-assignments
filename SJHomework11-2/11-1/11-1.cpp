/*1652270 �����2�� ��˴*/
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
	cout << "����������ѧ�� ���� �Ա�";
	s.get_value();
	cout << "�������������� ��ַ��";
	s.get_value_1();
}