/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;

class student {
private:
	int num;
	float score;
public:
	void display();  //���ѧ�źͳɼ�
	void get(void);  //��������ѧ�źͳɼ�
					 //���в�����������κ����ݳ�Ա�ͳ�Ա����
};

/* �ڴ˸������Ա����������ʵ�� */
void student::display()
{
	cout << "ѧ��: " << num << ", �ɼ�: " << score << endl;
}

void student::get()
{
	scanf_s("%d %g", &num, &score);
}

int main()
{
	/* ��ע�⣺�������в������ٶ����κ����͵ı���(����ȫ�ֱ���) */
	student *p, s[5];

	/* ��������5���˵�ѧ�ż��ɼ�
	��Ҫ�󣺡����������ȷ��������ʾ�����硰�������**����ѧ�źͳɼ��� */
	for (p = s; p - s < 5; p++)
	{
		cout << "������� " << p - s + 1 << " ����ѧ�źͳɼ���";
		p->get();
	}

	/* �����1��3��5���˵���Ϣ */
	for (p = s; p - s < 5; p++, p++)
	{
		cout << "�� " << p - s + 1 << " ���ˣ�";
		p->display();
	}

	return 0;
}