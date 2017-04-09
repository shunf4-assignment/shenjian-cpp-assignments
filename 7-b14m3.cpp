/*梅语冰 计科3班 1652311*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string.h>
#include <iomanip>
using namespace std;
int main(int argc, char *argv[]) {
	int i = 0, j;
	char filepath[100];
	char ch[16] = { 0 };
	ifstream fin;

	if (argc == 2) {
		strcpy(filepath, argv[1]);
	}
	if (argc == 1) {
		cout << "请输入文件路径:";
		cin >> filepath;
	}
	fin.open(filepath, ios::binary | ios::in);
	if (fin.is_open() == 0) {
		cout << "打开文件失败" << endl;
		return 0;
	}

	for (j = 0; !fin.eof(); j++) {
		cout << setw(8) << hex << setfill('0') << fin.tellg() << "    ";
		for (i = 0; i < 16 && !fin.eof(); i++) {
			fin.read((char *)&ch[i], sizeof(ch[i]));
			cout << "  " << hex << (unsigned int)ch[i];
			if (i == 7)
				cout << "-";
		}
		cout << "     ";
		for (i = 0; i < 16; i++) {
			if (int(ch[i]) <= 126 || ch[i] >= 33)
				cout << ch[i];
			else
				cout << "...";
		}
		cout << endl;
		for (i = 0; i < 16; i++) {
			ch[i] = 0;
		}
	}
	return 0;

}

