/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

class Cuboid
{
private:
	double length;
	double width;
	double height;
	double vol;
public:
	void input();
	void volume();
	void output();
};

int main()
{
	Cuboid c;

	for (int i = 1; i < 4; i++)
	{
		cout << "�� " << i << " �Σ�" << endl;
		c.input();
		c.volume();
		c.output();
	}
	return 0;
}

void Cuboid::input()
{
	cout << "�����볤�����ߣ��ո������";
	cin >> length >> width >> height;
}

void Cuboid::volume()
{
	vol = length * width*height;
}

void Cuboid::output()
{
	cout << "������������" << vol << endl;
}