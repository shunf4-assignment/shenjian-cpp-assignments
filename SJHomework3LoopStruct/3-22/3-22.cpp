/* 1652270 �����2�� ��˴ */
#include <iostream>
using namespace std;


int main()
{
	int peachNum = 1; //�ھ�����������Ҳ�͵��ڵ�ʮ���֮ǰ���������������ｲ������������ָ��n��Ժ����������
	int day = 9;  //�����ǵ�ʮ�죬�������������ھ�����

	//cout << "�� " << day + 1 << " �죬��֮ǰ�� " << peachNum << " �����ӣ�����һ���±�" << endl;

	for (; day >= 1; day--)  //ʱ�⵹��
	{
		//cout << "�� " << day << " �죬��֮ǰ�� " << (peachNum + 1) * 2 << " �����ӣ�����֮��ʣ�� " << peachNum << " ����" << endl;
		peachNum = (peachNum + 1) * 2;
	}
	
	cout << "��һ��ժ���� " << peachNum << " �����ӡ�" << endl;

	return 0;
}