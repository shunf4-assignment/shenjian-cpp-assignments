/* 1652270 �����2�� ��˴ */
/*HYPERBejeweled_SJProject - 90-b1-tools.cpp*/
#include "90-b1.h"

void startInit()
{
	srand(unsigned int(time(0)));
	system("color f0");
}

void restoreColor()
{
	setcolor(hout, commonColor[0], commonColor[1]);
}

void partInit(int part, int w, int h)
{
	switch (part)
	{
		case 0:
			setconsoleborder(hout, 100, 25, 500);
			setfontsize(hout, L"������", 20);
		case 1:
			setconsoleborder(hout, 100, 25, 500);
			setfontsize(hout, L"������", 20);
		default:
			setconsoleborder(hout, w, h, 500);
			setfontsize(hout, L"������", 20);
	}
	
	restoreColor();
	system("cls");
	
}

void pressEnterToContinue(char *p)
{
	//�纯����
	if (p == NULL)
		p = "��Enter������������";
	cout << p << endl;
	while (_getch() != '\r')
		;
	return;
}

