/* 1652270 �����2�� ��˴ */
#include <iostream>
#include <iomanip>
using namespace std;

const int maxDisk = 10;
char towerName[] = { 'A', 'B', 'C' };
int totalMove = 0;
int towers[3][maxDisk] = { { 0 },{ 0 },{ 0 } };
int towerPointer[] = { 0,0,0 };  //ָ���ǲ���+1��Ҳ����Push��һ��Բ��Ӧ���ڵ�λ��

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
	//����������һ�鶯��Ϊ����ŵ���衱
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
	cout << "��ʼ��               ";
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
		cout << "��ʼ���ж��ٲ�Բ��(1-" << maxDisk << ")��";
		cin >> n;

		if (!cin.good())
		{
			valid = false;
			cout << "���벻�Ϸ������������롣" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (n < 1 || n > maxDisk)
		{
			valid = false;
			cout << "���볬����Χ�����������롣" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
	} while (!valid);
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	do
	{
		valid = true;
		cout << "���ĸ������ߣ�(A-C)";
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
			cout << "���볬����Χ�����������롣" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		towerOrigin = toUpperCase(towerOrigin);

	} while (!valid);
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	do
	{
		valid = true;
		cout << "�Ƶ��ĸ�����(A-C����ͬ��֮ǰ�������)";
		cin >> towerDest;

		if (!cin.good())
		{
			valid = false;
			cout << "���벻�Ϸ������������롣" << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (!(towerDest >= 'A' && towerDest <= 'C' || towerDest >= 'a' && towerDest <= 'c'))
		{
			valid = false;
			cout << "���볬����Χ�����������롣" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		towerDest = toUpperCase(towerDest);
		if (towerDest == towerOrigin)
		{
			valid = false;
			cout << "������������ͬ�����������롣" << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
	} while (!valid);

	totalMove = 0;
	HanoiInit(towerOrigin - 'A', towerDest - 'A', n);
	cout << "�ܹ��ƶ� " << totalMove << " ����" << endl;
	return 0;
}
