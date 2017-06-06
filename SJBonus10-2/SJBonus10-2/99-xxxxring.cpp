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

/* 如果有需要的其它全局函数的实现，可以写于此处 */
istream& operator >> (istream& in, TString &str)
{
	str.TString::~TString();
	str.TString::TString();
	const int bufsize = 8;
	char buffer[bufsize + 1];
	int nowlen = 0;
	char(*&pstr) = str.content;
	char *tmppstr;
	bool end = false;
	int getCh;

	pstr = new(nothrow) char[1];
	if (nullptr == pstr)
	{
		return in;
	}

	pstr[0] = 0;

	while (true)
	{
		getCh = in.get();
		if (getCh == -1)
		{
			//EOF
			end = true;
			break;
		}
		if (getCh == ' ' || getCh == '\t' || getCh == '\n' || getCh == '\r')
		{
			continue;
		}
		else
		{
			in.putback(getCh);
			break;
		}
	}

	while (end == false)
	{
		char *p;
		for (p = buffer; p - buffer < bufsize + 1; p++)
		{

			getCh = in.get();
			if (getCh == -1)
			{
				//EOF
				end = true;
				break;
			}
			if (getCh == ' ' || getCh == '\t' || getCh == '\n' || getCh == '\r')
			{
				in.putback(getCh);
				end = true;
				break;
			}
			*p = getCh;
		}
		tmppstr = new(nothrow) char[(nowlen += (p - buffer)) + 1];
		if (nullptr == tmppstr)
		{
			delete[] pstr;
			return in;
		}
		memcpy_s(tmppstr, sizeof(char) * (nowlen + 1), pstr, sizeof(char) * (nowlen - (p - buffer) + 1));
		memcpy_s(tmppstr + nowlen - (p - buffer), sizeof(char) * ((p - buffer) + 1), buffer, sizeof(char) * (p - buffer));
		tmppstr[nowlen] = 0;
		delete[]pstr;
		pstr = tmppstr;
	}

	str.len = nowlen;
	str.content = pstr;
	//delete[] pstr;
	return in;
}

ostream& operator << (ostream& out, TString &str)
{
	if (str.content != nullptr)
		out << str.content;
	return out;
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

bool operator>(const TString & str1, const TString & str2)
{
	char *pstr1, *pstr2;
	pstr1 = str1.content;
	pstr2 = str2.content;
	if (nullptr == pstr1)
		pstr1 = "";
	if (nullptr == pstr2)
		pstr2 = "";
	int result = strcmp(pstr1, pstr2);
	return (result > 0);
}

bool operator>=(const TString & str1, const TString & str2)
{
	char *pstr1, *pstr2;
	pstr1 = str1.content;
	pstr2 = str2.content;
	if (nullptr == pstr1)
		pstr1 = "";
	if (nullptr == pstr2)
		pstr2 = "";
	int result = strcmp(pstr1, pstr2);
	return (result >= 0);
}

bool operator<(const TString & str1, const TString & str2)
{
	return !(str1 >= str2);
}

bool operator<=(const TString & str1, const TString & str2)
{
	return !(str1 > str2);
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

unsigned int TStringLen(const TString& str)
{
	return str.len;
}

char & TString::operator[](int index)
{
	if (index < 0 || index >= len)
	{
		/*throw "index out of range";
		return content[0];*/
		return content[index];
	}

	return content[index];
}