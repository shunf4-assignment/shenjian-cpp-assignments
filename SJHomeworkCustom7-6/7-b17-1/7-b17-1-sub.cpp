/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include "7-b17-1.h"

void debugCheck(fstream &fp)
{
	cout << endl;
	cout << "eof: " << int(fp.eof()) << endl;
	cout << "fail: " << int(fp.fail()) << endl;
	cout << "bad: " << int(fp.bad()) << endl;
	cout << "tellg: " << int(fp.tellg()) << endl;
	cout << "tellp: " << int(fp.tellp()) << endl;
	cout << "peek1: " << char(fp.peek());
	cout << "(" << int(fp.get()) << ")" << endl;
	cout << "peek2: " << char(fp.peek());
	cout << "(" << int(fp.peek()) << ")" << endl;
	fp.clear();
	fp.seekg(-1, ios::cur);
	getchar();
}

void print(fstream &fp)
{
	char c;
	fp.clear();
	fp.seekp(0, ios::beg);
	c = fp.get();
	while (!fp.eof())
	{
		cout  << c;
		c = fp.get();
	}
	fp.clear();
}

void resize(int size)
{
	experimental::filesystem::resize_file(fileName, size);
}

int isThisCharEmpty(char c, const char * emptyCharList)
{
	if (!c)
		return 1;
	int probeEmpty = 0;
	for (const char *p = emptyCharList; *p; p++)
	{
		if (c == *p)
		{
			probeEmpty = 1;
			break;
		}
	}
	return probeEmpty;
}

void readUntilEmpty(istrstream &f, char *buffer, const char * emptyCharList)
{
	//read until get a empty char
	char probe;

	probe = f.get();
	for (char *b = buffer; !f.eof(); b++)
	{

		if (!isThisCharEmpty(probe, emptyCharList))
		{
			*b = probe;
		}
		else
		{
			*b = '\0';
			break;
		}
		probe = f.get();
	}
	f.clear();
}

int loopUntilNotEmpty(fstream &f, const char * emptyCharList)
{
	//loop until get a non-empty char
	//returns true if ever got an empty char; false if never
	char probe;
	int everEmpty = 0;

	probe = f.get();
	for (; !f.eof();)
	{
		if (!isThisCharEmpty(probe, emptyCharList))
		{
			f.seekg(-1, ios::cur);
			break;
		}
		else
		{
			everEmpty = 1;
		}
		probe = f.get();
	}
	return everEmpty;
}

int loopUntilNotEmpty(istrstream &f, const char * emptyCharList)
{
	//loop until get a non-empty char
	//returns true if ever got an empty char; false if never
	char probe;
	int everEmpty = 0;

	probe = f.get();
	for (; !f.eof();)
	{
		if (!isThisCharEmpty(probe, emptyCharList))
		{
			f.seekg(-1, ios::cur);
			break;
		}
		else
		{
			everEmpty = 1;
		}
		probe = f.get();
	}
	return everEmpty;
}

int loopBackUntilNotEmpty(fstream &f, const char * emptyCharList)
{
	//loop back until get a non-empty char
	//returns true if ever got an empty char; false if never
	char probe;
	int everEmpty = 0;

	f.seekg(-1, ios::cur);
	probe = f.peek();
	for (; f.good() && int(f.tellg()) >= 0;)
	{
		if (!isThisCharEmpty(probe, emptyCharList))
		{
			break;
		}
		else
		{
			everEmpty = 1;
		}
		f.seekg(-1, ios::cur);
		probe = f.peek();
	}

	f.clear();
	return everEmpty;
}

int almostTheSame(const char *str1, const char *str2)
{
	char *p[2], *h[2], *e[2];
	int result = 0;
	p[0] = new(nothrow) char[strlen(str1) + 1];
	if (!p[0])
		return -1;
	p[1] = new(nothrow) char[strlen(str2) + 1];
	if (!p[1])
	{
		delete[](p[0]);
		return -1;
	}

	strcpy(p[0], str1);
	strcpy(p[1], str2);

	for (int i = 0; i < 2; i++)
	{
		char* px = p[i];
		while (true)
		{
			if (*px == '\0')
				break;
			if (!isThisCharEmpty(*px, emptyChar))
			{
				break;
			}
			px++;
		}
		h[i] = px;
	}


	for (int i = 0; i < 2; i++)
	{
		char* px = p[i] + strlen(p[i]);
		if (px == p[i])
		{
			//len == 0
			e[i] = px;
		}
		else
		{
			px--;
			while (true)
			{
				if (*px == '\0')
					break;
				if (!isThisCharEmpty(*px, emptyChar))
				{
					break;
				}
				px--;
			}
			e[i] = px + 1;
		}
		e[i][0] = '\0';
	}

	if (strcmp(h[0], h[1]) == 0)
	{
		result = 1;
	}

	for (int i = 0; i < 2; i++)
	{
		delete[](p[i]);
	}

	return result;
}

