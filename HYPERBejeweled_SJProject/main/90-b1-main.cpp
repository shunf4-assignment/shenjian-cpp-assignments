/* 1652270 计算机2班 冯舜 */
/*HYPERBejeweled_SJProject - 90-b1-main.cpp*/
#include "90-b1.h"

void part1()
{
	Map gameMap = { 0 };
	Map overMap = { 0 };


	inputThing(&(gameMap.w), "请输入游戏区域的宽(5-9)：", "输入非法！", "输入超过限制！", 5, MAXGRID, true);
	inputThing(&(gameMap.h), "请输入游戏区域的高(5-9)：", "输入非法！", "输入超过限制！", 5, MAXGRID, true);

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
		pressEnterToContinue("显示完了原始数组，按回车显示可消的球……");
		checkInARowWithScore(&gameMap, &overMap, &score);
		//checkHint(&gameMap, &overMap);
		printMap(&gameMap, &overMap, true);
		cout << score << endl;
		cout << endl;
		pressEnterToContinue("按回车键回主菜单……");
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

		cout << "\n            彩球消消乐 by 顺子\n\n\
	-------------------------------------------------------\n\
		1.内部数组，生成初始状态，寻找是否有初始可消除项\n\
		2.内部数组，消除初始可消除项后非0项下落并用0填充\n\
		3.内部数组，消除初始可消除项后查找消除提示\n\
		4.n*n的框架(无分隔线)，显示初始状态\n\
		5.n*n的框架(有分隔线)，显示初始状态\n\
		6.n*n的框架(有分隔线)，显示初始状态及初始可消除项\n\
		7.n*n的框架(有分隔线)，消除初始可消除项后显示消除提示\n\
		8.cmd图形界面完整版\n\
		0.退出\n\
	-------------------------------------------------------\n\
		[请选择0 - 9]";

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
				setfontsize(hout, L"新宋体", 24);
				part6OnceMove();
				break;
			case 7:
				setfontsize(hout, L"新宋体", 24);
				part7GraphicFull(false);
				break;
			case 8:
				setfontsize(hout, L"新宋体", 24);
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
