#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

struct KFC
{
	char no;
	char* name;
	float price;
};

struct SPECIAL
{
	char* comb;
	char* name;
	float price;
};

struct MENU
{
	short *kfc;
	int len;
};

struct CHARCHAIN
{
	char c;
	CHARCHAIN *next;
};

struct INPUTFIELD
{
	COORD pos;
	CHARCHAIN *head;
	int currPos;
	int chainLen;
};

void setcolor(const HANDLE hout, const int bg_color, const int fg_color);
void gotoxy(const HANDLE hout, const short X, const short Y);
void getxy(const HANDLE hout, short &x, short &y);

void printKFC(const KFC * const l);
int printSPECIAL(const SPECIAL * const s, const KFC * const l);
const KFC * searchChar(const KFC * const l, char c);
int printMenuStr(char *menustr, const KFC * const l);
MENU strToMenu(const char * const str, const KFC * const l);
void printMenu(const MENU m, const KFC * const l);
float menuPrice(const MENU m, const KFC * const l, const SPECIAL * const s, short specialY, HANDLE hout);
MENU strToMenu(const char * const str, const KFC * const l)
;

void freeCharChain(CHARCHAIN *head)
{
	CHARCHAIN *p = head, *q = p;
	for (; p; p = q)
	{
		q = p->next;
		delete p;
	}
}



int insertCharChain(CHARCHAIN *&head, int no, char c)
{
	CHARCHAIN *p = head, *q, *n;
	if (!p)
		return -2;
	n = new(nothrow) CHARCHAIN;
	if (!n)
		return -1;
	n->c = c;

	if (!n)
		return -1;
	if (no == 0)
	{
		n->next = head;
		head = n;
		return 0;
	}
	for (int i = 0; i < no - 1; i++)
	{
		p = p->next;
	}
	q = p->next;
	
	n->next = q;
	p->next = n;
	return 0;
}

int pushCharChain(CHARCHAIN *&head, char c)
{
	CHARCHAIN *p = head;
	int count = 0;
	if (!p)
		return -2;
	for (; p; p = p->next)
		count++;
	insertCharChain(head, count - 1, c);
	return 0;
}

int dropCharChain(CHARCHAIN *&head, int no, char c)
{
	CHARCHAIN *p = head, *q;
	if (!p)
		return -2;
	if (no == 0)
	{
		q = head;
		head = head->next;
		delete q;
		return 0;
	}
	for (int i = 0; i < no - 1; i++)
	{
		p = p->next;
	}
	q = p->next;
	p->next = q->next;
	delete q;
	
	return 0;
}

char * charChainToStr(CHARCHAIN *head)
{
	CHARCHAIN *p = head;
	int count = 0;
	char *str;
	for (; p; p = p->next)
	{
		count++;
	}
	
	str = new(nothrow) char[count];
	if (!str)
	{
		return NULL;
	}
	count = 0;
	p = head;
	for (; p; p = p->next)
	{
		str[count] = p->c;
		count++;
	}
	//str[count] = '\0';

	return str;
}

void getconsoleborder(const HANDLE hout, int &cols, int &lines, int &buffer_cols, int &buffer_lines)
{
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(hout, &binfo);

	cols = binfo.dwMaximumWindowSize.X;	//�ɼ����ڵ�����
	lines = binfo.dwMaximumWindowSize.Y;   //�ɼ����ڵ�����
	buffer_cols = binfo.dwSize.X;         //������������
	buffer_lines = binfo.dwSize.Y;			//������������
}

void clearLines(HANDLE hout, int line)
{
	int cols, lines, buffer_coles, buffer_lines;
	short x, y;
	getconsoleborder(hout, cols, lines, buffer_coles, buffer_lines);
	getxy(hout, x, y);
	cout << setw(cols - x) << "";
	line--;
	for (int i = 0; i < line; i++)
	{
		cout << setw(cols) << "";
	}
	gotoxy(hout, x, y);
}

/* ģ������ */
const struct KFC list[] = {
	{ 'A', "�������ȱ�",         17.0 },
	{ 'B', "���༦�ȱ�",         17.0 },
	{ 'C', "�°¶��������ȱ�",   17.0 },
	{ 'D', "ţ�͹��������ȱ�",   18.0 },
	{ 'E', "�ٽ��ϴ����",     11.0 },
	{ 'F', "�ϱ��������",       15.0 },
	{ 'G', "˱ָԭζ��(һ��)",   10.5 },
	{ 'H', "˱ָԭζ��(����)",   20.0 },
	{ 'I', "�°¶�������",       10.5 },
	{ 'J', "�������׻�",         10.5 },
	{ 'K', "��������",           9.5 },
	{ 'L', "�ƽ𼦿�(���)",     9.0 },
	{ 'M', "����ɫ��",           12.0 },
	{ 'N', "����(С)",           8.5 },
	{ 'O', "����(��)",           10.0 },
	{ 'P', "����(��)",           12.0 },
	{ 'Q', "ܽ��������",         7.5 },
	{ 'R', "��������",           7.0 },
	{ 'S', "����������",         6.0 },
	{ 'T', "�������װ�",         7.0 },
	{ 'U', "��Ƥ��Ͳ",           7.5 },
	{ 'V', "���¿���(С)",       6.5 },
	{ 'W', "���¿���(��)",       8.0 },
	{ 'X', "���¿���(��)",       9.5 },
	{ 'Y', "�����֭����",       10.5 },
	{ 'Z', "����������",         9.5 },
	{ '\0', NULL,                0 }
};

