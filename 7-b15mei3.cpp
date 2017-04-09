/*计科3班 梅语冰 1652311*/
#include<iostream>
#include<fstream>
using namespace std;
/*
struct data {
	char type[40];
	int lowest;
	int highest;
	int now;
	int begin_location;
};

int main() {

	struct data game[25] {
		{ "玩家昵称", 0,0,0,0 },
		{ "生命值",0,10000,3370,16 },
		{ "力量值", 0,10000,6500,18 },
		{ "体质",0,8192,3200,20 },
		{ "灵巧",0,1024,800,22 },
		{ "金钱数量",0,100000000,20000000,24 },
		{ "名声值", 0,1000000,230000,28 },
		{ "魅力值",  0,1000000,120000,32 },
		{ "移动速度",  0,100,90,44 },
		{ "攻击速度",  0,100,80,45 },
		{ "攻击范围",0,100,70,47 },
		{ "攻击力",  0,2000,1300,48 },
		{ "防御力",0,2000,1600,50 },
		{ "敏捷度", 0,100,50,52 },
		{ "智力",  0,100,40,53 },
		{ "经验", 0,100,30,54 },
		{ "等级",  0,100,64,55 },
		{ "魔法值",0,10000,3000,56 },
		{ "使用魔法时每次消耗的魔法值",0,100,18,58 },
		{ "魔法伤害力", 0,100,35,59 },
		{ "命中率", 0,100,52,60 },
		{ "魔法防御力",0,100,69,61 },
		{ "暴击率",  0,100,86,62 },
		{ "耐力", 0,100,100,63 },
		{ NULL,0,0,0 }
	};

	for (int i = 0; i < 25; i++) {
		cout << game[i].type << endl;
	}
	fstream iofile("game.dat", ios::in | ios::_Noreplace|ios::binary);
	if (!iofile) {
		cerr << "open error" << endl;
		exit(-1);
	}

	cout << "请输入要求改的内容：";
	char xiugai[40];
	cin >> xiugai;
	int num_xiugai,step=0,i;
	char name_xiugai[15];
	for (i = 0; i < 25; i++) {
		if (strcmp(xiugai, game[i].type) == 0) {
			if (i != 0) {
				cout << "请输入修改后的数据(" << game[i].lowest << "--" << game[i].highest << "):";
				cin >> num_xiugai;
				if (num_xiugai > game[i].highest || num_xiugai < game[i].lowest) {
					cout << "该值不在可修改范围内" << endl;
					return 0;
				}
			}
			else if (i == 0) {
				cout << "请输入修改后的玩家昵称（7个字以内）：";
				cin >> name_xiugai;
			}
			step = 1;
			break;
		}
	}
	if (step == 0) {
		cout << "无此项可修改" << endl;
		return 0;
	}

	game[i].now = num_xiugai;
	iofile.seekp(game[i].begin_location, ios::beg);
	if(i!=23)
		iofile.write((char *)&game[i].now, sizeof(game[i+1].begin_location-game[i].begin_location));
	else 
		iofile.write((char *)&game[i].now,1);


	iofile.close();
	cout << "修改成功" << endl;
	return 0;
}*/





int main() {
	cout << "A.玩家昵称" << endl;
	cout << "B.生命值" << endl;
	cout << "C.力量值" << endl;
	cout << "D.体质" << endl;
	cout << "E.灵巧" << endl;
	cout << "F.金钱数量" << endl;
	cout << "G.名声值" << endl;
	cout << "H.魅力值" << endl;
	cout << "I.预留值" << endl;
	cout << "J.移动速度" << endl;
	cout << "K.攻击速度" << endl;
	cout << "L.攻击范围" << endl;
	cout << "M.预留值" << endl;
	cout << "N.攻击力" << endl;
	cout << "O.防御力" << endl;
	cout << "P.敏捷度" << endl;
	cout << "Q.智力" << endl;
	cout << "R.经验" << endl;
	cout << "S.等级" << endl;
	cout << "T.魔法值" << endl;
	cout << "U.使用魔法时每次消耗的魔法值" << endl;
	cout << "V.魔法伤害力" << endl;
	cout << "W.命中率" << endl;
	cout << "X.魔法防御力" << endl;
	cout << "Y.暴击率" << endl;
	cout << "Z.耐力" << endl;
	cout << "请输入要求改的内容代号：";
	/*
	为什么A到Z要手动打印啊？不嫌累吗？本来可以用循环做的
	*/
	char change;
	cin >> change;
	if (int(change) < 65 || int(change) > 88) {   //你直接写'A'和'Z'会死啊？搞个ASCII码摆在那
		cout << "无此项可修改值" << endl;
	}
	change = int(change) - 65;	//你干啥子要减掉65啊？你后面直接判断是不是'O'或者是不是'Q'不是简单一百倍吗？
	int adr[27] = { 0,16,18,20,22,24,28,32,\36\,44,45,46,\47\,48,50,52,53,54,55,56,58,59,60,61,62,63 };
				    1  2  3  4  5  6  7  8   9  10 11 12  13  14  15 16 17 18 19 20 21 22 23 24 25 26
	fstream iofile("game.dat", ios::in | ios::_Noreplace | ios::binary);
	if (!iofile) {
		cerr << "open error" << endl;
		exit(-1);
	}

	cout << "请输入修改后数据:";

	if (change == 0)
		char aft[17];
	else if (change == 5, 6, 7, )  //TMD有这样写条件判断的吗？逗号是什么意思你搞懂没？？？？
		int aft;
	else if (change == 1, 2, 3, 4, 12, )//沈坚看到要被你气死，上学期学到哪去了
		short aft;//在if里面定义的不能拿外面去用，要另做条件判断
	else if (change ==  9, 10,11, )
		char aft;

	cin >> aft;
	
	iofile.seekp(adr[change], ios::beg);
	if (change != 25)
		iofile.write((char *)&aft, sizeof(adr[change+1]-adr[change]));
	/*什么意思？？？？？
	什么叫sizeof(adr[change+1]-adr[change])？这玩意不是恒为4吗？你在搞什么鬼？*/
	else
		iofile.write((char *)&aft, 1);  //你直接写个1上去，不用sizeof？沈坚被你气死

	cout << "修改成功" << endl;//你特么不关文件的啊？？？
	return 0;
}