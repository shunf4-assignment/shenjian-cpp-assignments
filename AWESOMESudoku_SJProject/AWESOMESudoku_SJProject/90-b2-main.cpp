/* 1652270 �����2�� ��˴ */
/*AWESOMESudokuSJProject - 90-b2-main.cpp*/
#include "90-b2.h"





int test_filebox()
{
	listbox a;
	int lastIndex, lastTop, inputStatus = -1, selected, getFileStatus;
	a.h = 8;
	a.w = 20;
	a.index = 0;
	a.top = 0;
	a.itemLen = 0;
	a.pos.X = 4;
	a.pos.Y = 4;
	a.items = NULL;

	getFileStatus = getFileList(a.items, &a);
	if (getFileStatus == -1)
	{
		cout << "�ڴ治�������ͷ��ڴ档\n���򼴽��˳���" << endl;
		itemFree(a.items);
		return -1;
	}
	
	//itemAppend(a.items, "��1", &a);

	boxDraw(&a);
	cout << endl;
	cout << endl;

	while (inputStatus != 3)
	{
		inputStatus = boxWaitInput(&a, &lastIndex, &lastTop);
		itemsUpdate(&a, lastIndex, lastTop);
	}
	

	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "ѡ���� " << a.index << endl;

	itemFree(a.items);
	return 0;

}

int charGame()
{
	char fileName[fileNameLen];
	int status;
	//char *errorStr;
	ifstream f;
	Sudoku initial;
	while (true)
	{
		status = charSelFile(fileName);
		if (status == -1)
			return -1;
		f.open(fileName, ios::in);
		if (!f.is_open())
		{
			cout << "���ļ�ʧ�ܡ����� " << fileName << " �Ƿ���ڡ�" << endl;
			continue;
		}
		initSudoku(&initial, -1, 0);
		status = inputSudoku(&initial, &f);
		if (status == -2)
		{
			cout << "���ļ���ʽ����ȷ�������ԡ�" << endl;
			continue;
		}
		status = validSudoku(&initial, NULL);
		if (status == -2)
		{
			cout << "���������ڷǷ����֡������ԡ�" << endl;
			continue;
		}
		break;
	}
	cout << "[" << fileName << "]" << " �������Ѿ����롣" << endl;

	Sudoku o;  //overlay
	Sudoku p;  //player
	char inputMove[4];
	int inputJ, inputI, inputToBe;
	COORD start;
	composition *comps = NULL;
	composition *currComp = NULL;

	
	initSudoku(&p, &initial);
	compAppend(comps, p);

	currComp = comps;

	start = getxy_(hout);
	
	while (true)
	{
		p = currComp->c;
		initSudoku(&o, -1, 0);
		status = validSudoku(&p, &o);
		

		gotoxy(hout, start.X, start.Y);
		clearLines(16);

		cout << "��ǰ�����¼��" << compCount(comps, currComp) + 1 << " / " << compCount(comps) << endl;

		charSudoku(&p, &initial, &o);
		if (status != 0)
		{
			cout << "�������� " << status << " ����ͻ��";
		}
		else
		{
			if (isSudokuFull(&p))
			{
				clearLines(3);
				printLine("��ʤ���ˣ�");
				break;
			}
		}
		cout << endl;
		cout << "������(5c9/bk/fw/end)��";


		cin.get(inputMove, 4);
		cin.clear();
		cin.ignore(FS_MAX_LENGTH, '\n');
		cin.sync();

		_strlwr(inputMove);
		if (strcmp(inputMove, "end") == 0)
		{
			break;
		}
		if (strcmp(inputMove, "bk") == 0)
		{
			clearLines(1);
			if(currComp->prev)
				currComp = currComp->prev;
			else
			{
				printLine("�Ѿ����˵�һ�����裬�޷��ٻ��ˡ�");
			}
			continue;
		}
		if (strcmp(inputMove, "fw") == 0)
		{
			clearLines(1);

			if (currComp->next)
				currComp = currComp->next;
			else
			{
				printLine("�Ѿ��������µĲ��裬�޷���ǰ����");
				
			}
			continue;
		}

		if (!(inputMove[0] >= '1' && inputMove[0] <= '9' && inputMove[1] >= 'a' && inputMove[1] <= 'i' && inputMove[2] >= '1'&& inputMove[2] <= '9'))
		{
			printLine("�����ʽ�Ƿ������������롣");
			continue;
		}

		inputJ = inputMove[0] - '0';
		inputI = inputMove[1] - 'a' + 1;
		inputToBe = inputMove[2] - '0';

		if (initial.t[inputJ][inputI])
		{

			printLine("��Ϊ��ʼ���֣����ܸ��ġ�");
			continue;
		}

		p.t[inputJ][inputI] = inputToBe;

		clearLines(1);
		cout << inputMove << ": �ɹ���" << endl;
		compFree(currComp->next);
		currComp->next = NULL;
		compAppend(currComp, p);
		currComp = currComp->next;
	}

	compFree(comps);

	
	return 0;
}

int main()
{
	int status = 0;
	status = charGame();
	if (status == -1)
		return -1;
	return 0;
}