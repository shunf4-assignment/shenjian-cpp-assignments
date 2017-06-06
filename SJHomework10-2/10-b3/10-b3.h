/* 1652270 ��˴ �����2�� */
#include <iostream>
using namespace std;

/* ��ȫTString��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
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

	friend bool operator> (const TString& str1, const TString &str2);
	friend bool operator>= (const TString& str1, const TString &str2);
	friend bool operator< (const TString& str1, const TString &str2);
	friend bool operator<= (const TString& str1, const TString &str2);
	friend bool operator== (const TString& str1, const TString &str2);
	friend bool operator!= (const TString& str1, const TString &str2);

	char& operator[] (int index);

	int length()
	{
		return len;
	}

	friend unsigned int TStringLen(const TString& str);
};

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */
