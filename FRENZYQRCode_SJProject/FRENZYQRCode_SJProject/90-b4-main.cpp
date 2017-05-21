/* 1652270 计算机2班 冯舜 */
/* FRENZYQRCode_SJProject - 90-b4-main.cpp */
#include "90-b4.h"

#define LEN_MAXBYTES 100

void QRCode::inputData()
{
	char inputBuf[LEN_MAXBYTES + 1];
	const char *hints[] = {"数字模式", "字母数字模式", "字节模式（ANSI编码或说ISO 8859-1，建议网址使用）", "字节模式（用UTF-8编码，带BOM）", "字节模式（用UTF-8编码，不带BOM）"};
	const int modes[] = { MODE_NUM, MODE_ALPHA, MODE_BYTE, MODE_BYTE };
	cout << "请输入要编码为二维码的数据内容，最长 " << LEN_MAXBYTES << " 字节：";
	cin.get(inputBuf, LEN_MAXBYTES + 1, '\n');
	cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
	cin.sync();

	//cout << "您输入了：" << inputBuf << endl;
	//check best mode
	int bestmode = 0;
	int selectMode = 0;
	
	for (char *p = inputBuf; *p; p++)
	{
		if (*p < '0' || *p > '9')

		{
			if (bestmode < 1)
				bestmode = 1;
			if (*p >= 0 && *p < 123)
			{
				if (bestmode < 2 && !alphanumericMap[*p])
					bestmode = 2;
			}
			else
			{
				if (bestmode < 2)
					bestmode = 2;
				if (bestmode < 3 && *p < 0)
					bestmode = 3;
			}
		}
		
	}
	for (int i = 0; i < 5; i++)
	{
		cout << i << ". " << hints[i];
		if (bestmode == i && i != 1)
			cout << "\t\t(推荐)";
		if (bestmode == i && i == 1)
			cout << "\t\t(推荐，如果不介意混淆大小写)";
		cout << endl;
	}
	cout << "请输入想要使用的模式：";
	for (bool valid = false; valid == false;)
	{
		valid = true;
		cin >> selectMode;
		if (!cin.good())
		{
			cout << "输入非法，请重新输入：";
			valid = false;
			cin.clear();
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			cin.sync();
		}
		else
		{
			if (!(selectMode >= 0 && selectMode <= 4))
			{
				cout << "输入超出范围，请重新输入：";
				valid = false;
			}
		}
	}

	//bool UTF8;
	UTF8 = (selectMode == 3 || selectMode == 4);
	UTF8BOM = (selectMode == 4);
	//int mode;
	unsigned int dataLen;

	switch (selectMode)
	{
		case 0:
			mode = MODE_NUM;
			break;
		case 1:
			mode = MODE_ALPHA;
			break;
		case 2:
		case 3:
		case 4:
			mode = MODE_BYTE;
			break;
	}

	if (UTF8)
	{
		dataBuf = new(nothrow) unsigned char[strlen(inputBuf) * 3 / 2 + 2];
		if (!dataBuf)
			exit(SOVF);
		Gb2312ToUtf8(inputBuf, (char *)dataBuf, strlen(inputBuf) * 3 / 2 + 1);
		cout << "我们把你输入的字符串转成了 UTF-8 编码，在控制台输出如下：" << endl;
		cout << dataBuf << endl;
	}
	else
	{
		dataBuf = new(nothrow) unsigned char[strlen(inputBuf) + 1];
		if (!dataBuf)
			exit(SOVF);
		strcpy_s((char *)dataBuf, strlen(inputBuf) + 1, inputBuf);
	}

	dataLen = validCharNum((unsigned char *)dataBuf, mode, UTF8, false);
	cout << "经过UTF-8编码（可选）和剔除无法表示的字符，实际的数据长度 " << dataLen << "，原数据长度 " << strlen((const char *)inputBuf) << endl;

	//select eclevel
	char errLevelIn;
	//unsigned errLevel;
	cout << "请输入需要的纠错等级(L/M/Q/H)：";

	for (bool valid = false; valid == false;)
	{
		valid = true;
		cin >> errLevelIn;
		if (!cin.good())
		{
			cout << "输入非法，请重新输入：";
			valid = false;
			cin.clear();
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			cin.sync();
		}
		else
		{
			errLevelIn = toupper(errLevelIn);
			if (!(errLevelIn == 'L' || errLevelIn == 'M' || errLevelIn == 'Q' || errLevelIn == 'H' ))
			{
				cout << "输入超出范围，请重新输入：";
				valid = false;
			}
		}
	}

	switch (errLevelIn)
	{
		case 'L':
			errLevel = ERRLVL_L;
			break;
		case 'M':
			errLevel = ERRLVL_M;
			break;
		case 'Q':
			errLevel = ERRLVL_Q;
			break;
		case 'H':
			errLevel = ERRLVL_H;
			break;
		default:
			errLevel = ERRLVL_Q;
	}

	//select version
	unsigned versionMin;
	unsigned versionInput;
	for (versionMin = 1; versionMin <= 40; versionMin++)
	{
		if (capabilityTable[versionMin - 1][errLevel][mode] >= dataLen)
			break;
	}
	if (versionMin == 41)
	{
		cout << "抱歉，您输入的数据量过大，无法用二维码表示。" << endl;
		return;
	}
	cout << "可以用 " << versionMin << " 及以上的版本号来表达该数字。" << endl;
	cout << "请输入版本号，范围从 " << versionMin << " 到 40 （含）：";
	for (bool valid = false; valid == false;)
	{
		valid = true;
		cin >> versionInput;
		if (!cin.good())
		{
			cout << "输入非法，请重新输入：";
			valid = false;
			cin.clear();
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			cin.sync();
		}
		else
		{
			if (!(versionInput >= versionMin && versionInput <= 40))
			{
				cout << "输入超出范围，请重新输入：";
				valid = false;
			}
		}
	}
	version = versionInput;

	char inputDebug[3];
	cout << "是否显示生成过程中详细内容（Y/y-是，其他或直接回车-否）：";
	cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
	cin.sync();
	cin.get(inputDebug, sizeof(inputDebug) / sizeof(char), '\n');
	if (tolower(inputDebug[0]) == 'y')
		debug = true;
	else
		debug = false;
}



int main()
{
	QRCode q;
	q.inputData();
	q.printQR();
	system("pause");
	return 0;
}