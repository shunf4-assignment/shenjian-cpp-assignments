/*÷��� 1652311 �ƿ�3��*/
#include<iostream>
using namespace std;
int main()
{
	double a[7][2], b[7][2], judge1, judge2, flag = 0;
	int i, j, m, k;
	cout << "���������ĸ���(4-7��:";
	while (1) {
		cin >> m;
		if (!cin.good()) {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������������룺";
		}
		else if (m >= 8 || m <= 3) {
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������������룺";
		}
		else
			break;
	}

	cout << "�밴������4-7��ֱ�����꣺";
	while (1) {
		for (j = 0; j <= m - 1; j++) {
			for (i = 0; i <= 1; i++) {
				cin >> a[j][i];
				if (!cin.good()) {
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "����������������룺";
				}
			}
		}
		break;
	}



	for (j = 0; j <= m - 1; j++) {
		for (k = 0; k <= m - 1; k++) {
			if (j <= m - 2) {
				b[k][0] = a[j][0] - a[j + 1][0];
				b[k][1] = a[k][1] - a[k][1];
			}
			else {
				b[k][0] = a[m - 1][0] - a[0][0];
				b[k][1] = a[m - 1][1] - a[0][1];
			}
		}
	}
	//���������ת������


		judge1 = b[k][0] * b[k + 1][1] - b[k + 1][0] * b[k][1];
		judge2 = b[k - 1][0] * b[0][1] - b[0][0] * b[k - 1][1];
		//��������жϣ�x1y2-x2y1)

		for (k = 0; k <= m - 2; k++) {
			if (fabs(judge1) <= 1e-6 || fabs(judge2) <= 1e-6)
				flag++;
		}
		//�ж���û�����㹲�ߣ���������㹲�ߣ�flag��++

		if (flag > 0) {
			cout << "����" << m << "����"<<endl;
			return 0;
		}
		//���flag>0�ˣ������㹲�ߣ�����m���Σ�ֱ��return 0��������


		flag = 0;//�����㹲�ߣ���flag��0�������µ��ж�
		for (k = 0; k <= m - 2; k++) {
			if (fabs(judge1) > 0 || fabs(judge2) > 0)
				flag++;
		}
		if (flag == m)
			cout << "��͹" << m << "����"<<endl;//ÿ��������˶�����0����͹�����
		else
			cout << "����͹" << m << "����"<<endl;//���������С��0������͹�����

		return 0;

	}

