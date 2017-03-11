/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <iomanip>
using namespace std;

const int maxDisk = 10;
char towerName[] = { 'A', 'B', 'C' };
int totalMove = 0;
int towers[3][maxDisk] = { { 0 },{ 0 },{ 0 } };
int towerPointer[] = { 0,0,0 };  //指的是层数+1，也就是Push下一个圆盘应该在的位置

int Push(int towerNum,int diskSize)
{
	towers[towerNum][towerPointer[towerNum]++] = diskSize;
	return diskSize;
}

int Pop(int towerNum)
{
	return towers[towerNum][--towerPointer[towerNum]];
}

void printTowers()
{
	for (int towerNo = 0; towerNo < 3; towerNo++)
	{
		cout << towerName[towerNo] << ":";
		for (int i = 0; i < towerPointer[towerNo]; i++)
		{
			cout << " " << setw(2) << towers[towerNo][i];
		}
		for (int i = 0; i < 30 - 3 * towerPointer[towerNo]; i++)
		{
			cout << ' ';
		}
	}
}

//A:0,B:1,C:2
void Move(int from, int to, int num)
{
	totalMove += 1;
	Pop(from);
	Push(to, num);
	cout << "Step" << setw(5) << setfill('0') << totalMove << setfill(' ') << ":(" << num << ")@" << towerName[from] << "-->" << towerName[to] << ". ";
	printTowers();
	cout << endl;
}

void HanoiStep(int origin, int dest, int totalNum)
{
	//定义这样的一组动作为“汉诺步骤”
	char intermediate;

	if (totalNum == 1)
	{
		Move(origin, dest, 1);
		return;
	}
	intermediate = 0 + 1 + 2 - origin - dest;
	HanoiStep(origin, intermediate, totalNum - 1);
	Move(origin, dest, totalNum);
	HanoiStep(intermediate, dest, totalNum - 1);
}

void HanoiInit(int origin, int dest, int totalNum)
{
	for (int i = 0; i < totalNum; i++)
	{
		towers[origin][i] = totalNum - i;
	}
	towerPointer[origin] = totalNum;
	cout << "初始：               ";
	printTowers();
	cout << endl;
	HanoiStep(origin, dest, totalNum);
}

char toUpperCase(char a)
{
	if (a >= 'a' && a <= 'z')
	{
		a = a - 'a' + 'A';
		//a - 65 + 97;
	}
	return a;
}

int main()
{
	int n;
	char towerOrigin, towerDest;
	bool valid;
	system("cls");
	system("mode con cols=140");
	do
	{
		valid = true;
		cout << "初始塔有多少层圆盘(1-" << maxDisk << ")：";
		cin >> n;

		if (!cin.good())
		{
			valid = false;
			cout << "输入不合法，请重新输入。" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (n < 1 || n > maxDisk)
		{
			valid = false;
			cout << "输入超出范围，请重新输入。" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
	} while (!valid);
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	do
	{
		valid = true;
		cout << "从哪个塔移走？(A-C)";
		cin >> towerOrigin;

		if (!cin.good())
		{
			valid = false;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (!(towerOrigin >= 'A' && towerOrigin <= 'C' || towerOrigin >= 'a' && towerOrigin <= 'c'))
		{
			valid = false;
			cout << "输入超出范围，请重新输入。" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		towerOrigin = toUpperCase(towerOrigin);

	} while (!valid);
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	do
	{
		valid = true;
		cout << "移到哪个塔？(A-C，不同于之前输入的塔)";
		cin >> towerDest;

		if (!cin.good())
		{
			valid = false;
			cout << "输入不合法，请重新输入。" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (!(towerDest >= 'A' && towerDest <= 'C' || towerDest >= 'a' && towerDest <= 'c'))
		{
			valid = false;
			cout << "输入超出范围，请重新输入。" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		towerDest = toUpperCase(towerDest);
		if (towerDest == towerOrigin)
		{
			valid = false;
			cout << "两个塔不能相同，请重新输入。" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
	} while (!valid);

	totalMove = 0;
	HanoiInit(towerOrigin - 'A', towerDest - 'A', n);
	cout << "总共移动 " << totalMove << " 步。" << endl;
	return 0;
}
