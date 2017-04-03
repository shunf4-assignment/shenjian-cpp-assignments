/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
using namespace std;
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max)()

/*string: 0; unsigned int: 1; short: 2; numberized-char: 3*/
struct Data
{
	char *desc;
	int type;
	int lowerLimit;
	int upperLimit;
	unsigned startPoint;
};

void modify(fstream &f, const Data *d);
template <typename T>
void inputThing(T* p, const char * promptText, const char * cinUngoodText, const char * outLimitText, T lowerLimit, T upperLimit)
{
	bool valid;
	do
	{
		valid = true;
		cout << promptText;
		cin >> *p;

		if (!cin.good())
		{
			valid = false;
			cout << cinUngoodText << endl;
		}
		else if (*p > upperLimit || *p < lowerLimit)
		{
			valid = false;
			cout << outLimitText << endl;
		}

		if (!valid)
		{
			cin.clear();
			cin.ignore(FS_MAX_LENGTH, '\n');
		}

	} while (!valid);
	cin.clear();
	cin.ignore(FS_MAX_LENGTH, '\n');
}

const Data gameData[] = { 
	{"玩家昵称",	 0, 0,0,0}, 
	{ "生命值", 2, 0,10000,16 },
	{ "力量值", 2, 0,10000,18 },
	{ "体质", 2, 0,8192,20 },
	{ "灵巧", 2, 0,1024,22 },
	{ "金钱数量", 1, 0,100000000,24 },
	{ "名声值", 1, 0,1000000,28 },
	{ "魅力值", 1, 0,1000000,32 },
	{ "移动速度", 3, 0,100,44 },
	{ "攻击速度", 3, 0,100,45 },
	{ "攻击范围", 3, 0,100,47 },
	{ "攻击力", 2, 0,2000,48 },
	{ "防御力", 2, 0,2000,50 },
	{ "敏捷度", 3, 0,100,52 },
	{ "智力", 3, 0,100,53 },
	{ "经验", 3, 0,100,54 },
	{ "等级", 3, 0,100,55 },
	{ "魔法值", 2, 0,10000,56 },
	{ "使用魔法时每次消耗的魔法值", 3, 0,100,58 },
	{ "魔法伤害力", 3, 0,100,59 },
	{ "命中率", 3, 0,100,60 },
	{ "魔法防御力", 3, 0,100,61 },
	{ "暴击率", 3, 0,100,62 },
	{ "耐力", 3, 0,100,63 },
	{NULL,0,0,0,0}
};

int main()
{
	char keyLower = 'A', keyUpper = keyLower, userOpt;
	int mode;
	fstream f;
	f.open("game.dat", ios::in | ios::out | ios::binary);
	f.setf(ios::unitbuf);
	if (!f.is_open())
	{
		cout << "打开 game.dat 失败！";
		return 1;
	}
	while (true)
	{
		system("cls");
		cout << "游戏存档修改器" << endl;
		keyLower = 'A', keyUpper = keyLower;
		for (const Data *p = gameData; p->desc; p++)
		{
			if ((p - gameData) % 2)
			{
				cout << setw(38 - strlen(p[-1].desc)) << "";
			}
			else
			{
				cout << endl;
			}
			cout << keyUpper << ". " << p->desc;
			keyUpper++;
		}
		cout << endl << endl;
		cout << "请选择 [ " << keyLower << " - " << char(keyUpper - 1) << " ], 0 退出: ";
		do
		{
			userOpt = _getch();
		} while (!(userOpt >= (keyLower) && userOpt < (keyUpper) || userOpt >= (keyLower + 'a' - 'A') && userOpt < (keyUpper + 'a' - 'A') || userOpt == '0'));
		cout << userOpt;
		if (userOpt == '0')
			break;
		if (userOpt >= (keyLower) && userOpt < (keyUpper))
			mode = userOpt - 'A';
		if (userOpt >= (keyLower + 'a' - 'A') && userOpt < (keyUpper + 'a' - 'A'))
			mode = userOpt - 'a';
		modify(f, gameData + mode);
		
	}
	f.close();
	return 0;
}

