/*�ƿ�3�� ÷��� 1652311*/
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
		{ "����ǳ�", 0,0,0,0 },
		{ "����ֵ",0,10000,3370,16 },
		{ "����ֵ", 0,10000,6500,18 },
		{ "����",0,8192,3200,20 },
		{ "����",0,1024,800,22 },
		{ "��Ǯ����",0,100000000,20000000,24 },
		{ "����ֵ", 0,1000000,230000,28 },
		{ "����ֵ",  0,1000000,120000,32 },
		{ "�ƶ��ٶ�",  0,100,90,44 },
		{ "�����ٶ�",  0,100,80,45 },
		{ "������Χ",0,100,70,47 },
		{ "������",  0,2000,1300,48 },
		{ "������",0,2000,1600,50 },
		{ "���ݶ�", 0,100,50,52 },
		{ "����",  0,100,40,53 },
		{ "����", 0,100,30,54 },
		{ "�ȼ�",  0,100,64,55 },
		{ "ħ��ֵ",0,10000,3000,56 },
		{ "ʹ��ħ��ʱÿ�����ĵ�ħ��ֵ",0,100,18,58 },
		{ "ħ���˺���", 0,100,35,59 },
		{ "������", 0,100,52,60 },
		{ "ħ��������",0,100,69,61 },
		{ "������",  0,100,86,62 },
		{ "����", 0,100,100,63 },
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

	cout << "������Ҫ��ĵ����ݣ�";
	char xiugai[40];
	cin >> xiugai;
	int num_xiugai,step=0,i;
	char name_xiugai[15];
	for (i = 0; i < 25; i++) {
		if (strcmp(xiugai, game[i].type) == 0) {
			if (i != 0) {
				cout << "�������޸ĺ������(" << game[i].lowest << "--" << game[i].highest << "):";
				cin >> num_xiugai;
				if (num_xiugai > game[i].highest || num_xiugai < game[i].lowest) {
					cout << "��ֵ���ڿ��޸ķ�Χ��" << endl;
					return 0;
				}
			}
			else if (i == 0) {
				cout << "�������޸ĺ������ǳƣ�7�������ڣ���";
				cin >> name_xiugai;
			}
			step = 1;
			break;
		}
	}
	if (step == 0) {
		cout << "�޴�����޸�" << endl;
		return 0;
	}

	game[i].now = num_xiugai;
	iofile.seekp(game[i].begin_location, ios::beg);
	if(i!=23)
		iofile.write((char *)&game[i].now, sizeof(game[i+1].begin_location-game[i].begin_location));
	else 
		iofile.write((char *)&game[i].now,1);


	iofile.close();
	cout << "�޸ĳɹ�" << endl;
	return 0;
}*/





int main() {
	cout << "A.����ǳ�" << endl;
	cout << "B.����ֵ" << endl;
	cout << "C.����ֵ" << endl;
	cout << "D.����" << endl;
	cout << "E.����" << endl;
	cout << "F.��Ǯ����" << endl;
	cout << "G.����ֵ" << endl;
	cout << "H.����ֵ" << endl;
	cout << "I.Ԥ��ֵ" << endl;
	cout << "J.�ƶ��ٶ�" << endl;
	cout << "K.�����ٶ�" << endl;
	cout << "L.������Χ" << endl;
	cout << "M.Ԥ��ֵ" << endl;
	cout << "N.������" << endl;
	cout << "O.������" << endl;
	cout << "P.���ݶ�" << endl;
	cout << "Q.����" << endl;
	cout << "R.����" << endl;
	cout << "S.�ȼ�" << endl;
	cout << "T.ħ��ֵ" << endl;
	cout << "U.ʹ��ħ��ʱÿ�����ĵ�ħ��ֵ" << endl;
	cout << "V.ħ���˺���" << endl;
	cout << "W.������" << endl;
	cout << "X.ħ��������" << endl;
	cout << "Y.������" << endl;
	cout << "Z.����" << endl;
	cout << "������Ҫ��ĵ����ݴ��ţ�";
	/*
	ΪʲôA��ZҪ�ֶ���ӡ�����������𣿱���������ѭ������
	*/
	char change;
	cin >> change;
	if (int(change) < 65 || int(change) > 88) {   //��ֱ��д'A'��'Z'�����������ASCII�������
		cout << "�޴�����޸�ֵ" << endl;
	}
	change = int(change) - 65;	//���ɶ��Ҫ����65���������ֱ���ж��ǲ���'O'�����ǲ���'Q'���Ǽ�һ�ٱ���
	int adr[27] = { 0,16,18,20,22,24,28,32,\36\,44,45,46,\47\,48,50,52,53,54,55,56,58,59,60,61,62,63 };
				    1  2  3  4  5  6  7  8   9  10 11 12  13  14  15 16 17 18 19 20 21 22 23 24 25 26
	fstream iofile("game.dat", ios::in | ios::_Noreplace | ios::binary);
	if (!iofile) {
		cerr << "open error" << endl;
		exit(-1);
	}

	cout << "�������޸ĺ�����:";

	if (change == 0)
		char aft[17];
	else if (change == 5, 6, 7, )  //TMD������д�����жϵ��𣿶�����ʲô��˼��㶮û��������
		int aft;
	else if (change == 1, 2, 3, 4, 12, )//��ῴ��Ҫ������������ѧ��ѧ����ȥ��
		short aft;//��if���涨��Ĳ���������ȥ�ã�Ҫ���������ж�
	else if (change ==  9, 10,11, )
		char aft;

	cin >> aft;
	
	iofile.seekp(adr[change], ios::beg);
	if (change != 25)
		iofile.write((char *)&aft, sizeof(adr[change+1]-adr[change]));
	/*ʲô��˼����������
	ʲô��sizeof(adr[change+1]-adr[change])�������ⲻ�Ǻ�Ϊ4�����ڸ�ʲô��*/
	else
		iofile.write((char *)&aft, 1);  //��ֱ��д��1��ȥ������sizeof����ᱻ������

	cout << "�޸ĳɹ�" << endl;//����ô�����ļ��İ�������
	return 0;
}