/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include "7-b17-2.h"

void back(FILE *fp)
{
	int currPos;
	currPos = int(ftell(fp));
	fseek(fp, currPos - 1, SEEK_SET);

}

void debugCheck(FILE *fp)
{
	char c;
	int backNum = 0;
	cout << endl;
	cout << "eof: " << int(feof(fp)) << endl;
	cout << "error: " << int(ferror(fp)) << endl;
	cout << "tell: " << int(ftell(fp)) << endl;
	c = fgetc(fp);
	
	cout << "peek1: " << c;
	cout << "(" << int(c) << ")" << endl;
	if (!feof(fp))
		backNum++;
	cout << "tell: " << int(ftell(fp)) << endl;
	c = fgetc(fp);
	cout << "peek2: " << c;
	cout << "(" << int(c) << ")" << endl;
	if (!feof(fp))
		backNum++;
	for (;backNum > 0; backNum--)
		back(fp);
	cout << "tell: " << int(ftell(fp)) << endl;

	//getchar();
}

void fignore(FILE *f, char delim)
{
	char c;
	while (!feof(f))
	{
		c = fgetc(f);
		if (c == delim)
			break;
	}
}

void print(FILE *fp)
{
	char c;
	clearerr(fp);
	fseek(fp, 0, SEEK_SET);
	c = fgetc(fp);
	while (!feof(fp))
	{
		putchar(c);
		c = fgetc(fp);
	}
	clearerr(fp);
}