void modify(fstream &f, const Data *d)
{
	system("cls");
	cout << "将要修改：" << d->desc;
	if (d->type == 1)
	{
		int origin;
		int now;
		cout << "，这是个 4 字节整数，初始位置在 ";
		//cout << "0x" << setiosflags(ios::uppercase) << hex;
		cout << d->startPoint << "，允许修改范围为 (" << dec << d->lowerLimit << " - " << d->upperLimit << ")。" << endl << endl;
		cout << "原数据：";
		f.seekg(d->startPoint, ios::beg);
		//cout << endl << "Tellp: " << f.tellp() << endl;
		f.read((char *)&origin, sizeof(int));
		cout << origin;
		//cout << endl << "Tellp: " << f.tellp() << endl;
		cout << endl;
		inputThing(&now, "你想把它修改为：", "输入非法。", "输入超限。", d->lowerLimit, d->upperLimit);
		f.seekp(d->startPoint, ios::beg);
		f.write((char *)&now, sizeof(int));
	}
	else if (d->type == 2)
	{
		short origin;
		short now;
		cout << "，这是个 2 字节短整数，初始位置在 ";
		//cout << "0x" << setiosflags(ios::uppercase) << hex;
		cout << d->startPoint << "，允许修改范围为 (" << dec << d->lowerLimit << " - " << d->upperLimit << ")。" << endl << endl;
		cout << "原数据：";
		f.seekg(d->startPoint, ios::beg);
		
		f.read((char *)&origin, sizeof(origin));
		cout << origin;
		cout << endl;
		inputThing(&now, "你想把它修改为：", "输入非法。", "输入超限。", (short)d->lowerLimit, (short)d->upperLimit);
		f.seekp(d->startPoint, ios::beg);
		f.write((char *)&now, sizeof(now));
	}
	else if (d->type == 3)
	{
		char origin;
		int now;
		char now_;
		cout << "，这是个 1 字节整数，初始位置在 ";
		//cout << "0x" << setiosflags(ios::uppercase) << hex;
		cout << d->startPoint << "，允许修改范围为 (" << dec << d->lowerLimit << " - " << d->upperLimit << ")。" << endl << endl;
		cout << "原数据：";
		f.seekg(d->startPoint, ios::beg);
		
		f.read((char *)&origin, sizeof(origin));
		
		cout << (unsigned)origin;
		cout << endl;
		inputThing(&now, "你想把它修改为：", "输入非法。", "输入超限。", d->lowerLimit, d->upperLimit);
		now_ = (char)now;
		f.seekp(d->startPoint, ios::beg);
		f.write((char *)&now, sizeof(now_));
	}
	else if (d->type == 0)
	{
		int len = (d + 1)->startPoint - d->startPoint - 1;
		char *p, *i;

		p = new(nothrow) char[len + 1];
		if (!p)
		{
			cout << "破机子！怎么连 " << len + 1 << " 字节的空间都申请不到？？" << endl;
			return;
		}
		p[len] = 0;

		i = new(nothrow) char[len + 1];
		if (!i)
		{
			cout << "破机子！怎么连 " << len + 1 << " 字节的空间都申请不到？？" << endl;
			delete[] p;
			return;
		}
		i[len] = 0;

		cout << "，这是个长度为 " << len << " 的字符串，初始位置在 ";
		//cout << "0x" << setiosflags(ios::uppercase) << hex;
		cout << d->startPoint << "。" << endl << endl;
		cout << "原数据：";
		f.seekg(d->startPoint, ios::beg);
		
		f.read(p, len * sizeof(char));
		cout << p;
		cout << endl;
		cout << "你想把它更改为：（限 " << len << " 字符）";
		cin.getline(i, (len + 1) * sizeof(char));
		f.seekp(d->startPoint, ios::beg);
		f.write(i, (len + 1) * sizeof(char));

		delete[] p;
		delete[] i;
		
	}
	//f.flush();
	cout << "成功！";
	system("pause");
}

