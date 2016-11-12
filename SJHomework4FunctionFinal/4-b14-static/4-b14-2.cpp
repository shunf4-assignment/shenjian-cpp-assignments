/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <iomanip>
using namespace std;

void Move(char from, char to, int num, int moveNum)
{
	cout << "第 " << setw(5) << setfill('0') << moveNum << " 步：将 " << num << " 号圆盘从 " << from << " 座移到 " << to << " 座" << endl;
	//totalMove += 1;
}

int HanoiStep(char origin, char dest, int totalNum, bool firstTime = true)
{
	//定义这样的一组动作为“汉诺步骤”
	char intermediate;
	static int totalMove = 0;

	if (firstTime) {
		totalMove = 0;
	}

	if (totalNum == 1)
	{
		totalMove += 1;
		Move(origin, dest, 1, totalMove);
		return totalMove;
	}
	intermediate = 'A' + 'B' + 'C' - origin - dest;
	HanoiStep(origin, intermediate, totalNum - 1, false);
	totalMove += 1;
	Move(origin, dest, totalNum, totalMove);
	HanoiStep(intermediate, dest, totalNum - 1, false);
	return totalMove;
}

int main()
{
	int n;
	int moveNum;
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
			continue;
		}

		if (n < 1)
		{
			valid = false;
			cout << "输入超出范围，请重新输入。" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
	} while (!valid);

	moveNum = HanoiStep('A', 'C', n);
	cout << "总共移动 " << moveNum << " 步。" << endl;
	return 0;
}
