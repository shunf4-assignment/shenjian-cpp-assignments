/* 1652270 ��˴ �����2�� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <time.h>
using namespace std;

/* �ڴ˴�������Ķ��弰ʵ�� */
class TString {
private:
	char *content;
	int   len;

	/* ������Ҫ��������ĳ�Ա��������Ԫ������ */
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

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */

/* ���� TString ������г�Ա����������ʵ�� */

TString::TString()
{
	//�ڲ�ָ��Ϊ��ָ��
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
		//����ʧ��
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
	//����cstr�е�����
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
		//����ʧ��
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

/* main ����������Ķ� */
int main()
{
	const int MAX_BYTES = 100 * 1024 * 1024;
	TString s1;

	int     total, len, i;
	char    temp[65536];
	long    t_start, t_end;
	char   *crc_str;

	cout << "�ڴ��ۼ��������ܲ��ԣ����ڴ�ľ���������100MB�ֽ�Ϊ�������������������ʼ" << endl;
	_getch();

	crc_str = new char[MAX_BYTES + 65536]; //���루100MB+64KB���ռ�
	if (crc_str == NULL) {
		cout << "�޷�����" << MAX_BYTES + 65536 << "�ֽڵ�У��ռ䣬������ֹ��������ٴ�����" << endl;
		goto END;
	}
	*crc_str = 0; //��Ϊ�մ�

	t_start = GetTickCount(); //ȡ��ǰϵͳʱ�䣬��λ����
	srand((unsigned int)time(0));
	total = 0;
	while (1) {
		len = 32768 + rand() % 32768;

		cout << "s1���г��ȣ�" << s1.length() / (1024.0 * 1024) << " MB�ֽڣ��������� " << len << " �ֽ�" << endl;
		for (i = 0; i<len; i++)
			temp[i] = ' ' + rand() % 95;	//����������ַ����
		temp[len] = 0;
		total += len;
		s1 += temp;
		strcat(crc_str, temp);
		if (s1.length() == 0 || s1.length() > MAX_BYTES)	//��100MB���ڴ�ľ������
			break;

		/* ���������²�Ҫ����ʲô������ */
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
	t_end = GetTickCount();   //ȡ��ǰϵͳʱ��

	cout << "time=" << (t_end - t_start) / 1000.0 << endl;
	if (s1.length() == 0)
		cout << "�ڴ���䵽�� " << total / (1024.0 * 1024) << " MB�ֽں��ڴ�ľ�" << endl;
	else
		cout << "�ڴ���䵽����100MB�����Խ���" << endl;

	if (s1 != crc_str)
		cout << "s1�ۼ���֤������������ʵ�ֲ���" << endl;
	else
		cout << "    ���β��Ժ�ʱ " << (t_end - t_start) / 1000.0 << "��" << endl;

	delete crc_str;

	cout << endl;

END:
	cout << "���������������۲챾�����ʱ���ڴ�ռ�����" << endl << endl;
	system("pause");

	return 0;
}
