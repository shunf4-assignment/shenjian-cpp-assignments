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
	cout << "������һ���ַ�����";
	gets_s(str);
	if (isPalindrome(str))
	{
		cout << str << "�ǻ����ַ�����" << endl;
	}
	else
	{
		cout << str << "���ǻ��Ĵ���" << endl;
	}
	
}