int fileLength(fstream &fp)
{
	int fileLen, originPos;
	originPos = int(fp.tellg());
	fp.clear();
	
	fp.seekg(0, ios::end);
	fileLen = int(fp.tellg());
	fp.seekg(originPos, ios::beg);

	fp.clear();

	return fileLen;
}


int whereIsThisGroup(fstream &fp, const char *group_name)
{
	//if not found, return -2
	int nowLineLen;
	int fileLen;
	int result = -2;
	char *currLine, *toMatch;
	int groupHead = 0;

	

	//create string that stores target group tag
	toMatch = new(nothrow) char[strlen(group_name) + 5];
	strcpy(toMatch, "[");
	strcat(toMatch, group_name);
	strcat(toMatch, "]\n");

	fileLen = fileLength(fp);

	fp.seekp(0, ios::beg);

	while (!fp.eof())
	{
		//get the length of this line
		groupHead = int(fp.tellg());
		fp.ignore(fileLen, '\n');
		if (fp.eof())
		{
			fp.clear();
			fp.seekg(0, ios::end);
		}
		nowLineLen = int(fp.gcount());

		fp.seekg(groupHead, ios::beg);
		currLine = new(nothrow) char[nowLineLen + 1];

		if (!currLine)
		{
			delete[]toMatch;
			fp.clear();
			return -1;
		}

		//read in this line
		fp.read(currLine, nowLineLen);  //may have 0d0a->0a problem
		
		currLine[nowLineLen] = '\0';
		if (almostTheSame(currLine, toMatch))
		{
			result = groupHead;
			delete[]currLine;
			break;
		}
		delete[]currLine;
		fp.peek();
	}

	delete[]toMatch;
	fp.clear();
	return result;
}

int whereIsNextGroup(fstream &fp)
{
	//if not found, return -2
	int fileLen;
	int result = -2;
	int groupHead = 0;
	
	fileLen = fileLength(fp);
	//skip current line
	
	fp.ignore(fileLen, '\n');
	fp.peek();
	while (!fp.eof())
	{
		groupHead = int(fp.tellg());
		loopUntilNotEmpty(fp, emptyCharWithoutNewLine);

		if (fp.peek() == '[')
		{
			result = groupHead;
			break;
		}

		fp.ignore(fileLen, '\n');
		fp.peek();
	}

	fp.clear();
	return result;
}


int whereIsThisItem(fstream& fp, const char * item_name)
{
	//if not found, return -2
	int nowLineLen;
	int fileLen;
	int result = -2;
	char *currLine, *currLineTmp;
	int groupHead = 0;

	fileLen = fileLength(fp);

	fp.ignore();

	while (!fp.eof() && result == -2)
	{
		groupHead = int(fp.tellg());
		fp.ignore(fileLen, '\n');
		nowLineLen = int(fp.gcount());
		if (fp.eof())
		{
			fp.clear();
			fp.seekg(0, ios::end);
		}

		fp.seekg(groupHead, ios::beg);
		currLine = new(nothrow) char[nowLineLen + 1];

		if (!currLine)
		{
			return -1;
		}

		currLineTmp = new(nothrow) char[nowLineLen + 1];

		if (!currLineTmp)
		{
			delete[]currLine;
			return -1;
		}

		fp.read(currLine, nowLineLen);

		currLine[nowLineLen] = '\0';

		istrstream currLineStream(currLine, nowLineLen);
		loopUntilNotEmpty(currLineStream, emptyCharWithoutNewLine);
		
		if ((currLineStream.peek()) == '[')
		{
			//next Group
			delete[]currLineTmp;
			delete[]currLine;
			break;
		}
		readUntilEmpty(currLineStream, currLineTmp, "= \t");
		if (!strcmp(currLineTmp, item_name))
		{
			//found this item
			result = groupHead;

		}
		delete[]currLineTmp;
		delete[]currLine;
		fp.peek();
	}
	fp.clear();
	return result;
}

