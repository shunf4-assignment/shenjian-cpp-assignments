/* 1652270 �����2�� ��˴ */
/* FRENZYQRCode_SJProject - 90-b4-main.cpp */
#include "90-b4.h"

#define LEN_MAXBYTES 100

void QRCode::inputData()
{
	char inputBuf[LEN_MAXBYTES + 1];
	const char *hints[] = {"����ģʽ", "��ĸ����ģʽ", "�ֽ�ģʽ��ANSI�����˵ISO 8859-1��������ַʹ�ã�", "�ֽ�ģʽ����UTF-8���룬��BOM��", "�ֽ�ģʽ����UTF-8���룬����BOM��"};
	const int modes[] = { MODE_NUM, MODE_ALPHA, MODE_BYTE, MODE_BYTE };
	cout << "������Ҫ����Ϊ��ά����������ݣ�� " << LEN_MAXBYTES << " �ֽڣ�";
	cin.get(inputBuf, LEN_MAXBYTES + 1, '\n');
	cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
	cin.sync();

	//cout << "�������ˣ�" << inputBuf << endl;
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
			cout << "\t\t(�Ƽ�)";
		if (bestmode == i && i == 1)
			cout << "\t\t(�Ƽ�����������������Сд)";
		cout << endl;
	}
	cout << "��������Ҫʹ�õ�ģʽ��";
	for (bool valid = false; valid == false;)
	{
		valid = true;
		cin >> selectMode;
		if (!cin.good())
		{
			cout << "����Ƿ������������룺";
			valid = false;
			cin.clear();
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			cin.sync();
		}
		else
		{
			if (!(selectMode >= 0 && selectMode <= 4))
			{
				cout << "���볬����Χ�����������룺";
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
		cout << "���ǰ���������ַ���ת���� UTF-8 ���룬�ڿ���̨������£�" << endl;
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
	cout << "����UTF-8���루��ѡ�����޳��޷���ʾ���ַ���ʵ�ʵ����ݳ��� " << dataLen << "��ԭ���ݳ��� " << strlen((const char *)inputBuf) << endl;

	//select eclevel
	char errLevelIn;
	//unsigned errLevel;
	cout << "��������Ҫ�ľ���ȼ�(L/M/Q/H)��";

	for (bool valid = false; valid == false;)
	{
		valid = true;
		cin >> errLevelIn;
		if (!cin.good())
		{
			cout << "����Ƿ������������룺";
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
				cout << "���볬����Χ�����������룺";
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
		cout << "��Ǹ��������������������޷��ö�ά���ʾ��" << endl;
		return;
	}
	cout << "������ " << versionMin << " �����ϵİ汾�����������֡�" << endl;
	cout << "������汾�ţ���Χ�� " << versionMin << " �� 40 ��������";
	for (bool valid = false; valid == false;)
	{
		valid = true;
		cin >> versionInput;
		if (!cin.good())
		{
			cout << "����Ƿ������������룺";
			valid = false;
			cin.clear();
			cin.ignore((numeric_limits<std::streamsize>::max)(), '\n');
			cin.sync();
		}
		else
		{
			if (!(versionInput >= versionMin && versionInput <= 40))
			{
				cout << "���볬����Χ�����������룺";
				valid = false;
			}
		}
	}
	version = versionInput;

	char inputDebug[3];
	cout << "�Ƿ���ʾ���ɹ�������ϸ���ݣ�Y/y-�ǣ�������ֱ�ӻس�-�񣩣�";
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