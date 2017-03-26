/* 1652270 计算机2班 冯舜 */
#define _CRT_SECURE_NO_WARNINGS
#define FS_MAX_LENGTH (numeric_limits<std::streamsize>::max)()

#define nameLen 8
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstring>
using namespace std;


void printClassroom(const char * const * const name, const short * const room, const int * const roomStu, ostream& out);
int checkSeatEnough(const char * const * const name, const short * const room, int *nN, int *rN);
void arrangeSeat(const char * const * const name, const short * const room, bool order, ostream& out);
void printUsage(const char * const procName);
void cleanUp(ifstream *f, int fileNum, short *room, char **name);
void YNtoShort(short *room, char *YN);
int readFile(const char * const * const argv, char ***name, short **room);

int main(int argc, char ** argv)
{
	char input[2] = { 0 };
	int status, roomEnoughStatus;

	if (argc != 4)
	{
		printUsage(argv[0]);
		return 0;
	}

	char **name;
	short *room;

	status = readFile(argv, &name, &room);

	if (status == -1)
	{
		cout << "错误：系统没有足够的内存。" << endl;
		return -1;

	}
	else if (status == -2)
	{
		printUsage(argv[0]);
		cout << "没有找到其中的一个输入文件。" << endl;
		return -2;
	}

	roomEnoughStatus = checkSeatEnough(name, room, NULL, NULL);
	if (roomEnoughStatus != 0)
	{
		cout << "输入的学生数超过了座位数。请检查数据后重试。" << endl;
		return -3;
	}

	ofstream fout;

	fout.open(argv[3], ios::out);
	if (!fout.is_open())
	{
		printUsage(argv[0]);
		cout << "没有找到输出文件。" << endl;
		cleanUp(NULL, 0, room, name);
		return -2;
	}

	srand((unsigned)time(0));

	if (1)
	{
		system("cls");
		cout << "考试座位编排程序" << endl;
		cout << "\t1. 顺次位置排列\n\t2. 随机位置次序排列\n\t0. 退出" << endl << endl;
		cout << "请选择: ";
		cin.get(input, 2);
		cin.clear();
		cin.ignore(FS_MAX_LENGTH, '\n');
		if (!strcmp(input, "0"))
		{
			;
		}
		if (!strcmp(input, "1"))
		{
			arrangeSeat(name, room, true, fout);
		}
		if (!strcmp(input, "2"))
		{
			arrangeSeat(name, room, false, fout);

		}
	}

	cleanUp(NULL, 0, room, name);
	return 0;
}



void printClassroom(const char * const * const name, const short * const room, const int * const roomStu, ostream& out)
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
		out << "|   /    ";
		for (int j = maxLeft - 1; j >= 0; j--)
		{
			out << "|";
			if (((unsigned short)(room[i] >> j) & 0x01) && roomStu[++seatCount] != -1)
			{
				out << setw(8) << name[roomStu[seatCount]];
			}
			else
			{
				out << setw(4) << "/" << setw(4) << "";
			}
		}
		out << "|" << endl;
	}
	out << endl;
	return;
}
int checkSeatEnough(const char * const * const name, const short * const room, int *nN, int *rN)
{
	int nameNum, roomNum;

	for (nameNum = 0; name[nameNum]; nameNum++)
		;
	roomNum = 0;
	for (int i = 0; room[i]; i++)
	{
		for (int j = 0; ((unsigned short)(room[i]) >> j); j++)
			roomNum += (((unsigned short)(room[i]) >> j) & 1);
	}

	if (nN && rN)
	{
		*nN = nameNum;
		*rN = roomNum;
	}

	if (nameNum > roomNum)
	{
		return -3;
	}
	return 0;
}
void arrangeSeat(const char * const * const name, const short * const room, bool order, ostream& out)
{
	int nameNum, roomNum, randomName, randomSeat, roomEnoughStatus;

	roomEnoughStatus = checkSeatEnough(name, room, &nameNum, &roomNum);
	if (roomEnoughStatus != 0)
	{
		return;
	}

	int * const roomStu = new(nothrow) int[roomNum];
	bool * const stuSel = new(nothrow) bool[nameNum];
	if (!roomStu || !stuSel)
	{
		cout << "系统内存不足。" << endl;
		if (roomStu)
			delete[]roomStu;
		if (stuSel)
			delete[]stuSel;

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

	printClassroom(name, room, roomStu, out);

	delete[]roomStu;
	delete[]stuSel;

	cout << "完成。" << endl;
}

void printUsage(const char * const procName)
{
	cout << "用法：" << endl;
	cout << "" << procName << " room.txt student.txt out.txt" << endl;
	return;
}

void cleanUp(ifstream *f, int fileNum, short *room, char **name)
{
	//不clean arrangeSeat的内存
	for (int j = 0; j < fileNum; j++)
	{
		f[j].close();
	}
	if (room)
		delete[] room;
	if (name)
	{
		for (char **p = name; *p; p++)
		{
			delete[](*p);
		}
		delete[] name;
	}

}

void YNtoShort(short *room, char *YN)
{
	short mask = 0x01;
	*room = 0;
	mask <<= strlen(YN);
	for (char *p = YN; *p; p++)
	{
		mask >>= 1;
		if (*p == 'Y')
			*room |= mask;
	}
}

int readFile(const char * const * const argv, char ***name, short **room)
{
	int roomLineNum, nameLineNum;
	char *tempStr;
	char tempArr[17];
	ifstream f[2];

	*room = NULL;
	*name = NULL;

	for (int i = 0; i < 2; i++)
	{
		f[i].open(argv[i + 1], ios::in);
		if (false == f[i].is_open())
		{
			cleanUp(f, 2, *room, *name);
			return -2;
		}
	}

	for (roomLineNum = 0; !f[0].eof(); roomLineNum++)
	{
		bool allZero = 1;
		f[0].get(tempArr, 17);
		f[0].ignore(FS_MAX_LENGTH, '\n');
		for (char *p = tempArr; *p; p++)
		{
			if (*p != 'N')
			{
				allZero = false;
				break;
			}
		}
		if (allZero)
		{
			break;
		}
	}
	for (nameLineNum = 0; !f[1].eof(); nameLineNum++)
	{
		f[1].get(tempArr, 9);
		f[1].ignore(FS_MAX_LENGTH, '\n');
		if (strcmp(tempArr, "NULL") == 0)
		{
			break;
		}
	}

	f[0].clear();
	f[1].clear();
	f[0].seekg(fstream::beg);
	f[1].seekg(fstream::beg);

	*room = new(nothrow) short[roomLineNum + 1];
	*name = new(nothrow) char *[nameLineNum + 1];

	if (!(*room && *name))
	{
		cleanUp(f, 2, *room, *name);
		return -1;
	}

	for (int i = 0; i < roomLineNum; i++)
	{
		f[0].get(tempArr, 17);
		f[0].ignore(FS_MAX_LENGTH, '\n');
		YNtoShort(&room[0][i], tempArr);
	}

	for (int i = 0; i < nameLineNum; i++)
	{
		f[1].get(tempArr, nameLen + 1);
		f[1].ignore(FS_MAX_LENGTH, '\n');
		tempStr = new(nothrow) char[nameLen + 1];
		if (!tempStr)
		{
			cleanUp(f, 2, *room, *name);
			return -1;
		}
		strcpy(tempStr, tempArr);
		(*name)[i] = tempStr;
	}

	(*name)[nameLineNum] = NULL;
	(*room)[roomLineNum] = 0;
	cleanUp(f, 2, NULL, NULL);
	return 0;
}