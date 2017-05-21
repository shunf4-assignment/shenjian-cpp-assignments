/*÷��� �ƿ����� 1652311*/
#include <iostream>
using namespace std;

class Days {
private:
	int year;
	int month;
	int day;
	int is_leap_year();  //�ж��Ƿ����꣬�ǣ�����1  /   �񣺷���0
public:
	int calc_days();     //�����ǵ���ĵڼ���
	Days(int, int, int);					 /* ������Բ���������Ҫ�����Ա�����Ķ��壬�������� */

};

/* �˴��������Ա����������ʵ�� */
int Days::is_leap_year() {
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		return 1;
	else 
		return 0;
}

int Days::calc_days() {
	if (is_leap_year() == 0) {
		int e_month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		if (e_month[month] < day)
			exit(-1);
		int i, sum;
		for (i = 0, sum = 0; i < month - 1; i++) {
			sum += e_month[i];
		}
		sum += day;
		return sum;
	}
	else {
		int e_month[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
		if (e_month[month] < day)
			exit(-1);
		int i, sum;
		for (i = 0, sum = 0; i < month - 1; i++) {
			sum += e_month[i];
		}
		sum += day;
		return sum;
	}


}

Days::Days(int y, int m, int d) {
	year = y;
	month = m;
	day = d;
}

/* main������׼�� */
int main()
{
	if (1) {
		Days d1(2012, 3, 18);
		cout << "Ӧ�����78�� ʵ���ǣ�" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 12, 31);
		cout << "Ӧ�����365��ʵ���ǣ�" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2012, 12, 31);
		cout << "Ӧ�����366��ʵ���ǣ�" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 2, 29);
		cout << "Ӧ�����-1�� ʵ���ǣ�" << d1.calc_days() << endl;
	}

	return 0;
}
