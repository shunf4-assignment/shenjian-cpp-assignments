/* 1652270 计算机2班 冯舜 */
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
		cout << "第 " << i << " 次：" << endl;
		c.input();
		c.volume();
		c.output();
	}
	return 0;
}

void Cuboid::input()
{
	cout << "请输入长、宽、高，空格隔开：";
	cin >> length >> width >> height;
}

void Cuboid::volume()
{
	vol = length * width*height;
}

void Cuboid::output()
{
	cout << "长方体的体积：" << vol << endl;
}