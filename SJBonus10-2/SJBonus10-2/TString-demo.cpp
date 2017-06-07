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

public:
	TString();
	~TString();
	friend bool operator!=(const TString & str1, const char * str2);
	template<int s>
	void operator+=(const char (&cstr)[s])
	{
		len += s;
	}

	int length()
	{
		return len;
	}
};

TString::TString()
{
	content = "";
	len = 0;
}

TString::~TString()
{
	;
}

bool operator!=(const TString & str1, const char * str2)
{
	const char *pstr1, *pstr2;
	pstr1 = str1.content;
	pstr2 = str2;
	if (nullptr == pstr1)
		pstr1 = "";
	if (nullptr == pstr2)
		pstr2 = "";
	int result = strcmp(pstr1, pstr2);
	return (result != 0);
}

void strcat_(char *str1, const char *str2)
{
	*str1 = '\0';
}

#define strcat strcat_

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
