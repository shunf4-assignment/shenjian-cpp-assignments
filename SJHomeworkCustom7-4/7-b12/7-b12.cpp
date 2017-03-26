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

	cols = binfo.dwMaximumWindowSize.X;	//可见窗口的列数
	lines = binfo.dwMaximumWindowSize.Y;   //可见窗口的行数
	buffer_cols = binfo.dwSize.X;         //缓冲区的列数
	buffer_lines = binfo.dwSize.Y;			//缓冲区的行数
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

/* 模拟数据 */
const struct KFC list[] = {
	{ 'A', "香辣鸡腿堡",         17.0 },
	{ 'B', "劲脆鸡腿堡",         17.0 },
	{ 'C', "新奥尔良烤鸡腿堡",   17.0 },
	{ 'D', "牛油果香辣鸡腿堡",   18.0 },
	{ 'E', "藤椒肯大大鸡排",     11.0 },
	{ 'F', "老北京鸡肉卷",       15.0 },
	{ 'G', "吮指原味鸡(一块)",   10.5 },
	{ 'H', "吮指原味鸡(二块)",   20.0 },
	{ 'I', "新奥尔良烤翅",       10.5 },
	{ 'J', "劲爆鸡米花",         10.5 },
	{ 'K', "香辣鸡翅",           9.5 },
	{ 'L', "黄金鸡块(五块)",     9.0 },
	{ 'M', "鲜蔬色拉",           12.0 },
	{ 'N', "薯条(小)",           8.5 },
	{ 'O', "薯条(中)",           10.0 },
	{ 'P', "薯条(大)",           12.0 },
	{ 'Q', "芙蓉蔬荟汤",         7.5 },
	{ 'R', "骨肉相连",           7.0 },
	{ 'S', "醇香土豆泥",         6.0 },
	{ 'T', "香甜粟米棒",         7.0 },
	{ 'U', "脆皮甜筒",           7.5 },
	{ 'V', "百事可乐(小)",       6.5 },
	{ 'W', "百事可乐(中)",       8.0 },
	{ 'X', "百事可乐(大)",       9.5 },
	{ 'Y', "九珍果汁饮料",       10.5 },
	{ 'Z', "纯纯玉米饮",         9.5 },
	{ '\0', NULL,                0 }
};

const struct SPECIAL special[] = {
	{ "ANV", "香辣汉堡工作日午餐",    20 },
	{ "GGGGGJJJSTWWW", "超值全家桶",  82 },
	{ "ZZ", "玉米饮第2件半价",        14.5 },
	{ "UUU","脆皮甜筒买2送1",         15 },
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

	cout << "【肯德基菜单】" << endl;
	printKFC(list);
	cout << endl;
	cout << "【优惠信息】" << endl;
	getxy(hout, specialX, specialY);
	printSPECIAL(special, list);
	cout << endl;
	cout << endl << "【当前点单】：请在下方输入字母，回车确认，按0退出"<< endl;

	getxy(hout, orderX, orderY);
	cout << endl << endl << endl << endl;
	getxy(hout, inputX, inputY);

	while (!quit)
	{
		CHARCHAIN *inChar = new(nothrow) CHARCHAIN;
		if (!inChar)
		{
			cout << "内存不足。" << endl;
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

			//读键
			do
			{
				ReadConsoleInput(hin, &r, 1, &res);

			} while (!(r.EventType == KEY_EVENT && r.Event.KeyEvent.bKeyDown));

			key = r.Event.KeyEvent.wVirtualKeyCode;

			//搜菜
			k = searchChar(list, (char)key);
			if (k)
			{
				//有菜
				//插入字母
				status = insertCharChain(input.head, input.currPos, (char)key);
				if (status < 0)
				{
					freeCharChain(input.head);
					cout << "内存不足！" << endl;
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
					//消除字母
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
				//打印插入后的字母
				gotoxy(hout, input.pos.X, input.pos.Y);
				clearLines(hout, 3);
				tmpStr = charChainToStr(input.head);
				if (tmpStr == NULL)
				{
					freeCharChain(input.head);
					cout << "内存不足！" << endl;
					return -1;
				}
				cout << tmpStr;

				//打印菜单
				gotoxy(hout, orderX, orderY);
				clearLines(hout, 3);

				MENU thisMENU;
				thisMENU = strToMenu(tmpStr, list);
				if (thisMENU.len < 0)
				{
					freeCharChain(input.head);
					cout << "内存不足！" << endl;
					return -1;
				}

				printMenu(thisMENU, list);
				
				//计算钱数
				price = menuPrice(thisMENU, list, special, specialY, hout);
				if (price < 0)
				{
					//出现无内存错误
					freeCharChain(input.head);
					cout << "内存不足！" << endl;
					return -1;
				}

				//打印钱数
				gotoxy(hout, orderX + 110 - 16, orderY - 1);
				cout << "总价￥" << setw(8) << setprecision(8) << price << "  " << endl;
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
			cout << setw(4) << "｜" << "  ";
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