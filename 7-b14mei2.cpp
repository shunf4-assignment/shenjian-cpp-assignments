/*÷��� �ƿ�3�� 1652311*/
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
		cout << "�������ļ�·��:";
		cin >> filepath;
	}
	fin.open(filepath, ios::binary|ios::in);
	if (fin.is_open() == 0) {
		cout << "���ļ�ʧ��" << endl;
		return 0;
	}

	for (j = 0;!fin.eof(); j++) {
			cout <<setw(8)<<hex<< setfill('0')<<fin.tellg() << "    ";
			for (i = 0; i < 16&&!fin.eof(); i++) {
				fin.read((char *)&ch[i], sizeof(ch[i]));
				cout << fin.gcount() << " ";
				if (i == 7)
					cout << "-";
			}
			cout << "     ";
			cout << ch << endl;		
		}		
	return 0;
}