void resize(int size)
{
	int fh;
	if (_sopen_s(&fh, fileName, _O_RDWR | _O_CREAT, SH_DENYNO, _S_IREAD | _S_IWRITE) == 0)
	{
		_chsize(fh, size);
	}
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


int loopUntilNotEmpty(FILE *f, const char * emptyCharList)
{
	//loop until get a non-empty char
	//returns true if ever got an empty char; false if never
	char probe;
	int everEmpty = 0;

	probe = fgetc(f);
	for (; !feof(f);)
	{
		if (!isThisCharEmpty(probe, emptyCharList))
		{
			back(f);
			break;
		}
		else
		{
			everEmpty = 1;
		}
		probe = fgetc(f);
	}
	return everEmpty;
}

char * loopUntilNotEmpty(const char *f, const char * emptyCharList)
{
	//loop until get a non-empty char
	char probe;
	const char *p = f;

	probe = *p;
	for (; probe;)
	{
		if (!isThisCharEmpty(probe, emptyCharList))
		{
			break;
		}
		probe = *(++p);
	}
	return (char *)p;
}

int loopBackUntilNotEmpty(FILE *f, const char * emptyCharList)
{
	//loop back until get a non-empty char
	//returns true if ever got an empty char; false if never
	char probe;
	int everEmpty = 0;

	back(f);
	probe = fgetc(f);
	back(f);

	for (; int(ftell(f)) >= 0;)
	{
		if (!isThisCharEmpty(probe, emptyCharList))
		{
			break;
		}
		else
		{
			everEmpty = 1;
		}
		back(f);
		probe = fgetc(f);
		back(f);
	}

	clearerr(f);
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

int fileLength(FILE *fp)
{
	int fileLen, originPos;
	originPos = int(ftell(fp));
	clearerr(fp);

	fseek(fp, 0, SEEK_END);
	fileLen = int(ftell(fp));
	fseek(fp, originPos, SEEK_SET);

	clearerr(fp);

	return fileLen;
}


int whereIsThisGroup(FILE *fp, const char *group_name)
{
	//if not found, return -2
	int nowLineLen;
	int fileLen;
	int result = -2;
	char *currLine, *toMatch;
	int groupHead = 0;



	//create string that stores target group tag
	toMatch = (char * )malloc((strlen(group_name) + 5) * sizeof(char));
	strcpy(toMatch, "[");
	strcat(toMatch, group_name);
	strcat(toMatch, "]\n");

	fileLen = fileLength(fp);

	fseek(fp, 0, SEEK_SET);

	while (!feof(fp))
	{
		//get the length of this line
		groupHead = int(ftell(fp));

		fignore(fp, '\n');

		if (feof(fp))
		{
			clearerr(fp);
			fseek(fp, 0, SEEK_END);
		}

		nowLineLen = int(ftell(fp)) - groupHead; 

		if (nowLineLen < 0)
			nowLineLen = 0;

		fseek(fp, groupHead, SEEK_SET);
		currLine = (char *)calloc((nowLineLen + 1), sizeof(char));

		if (!currLine)
		{
			free(toMatch);
			return -1;
		}

		//read in this line
		fread(currLine, nowLineLen,1 , fp);

		currLine[nowLineLen] = '\0';
		if (almostTheSame(currLine, toMatch))
		{
			result = groupHead;
			free(currLine);
			break;
		}
		free(currLine);

		fgetc(fp);
		//debugCheck(fp);
		if (!feof(fp))
		{
			back(fp);
		}
		else
		{
			break;
		}
	}

	free(toMatch);
	clearerr(fp);
	return result;
}

int whereIsNextGroup(FILE *fp)
{
	//if not found, return -2
	int result = -2;
	int groupHead = 0;

	//skip current line

	fignore(fp, '\n');
	fgetc(fp);
	if (!feof(fp))
	{
		back(fp);
	}
	else
	{
		return result;
	}
	while (!feof(fp))
	{
		groupHead = int(ftell(fp));
		loopUntilNotEmpty(fp, emptyCharWithoutNewLine);

		if (fgetc(fp) == '[')
		{
			back(fp);
			result = groupHead;
			break;
		}

		back(fp);
		fignore(fp, '\n');
		fgetc(fp);
		if (!feof(fp))
		{
			back(fp);
		}
		else
		{
			break;
		}
	}

	clearerr(fp);
	return result;
}


int whereIsThisItem(FILE * fp, const char * item_name)
{
	//if not found, return -2
	int nowLineLen;
	int result = -2;
	char *currLine, *cLTdu;
	int groupHead = 0;


	fgetc(fp);

	while (!feof(fp) && result == -2)
	{
		groupHead = int(ftell(fp));
		fignore(fp, '\n');
		nowLineLen = int(ftell(fp)) - groupHead ;
		if (nowLineLen < 0)
			nowLineLen = 0;
		if (feof(fp))
		{
			clearerr(fp);
			fseek(fp, 0, SEEK_END);
		}

		fseek(fp, groupHead, SEEK_SET);
		currLine = (char *)calloc((nowLineLen + 1), sizeof(char));

		if (!currLine)
		{
			return -1;
		}


		fread(currLine, nowLineLen, 1, fp);

		cLTdu = loopUntilNotEmpty(currLine, emptyCharWithoutNewLine);

		if (*cLTdu == '[')
		{
			//next Group
			free(currLine);
			break;
		}
		
		char *p = cLTdu;
		while (*p)
		{
			if (*p == '=')
			{
				*p = '\0';
				break;
			}
			p++;
		}
		if (!strcmp(cLTdu, item_name))
		{
			//found this item
			result = groupHead;

		}
		free(currLine);
		fgetc(fp);
		if (!feof(fp))
		{
			back(fp);
		}
		else
		{
			break;
		}
	}
	clearerr(fp);
	return result;
}

char *makeItem(const char * item_name, const void *item_value, enum ITEM_TYPE item_type)
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

	strcpy(buf, item_name);
	strcat(buf, "=");

	char *p = buf + strlen(buf);
	switch (item_type)
	{
		case TYPE_DOUBLE:
			sprintf(p, "%g\n", *(double *)item_value);
			break;
		case TYPE_INT:
			sprintf(p, "%d\n", *(int *)item_value);
			break;
		case TYPE_CHARACTER:
			sprintf(p, "%c\n", *(char *)item_value);
			break;
		case TYPE_NULL:
			sprintf(p, "\n");
			break;
		case TYPE_STRING:
			sprintf(p, "%s\n", (char *)item_value);
			break;
		default:
			;
	}
	return buf;
}

int tail_move_inside(FILE *fp, int from, int to)
{
	int jumpOut, lastCount;
	int groupFormer, groupLatter, lastFormer;
	char block[LEN_BLOCK + 1] = { 0 };

	jumpOut = 0;

	groupFormer = to;
	groupLatter = from;

	while (!jumpOut)
	{
		fseek(fp, groupLatter, SEEK_SET);
		
		lastCount = int(fread(block, 1, LEN_BLOCK, fp));

		if (lastCount < LEN_BLOCK)
		{
			clearerr(fp);
			jumpOut = 1;
		}
		fseek(fp, groupFormer, SEEK_SET);
		fwrite(block, lastCount, 1, fp);

		lastFormer = groupFormer;
		groupFormer = int(ftell(fp));
		groupLatter = groupFormer - lastFormer + groupLatter;
	}
	fflush(fp);
	resize(groupFormer);
	return 0;
}

int tail_move_outside(FILE *fp, int from, int to)
{
	int jumpOut;
	int groupFormer, groupLatter;
	int tailSize;
	char *tail;

	jumpOut = 0;

	groupFormer = from;
	groupLatter = to;

	fseek(fp, 0, SEEK_END);
	tailSize = int(ftell(fp)) - groupFormer + 1;
	tail = (char*)calloc((tailSize + 2),sizeof(char));
	if (!tail)
		return -1;
	fseek(fp, groupFormer, SEEK_SET);

	tailSize = int(fread(tail, 1, tailSize, fp));
	

	clearerr(fp);
	fseek(fp, groupLatter, SEEK_SET);
	fwrite(tail, tailSize, 1, fp);
	fflush(fp);
	free(tail);
	return 0;
}

int group_add(FILE *fp, const char *group_name)
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
		toMatch = (char *)calloc(strlen(group_name) + 5, sizeof(char));
		strcpy(toMatch, "[");
		strcat(toMatch, group_name);
		strcat(toMatch, "]\n");
		fseek(fp, 0, SEEK_END);
		fputc('\n', fp);
		fwrite(toMatch, strlen(toMatch), 1, fp);

		free(toMatch);
	}
	fflush(fp);

	return 1;
}

