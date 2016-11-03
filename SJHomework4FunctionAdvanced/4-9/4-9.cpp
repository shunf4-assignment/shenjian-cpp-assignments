/* 1652270 计算机2班 冯舜 */
#include <iostream>
using namespace std;

//int totalMove = 0;

void Move(char from, char to, int num)
{
	cout << "将 " << num << " 号圆盘从 " << from << " 座移到 " << to << " 座" << endl;
	//totalMove += 1;
}

void HanoiStep(char origin, char dest, int totalNum)
{
	//我自己的解法
	//定义这样的一组动作为“汉诺步骤”
	char intermediate;

	if (totalNum == 1)
	{
		Move(origin, dest, 1);
		return;
	}
	intermediate = 'A' + 'B' + 'C' - origin - dest;
	//cout << "  尝试将" << origin << "柱上的" << totalNum - 1 << " 个圆盘移动到" << intermediate << "柱" << endl;
	HanoiStep(origin, intermediate, totalNum - 1);
	Move(origin, dest, totalNum);
	//cout << "  尝试将" << intermediate << "i柱上的" << totalNum - 1 << " 个圆盘移动到" << dest << "柱d" << endl;
	HanoiStep(intermediate, dest, totalNum - 1);
}

int main()
{
	int n;
	bool valid;

	do
	{
		valid = true;
		cout << "初始 A 塔有多少层圆盘：";
		cin >> n;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

		if (n < 1)
			valid = false;
	} while (!valid);
	
	//totalMove = 0;
	HanoiStep('A', 'C', n);
	//cout << "总共移动 " << totalMove << " 步。" << endl;
	return 0;
}