const struct SPECIAL special[] = {
	{ "ANV", "�����������������",    20 },
	{ "GGGGGJJJSTWWW", "��ֵȫ��Ͱ",  82 },
	{ "ZZ", "��������2�����",        14.5 },
	{ "UUU","��Ƥ��Ͳ��2��1",         15 },
	{ NULL, NULL, 0 }
};



int main()
{
	short specialX, specialY, orderX, orderY, inputX, inputY;
	int status;
	bool quit = 0;
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
	
	system("mode con cols=110 lines=30");

	cout << "���ϵ»��˵���" << endl;
	printKFC(list);
	cout << endl;
	cout << "���Ż���Ϣ��" << endl;
	getxy(hout, specialX, specialY);
	printSPECIAL(special, list);
	cout << endl;
	cout << endl << "����ǰ�㵥���������·�������ĸ���س�ȷ�ϣ���0�˳�"<< endl;

	getxy(hout, orderX, orderY);
	cout << endl << endl << endl << endl;
	getxy(hout, inputX, inputY);

	while (!quit)
	{
		CHARCHAIN *inChar = new(nothrow) CHARCHAIN;
		if (!inChar)
		{
			cout << "�ڴ治�㡣" << endl;
			return -1;
		}
		inChar->c = '\0';
		inChar->next = NULL;
		INPUTFIELD input;
		char * tmpStr;
		bool menuChanged;
		float price;


		input.pos.X = inputX;
		input.pos.Y = inputY;
		input.head = inChar;
		input.currPos = 0;
		input.chainLen = 0;

		while (true)
		{
			INPUT_RECORD r;
			DWORD res;
			WORD key;
			const KFC * k;

			menuChanged = false;

			//����
			do
			{
				ReadConsoleInput(hin, &r, 1, &res);

			} while (!(r.EventType == KEY_EVENT && r.Event.KeyEvent.bKeyDown));

			key = r.Event.KeyEvent.wVirtualKeyCode;

			//�Ѳ�
			k = searchChar(list, (char)key);
			if (k)
			{
				//�в�
				//������ĸ
				status = insertCharChain(input.head, input.currPos, (char)key);
				if (status < 0)
				{
					freeCharChain(input.head);
					cout << "�ڴ治�㣡" << endl;
					return -1;
				}
				input.currPos++;
				input.chainLen++;
				menuChanged = true;
			}
			else
			{
				if (key == VK_BACK && input.currPos > 0)
				{
					//������ĸ
					dropCharChain(input.head, --input.currPos, (char)key);
					input.chainLen--;
					menuChanged = true;
				}
				if (key == VK_LEFT)
				{
					--input.currPos;
					if (input.currPos < 0)
					{
						input.currPos = 0;
					}
				}
				if (key == VK_RIGHT)
				{
					++input.currPos;
					if (input.currPos > input.chainLen)
					{
						input.currPos = input.chainLen;
					}
				}
				if (key == VK_RETURN)
				{
					break;
				}
				if (key == '0')
				{
					quit = 1;
					break;
				}
			}
			if (menuChanged)
			{
				//��ӡ��������ĸ
				gotoxy(hout, input.pos.X, input.pos.Y);
				clearLines(hout, 3);
				tmpStr = charChainToStr(input.head);
				if (tmpStr == NULL)
				{
					freeCharChain(input.head);
					cout << "�ڴ治�㣡" << endl;
					return -1;
				}
				cout << tmpStr;

				//��ӡ�˵�
				gotoxy(hout, orderX, orderY);
				clearLines(hout, 3);

				MENU thisMENU;
				thisMENU = strToMenu(tmpStr, list);
				if (thisMENU.len < 0)
				{
					freeCharChain(input.head);
					cout << "�ڴ治�㣡" << endl;
					return -1;
				}

				printMenu(thisMENU, list);
				
				//����Ǯ��
				price = menuPrice(thisMENU, list, special, specialY, hout);
				if (price < 0)
				{
					//�������ڴ����
					freeCharChain(input.head);
					cout << "�ڴ治�㣡" << endl;
					return -1;
				}

				//��ӡǮ��
				gotoxy(hout, orderX + 110 - 16, orderY - 1);
				cout << "�ܼۣ�" << setw(8) << setprecision(8) << price << "  " << endl;
				delete[] thisMENU.kfc;

				delete[]tmpStr;
			}
			gotoxy(hout, input.pos.X + input.currPos % 110, input.pos.Y + input.currPos / 110);
		}
		freeCharChain(input.head);
		gotoxy(hout, input.pos.X, input.pos.Y);
		clearLines(hout, 3);
		gotoxy(hout, orderX, orderY);
		clearLines(hout, 3);
		gotoxy(hout, input.pos.X, input.pos.Y);

	}

	cout << endl;
	return 0;
}

