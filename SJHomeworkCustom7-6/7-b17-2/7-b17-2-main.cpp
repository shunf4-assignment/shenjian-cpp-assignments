/* 1652270 �����2�� ��˴ */
#include "7-b17-2.h"

int main()
{
	FILE * fp;
	int code, foundtime;
	double pop;
	char *capital;
	char firstletter;
	char space[100];

	fp = fopen(fileName, "wb+");
	if (!fp)
	{
		cout << fileName << " ��ʧ�ܣ�" << endl;
		return -1;
	}
	cout << fileName << " �����ɹ���" << endl;
	cout << endl;
	cout << "group_add(fp, \"China\");  ���������1  ʵ�ʽ����";
	cout << group_add(fp, "China") << endl;

	cout << "�ļ����ݣ�" << endl;
	print(fp);

	system("pause");

	cout << endl;
	cout << "group_add(fp, \"China\"); (�ڶ���)  ���������0  ʵ�ʽ����";
	cout << group_add(fp, "China") << endl;
	cout << "�ļ����ݣ�" << endl;
	print(fp);

	system("pause");

	cout << endl;
	cout << "group_add(fp, \"British\");  ���������1  ʵ�ʽ����";
	cout << group_add(fp, "British") << endl;
	print(fp);
	cout << "group_add(fp, \"America\");  ���������1  ʵ�ʽ����";
	cout << group_add(fp, "America") << endl;
	cout << "group_add(fp, \"Russia\");  ���������1  ʵ�ʽ����";
	cout << group_add(fp, "Russia") << endl;
	cout << "�ļ����ݣ�" << endl;
	print(fp);

	system("pause");

	cout << endl;
	cout << "����������" << endl;

	cout << "item_add(fp, \"China\", \"�˿�\" , &pop, TYPE_DOUBLE);  \n���������1  ʵ�ʽ����";
	pop = 14.25e8;
	cout << item_add(fp, "China", "�˿�", &pop, TYPE_DOUBLE) << endl;

	print(fp);
	system("pause");

	cout << "item_add(fp, \"China\", \"����ĸ\", &firstletter, TYPE_CHARACTER)��  \n���������1  ʵ�ʽ����";
	firstletter = 'C';
	cout << item_add(fp, "China", "����ĸ", &firstletter, TYPE_CHARACTER) << endl;

	cout << "item_add(fp, \"China\", \"�׶�\", capital, TYPE_STRING);  \n���������1  ʵ�ʽ����";
	capital = "����";
	cout << item_add(fp, "China", "�׶�", capital, TYPE_STRING) << endl;

	cout << "item_add(fp, \"China\", \"��������\", &code, TYPE_INT);  \n���������1  ʵ�ʽ����";
	code = 86;
	cout << item_add(fp, "China", "��������", &code, TYPE_INT) << endl;

	cout << "item_add(fp, \"China\", \"��\", NULL, TYPE_NULL);  \n���������1  ʵ�ʽ����";
	cout << item_add(fp, "China", "��", NULL, TYPE_NULL) << endl << endl;

	system("pause");


	cout << "�����ظ��� item_add(fp, \"China\", \"�׶�\", capital, TYPE_STRING);  \n���������0  ʵ�ʽ����";
	capital = "�Ϻ�";
	cout << item_add(fp, "China", "�׶�", capital, TYPE_STRING) << endl;

	cout << "���Դ������ item_add(fp, \"NonExist\", \"������1\", NULL, TYPE_NULL);  \n���������0  ʵ�ʽ����";
	cout << item_add(fp, "NonExist", "������1", NULL, TYPE_NULL) << endl;

	system("pause");
	cout << endl;

	cout << "item_add(fp, \"America\", \"�˿�\" , &pop, TYPE_DOUBLE);  \n���������1  ʵ�ʽ����";
	pop = 3.2e8;
	cout << item_add(fp, "America", "�˿�", &pop, TYPE_DOUBLE) << endl;

	cout << "item_add(fp, \"America\", \"����ĸ\", &firstletter, TYPE_CHARACTER)��  \n���������1  ʵ�ʽ����";
	firstletter = 'A';
	cout << item_add(fp, "America", "����ĸ", &firstletter, TYPE_CHARACTER) << endl;

	cout << "item_add(fp, \"America\", \"�׶�\", capital, TYPE_STRING);  \n���������1  ʵ�ʽ����";
	capital = "Washington";
	cout << item_add(fp, "America", "�׶�", capital, TYPE_STRING) << endl;

	cout << "item_add(fp, \"America\", \"��������\", &code, TYPE_INT);  \n���������1  ʵ�ʽ����";
	code = 1;
	cout << item_add(fp, "America", "��������", &code, TYPE_INT) << endl;

	cout << "item_add(fp, \"America\", \"��\", NULL, TYPE_NULL);  \n���������1  ʵ�ʽ����";
	cout << item_add(fp, "America", "��", NULL, TYPE_NULL) << endl;

	cout << "�ļ����ݣ�" << endl;
	print(fp);

	system("pause");
	cout << endl;
	cout << "����ȡ�����" << endl;
	cout << "item_get_value(fp, \"America\", \"�˿�\" , &pop, TYPE_DOUBLE);  \n���������1  ʵ�ʽ����";
	cout << item_get_value(fp, "America", "�˿�", &pop, TYPE_DOUBLE) << endl;
	cout << "pop : " << pop << endl;

	cout << "item_get_value(fp, \"America\", \"����ĸ\", &firstletter, TYPE_CHARACTER)��  \n���������1  ʵ�ʽ����";
	cout << item_get_value(fp, "America", "����ĸ", &firstletter, TYPE_CHARACTER) << endl;
	cout << "fistletter : " << firstletter << endl;

	cout << "�� capital ��ֵΪһ���㹻���ַ�������׵�ַ" << endl;
	capital = space;
	cout << "item_get_value(fp, \"America\", \"�׶�\", capital, TYPE_STRING);  \n���������1  ʵ�ʽ����";
	cout << item_get_value(fp, "America", "�׶�", capital, TYPE_STRING) << endl;
	cout << "capital : " << capital << endl;

	cout << "item_get_value(fp, \"America\", \"��������\", &code, TYPE_INT);  \n���������1  ʵ�ʽ����";
	cout << item_get_value(fp, "America", "��������", &code, TYPE_INT) << endl;
	cout << "code : " << code << endl << endl;

	system("pause");

	cout << endl << "���Դ������" << endl;
	code = 333;
	cout << "code ��ʼ: " << code << endl;
	cout << "item_get_value(fp, \"America\", \"��\", &code, TYPE_NULL);  \n���������1  ʵ�ʽ����";
	cout << item_get_value(fp, "America", "��", &code, TYPE_NULL) << endl;
	cout << "code : " << code << endl;

	cout << "���Դ������" << endl;
	cout << "item_get_value(fp, \"NonExist\", \"��������\", &code, TYPE_INT);  \n���������0  ʵ�ʽ����";
	cout << item_get_value(fp, "NonExist", "��������", &code, TYPE_INT) << endl;
	cout << "code : " << code << endl;

	cout << "���Դ���������" << endl;
	cout << "item_get_value(fp, \"America\", \"�����ڵ�\", &code, TYPE_INT);  \n���������0  ʵ�ʽ����";
	cout << item_get_value(fp, "America", "�����ڵ�", &code, TYPE_INT) << endl;
	cout << "code : " << code << endl;

	cout << "item_get_value(fp, \"Russia\", \"��������\", &code, TYPE_INT);  \n���������0  ʵ�ʽ����";
	cout << item_get_value(fp, "Russia", "��������", &code, TYPE_INT) << endl;
	cout << "code : " << code << endl;

	cout << "���ԷǱ���������" << endl;
	cout << "item_get_value(fp, \"British\", \"��������\", &code, TYPE_INT);  \n���������0  ʵ�ʽ����";
	cout << item_get_value(fp, "British", "��������", &code, TYPE_INT) << endl;
	cout << "code : " << code << endl;

	cout << "�ļ����ݣ�" << endl;
	print(fp);
	system("pause");
	cout << endl;
	cout << "�����������" << endl;

	pop = 30.1e8;
	cout << "pop : " << pop << endl;
	cout << "item_update(fp, \"China\", \"�˿�\" , &pop, TYPE_DOUBLE);  \n���������1  ʵ�ʽ����";
	cout << item_update(fp, "China", "�˿�", &pop, TYPE_DOUBLE) << endl;
	pop = 0;
	item_get_value(fp, "China", "�˿�", &pop, TYPE_DOUBLE);
	cout << "�ļ��� pop : " << pop << endl;


	strcpy(space, "Beijing");
	cout << "string : " << space << endl;
	cout << "item_update(fp, \"China\", \"�׶�\" , space, TYPE_STRING);  \n���������1  ʵ�ʽ����";
	cout << item_update(fp, "China", "�׶�", space, TYPE_STRING) << endl;
	strcpy(space, "");
	item_get_value(fp, "China", "�׶�", space, TYPE_STRING);
	cout << "�ļ��� string : " << space << endl;

	cout << endl << "update ���������ڵ� item ��ʱ�����½�" << endl;
	foundtime = 1945;
	cout << "foundtime : " << foundtime << endl;
	cout << "item_update(fp, \"China\", \"����ʱ��\" , &foundtime, TYPE_INT);  \n���������1  ʵ�ʽ����";
	cout << item_update(fp, "China", "����ʱ��", &foundtime, TYPE_INT) << endl;
	foundtime = 0;
	item_get_value(fp, "China", "����ʱ��", &foundtime, TYPE_INT);
	cout << "�ļ��� ����ʱ�� : " << foundtime << endl << endl;

	system("pause");


	cout << endl << "���Դ������" << endl;
	code = 333;
	cout << "code : " << code << endl;

	cout << "���Դ������" << endl;
	cout << "item_update(fp, \"NonExist\", \"��������\", &code, TYPE_INT);  \n���������0  ʵ�ʽ����";
	cout << item_update(fp, "NonExist", "��������", &code, TYPE_INT) << endl;

	cout << "�ļ����ݣ�" << endl;
	print(fp);
	system("pause");

	cout << endl;
	cout << "��ɾ�������" << endl;

	cout << "item_del(fp, \"America\", \"�׶�\");  \n���������1  ʵ�ʽ����";
	cout << item_del(fp, "America", "�׶�") << endl;
	cout << "Ŀ�����Ƿ񻹴��ڣ����������0  ʵ�ʽ����" << item_get_value(fp, "America", "�׶�", space, TYPE_STRING) << endl;

	cout << "item_del(fp, \"America\", \"��������\");  \n���������1  ʵ�ʽ����";
	cout << item_del(fp, "America", "��������") << endl;
	cout << "Ŀ�����Ƿ񻹴��ڣ����������0  ʵ�ʽ����" << item_get_value(fp, "America", "��������", &code, TYPE_INT) << endl << endl;

	system("pause");
	cout << endl << "���Դ������" << endl;

	cout << "���Դ������" << endl;
	cout << "item_del(fp, \"NonExist\", \"�׶�\");  \n���������0  ʵ�ʽ����";
	cout << item_del(fp, "NonExist", "�׶�") << endl;

	cout << "���Դ���������" << endl;
	cout << "item_del(fp, \"British\", \"�����ڵ�\", &code, TYPE_INT);  \n���������0  ʵ�ʽ����";
	cout << item_get_value(fp, "America", "�����ڵ�", &code, TYPE_INT) << endl;

	cout << "���ԷǱ���������" << endl;
	cout << "item_del(fp, \"British\", \"��������\");  \n���������0  ʵ�ʽ����";
	cout << item_del(fp, "British", "��������") << endl;

	cout << "�ļ����ݣ�" << endl;
	print(fp);

	system("pause");
	cout << endl;
	cout << "��ɾ���顿" << endl;

	cout << "group_del(fp, \"China\");  \n���������1  ʵ�ʽ����";
	cout << group_del(fp, "China") << endl;
	cout << "Ŀ�����Ƿ񻹴��ڣ����������0  ʵ�ʽ����" << item_get_value(fp, "China", "�׶�", space, TYPE_STRING) << endl;

	cout << "group_del(fp, \"Russia\");  \n���������1  ʵ�ʽ����";
	cout << group_del(fp, "Russia") << endl;

	cout << endl << "���Դ������" << endl;

	cout << "���Դ������" << endl;
	cout << "group_del(fp, \"NonExist\");  \n���������0  ʵ�ʽ����";
	cout << group_del(fp, "NonExist") << endl;

	cout << "�ļ����ݣ�" << endl;
	print(fp);

	cout << endl;
	cout << "���������" << endl;


	fclose(fp);

	return 0;
}
