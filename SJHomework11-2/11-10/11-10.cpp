/*1652270 计算机2班 冯舜*/
#include <iostream>
#include <string>
using namespace std;

class Teacher
{
public:
	Teacher(int n, string nam, char se) :num(n), name(nam), sex(se)
	{

	}
	int getNum()
	{
		return num;
	}
	string getName()
	{
		return name;
	}
	char getSex()
	{
		return sex;
	}
private:
	int num;
	string name;
	char sex;
};

class BirthDate
{
public:
	BirthDate(int y, int m, int d) :year(y), month(m), day(d)
	{

	}
	void set(int y, int m, int d)
	{
		year = y, month = m, day = d;
	}
	int getYear()
	{
		return year;
	}
	int getMonth()
	{
		return month;
	}
	int getDay()
	{
		return day;
	}
private:
	int year;
	int month;
	int day;
};

class Professor : public Teacher
{
public:
	Professor(int n, string nam, char se, int y,int m,int d):Teacher(n,nam,se),birthday(y,m,d)
	{}
	void setBirthday(int y, int m, int d)
	{
		birthday.set(y, m, d);
	}
	void print()
	{
		cout << "Num: " << getNum() << endl;
		cout << "Name: " << getName() << endl;
		cout << "Sex : " << getSex() << endl;
		cout << "Year: " << birthday.getYear() << endl;
		cout << "Month:" << birthday.getMonth() << endl;
		cout << "Day :" << birthday.getDay() << endl;
	}
private:
	BirthDate birthday;
};

int main()
{
	int num, y, m, d;
	char sex;
	string name;
	cout << "Please input the number, name, sex, birth year, birth month and birth day of this Professor: " << endl;
	cin >> num >> name >> sex >> y >> m >> d;
	Professor prof1(num, name, sex, y, m, d);
	cout << "Please input new birth year, birth month and birth day of this Professor: " << endl;
	cin >>  y >> m >> d;
	prof1.setBirthday(y, m, d);
	cout << "Newest Data:" << endl;
	prof1.print();
	return 0;
}
/*
测试数据：
1652270 SJ M 1990 1 1
1899 7 7

*/