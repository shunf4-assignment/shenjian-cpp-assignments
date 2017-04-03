/* 1652270 �����2�� ��˴ */
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
	{"����ǳ�",	 0, 0,0,0}, 
	{ "����ֵ", 2, 0,10000,16 },
	{ "����ֵ", 2, 0,10000,18 },
	{ "����", 2, 0,8192,20 },
	{ "����", 2, 0,1024,22 },
	{ "��Ǯ����", 1, 0,100000000,24 },
	{ "����ֵ", 1, 0,1000000,28 },
	{ "����ֵ", 1, 0,1000000,32 },
	{ "�ƶ��ٶ�", 3, 0,100,44 },
	{ "�����ٶ�", 3, 0,100,45 },
	{ "������Χ", 3, 0,100,47 },
	{ "������", 2, 0,2000,48 },
	{ "������", 2, 0,2000,50 },
	{ "���ݶ�", 3, 0,100,52 },
	{ "����", 3, 0,100,53 },
	{ "����", 3, 0,100,54 },
	{ "�ȼ�", 3, 0,100,55 },
	{ "ħ��ֵ", 2, 0,10000,56 },
	{ "ʹ��ħ��ʱÿ�����ĵ�ħ��ֵ", 3, 0,100,58 },
	{ "ħ���˺���", 3, 0,100,59 },
	{ "������", 3, 0,100,60 },
	{ "ħ��������", 3, 0,100,61 },
	{ "������", 3, 0,100,62 },
	{ "����", 3, 0,100,63 },
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
		cout << "�� game.dat ʧ�ܣ�";
		return 1;
	}
	while (true)
	{
		system("cls");
		cout << "��Ϸ�浵�޸���" << endl;
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
		cout << "��ѡ�� [ " << keyLower << " - " << char(keyUpper - 1) << " ], 0 �˳�: ";
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
	cout << "��Ҫ�޸ģ�" << d->desc;
	if (d->type == 1)
	{
		int origin;
		int now;
		cout << "�����Ǹ� 4 �ֽ���������ʼλ���� ";
		//cout << "0x" << setiosflags(ios::uppercase) << hex;
		cout << d->startPoint << "�������޸ķ�ΧΪ (" << dec << d->lowerLimit << " - " << d->upperLimit << ")��" << endl << endl;
		cout << "ԭ���ݣ�";
		f.seekg(d->startPoint, ios::beg);
		//cout << endl << "Tellp: " << f.tellp() << endl;
		f.read((char *)&origin, sizeof(int));
		cout << origin;
		//cout << endl << "Tellp: " << f.tellp() << endl;
		cout << endl;
		inputThing(&now, "��������޸�Ϊ��", "����Ƿ���", "���볬�ޡ�", d->lowerLimit, d->upperLimit);
		f.seekp(d->startPoint, ios::beg);
		f.write((char *)&now, sizeof(int));
	}
	else if (d->type == 2)
	{
		short origin;
		short now;
		cout << "�����Ǹ� 2 �ֽڶ���������ʼλ���� ";
		//cout << "0x" << setiosflags(ios::uppercase) << hex;
		cout << d->startPoint << "�������޸ķ�ΧΪ (" << dec << d->lowerLimit << " - " << d->upperLimit << ")��" << endl << endl;
		cout << "ԭ���ݣ�";
		f.seekg(d->startPoint, ios::beg);
		
		f.read((char *)&origin, sizeof(origin));
		cout << origin;
		cout << endl;
		inputThing(&now, "��������޸�Ϊ��", "����Ƿ���", "���볬�ޡ�", (short)d->lowerLimit, (short)d->upperLimit);
		f.seekp(d->startPoint, ios::beg);
		f.write((char *)&now, sizeof(now));
	}
	else if (d->type == 3)
	{
		char origin;
		int now;
		char now_;
		cout << "�����Ǹ� 1 �ֽ���������ʼλ���� ";
		//cout << "0x" << setiosflags(ios::uppercase) << hex;
		cout << d->startPoint << "�������޸ķ�ΧΪ (" << dec << d->lowerLimit << " - " << d->upperLimit << ")��" << endl << endl;
		cout << "ԭ���ݣ�";
		f.seekg(d->startPoint, ios::beg);
		
		f.read((char *)&origin, sizeof(origin));
		
		cout << (unsigned)origin;
		cout << endl;
		inputThing(&now, "��������޸�Ϊ��", "����Ƿ���", "���볬�ޡ�", d->lowerLimit, d->upperLimit);
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
			cout << "�ƻ��ӣ���ô�� " << len + 1 << " �ֽڵĿռ䶼���벻������" << endl;
			return;
		}
		p[len] = 0;

		i = new(nothrow) char[len + 1];
		if (!i)
		{
			cout << "�ƻ��ӣ���ô�� " << len + 1 << " �ֽڵĿռ䶼���벻������" << endl;
			delete[] p;
			return;
		}
		i[len] = 0;

		cout << "�����Ǹ�����Ϊ " << len << " ���ַ�������ʼλ���� ";
		//cout << "0x" << setiosflags(ios::uppercase) << hex;
		cout << d->startPoint << "��" << endl << endl;
		cout << "ԭ���ݣ�";
		f.seekg(d->startPoint, ios::beg);
		
		f.read(p, len * sizeof(char));
		cout << p;
		cout << endl;
		cout << "�����������Ϊ������ " << len << " �ַ���";
		cin.getline(i, (len + 1) * sizeof(char));
		f.seekp(d->startPoint, ios::beg);
		f.write(i, (len + 1) * sizeof(char));

		delete[] p;
		delete[] i;
		
	}
	//f.flush();
	cout << "�ɹ���";
	system("pause");
}