int group_del(FILE *fp, const char *group_name)
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

	fseek(fp, groupStart, SEEK_SET);
	//if yes, del group
	groupNext = whereIsNextGroup(fp);	//may return -2 as the file position identifier, but it doesn't matter

	status = tail_move_inside(fp, groupNext, groupStart);
	if (status < 0)
		return 0;

	return 1;
}

int item_add(FILE *fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
{
	int groupStart, groupNext, pointerCur, itemStart;
	char *buf;

	groupStart = whereIsThisGroup(fp, group_name);
	if (groupStart == -1)
		return -1;
	else if (groupStart < 0)
		return 0;

	fseek(fp, groupStart, SEEK_SET);

	groupNext = whereIsNextGroup(fp);
	if (groupNext == -2)
	{
		fseek(fp, 0, SEEK_END);
		groupNext = int(ftell(fp));
	}
	clearerr(fp);
	fseek(fp, groupStart, SEEK_SET);

	//check if this item exists
	itemStart = whereIsThisItem(fp, item_name);
	if (itemStart == -1)
		return -1;
	else if (itemStart >= 0)
		return 0;

	fseek(fp, groupNext, SEEK_SET);



	loopBackUntilNotEmpty(fp, emptyChar);

	fignore(fp, '\n');
	if (feof(fp))
	{
		clearerr(fp);
		fseek(fp, 0, SEEK_END);
		fputc('\n', fp);
	}
	pointerCur = int(ftell(fp));

	buf = makeItem(item_name, item_value, item_type);
	if (!buf)
		return -1;

	tail_move_outside(fp, pointerCur, pointerCur + strlen(buf));
	
	fseek(fp, pointerCur, SEEK_SET);
	
	fwrite(buf, strlen(buf), 1, fp);

	fflush(fp);
	free(buf);
	return 1;
}


int item_del(FILE *fp, const char *group_name, const char *item_name)
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

	fseek(fp, groupStart, SEEK_SET);

	//check if this item exists
	itemStart = whereIsThisItem(fp, item_name);
	if (itemStart == -1)
		return -1;
	else if (itemStart < 0)
		return 0;

	//if yes, del item
	fseek(fp, itemStart, SEEK_SET);
	fignore(fp, '\n');
	if (feof(fp))
	{
		clearerr(fp);
		fseek(fp, 0, SEEK_END);
	}
	itemNext = int(ftell(fp));

	status = tail_move_inside(fp, itemNext, itemStart);
	if (status < 0)
		return 0;

	return 1;
}

int item_update(FILE *fp, const char *group_name, const char *item_name, const void *item_value, const enum ITEM_TYPE item_type)
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

	fseek(fp, groupStart, SEEK_SET);

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
	fseek(fp, itemStart, SEEK_SET);
	fignore((fp), '\n');
	if (feof(fp))
	{
		clearerr(fp);
		fseek(fp, 0, SEEK_END);
	}
	itemNext = int(ftell(fp));

	buf = makeItem(item_name, item_value, item_type);
	if (!buf)
		return -1;

	itemNextNew = itemStart + strlen(buf);

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

	fseek(fp, itemStart, SEEK_SET);
	fwrite(buf, strlen(buf), 1, fp);

	fflush(fp);
	free(buf);
	return 1;
}

int item_get_value(FILE *fp, const char *group_name, const char *item_name, void *item_value, const enum ITEM_TYPE item_type)
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

	fseek(fp, groupStart, SEEK_SET);

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
	fseek(fp, itemStart, SEEK_SET);
	fignore((fp), '\n');
	if (feof(fp))
	{
		clearerr(fp);
		fseek(fp, 0, SEEK_END);
	}
	tgtLen = int(ftell(fp)) - itemStart;

	buf = (char *)calloc(tgtLen + 1, sizeof(char));
	if (!buf)
		return -1;

	fseek(fp, itemStart, SEEK_SET);

	char *p = buf;
	while (!feof(fp))
	{
		char c = fgetc(fp);
		*p++ = c;
		if (c == '\n' || c == '\r')
		{
			*(p - 1) = '\0';
			break;
		}
	}

	p = buf;
	while (*p != '=' && *p)
	{
		p++;
	}

	if (!(*p))
	{
		free(buf);
		return 0;
	}

	p++;
	switch (item_type)
	{
		case TYPE_DOUBLE:
			sscanf(p, "%lg", (double *)item_value);
			break;
		case TYPE_INT:
			sscanf(p, "%d", (int *)item_value);
			break;
		case TYPE_CHARACTER:
			sscanf(p, "%c", (char *)item_value);
			break;
		case TYPE_NULL:
			break;
		case TYPE_STRING:
			sscanf(p, "%s", (char *)item_value);
			break;
		default:
			;
	}

	free(buf);
	return 1;
}