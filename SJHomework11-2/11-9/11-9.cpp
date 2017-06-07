/*1652270 ¼ÆËã»ú2°à ·ëË´*/
#include <iostream>
#include <string>
using namespace std;

class Teacher
{
protected:
	string name;
	unsigned age;
	char sex;
	string addr;
	string tel;
	string title;
public:
	void display()
	{
		cout << "Name: " << name << endl;
		cout << "Age : " << age << endl;
		cout << "Sex : " << sex << endl;
		cout << "Addr: " << addr << endl;
		cout << "Tele: " << tel << endl;
		cout << "Title:" << title << endl;
	}
	void input()
	{
		cout << "Please input name age sex addr tele title: ";
		cin >> name >> age >> sex >> addr >> tel >> title;
	}
};

class Cadre
{
protected:
	string name;
	unsigned age;
	char sex;
	string addr;
	string tel;
	string post;
public:
	//void display()
	//{
	//	cout << "Name: " << name;
	//	cout << "Age : " << age;
	//	cout << "Sex : " << sex;
	//	cout << "Addr: " << addr;
	//	cout << "Tele: " << tel;
	//	cout << "Post:" << post;
	//}
	void input()
	{
		cout << "Please input name age sex addr tele post: ";
		cin >> name >> age >> sex >> addr >> tel >> post;
	}
};

class Teacher_Cadre : public Teacher, public Cadre
{
protected:
	double wages;
public:
	void show()
	{
		display();
		cout << "Post :" << post << endl;
		cout << "Wage :" << wages << endl;
	}
	void input()
	{
		cout << "Please input name age sex addr tele title post wages: ";
		cin >> Teacher::name >> Teacher::age >> Teacher::sex >> Teacher::addr >> Teacher::tel >> title >> post >> wages;
		Cadre::name = Teacher::name;
		Cadre::age = Teacher::age;
		Cadre::sex = Teacher::sex;
		Cadre::addr = Teacher::addr;
		Cadre::tel = Teacher::tel;
	}
};

int main()
{
	Teacher_Cadre p1;
	p1.input();
	p1.show();
	return 0;
}

/*
Test data:
SJ 100 F TJ 123456789 GJGCS JS 1000.2
*/