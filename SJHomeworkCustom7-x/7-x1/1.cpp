#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string> //C++ string类 需要用到

#include <stdio.h>


using namespace std;

struct student {
	string name;
	int num;
	char sex;
	struct student *next;//指向结构体自身的指针(下个结点)
};

int main()
{
	student *head = NULL, *p = NULL, *q = NULL;
	int i;

	freopen("Text.txt", "r", stdin);


	for (i = 0; i < 5; i++) {
		if (i > 0)
			q = p;
		p = new(nothrow) student; //思考：为什么不能用malloc
		if (p == NULL)
			return -1;
		if (i == 0)
			head = p; //head指向第1个结点
		else
			q->next = p;
		cout << "请输入第" << i + 1 << "个人的基本信息" << endl;
		cin >> p->name >> p->num >> p->sex; //键盘输入基本信息
		p->next = NULL;
	}

	p = head; //p复位，指向第1个结点
	while (p != NULL) { //循环进行输出
		cout << p->name << " " << p->num << " " << p->sex << endl;
		p = p->next;
	}

	p = head; //p复位，指向第1个结点
	while (p) {  //循环进行各结点释放
		q = p->next;
		delete p;
		p = q;
	}

	return 0;
}