void setcolor(const HANDLE hout, const int bg_color, const int fg_color)
{
	SetConsoleTextAttribute(hout, bg_color * 16 + fg_color);
}

void gotoxy(const HANDLE hout, const short X, const short Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}

void getxy(const HANDLE hout, short &x, short &y)
{
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(hout, &binfo);

	x = binfo.dwCursorPosition.X;
	y = binfo.dwCursorPosition.Y;

	return;
}

void printKFC(const KFC * const l)
{
	const KFC * p = l;
	
	for (; p->no; p++)
	{
		cout << setw(3) << p->no << setw(2) << setw(20) << p->name << setw(2) << "" << setw(6) << p->price;
		if ((p - l) % 3 == 0 || (p - l) % 3 == 1)
		{
			cout << setw(4) << "��" << "  ";
		}
		else
		{
			cout << endl;
		}
	}
	if ((p - l) % 3 != 0)
	{
		cout << endl;
	}
}

const KFC * searchChar(const KFC * const l, char c)
{
	const KFC * p = l;
	for (; p->no && p->no != c; p++)
		;
	if (p->no)
		return p;
	else
		return NULL;
}

int KFClen(const KFC * const l)
{
	const KFC * p = l;

	for (; p->no; p++)
		;

	return p - l;
}

int menuSubstract(const MENU &orderMenu, const MENU &specMenu)
{
	bool substractable = true;
	int substractNum = 0;
	while (substractable)
	{
		substractable = true;
		for (int i = 0; i < orderMenu.len; i++)
		{
			if (orderMenu.kfc[i] < specMenu.kfc[i])
			{
				substractable = false;
			}
		}
		if (substractable)
		{
			for (int i = 0; i < orderMenu.len; i++)
			{
				orderMenu.kfc[i] -= specMenu.kfc[i];
			}
			substractNum++;
		}
	}
	return substractNum;
}

float menuPrice(const MENU m, const KFC * const l, const SPECIAL * const s, short specialY, HANDLE hout)
{
	const SPECIAL * p = s;
	const KFC * q = l;
	MENU currMenu;
	int status, thisSubstract;
	float price = 0;
	for (; p->comb; p++)
	{
		currMenu = strToMenu(p->comb, l);
		thisSubstract = menuSubstract(m, currMenu);
		price += thisSubstract * p->price;
		delete[] currMenu.kfc;

		if (specialY >= 0)
		{
			gotoxy(hout, 0, specialY + p - s);
			clearLines(hout, 1);
			if (thisSubstract > 0)
			{
				setcolor(hout, 0, 0xa);
			}
			cout << p->name << " = ";
			status = printMenuStr(p->comb, l);
			if (status < 0)
			{
				return (float)status;
			}
			cout << " = " << p->price;
			if (thisSubstract > 0)
			{
				cout << " * " << thisSubstract;
				setcolor(hout, 0, 0x7);
			}
		}
	}
	for (; q->no; q++)
	{
		price += q->price * m.kfc[q - l];
	}
	return price;
}

MENU strToMenu(const char * const str, const KFC * const l)
{
	int len = KFClen(l);
	short *kfc = new(nothrow) short[len];
	MENU result;
	result.len = -1;

	if (!kfc)
	{
		return result;
	}
	
	result.kfc = kfc;
	result.len = len;

	for (short *p = kfc; p - kfc < len; p++)
	{
		*p = 0;
	}
	for (const char *p = str; *p; p++)
	{
		const KFC * currItem = searchChar(l, *p);
		if (currItem)
		{
			result.kfc[currItem - l]++;
		}
		else
		{
			result.len = -2;
			delete[] kfc;
			return result;
		}
	}
	return result;
}

void printMenu(const MENU m, const KFC * const l)
{
	bool first = true;
	for (int i = 0; i < m.len; i++)
	{
		if (m.kfc[i] >= 1) {
			if (!first)
			{
				cout << "+";
			}
			else
			{
				first = false;
			}
			if (m.kfc[i] == 1)
			{
				cout << l[i].name;
			}
			else if (m.kfc[i] > 1)
			{
				cout << l[i].name << "*" << m.kfc[i];
			}
		}
	}
}

int printMenuStr(char *menustr, const KFC * const l)
{
	MENU thisSpecial;
	thisSpecial = strToMenu(menustr, l);
	if (thisSpecial.len < 0)
		return (thisSpecial.len);
	
	printMenu(thisSpecial, l);
	delete[] thisSpecial.kfc;
	return 0;
}

int printSPECIAL(const SPECIAL * const s, const KFC * const l)
{
	const SPECIAL * p = s;
	int status;
	for (; p->comb; p++)
	{
		cout << p->name << " = ";
		status = printMenuStr(p->comb, l);
		if (status < 0)
		{
			return status;
		}
		cout << " = " << p->price;
		cout << endl;
	}
	return 0;
}