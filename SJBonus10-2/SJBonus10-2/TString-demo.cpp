/* 1652270 冯舜 计算机2班 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

/* 在此处给出你的定义及实现 */
class TString {
private:
	char *content;
	int   len;

	/* 根据需要定义所需的成员函数、友元函数等 */
public:
	TString();
	TString(const char *cstr, int len_);
	TString(int len_);
	TString(const char *cstr);
	TString(const TString &str);
	~TString();

	TString& operator=(const TString &str);
	TString& operator=(const char *cstr);

	friend istream& operator >> (istream& in, TString &str);
	friend ostream& operator << (ostream& out, TString &str);

	friend TString operator+ (const TString& str1, const TString &str2);
	friend bool operator== (const TString& str1, const TString &str2);
	friend bool operator!= (const TString& str1, const TString &str2);

	TString& operator+=(const TString &str)
	{
		return (*this = *this + str);
	}

	int length()
	{
		return len;
	}
};

/* 如果有其它全局函数需要声明，写于此处 */

/* 如果有需要的宏定义、只读全局变量等，写于此处 */

/* 给出 TString 类的所有成员函数的体外实现 */

TString::TString()
{
	//内部指针为空指针
	content = nullptr;
	len = 0;
}

TString::TString(const char *cstr)
{
	this->TString::TString(cstr, -1);
}

TString::TString(int len_)
{
	len = len_;
	content = new(nothrow) char[len_ + 1];
	if (nullptr == content)
	{
		//申请失败
		len = 0;
		return;
	}
	content[len_] = '\0';
}

TString::TString(const char *cstr, int len_)
{
	if (nullptr == cstr)
	{
		len = 0;
		content = nullptr;
		return;
	}
	//复制cstr中的内容
	if (-1 == len_)
	{
		int cstrlen = strlen(cstr);
		len = cstrlen;
	}
	else
	{
		len = len_;
	}
	content = new(nothrow) char[len + 1];
	if (nullptr == content)
	{
		//申请失败
		len = 0;
		return;
	}

	memcpy_s(content, sizeof(char) * (len + 1), cstr, sizeof(char) * (len + 1));
}

TString::TString(const TString &str)
{
	this->TString::TString(str.content, str.len);
}

TString::~TString()
{
	if (content != nullptr)
		delete content;
}

TString& TString::operator=(const TString &str)
{
	if (nullptr == str.content)
	{
		this->~TString();
		len = 0;
		content = nullptr;
		return *this;
	}
	if (str.len <= this->len)
	{
		len = str.len;
		memcpy_s(content, sizeof(char) * (len + 1), str.content, sizeof(char) *(len + 1));
	}
	else
	{
		this->~TString();
		this->TString::TString(str);
	}
	return *this;
}

TString& TString::operator=(const char *cstr)
{
	if (nullptr == cstr)
	{
		this->~TString();
		len = 0;
		content = nullptr;
		return *this;
	}
	int cstrlen;
	if ((cstrlen = strlen(cstr)) <= len)
	{
		len = cstrlen;
		memcpy_s(content, sizeof(char) * (len + 1), cstr, sizeof(char) * (len + 1));
	}
	else
	{
		this->~TString();
		this->TString::TString(cstr);
	}
	return *this;
}

TString operator+ (const TString& str1, const TString &str2)
{
	auto result = TString(str1.len + str2.len);
	if (str1.content != nullptr)
		memcpy_s(result.content, result.len + 1, str1.content, sizeof(char) * (str1.len + 1));
	if (str2.content != nullptr)
		memcpy_s(result.content + str1.len, result.len - str1.len + 1, str2.content, sizeof(char) * (str2.len + 1));
	return result;
}


bool operator==(const TString & str1, const TString & str2)
{
	char *pstr1, *pstr2;
	pstr1 = str1.content;
	pstr2 = str2.content;
	if (nullptr == pstr1)
		pstr1 = "";
	if (nullptr == pstr2)
		pstr2 = "";
	int result = strcmp(pstr1, pstr2);
	return (result == 0);
	//return (strcmp(str1.content, str2.content) == 0);
}

bool operator!=(const TString & str1, const TString & str2)
{
	char *pstr1, *pstr2;
	pstr1 = str1.content;
	pstr2 = str2.content;
	if (nullptr == pstr1)
		pstr1 = "";
	if (nullptr == pstr2)
		pstr2 = "";
	int result = strcmp(pstr1, pstr2);
	return (result != 0);
}

/* main 函数不允许改动 */
int main()
{
	const int MAX_BYTES = 100 * 1024 * 1024;
	TString s1;

	int     total, len, i;
	char    temp[65536];
	long    t_start, t_end;
	char   *crc_str;

	cout << "内存累加申请性能测试，以内存耗尽或申请满100MB字节为结束条件，按任意键开始" << endl;
	_getch();

	crc_str = new char[MAX_BYTES + 65536]; //申请（100MB+64KB）空间
	if (crc_str == NULL) {
		cout << "无法申请" << MAX_BYTES + 65536 << "字节的校验空间，程序终止，请检查后再次运行" << endl;
		goto END;
	}
	*crc_str = 0; //置为空串

	t_start = GetTickCount(); //取当前系统时间，单位毫秒
	srand((unsigned int)time(0));
	total = 0;
	while (1) {
		len = 32768 + rand() % 32768;

		cout << "s1已有长度：" << s1.length() / (1024.0 * 1024) << " MB字节，本次增加 " << len << " 字节" << endl;
		for (i = 0; i<len; i++)
			temp[i] = ' ' + rand() % 95;	//数组用随机字符填充
		temp[len] = 0;
		total += len;
		s1 += temp;
		strcat(crc_str, temp);
		if (s1.length() == 0 || s1.length() > MAX_BYTES)	//满100MB或内存耗尽则结束
			break;

		/* 下面做的事不要问问什么，任性 */
		if (1) {
			char d1[64], d2[16];
			int  d1_len, d2_len;
			d1_len = 16 + rand() % 16;
			d2_len = 8 + rand() % 8;
			for (i = 0; i < d1_len; i++)
				d1[i] = ' ' + rand() % 95;
			d1[d1_len] = 0;
			for (i = 0; i < d2_len; i++)
				d2[i] = ' ' + rand() % 95;
			d2[d2_len] = 0;
			strcat(d1, d2);
		}
	}
	t_end = GetTickCount();   //取当前系统时间

	cout << "time=" << (t_end - t_start) / 1000.0 << endl;
	if (s1.length() == 0)
		cout << "内存分配到达 " << total / (1024.0 * 1024) << " MB字节后，内存耗尽" << endl;
	else
		cout << "内存分配到达满100MB，测试结束" << endl;

	if (s1 != crc_str)
		cout << "s1累加验证出错，请检查程序的实现部分" << endl;
	else
		cout << "    本次测试耗时 " << (t_end - t_start) / 1000.0 << "秒" << endl;

	delete crc_str;

	cout << endl;

END:
	cout << "请打开任务管理器，观察本程序此时的内存占用情况" << endl << endl;
	system("pause");

	return 0;
}
