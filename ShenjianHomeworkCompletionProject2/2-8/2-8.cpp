/*1652270 �����2�� ��˴*/
#include <iostream>
using namespace std;

char encrypt(char s1, int offset)
{
	char firstLetter;
	if (s1 >= 65 && s1 <= (65 + 25))
	{
		//��д��ĸ
		firstLetter = 65;
	}
	else if (s1 >= 97 && s1 <= (97 + 25))
	{
		//Сд��ĸ
		firstLetter = 97;
	}
	else
	{
		return '?';
	}
	return ((s1 - firstLetter) + offset + 26) % 26 + firstLetter;
}

int main()
{
	char c1 = 'C', c2 = 'h', c3 = 'i', c4 = 'n', c5 = 'a';
	c1 = encrypt(c1, 4);
	c2 = encrypt(c2, 4);
	c3 = encrypt(c3, 4);
	c4 = encrypt(c4, 4);
	c5 = encrypt(c5, 4);
	cout << c1 << c2 << c3 << c4 << c5 << endl;
	return 0;
}

/*
�����ܣ�
����5��char�ͱ������ֱ�ֵΪC,h,i,n,a���ٵ���encrypt����������п������ܡ�����������c1��c5��
չʾ���ܽ��ΪGlmre��
*/