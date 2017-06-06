/* 1652270 冯舜 计算机2班 */
#include <iostream>
using namespace std;

/* 补全TString类的定义，所有成员函数均体外实现，不要在此处体内实现 */
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

/* 如果有其它全局函数需要声明，写于此处 */

/* 如果有需要的宏定义、只读全局变量等，写于此处 */
