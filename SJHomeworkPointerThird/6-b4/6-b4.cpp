#include <iostream>
using namespace std;
#define FS_LEN 20

bool isPalindrome(char * str)
{
	char *start = str, *end = str + strlen(str)-1;
	for (; start < end; start++, end--)
	{
		if (*start != *end)
		{
			return false;
		}
	}
	return true;
}

int main()
{
	char str[FS_LEN +1] = { 0 };
	cout << "请输入一个字符串：";
	gets_s(str);
	if (isPalindrome(str))
	{
		cout << str << "是回文字符串。" << endl;
	}
	else
	{
		cout << str << "不是回文串。" << endl;
	}
	
}