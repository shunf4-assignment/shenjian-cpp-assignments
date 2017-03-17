/* 1652270 计算机2班 冯舜 */
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max)()

void printClassroom(const char * const * const name, const short * const room, const int * const roomStu)
{
	int maxLeft = 0;
	int seatCount = -1;
	//scan room
	for (int i = 0; room[i]; i++)
	{
		int moveLeft;
		for (moveLeft = 0; (unsigned short)room[i] >> moveLeft; moveLeft++)
			;
		if (moveLeft > maxLeft)
			maxLeft = moveLeft;
	}
	for (int i = 0; room[i]; i++)
	{
		cout << "|   /    ";
		for (int j = maxLeft-1; j >= 0; j--)
		{
			cout << "|";
			if (((unsigned short)(room[i] >> j) & 0x01) && roomStu[++seatCount] != -1)
			{
				cout << setw(8) << name[roomStu[seatCount]];
			}
			else
			{
				cout << setw(4) << "/" << setw(4) << "";
			}
		}
		cout << "|" << endl;
	}
	cout << endl;
	return;
}

void arrangeSeat(bool order)
{
	/*const char *name[] = {
		"赵一","钱二","孙三","李四",
		"周五","吴六","郑七","王九",
		"冯九","陈十","褚十一","卫十二",
		"蒋十三","沈十四","韩十五","杨十六",
		"朱十七","秦十八","尤十九","许二十",
		"何二一","吕二二","施二三","张二四",
		"孔二五","曹二六","严二七","华二八",
		NULL
	};*/
	const char *name[] = {
		"赵一","钱二","孙三","李四",
		"周五","吴六","郑七","王九",

		NULL
	};
	/*short room_[] = {
		(short)0xFFFF,
		0x00FF,
		0x00F2,
		0x00F2,
		0x00F2,
		0x00F2,
		0x00F2,
		0x00F2,
		0x00F2,
		0x0000
	};
	short roomy[] = {
		0x0092,
		0x0092,
		0x0092,
		0x0092,
		0x0092,
		0x0082,
		0x0092,
		0x0092,
		0x0092,
		0x0000
	};*/
	short room[] = {
		0x0081,
		0x00a9,
		0x00a9,
		0x00a9,
		0x00a9,
		0x00a8,
		0x00a9,
		0x0081,
		0x00a9,
		0x00a9,
		0x0000
	};
	int nameNum, roomNum, randomName, randomSeat;
	for (nameNum = 0; name[nameNum]; nameNum++)
		;
	roomNum = 0;
	for (int i = 0; room[i]; i++)
	{
		for (int j = 0; ((unsigned short)(room[i]) >> j); j++)
			roomNum += (((unsigned short)(room[i]) >> j) & 1);
	}

	if (nameNum > roomNum)
	{
		cout << "座位不够！按回车键回主菜单……" << endl;
		getchar();
		return;
	}

	int * const roomStu = new(nothrow) int[roomNum];
	bool * const stuSel = new(nothrow) bool[nameNum];
	if (!roomStu || !stuSel)
	{
		cout << "系统内存不足！按回车键回主菜单……" << endl;
		if (roomStu)
			delete[]roomStu;
		if (stuSel)
			delete[]stuSel;

		getchar();
		return;
	}

	for (int i = 0; i < roomNum; i++)
		roomStu[i] = -1;
	for (int i = 0; i < nameNum; i++)
		stuSel[i] = false;

	for (int i = 0; i < nameNum; i++)
	{
		int seatNo = 0;
		if (order)
		{
			seatNo = i;
		}
		else
		{
			//pickup seat
			randomSeat = rand() % (roomNum - i) + 1;
			for (int j = 0; j < randomSeat; j++, seatNo++)
			{
				while (roomStu[seatNo] != -1)
					seatNo++;
			}
			seatNo--;
		}
		

		//pickup people
		int nameNo = 0;
		randomName = rand() % (nameNum - i) + 1;
		for (int j = 0; j < randomName; j++, nameNo++)
		{
			while (stuSel[nameNo])
				nameNo++;
		}
		nameNo--;

		roomStu[seatNo] = nameNo;
		stuSel[nameNo] = true;
	}

	printClassroom(name, room, roomStu);

	delete[]roomStu;
	delete[]stuSel;

	cout << "完成！按回车键回主菜单……" << endl;

	getchar();
}

int main()
{
	char input[2] = { 0 };
	srand((unsigned)time(0));
	system("mode con cols=100 lines=25");

	for (;;)
	{
		system("cls");
		cout << "考试座位编排程序" << endl;
		cout << "\t1. 顺次位置排列\n\t2. 随机位置次序排列\n\t3. 扩大窗口\n\t4. 缩小窗口\n\t0. 退出" << endl << endl;
		cout << "请选择: ";
		cin.get(input, 2);
		cin.clear();
		cin.ignore(FS_MAX_LENGTH, '\n');
		if (!strcmp(input, "0"))
		{
			return 0;
		}
		if (!strcmp(input, "1"))
		{
			arrangeSeat(true);

		}
		if (!strcmp(input, "2"))
		{
			arrangeSeat(false);
		}
		if (!strcmp(input, "3"))
		{
			system("mode con cols=160 lines=30");
		}
		if (!strcmp(input, "4"))
		{
			system("mode con cols=100 lines=25");
		}
	}
	return 0;
}