char *makeItem(const char * item_name, const void *item_value , enum ITEM_TYPE item_type)
{
	int tgtLen;
	char * buf;
	switch (item_type)
	{
		case TYPE_DOUBLE:
			tgtLen = 15;
			break;
		case TYPE_INT:
			tgtLen = 11;
			break;
		case TYPE_CHARACTER:
			tgtLen = 2;
			break;
		case TYPE_NULL:
			tgtLen = 1;
			break;
		case TYPE_STRING:
			tgtLen = strlen((char*)(item_value));
			break;
		default:
			tgtLen = 0;
	}

	tgtLen += strlen(item_name) + 5;
	buf = new(nothrow) char[tgtLen];
	if (!buf)
		return NULL;

	ostrstream ss(buf, tgtLen, ios::out);

	ss << item_name << "=";
	switch (item_type)
	{
		case TYPE_DOUBLE:
			ss << *(double *)item_value;
			break;
		case TYPE_INT:
			ss << *(int *)item_value;
			break;
		case TYPE_CHARACTER:
			ss << *(char *)item_value;
			break;
		case TYPE_NULL:
			break;
		case TYPE_STRING:
			ss << (char *)item_value;
			break;
		default:
			;
	}
	ss << endl << ends;
	return buf;
}

int tail_move_inside(fstream &fp, int from, int to)
{
	int jumpOut, lastCount;
	int groupFormer, groupLatter, lastFormer;
	char block[LEN_BLOCK + 1] = { 0 };

	jumpOut = 0;

	groupFormer = to;
	groupLatter = from;

	while (!jumpOut)
	{
		fp.seekg(groupLatter, ios::beg);
		fp.read(block, LEN_BLOCK);
		lastCount = int(fp.gcount());

		if (lastCount < LEN_BLOCK)
		{
			fp.clear();
			jumpOut = 1;
		}
		fp.seekg(groupFormer, ios::beg);
		fp.write(block, lastCount);

		lastFormer = groupFormer;
		groupFormer = int(fp.tellg());
		groupLatter = groupFormer - lastFormer + groupLatter;
	}
	fp << flush;
	resize(groupFormer);
	return 0;
}

int tail_move_outside(fstream &fp, int from, int to)
{
	int jumpOut;
	int groupFormer, groupLatter;
	int tailSize;
	char *tail;

	jumpOut = 0;

	groupFormer = from;
	groupLatter = to;

	fp.seekg(0, ios::end);
	tailSize = int(fp.tellg()) - groupFormer + 1;
	tail = new(nothrow) char[tailSize + 2];
	if (!tail)
		return -1;
	fp.seekg(groupFormer, ios::beg);
	fp.read(tail, tailSize);
	tailSize = int(fp.gcount());
	fp.clear();
	fp.seekp(groupLatter, ios::beg);
	fp.write(tail, tailSize);
	fp.flush();
	delete[]tail;
	return 0;
}

int group_add(fstream &fp, const char *group_name)
{
	int status;
	char *toMatch;
	int groupExist = 0;

	//check if this group exists

	status = whereIsThisGroup(fp, group_name);
	if (status == -1)
		return -1;
	else if (status > 0)
		groupExist = 1;

	//if not, add group
	if (groupExist)
	{
		return 0;
	}
	else
	{
		toMatch = new(nothrow) char[strlen(group_name) + 5];
		strcpy(toMatch, "[");
		strcat(toMatch, group_name);
		strcat(toMatch, "]\n");
		fp.seekp(0, ios::end);
		fp << endl ;
		fp.write(toMatch, strlen(toMatch));
		
		delete[]toMatch;
	}
	fp.flush();
	
	return 1;

}

int group_del(fstream &fp, const char *group_name)
{
	int groupStart;
	int groupExist = 0;
	int groupNext;
	int status;

	//check if this group exists
	groupStart = whereIsThisGroup(fp, group_name);
	if (groupStart == -1)
		return -1;
	else if (groupStart < 0)
		return 0;

	fp.seekp(groupStart, ios::beg);
	//if yes, del group
	groupNext = whereIsNextGroup(fp);	//may return -2 as the file position identifier, but it doesn't matter
	
	status = tail_move_inside(fp, groupNext, groupStart);
	if (status < 0)
		return 0;

	return 1;
}

int item_add(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	int groupStart, groupNext, pointerCur, itemStart;
	char *buf;

	groupStart = whereIsThisGroup(fp, group_name);
	if (groupStart == -1)
		return -1;
	else if (groupStart < 0)
		return 0;

	fp.seekg(groupStart, ios::beg);

	groupNext = whereIsNextGroup(fp);
	if (groupNext == -2)
	{
		fp.seekg(0, ios::end);
		groupNext = int(fp.tellg());
	}
	fp.clear();
	fp.seekp(groupStart, ios::beg);

	//check if this item exists
	itemStart = whereIsThisItem(fp, item_name);
	if (itemStart == -1)
		return -1;
	else if (itemStart >= 0)
		return 0;

	fp.seekp(groupNext, ios::beg);

	

	loopBackUntilNotEmpty(fp, emptyChar);

	fp.ignore(fileLength(fp), '\n');
	if (fp.eof())
	{
		fp.clear();
		fp.seekp(0, ios::end);
		fp << endl;
	}
	pointerCur = int(fp.tellg());

	buf = makeItem(item_name, item_value, item_type);
	if (!buf)
		return -1;

	tail_move_outside(fp, pointerCur, pointerCur + strlen(buf) + 1); // 0a->0d0a, so + 1
	fp.seekp(pointerCur, ios::beg);
	fp.write(buf, strlen(buf));

	fp.flush();
	delete[]buf;
	return 1;
}


