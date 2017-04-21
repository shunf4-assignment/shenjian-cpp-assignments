/* 1652270 �����2�� ��˴ */
#include "7-b17-1.h"

void demo1(fstream &);
void demo2(fstream &);

int main()
{
	fstream fp;
	int option;

	if (true)
	{
		system("cls");
		cout << "C++ ��ʽ�����ļ��������Գ���" << endl;
		cout << "�ļ�����" << fileName << endl;
		cout << "1. ���/�½����ļ�����ʼ����" << endl;
		cout << "2. �������ļ�(ִ�� 1. ��)�Ļ����ϲ���" << endl;
		//cout << "0. �˳�" << endl;
		
		while (true)
		{
			cout << "��ѡ��";
			cin >> option;
			if (!cin.fail())
			{
				if (option >= 1 && option <= 2)
				{
					break;
				}
			}
			cout << "������������� 1 �� 2��" << endl;
		}
		if (option == 1)
		{
			fp.open(fileName, ios::in | ios::out | ios::trunc);

			if (!fp.is_open())
			{
				cout << fileName << " ��ʧ�ܣ�" << endl;
			}
			else
			{
				cout << fileName << " �½�/��ճɹ���" << endl;
				demo1(fp);
			}
		}
			
		if (option == 2)
		{
			fp.open(fileName, ios::in | ios::out);

			if (!fp.is_open())
			{
				cout << fileName << " ��ʧ�ܣ���ȷ�ϸ��ļ��Ƿ���ڲ���д��" << endl;
			}
			else
			{
				cout << fileName << " �򿪳ɹ���" << endl;
				demo2(fp);
			}
		}
	}
	fp.close();
	return 0;
}

void demo1(fstream &fp)
{
	int code;
	double pop;
	char *capital;
	char firstletter;
	char space[100];

	
	cout << endl;
	cout << "���½����" << endl;
	cout << "group_add(fp, \"China\");  ���������1  ʵ�ʽ����";
	cout << group_add(fp, "China") << endl;

	cout << "�ļ����ݣ�" << endl;
	print(fp);

	system("pause");

	cout << endl;
	cout << "group_add(fp, \"British\");  ���������1  ʵ�ʽ����";
	cout << group_add(fp, "British") << endl;
	cout << "group_add(fp, \"America\");  ���������1  ʵ�ʽ����";
	cout << group_add(fp, "America") << endl;
	cout << "group_add(fp, \"Russia\");  ���������1  ʵ�ʽ����";
	cout << group_add(fp, "Russia") << endl;

	system("pause");
	cout << endl;
	cout << "����������" << endl;

	cout << "item_add(fp, \"China\", \"�˿�\" , &pop, TYPE_DOUBLE);  ���������1\n  ʵ�ʽ����";
	pop = 14.25e8;
	cout << item_add(fp, "China", "�˿�" , &pop, TYPE_DOUBLE) << endl;

	cout << "item_add(fp, \"China\", \"����ĸ\", &firstletter, TYPE_CHARACTER)��  ���������1\n  ʵ�ʽ����";
	firstletter = 'C';
	cout << item_add(fp, "China", "����ĸ", &firstletter, TYPE_CHARACTER) << endl;
	
	cout << "item_add(fp, \"China\", \"�׶�\", capital, TYPE_STRING);  ���������1\n  ʵ�ʽ����";
	capital = "����";
	cout << item_add(fp, "China", "�׶�", capital, TYPE_STRING) << endl;

	cout << "item_add(fp, \"China\", \"��������\", &code, TYPE_INT);  ���������1\n  ʵ�ʽ����";
	code = 86;
	cout << item_add(fp, "China", "��������", &code, TYPE_INT) << endl;

	cout << "item_add(fp, \"China\", \"��\", NULL, TYPE_NULL);  ���������1\n  ʵ�ʽ����";
	cout << item_add(fp, "China", "��", NULL, TYPE_NULL) << endl << endl;

	system("pause");
	cout << "�ļ����ݣ�" << endl;
	print(fp);

	system("pause");
	cout << endl;

	cout << "�����������" << endl;

	pop = 30.1e8;
	cout << "pop : " << pop << endl;
	cout << "item_update(fp, \"China\", \"�˿�\" , &pop, TYPE_DOUBLE);  ���������1\n  ʵ�ʽ����";
	cout << item_update(fp, "China", "�˿�", &pop, TYPE_DOUBLE) << endl;
	pop = 0;
	item_get_value(fp, "China", "�˿�", &pop, TYPE_DOUBLE);
	cout << "�ļ��� �˿� : " << pop << endl;

	strcpy(space, "Beijing");
	cout << "space : " << space << endl;
	cout << "item_update(fp, \"China\", \"�׶�\" , space, TYPE_STRING);  ���������1\n  ʵ�ʽ����";
	cout << item_update(fp, "China", "�׶�", space, TYPE_STRING) << endl;
	strcpy(space, "");
	item_get_value(fp, "China", "�׶�", space, TYPE_STRING);
	cout << "�ļ��� �׶� : " << space << endl;

	system("pause");
	cout << endl;
	cout << "��ɾ�������" << endl;

	cout << "item_del(fp, \"China\", \"�˿�\");  ���������1\n  ʵ�ʽ����";
	cout << item_del(fp, "China", "�˿�") << endl;
	cout << "Ŀ�����Ƿ񻹴��ڣ� ���������0 ʵ�ʽ����" << item_get_value(fp, "China", "�˿�", &pop, TYPE_DOUBLE) << endl;

	system("pause");

	cout << "�ļ����ݣ�" << endl;
	print(fp);

	system("pause");
	cout << endl;
	
	cout << "��ɾ���顿" << endl;

	cout << "group_del(fp, \"Russia\");  ���������1\n  ʵ�ʽ����";
	cout << group_del(fp, "Russia") << endl;

	system("pause");

	cout << "�ļ����ݣ�" << endl;
	print(fp);

	cout << endl;
	cout << "���������" << endl;


	
}

