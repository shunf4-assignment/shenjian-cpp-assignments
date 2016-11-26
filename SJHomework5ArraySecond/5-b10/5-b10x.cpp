/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include <iostream>
using namespace std;

int convertCap(char letter, bool upperCase = false)
{
	int offset = 0;
	if (letter >= 'A' && letter <= 'Z')
	{
		if (!upperCase)
			offset = 97 - 65;
	}
	else if (letter >= 'a' && letter <= 'z')
	{
		if (upperCase)
			offset = -97 + 65;
	}
	else
		return -1024;
	return offset;
}

int main_()
{
	char chara;
	bool newWord = true;
	int convertOffset;
	while (true)
	{
		chara = getchar();
		if (chara == '\n')
			break;
		if (chara == ' ')
			newWord = true;
		convertOffset = convertCap(chara, newWord);
		cout << (char)(((convertOffset == -1024) ? 0 : convertOffset) + chara);
		if (newWord && convertOffset != -1024)
		{
			newWord = false;
		}
	}
	return 0; //hi there %6m7Ml 5Hnnx  h
}