int item_del(fstream &fp, const char *group_name, const char *item_name)
{
	int groupStart;
	int itemStart, itemNext;
	int status;

	//check if this group exists
	groupStart = whereIsThisGroup(fp, group_name);

	if (groupStart == -1)
		return -1;
	else if (groupStart < 0)
		return 0;

	fp.seekp(groupStart, ios::beg);
	
	//check if this item exists
	itemStart = whereIsThisItem(fp, item_name);
	if (itemStart == -1)
		return -1;
	else if (itemStart < 0)
		return 0;

	//if yes, del item
	fp.seekg(itemStart, ios::beg);
	fp.ignore(fileLength(fp), '\n');
	if (fp.eof())
	{
		fp.clear();
		fp.seekp(0, ios::end);
	}
	itemNext = int(fp.tellg());

	status = tail_move_inside(fp, itemNext, itemStart);
	if (status < 0)
		return 0;

	return 1;
}

int item_update(fstream &fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	int groupStart;
	int itemStart, itemNext, itemNextNew;
	int status = 0;
	char *buf;

	//check if this group exists
	groupStart = whereIsThisGroup(fp, group_name);
	if (groupStart == -1)
		return -1;
	else if (groupStart < 0)
		return 0;

	fp.seekp(groupStart, ios::beg);

	//check if this item exists
	itemStart = whereIsThisItem(fp, item_name);
	if (itemStart == -1)
		return -1;
	else
	{
		if (itemStart == -2)
		{
			//item not exist
			return item_add(fp, group_name, item_name, item_value, item_type);
		}
		else
		{
			//continue
			;
		}
	}

	//if yes, modify item
	fp.seekg(itemStart, ios::beg);
	fp.ignore(fileLength(fp), '\n');
	if (fp.eof())
	{
		fp.clear();
		fp.seekp(0, ios::end);
	}
	itemNext = int(fp.tellg());

	buf = makeItem(item_name, item_value, item_type);
	if (!buf)
		return -1;

	itemNextNew = itemStart + strlen(buf) + 1;  // 0a->0d0a

	if (itemNext < itemNextNew)
	{
		status = tail_move_outside(fp, itemNext, itemNextNew); 
	}
	else if (itemNext > itemNextNew)
	{
		status = tail_move_inside(fp, itemNext, itemNextNew);
	}
	if (status == -1)
	{
		delete[]buf;
		return -1;
	}

	fp.seekp(itemStart, ios::beg);
	fp.write(buf, strlen(buf));

	fp.flush();
	delete[]buf;
	return 1;
}

int item_get_value(fstream &fp, const char *group_name, const char *item_name, void *item_value, const enum ITEM_TYPE item_type)
{
	int groupStart;
	int itemStart;
	int status = 0, tgtLen;
	char *buf;

	//check if this group exists
	groupStart = whereIsThisGroup(fp, group_name);
	if (groupStart == -1)
		return -1;
	else if (groupStart < 0)
		return 0;

	fp.seekp(groupStart, ios::beg);

	//check if this item exists
	itemStart = whereIsThisItem(fp, item_name);
	if (itemStart == -1)
		return -1;
	else
	{
		if (itemStart == -2)
		{
			//item not exist
			return 0;
		}
		else
		{
			//continue
			;
		}
	}

	//if yes, get item
	fp.seekg(itemStart, ios::beg);
	fp.ignore(fileLength(fp), '\n');
	if (fp.eof())
	{
		fp.clear();
		fp.seekg(0, ios::end);
	}
	tgtLen = int(fp.tellg()) - itemStart;

	buf = new(nothrow) char[tgtLen + 1];
	if (!buf)
		return -1;

	fp.seekg(itemStart, ios::beg);

	istrstream ss(buf, tgtLen);
	fp.get(buf, tgtLen, '\n');
	
	while (ss.get() != '=' && !ss.eof())
		;

	if (ss.eof())
	{
		delete[]buf;
		return 0;
	}

	switch (item_type)
	{
		case TYPE_DOUBLE:
			ss >> *(double *)item_value;
			break;
		case TYPE_INT:
			ss >> *(int *)item_value;
			break;
		case TYPE_CHARACTER:
			ss >> *(char *)item_value;
			break;
		case TYPE_NULL:
			break;
		case TYPE_STRING:
			ss.getline((char *)item_value, tgtLen);
			break;
		default:
			;
	}

	delete[]buf;
	return 1;
}