void demo2(fstream &fp)
{
	int code, foundtime;
	double pop;
	char *capital;
	char firstletter;
	char space[100];

	
	
	cout << endl;
	cout << "���½����" << endl;

	cout << "group_add(fp, \"India\");  ���������1  ʵ�ʽ����";
	cout << group_add(fp, "India") << endl;

	cout << "���ظ��½����" << endl;
	cout << "group_add(fp, \"China\"); (�ڶ���)  ���������0  ʵ�ʽ����";
	cout << group_add(fp, "China") << endl;

	cout << "�ļ����ݣ�" << endl;
	print(fp);

	system("pause");
	cout << endl;
	cout << "����������" << endl;

	cout << "item_add(fp, \"America\", \"�˿�\" , &pop, TYPE_DOUBLE);  ���������1\n  ʵ�ʽ����";
	pop = 3.2e8;
	cout << item_add(fp, "America", "�˿�", &pop, TYPE_DOUBLE) << endl;

	cout << "item_add(fp, \"America\", \"����ĸ\", &firstletter, TYPE_CHARACTER)��  ���������1\n  ʵ�ʽ����";
	firstletter = 'A';
	cout << item_add(fp, "America", "����ĸ", &firstletter, TYPE_CHARACTER) << endl;

	cout << "item_add(fp, \"America\", \"�׶�\", capital, TYPE_STRING);  ���������1\n  ʵ�ʽ����";
	capital = "Washington";
	cout << item_add(fp, "America", "�׶�", capital, TYPE_STRING) << endl;

	cout << "item_add(fp, \"America\", \"��������\", &code, TYPE_INT);  ���������1\n  ʵ�ʽ����";
	code = 1;
	cout << item_add(fp, "America", "��������", &code, TYPE_INT) << endl;

	cout << "item_add(fp, \"America\", \"��\", NULL, TYPE_NULL);  ���������1\n  ʵ�ʽ����";
	cout << item_add(fp, "America", "��", NULL, TYPE_NULL) << endl;

	system("pause");
	cout << endl;
	cout << "���ظ������Ŀ��" << endl;
	capital = "�Ϻ�";
	cout << "capital : " << capital << endl;
	cout << "item_add(fp, \"China\", \"�׶�\", capital, TYPE_STRING);  ���������0\n  ʵ�ʽ����";
	
	cout << item_add(fp, "China", "�׶�", capital, TYPE_STRING) << endl;

	cout << "�����Դ������" << endl;
	cout << "item_add(fp, \"NonExist\", \"������1\", NULL, TYPE_NULL);  ���������0\n  ʵ�ʽ����";
	cout << item_add(fp, "NonExist", "������1", NULL, TYPE_NULL) << endl;

	system("pause");
	cout << "�ļ����ݣ�" << endl;
	print(fp);

	system("pause");
	cout << endl;

	cout << "����ȡ�����" << endl;
	cout << "item_get_value(fp, \"America\", \"�˿�\" , &pop, TYPE_DOUBLE);  ���������1\n  ʵ�ʽ����";
	cout << item_get_value(fp, "America", "�˿�", &pop, TYPE_DOUBLE) << endl;
	cout << "pop : " << pop << endl;

	cout << "item_get_value(fp, \"America\", \"����ĸ\", &firstletter, TYPE_CHARACTER)��  ���������1\n  ʵ�ʽ����";
	cout << item_get_value(fp, "America", "����ĸ", &firstletter, TYPE_CHARACTER) << endl;
	cout << "fistletter : " << firstletter << endl;

	cout << "�� capital ��ֵΪһ���㹻���ַ�������׵�ַ" << endl;
	capital = space;
	cout << "item_get_value(fp, \"America\", \"�׶�\", capital, TYPE_STRING);  ���������1\n  ʵ�ʽ����";
	cout << item_get_value(fp, "America", "�׶�", capital, TYPE_STRING) << endl;
	cout << "capital : " << capital << endl;

	cout << "item_get_value(fp, \"America\", \"��������\", &code, TYPE_INT);  ���������1\n  ʵ�ʽ����";
	cout << item_get_value(fp, "America", "��������", &code, TYPE_INT) << endl;
	cout << "code : " << code << endl << endl;

	system("pause");

	cout << endl << "�����Ի�ȡ��������������" << endl;
	code = 333;
	cout << "������TYPE_NULL��" << endl;
	cout << "code ��ʼ: " << code << endl;
	cout << "item_get_value(fp, \"America\", \"��\", &code, TYPE_NULL);  ���������1\n  ʵ�ʽ����";
	cout << item_get_value(fp, "America", "��", &code, TYPE_NULL) << endl;
	cout << "code : " << code << endl;

	cout << "�����Դ������" << endl;
	cout << "item_get_value(fp, \"NonExist\", \"��������\", &code, TYPE_INT);  ���������0\n  ʵ�ʽ����";
	cout << item_get_value(fp, "NonExist", "��������", &code, TYPE_INT) << endl;
	cout << "code : " << code << endl;

	cout << "�����Դ���������" << endl;
	cout << "item_get_value(fp, \"America\", \"�����ڵ�\", &code, TYPE_INT);  ���������0\n  ʵ�ʽ����";
	cout << item_get_value(fp, "America", "�����ڵ�", &code, TYPE_INT) << endl;
	cout << "code : " << code << endl;

	cout << "item_get_value(fp, \"Russia\", \"��������\", &code, TYPE_INT);  ���������0\n  ʵ�ʽ����";
	cout << item_get_value(fp, "Russia", "��������", &code, TYPE_INT) << endl;
	cout << "code : " << code << endl;

	cout << "�����ԷǱ���������" << endl;
	cout << "item_get_value(fp, \"British\", \"��������\", &code, TYPE_INT);  ���������0\n  ʵ�ʽ����";
	cout << item_get_value(fp, "British", "��������", &code, TYPE_INT) << endl;
	cout << "code : " << code << endl;

	system("pause");
	cout << endl;

	cout << "�����������" << endl;
	
	pop = 9.9e9;
	cout << "pop : " << pop << endl;
	cout << "item_update(fp, \"America\", \"�˿�\" , &pop, TYPE_DOUBLE);  ���������1\n  ʵ�ʽ����";
	cout << item_update(fp, "America", "�˿�", &pop, TYPE_DOUBLE) << endl;
	pop = 0;
	item_get_value(fp, "America", "�˿�", &pop, TYPE_DOUBLE);
	cout << "�ļ��� �˿� : " << pop << endl;

	cout << endl << "��update ���������ڵ� item ��ʱ�����½���" << endl;
	foundtime = 1945;
	cout << "foundtime : " << foundtime << endl;
	cout << "item_update(fp, \"China\", \"����ʱ��\" , &foundtime, TYPE_INT);  ���������1\n  ʵ�ʽ����";
	cout << item_update(fp, "China", "����ʱ��", &foundtime, TYPE_INT) << endl;
	foundtime = 0;
	item_get_value(fp, "China", "����ʱ��", &foundtime, TYPE_INT);
	cout << "�ļ��� ����ʱ�� : " << foundtime << endl << endl;

	cout << endl << "�����Դ��������" << endl;
	code = 333;
	cout << "code ��ʼ : " << code << endl;

	cout << "���Դ������" << endl;
	cout << "item_update(fp, \"NonExist\", \"��������\", &code, TYPE_INT);  ���������0\n  ʵ�ʽ����";
	cout << item_update(fp, "NonExist", "��������", &code, TYPE_INT) << endl;
	
	cout << "code : " << code << endl;
	system("pause");
	cout << "�ļ����ݣ�" << endl;
	print(fp);

	system("pause");
	cout << endl;

	cout << "��ɾ�������" << endl;

	cout << "item_del(fp, \"America\", \"�׶�\");  ���������1\n  ʵ�ʽ����";
	cout << item_del(fp, "America", "�׶�") << endl;
	cout << "Ŀ�����Ƿ񻹴��ڣ� ���������0 ʵ�ʽ����" << item_get_value(fp, "America", "�׶�", space, TYPE_STRING) << endl;

	cout << "item_del(fp, \"America\", \"��������\");  ���������1\n  ʵ�ʽ����";
	cout << item_del(fp, "America", "��������") << endl;
	cout << "Ŀ�����Ƿ񻹴��ڣ� ���������0 ʵ�ʽ����" << item_get_value(fp, "America", "��������", &code, TYPE_INT) << endl << endl;

	system("pause");
	cout << endl << "�����Դ��������" << endl;

	cout << "���Դ������" << endl;
	cout << "item_del(fp, \"NonExist\", \"�׶�\");  ���������0\n  ʵ�ʽ����";
	cout << item_del(fp, "NonExist", "�׶�") << endl;

	cout << "���Դ���������" << endl;
	cout << "item_del(fp, \"British\", \"�����ڵ�\", &code, TYPE_INT);  ���������0\n  ʵ�ʽ����";
	cout << item_get_value(fp, "America", "�����ڵ�", &code, TYPE_INT) << endl;

	cout << "���ԷǱ���������" << endl;
	cout << "item_del(fp, \"British\", \"��������\");  ���������0\n  ʵ�ʽ����";
	cout << item_del(fp, "British", "��������") << endl;

	cout << "��ɾ���顿" << endl;
	cout << "group_del(fp, \"China\");  ���������1\n  ʵ�ʽ����";
	cout << group_del(fp, "China") << endl;
	cout << "Ŀ�����Ƿ񻹴��ڣ� ���������0 ʵ�ʽ����" << item_get_value(fp, "China", "�׶�", space, TYPE_STRING) << endl;

	cout << endl << "�����Դ��������" << endl;

	cout << "���Դ������" << endl;
	cout << "group_del(fp, \"NonExist\");  ���������0\n  ʵ�ʽ����";
	cout << group_del(fp, "NonExist") << endl;

	system("pause");
	cout << "�ļ����ݣ�" << endl;
	print(fp);

	cout << endl;
	cout << "���������" << endl;
}