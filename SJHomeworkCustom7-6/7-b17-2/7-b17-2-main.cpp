/* 1652270 计算机2班 冯舜 */
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
		cout << fileName << " 打开失败！" << endl;
		return -1;
	}
	cout << fileName << " 创建成功。" << endl;
	cout << endl;
	cout << "group_add(fp, \"China\");  期望结果：1  实际结果：";
	cout << group_add(fp, "China") << endl;

	cout << "文件内容：" << endl;
	print(fp);

	system("pause");

	cout << endl;
	cout << "group_add(fp, \"China\"); (第二次)  期望结果：0  实际结果：";
	cout << group_add(fp, "China") << endl;
	cout << "文件内容：" << endl;
	print(fp);

	system("pause");

	cout << endl;
	cout << "group_add(fp, \"British\");  期望结果：1  实际结果：";
	cout << group_add(fp, "British") << endl;
	print(fp);
	cout << "group_add(fp, \"America\");  期望结果：1  实际结果：";
	cout << group_add(fp, "America") << endl;
	cout << "group_add(fp, \"Russia\");  期望结果：1  实际结果：";
	cout << group_add(fp, "Russia") << endl;
	cout << "文件内容：" << endl;
	print(fp);

	system("pause");

	cout << endl;
	cout << "【添加配置项】" << endl;

	cout << "item_add(fp, \"China\", \"人口\" , &pop, TYPE_DOUBLE);  \n期望结果：1  实际结果：";
	pop = 14.25e8;
	cout << item_add(fp, "China", "人口", &pop, TYPE_DOUBLE) << endl;

	print(fp);
	system("pause");

	cout << "item_add(fp, \"China\", \"首字母\", &firstletter, TYPE_CHARACTER)；  \n期望结果：1  实际结果：";
	firstletter = 'C';
	cout << item_add(fp, "China", "首字母", &firstletter, TYPE_CHARACTER) << endl;

	cout << "item_add(fp, \"China\", \"首都\", capital, TYPE_STRING);  \n期望结果：1  实际结果：";
	capital = "北京";
	cout << item_add(fp, "China", "首都", capital, TYPE_STRING) << endl;

	cout << "item_add(fp, \"China\", \"国际区号\", &code, TYPE_INT);  \n期望结果：1  实际结果：";
	code = 86;
	cout << item_add(fp, "China", "国际区号", &code, TYPE_INT) << endl;

	cout << "item_add(fp, \"China\", \"空\", NULL, TYPE_NULL);  \n期望结果：1  实际结果：";
	cout << item_add(fp, "China", "空", NULL, TYPE_NULL) << endl << endl;

	system("pause");


	cout << "尝试重复： item_add(fp, \"China\", \"首都\", capital, TYPE_STRING);  \n期望结果：0  实际结果：";
	capital = "上海";
	cout << item_add(fp, "China", "首都", capital, TYPE_STRING) << endl;

	cout << "尝试错误组别： item_add(fp, \"NonExist\", \"配置项1\", NULL, TYPE_NULL);  \n期望结果：0  实际结果：";
	cout << item_add(fp, "NonExist", "配置项1", NULL, TYPE_NULL) << endl;

	system("pause");
	cout << endl;

	cout << "item_add(fp, \"America\", \"人口\" , &pop, TYPE_DOUBLE);  \n期望结果：1  实际结果：";
	pop = 3.2e8;
	cout << item_add(fp, "America", "人口", &pop, TYPE_DOUBLE) << endl;

	cout << "item_add(fp, \"America\", \"首字母\", &firstletter, TYPE_CHARACTER)；  \n期望结果：1  实际结果：";
	firstletter = 'A';
	cout << item_add(fp, "America", "首字母", &firstletter, TYPE_CHARACTER) << endl;

	cout << "item_add(fp, \"America\", \"首都\", capital, TYPE_STRING);  \n期望结果：1  实际结果：";
	capital = "Washington";
	cout << item_add(fp, "America", "首都", capital, TYPE_STRING) << endl;

	cout << "item_add(fp, \"America\", \"国际区号\", &code, TYPE_INT);  \n期望结果：1  实际结果：";
	code = 1;
	cout << item_add(fp, "America", "国际区号", &code, TYPE_INT) << endl;

	cout << "item_add(fp, \"America\", \"空\", NULL, TYPE_NULL);  \n期望结果：1  实际结果：";
	cout << item_add(fp, "America", "空", NULL, TYPE_NULL) << endl;

	cout << "文件内容：" << endl;
	print(fp);

	system("pause");
	cout << endl;
	cout << "【获取配置项】" << endl;
	cout << "item_get_value(fp, \"America\", \"人口\" , &pop, TYPE_DOUBLE);  \n期望结果：1  实际结果：";
	cout << item_get_value(fp, "America", "人口", &pop, TYPE_DOUBLE) << endl;
	cout << "pop : " << pop << endl;

	cout << "item_get_value(fp, \"America\", \"首字母\", &firstletter, TYPE_CHARACTER)；  \n期望结果：1  实际结果：";
	cout << item_get_value(fp, "America", "首字母", &firstletter, TYPE_CHARACTER) << endl;
	cout << "fistletter : " << firstletter << endl;

	cout << "将 capital 赋值为一个足够大字符数组的首地址" << endl;
	capital = space;
	cout << "item_get_value(fp, \"America\", \"首都\", capital, TYPE_STRING);  \n期望结果：1  实际结果：";
	cout << item_get_value(fp, "America", "首都", capital, TYPE_STRING) << endl;
	cout << "capital : " << capital << endl;

	cout << "item_get_value(fp, \"America\", \"国际区号\", &code, TYPE_INT);  \n期望结果：1  实际结果：";
	cout << item_get_value(fp, "America", "国际区号", &code, TYPE_INT) << endl;
	cout << "code : " << code << endl << endl;

	system("pause");

	cout << endl << "测试错误情况" << endl;
	code = 333;
	cout << "code 初始: " << code << endl;
	cout << "item_get_value(fp, \"America\", \"空\", &code, TYPE_NULL);  \n期望结果：1  实际结果：";
	cout << item_get_value(fp, "America", "空", &code, TYPE_NULL) << endl;
	cout << "code : " << code << endl;

	cout << "尝试错误组别：" << endl;
	cout << "item_get_value(fp, \"NonExist\", \"国际区号\", &code, TYPE_INT);  \n期望结果：0  实际结果：";
	cout << item_get_value(fp, "NonExist", "国际区号", &code, TYPE_INT) << endl;
	cout << "code : " << code << endl;

	cout << "尝试错误项名：" << endl;
	cout << "item_get_value(fp, \"America\", \"不存在的\", &code, TYPE_INT);  \n期望结果：0  实际结果：";
	cout << item_get_value(fp, "America", "不存在的", &code, TYPE_INT) << endl;
	cout << "code : " << code << endl;

	cout << "item_get_value(fp, \"Russia\", \"国际区号\", &code, TYPE_INT);  \n期望结果：0  实际结果：";
	cout << item_get_value(fp, "Russia", "国际区号", &code, TYPE_INT) << endl;
	cout << "code : " << code << endl;

	cout << "尝试非本组项名：" << endl;
	cout << "item_get_value(fp, \"British\", \"国际区号\", &code, TYPE_INT);  \n期望结果：0  实际结果：";
	cout << item_get_value(fp, "British", "国际区号", &code, TYPE_INT) << endl;
	cout << "code : " << code << endl;

	cout << "文件内容：" << endl;
	print(fp);
	system("pause");
	cout << endl;
	cout << "【更新配置项】" << endl;

	pop = 30.1e8;
	cout << "pop : " << pop << endl;
	cout << "item_update(fp, \"China\", \"人口\" , &pop, TYPE_DOUBLE);  \n期望结果：1  实际结果：";
	cout << item_update(fp, "China", "人口", &pop, TYPE_DOUBLE) << endl;
	pop = 0;
	item_get_value(fp, "China", "人口", &pop, TYPE_DOUBLE);
	cout << "文件中 pop : " << pop << endl;


	strcpy(space, "Beijing");
	cout << "string : " << space << endl;
	cout << "item_update(fp, \"China\", \"首都\" , space, TYPE_STRING);  \n期望结果：1  实际结果：";
	cout << item_update(fp, "China", "首都", space, TYPE_STRING) << endl;
	strcpy(space, "");
	item_get_value(fp, "China", "首都", space, TYPE_STRING);
	cout << "文件中 string : " << space << endl;

	cout << endl << "update 碰到不存在的 item 名时，会新建" << endl;
	foundtime = 1945;
	cout << "foundtime : " << foundtime << endl;
	cout << "item_update(fp, \"China\", \"建立时间\" , &foundtime, TYPE_INT);  \n期望结果：1  实际结果：";
	cout << item_update(fp, "China", "建立时间", &foundtime, TYPE_INT) << endl;
	foundtime = 0;
	item_get_value(fp, "China", "建立时间", &foundtime, TYPE_INT);
	cout << "文件中 建立时间 : " << foundtime << endl << endl;

	system("pause");


	cout << endl << "测试错误情况" << endl;
	code = 333;
	cout << "code : " << code << endl;

	cout << "尝试错误组别：" << endl;
	cout << "item_update(fp, \"NonExist\", \"国际区号\", &code, TYPE_INT);  \n期望结果：0  实际结果：";
	cout << item_update(fp, "NonExist", "国际区号", &code, TYPE_INT) << endl;

	cout << "文件内容：" << endl;
	print(fp);
	system("pause");

	cout << endl;
	cout << "【删除配置项】" << endl;

	cout << "item_del(fp, \"America\", \"首都\");  \n期望结果：1  实际结果：";
	cout << item_del(fp, "America", "首都") << endl;
	cout << "目标项是否还存在，期望结果：0  实际结果：" << item_get_value(fp, "America", "首都", space, TYPE_STRING) << endl;

	cout << "item_del(fp, \"America\", \"国际区号\");  \n期望结果：1  实际结果：";
	cout << item_del(fp, "America", "国际区号") << endl;
	cout << "目标项是否还存在，期望结果：0  实际结果：" << item_get_value(fp, "America", "国际区号", &code, TYPE_INT) << endl << endl;

	system("pause");
	cout << endl << "测试错误情况" << endl;

	cout << "尝试错误组别：" << endl;
	cout << "item_del(fp, \"NonExist\", \"首都\");  \n期望结果：0  实际结果：";
	cout << item_del(fp, "NonExist", "首都") << endl;

	cout << "尝试错误项名：" << endl;
	cout << "item_del(fp, \"British\", \"不存在的\", &code, TYPE_INT);  \n期望结果：0  实际结果：";
	cout << item_get_value(fp, "America", "不存在的", &code, TYPE_INT) << endl;

	cout << "尝试非本组项名：" << endl;
	cout << "item_del(fp, \"British\", \"国际区号\");  \n期望结果：0  实际结果：";
	cout << item_del(fp, "British", "国际区号") << endl;

	cout << "文件内容：" << endl;
	print(fp);

	system("pause");
	cout << endl;
	cout << "【删除组】" << endl;

	cout << "group_del(fp, \"China\");  \n期望结果：1  实际结果：";
	cout << group_del(fp, "China") << endl;
	cout << "目标组是否还存在，期望结果：0  实际结果：" << item_get_value(fp, "China", "首都", space, TYPE_STRING) << endl;

	cout << "group_del(fp, \"Russia\");  \n期望结果：1  实际结果：";
	cout << group_del(fp, "Russia") << endl;

	cout << endl << "测试错误情况" << endl;

	cout << "尝试错误组别：" << endl;
	cout << "group_del(fp, \"NonExist\");  \n期望结果：0  实际结果：";
	cout << group_del(fp, "NonExist") << endl;

	cout << "文件内容：" << endl;
	print(fp);

	cout << endl;
	cout << "程序结束。" << endl;


	fclose(fp);

	return 0;
}
