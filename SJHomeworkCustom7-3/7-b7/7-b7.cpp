/* 1652270 �����2�� ��˴ */
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
		"��һ","Ǯ��","����","����",
		"����","����","֣��","����",
		"���","��ʮ","��ʮһ","��ʮ��",
		"��ʮ��","��ʮ��","��ʮ��","��ʮ��",
		"��ʮ��","��ʮ��","��ʮ��","���ʮ",
		"�ζ�һ","������","ʩ����","�Ŷ���",
		"�׶���","�ܶ���","�϶���","������",
		NULL
	};*/
	const char *name[] = {
		"��һ","Ǯ��","����","����",
		"����","����","֣��","����",

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
		cout << "��λ���������س��������˵�����" << endl;
		getchar();
		return;
	}

	int * const roomStu = new(nothrow) int[roomNum];
	bool * const stuSel = new(nothrow) bool[nameNum];
	if (!roomStu || !stuSel)
	{
		cout << "ϵͳ�ڴ治�㣡���س��������˵�����" << endl;
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

	cout << "��ɣ����س��������˵�����" << endl;

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
		cout << "������λ���ų���" << endl;
		cout << "\t1. ˳��λ������\n\t2. ���λ�ô�������\n\t3. ���󴰿�\n\t4. ��С����\n\t0. �˳�" << endl << endl;
		cout << "��ѡ��: ";
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
