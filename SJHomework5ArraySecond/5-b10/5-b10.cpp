/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;


int main()
{
	const int maxLength = 80;
	char chara[maxLength] = {'\0'};
	int i;
	bool upper = true;
	bool first = true;
	while (true)
	{
		cin >> chara;
		upper = true;
		if (first)
		{
			first = false;
		}
		else
			cout << " ";
		for (i = 0; i < maxLength; i++)
		{
			if (chara[i] != '\0' && chara[i] != '\n')
			{
				if (chara[i] >= 'A' && chara[i] <= 'Z')
				{
					if (!upper)
						chara[i] += 97 - 65;
					else
						upper = false;
				}
				else if (chara[i] >= 'a' && chara[i] <= 'z')
				{
					if (upper)
					{
						chara[i] += -97 + 65;
						upper = false;
					}
				}
				cout << chara[i];
				chara[i] = '\0';
			}
			else
				break;
		}
		if (cin.get() == '\n')
			break;
	}
	cout << endl;
	return 0; //hi there %6m7Ml 5Hnnx  h
}
