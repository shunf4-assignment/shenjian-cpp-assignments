/*1652270 �����2�� ��˴*/
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
	cout << "����������ѧ�� ���� �Ա� ���� ��ַ��";
	//s.get_value();
	//cout << "���������룺";
	s.get_value_1();
}