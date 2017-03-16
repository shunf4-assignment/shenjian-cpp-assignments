/*1652311 Ã·Óï±ù ¼Æ¿Æ3°à*/
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <stdlib.h>	//srand/randº¯Êý
#include <time.h>	//timeº¯Êý
using namespace std;

struct student {
	char no[10];
	char *name;
	char *school;
	bool flag=0;
};

int main() {

	srand((unsigned int)time(0));

	int N, M,t;
	ifstream fin;
	ofstream fout;
	fin.open("stulist.txt", ios::in);
	fout.open("result.txt", ios::out);
	if (fin.is_open() == 0) {
		cout << "´ò¿ªÊ§°Ü" << endl;
		return -1;
	}
	if (fout.is_open() == 0) {
		cout << "´ò¿ªÊä³öÎÄ¼þÊ§°Ü" << endl;
		fin.close();
		return -1;
	}
	fin >> N;
	fin >> M;
	student *m,*n;
	m=new(nothrow) student[M];
	n = new(nothrow) student[N];
	if (m == NULL) {
		cout << "ÉêÇëÊ§°Ü" << endl;
		return -1;
	}
	if (n == NULL) {
		cout << "ÉêÇëÊ§°Ü" << endl;
		return -1;
	}

	int i,j;

	for (i = 0; i < M; i++) {
		fin >> (m + i)->no;
		char name[10];
		fin >> name;
		for (j = 0; name[j] != '\0'; j++);
		(m+i)->name = (char *)malloc((j + 1) * sizeof(char));
		if ((m + i)->name == NULL) {
			cout << "ÉêÇëÊ§°Ü" << endl;
			return -1;
		}
		char school[10];
		fin >> school;
		for (j = 0; school[j] != '\0'; j++);
		(m + i)->school = (char *)malloc((j + 1) * sizeof(char));
		if ((m + i)->school == NULL) {
			cout << "ÉêÇëÊ§°Ü" << endl;
			return -1;
		}

	}

	for (i = 0; i < N; i++) {
		t = rand() % M;
		if ((m + t)->flag == 1) {
			i--;
			continue;
		}
		(n + i)->name = (m + t)->name;
		strcpy((n + i)->no, (m + t)->no);
		(n + i)->school = (m + t)->school;
		(m + t)->flag = 1;
	}

	for (i = 0; i < N; i++) {
		fout << (n + i)->no << setw(15) << (n + i)->name << setw(15) << (n + i)->school << endl;
	}

	for (i = 0; i < M; i++) {
		delete ((m + i)->name);
		delete ((m + i)->school);
	}
	delete m;
	delete n;

	fin.close();
	fout.close();
	return 0;
}