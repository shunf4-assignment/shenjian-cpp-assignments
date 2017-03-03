/* 1652270 �����2�� ��˴ */
/*HYPERBejeweled_SJProject - 90-b1-main.cpp*/
#include "90-b1.h"

void part1()
{
	Map gameMap = { 0 };
	Map overMap = { 0 };


	inputThing(&(gameMap.w), "��������Ϸ����Ŀ�(5-9)��", "����Ƿ���", "���볬�����ƣ�", 5, MAXGRID, true);
	inputThing(&(gameMap.h), "��������Ϸ����ĸ�(5-9)��", "����Ƿ���", "���볬�����ƣ�", 5, MAXGRID, true);

	while(1){
		partInit(1);
		int score = 0;
		

		overMap.w = gameMap.w;
		overMap.h = gameMap.h;
		initializeMap(&gameMap, -1, 0);
		initializeMap(&overMap, -1, 0);

		initEmerge(&gameMap);
		printMap(&gameMap, NULL, true);
		cout << endl;
		pressEnterToContinue("��ʾ����ԭʼ���飬���س���ʾ�������򡭡�");
		checkInARowWithScore(&gameMap, &overMap, &score);
		//checkHint(&gameMap, &overMap);
		printMap(&gameMap, &overMap, true);
		cout << score << endl;
		cout << endl;
		pressEnterToContinue("���س��������˵�����");
	}
	

}

int main()
{
	int mode;
	char userOpt;
	startInit();
	
	while (true)
	{
		mode = 1;
		partInit(0);

		cout << "\n            ���������� by ˳��\n\n\
	-------------------------------------------------------\n\
		1.�ڲ����飬���ɳ�ʼ״̬��Ѱ���Ƿ��г�ʼ��������\n\
		2.�ڲ����飬������ʼ����������0�����䲢��0���\n\
		3.�ڲ����飬������ʼ������������������ʾ\n\
		4.n*n�Ŀ��(�޷ָ���)����ʾ��ʼ״̬\n\
		5.n*n�Ŀ��(�зָ���)����ʾ��ʼ״̬\n\
		6.n*n�Ŀ��(�зָ���)����ʾ��ʼ״̬����ʼ��������\n\
		7.n*n�Ŀ��(�зָ���)��������ʼ�����������ʾ������ʾ\n\
		8.cmdͼ�ν���������\n\
		0.�˳�\n\
	-------------------------------------------------------\n\
		[��ѡ��0 - 9]";

		do {
			userOpt = _getch();
		} while (!(userOpt >= '0' && userOpt <= '9'));
		cout << userOpt << endl;
		mode = userOpt - '0';

		switch (mode)
		{
			case 0:
				return 0;
			case 1:
				part1();
				break;
			/*case 2:
				part2FindMove();
				break;
			case 3:
				part3FullFunction();
				break;
			case 4:
				part4Frame();
				break;
			case 5:
				part5Table();
				break;
			case 6:
				setfontsize(hout, L"������", 24);
				part6OnceMove();
				break;
			case 7:
				setfontsize(hout, L"������", 24);
				part7GraphicFull(false);
				break;
			case 8:
				setfontsize(hout, L"������", 24);
				part7GraphicFull(true);
				break;
			case 9:
				part9();
				break;
			*/
		}
	}
	return 0;
}
