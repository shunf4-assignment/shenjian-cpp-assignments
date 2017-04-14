/* 1652270 计算机2班 冯舜 */
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <fcntl.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <stdio.h>  
#include <share.h> 
#include <io.h>
#include <windows.h>

#define MODE_CHECK_TITLE (1 << 2)
#define MODE_REPLACE (1 << 1)
#define MODE_INVALID_PARAM (1)
#define MODE_IS_ALL (1 << 3)
#define CHECK_INVALID 1
#define CHECK_CLASSGOOD 1<<1
#define CHECK_NAMEGOOD 1<<2
#define CHECK_NOGOOD 1<<3
#define CHECK_INCOMPLETE 1<<4
#define CHECK_PASS 0
#define LEN_MAX_CLASSNO 15
#define LEN_MAX_FILENAME 31
#define LEN_MAX_NAME 8
#define LEN_MAX_CLASSNAME 16

#define true 1
#define false 0

const char * const exts[] = { ".cpp", ".c", ".h", NULL };
const char emptyChar[] = { '\t', ' ', '\n', '\r', '\0' };
const char emptyCharWithoutNewLine[] = { '\t', ' ',  '\0' };
const char emptyCharWithStar[] = { '\t', ' ', '\n', '\r', '*', '\0' };
const char intMain[] = "int main\t()\t{";

int checkParam(int argc, char **argv);
void printUsage(char **argv);
int doThings(const char * const classNo, const char * const fileName, const char * replName, int all, int replace);
void printNotValidExt(const char * const filename);
int checkThisFileFun(FILE **f, const char *stuNo, const char * stuName, const char(*className)[LEN_MAX_CLASSNAME + 1]);
void checkThisFile(FILE **objFin, const char *objFileName, const char *shortFileName, const char *stuNo, const char*stuName, const char(*className)[LEN_MAX_CLASSNAME + 1]);
int replaceThisFile(FILE **objF, const char *replString, const char * objFileName, const char * fileName, const char * stuNo, const char * stuName);

int main(int argc, char **argv)
{
	int status;

	status = checkParam(argc, argv);
	if (status & MODE_INVALID_PARAM)
	{
		return 1;
	}

	if (status & MODE_CHECK_TITLE)
	{
		if (status & MODE_IS_ALL)
		{
			status = doThings(argv[2], NULL, NULL, true, false);
		}
		else
		{
			status = doThings(argv[2], argv[3], NULL, false, false);
		}
	}
	else if (status & MODE_REPLACE)
	{
		status = doThings(argv[2], argv[3], argv[4], false, true);
	}

	return 0;
}

int checkParam(int argc, char **argv)
{
	//check if parameters are valid by number of args and pointers of args
	//returns mode code
	int status = 0;
	int unableToUnderstand = false;
	if (argc != 4 && argc != 5)
	{
		unableToUnderstand = true;
	}
	else if (argc == 4 && strcmp(argv[1], "-checktitle") != 0)
	{
		unableToUnderstand = true;
	}
	else if (argc == 5 && strcmp(argv[1], "-replace") != 0)
	{
		unableToUnderstand = true;
	}
	if (unableToUnderstand)
	{
		printUsage(argv);
		status |= MODE_INVALID_PARAM;
		return status;
	}

	//check title
	if (argc == 4)
	{
		int notValidExt = true;
		int fileValid = true;
		const char *q;
		status |= MODE_CHECK_TITLE;
		if (strcmp(argv[3], "all") == 0)
		{
			status |= MODE_IS_ALL;
		}
		else
		{
			for (const char * const * p = exts; *p && notValidExt; p++)
			{
				if ((q = strstr(argv[3], *p)) != NULL && (argv[3] + strlen(argv[3]) - q) == strlen(*p))
				{
					notValidExt = false;
				}
			}

			if (strlen(argv[2]) > LEN_MAX_CLASSNO)
			{
				fileValid = false;
			}
			if (strlen(argv[3]) > LEN_MAX_FILENAME)
			{
				fileValid = false;
			}

			if (notValidExt)
			{
				printNotValidExt(argv[3]);
				printUsage(argv);
				status |= MODE_INVALID_PARAM;
				return status;
			}

			if (!fileValid)
			{
				//cout << "Length of Class No(" << LEN_MAX_CLASSNO << ") or File Name(" << LEN_MAX_FILENAME << ") out of range!" << endl;
				printf("Length of Class No(%d) or File Name(%d) out of range!", LEN_MAX_CLASSNO, LEN_MAX_FILENAME);
				status |= MODE_INVALID_PARAM;
				return status;
			}

		}
		return status;
	}
	//replace
	else
	{
		int fileValid = true;
		status |= MODE_REPLACE;

		if (strlen(argv[2]) > LEN_MAX_CLASSNO)
		{
			fileValid = false;
		}
		if (strlen(argv[3]) > LEN_MAX_FILENAME || strlen(argv[4]) > LEN_MAX_FILENAME)
		{
			fileValid = false;
		}
		if (!fileValid)
		{
			//cout << "Length of Class No(" << LEN_MAX_CLASSNO << ") or File Name(" << LEN_MAX_FILENAME << ") out of range!" << endl;
			printf("Length of Class No(%d) or File Name(%d) out of range!", LEN_MAX_CLASSNO, LEN_MAX_FILENAME);
			status |= MODE_INVALID_PARAM;

		}
		return status;
	}

}

void printUsage(char **argv)
{
	printf("Usage: \nTo check title: %s -checktitle 100384 3-b1.cpp/all\nTo replace main function: %s -replace 100384 4-2.cpp 4-2-m.cpp\n", argv[0], argv[0]);
	/*cout << "Usage: " << endl;
	cout << "To check title: " << argv[0] << " -checktitle 100384 3-b1.cpp/all" << endl;
	cout << "To replace main function: " << argv[0] << " -replace 100384 4-2.cpp 4-2-m.cpp" << endl;*/
}

void printNotValidExt(const char * const filename)
{
	printf("Error: %s is not a valid source file.\n", filename);
	//cout << "Error: " << filename << " is not a valid source file." << endl;
}



void checkThisFile(FILE **objFin, const char *objFileName, const char *shortFileName, const char *stuNo, const char*stuName, const char(*className)[LEN_MAX_CLASSNAME + 1])
{
	int status;
	(*objFin) = fopen(objFileName, "rb");
	printf("学生 %s - %s \t%s  \t: ", stuNo, stuName, shortFileName);
	//cout << "学生 " << stuNo << " - " << stuName << " \t" << shortFileName << "  \t: ";
	if (!(*objFin))
	{
		printf("文件不存在或无法打开");
	}
	else
	{
		status = checkThisFileFun(objFin, stuNo, stuName, className);
		if (status == CHECK_INVALID)
		{
			printf("未取到首行信息");
		}
		else
		{
			if (status & CHECK_INCOMPLETE)
			{
				printf("首行信息不全");
			}
			else
			{
				if (!(status & CHECK_CLASSGOOD))
				{
					printf("班级不匹配 ");
				}
				if (!(status & CHECK_NOGOOD))
				{
					printf("学号不匹配 ");
				}
				if (!(status & CHECK_NAMEGOOD))
				{
					printf("姓名不匹配 ");
				}
				if (status == (CHECK_CLASSGOOD | CHECK_NOGOOD | CHECK_NAMEGOOD))
					printf("通过");
			}
		}
		fclose((*objFin));
	}
	printf("\n");
}

int doThings(const char * const classNo, const char * const fileName, const char * replName, int all, int replace)
{
	FILE * fin;
	FILE * objFin;
	FILE * repFin;
	int status;
	char dataFileName[LEN_MAX_FILENAME + 14] = { 0 };
	char replFileName[LEN_MAX_FILENAME + 14] = { 0 };
	char objFileName[LEN_MAX_FILENAME + LEN_MAX_CLASSNO * 2 + 20] = { 0 };
	char stuNo[LEN_MAX_CLASSNO + 1] = { 0 };
	char stuName[LEN_MAX_NAME + 1] = { 0 };
	char className[2][LEN_MAX_CLASSNAME + 1] = { 0 };
	char *replString;
	strcpy(dataFileName, ".\\source\\");
	strcat(dataFileName, classNo);
	strcat(dataFileName, ".dat");
	fin = fopen(dataFileName, "r");
	if (!fin)
	{
		printf("%s not exist.\n", dataFileName);
		return -2;
	}
	if (replace)
	{
		int replLen = 0;
		strcpy(replFileName, ".\\source\\");
		strcat(replFileName, replName);
		repFin = fopen(replFileName, "rb");
		if (!repFin)
		{
			printf("%s not exist.\n", replFileName);
			return -2;
		}

		fseek(repFin, 0, SEEK_END);
		replLen = (unsigned)(ftell(repFin));

		replString = (char *)malloc(sizeof(char) * (replLen + 1));  //replString = new(nothrow) char[replLen + 1];
		if (!replString)
		{
			printf("Memory allocation failed.\n");
			return -1;
		}
		fseek(repFin, 0, SEEK_SET);
		fread(replString, 1, replLen, repFin);
		replString[replLen] = '\0';
		replLen = replLen;
	}
	for (; !feof(fin);)
	{
		//fin >> stuNo >> stuName >> className[0] >> className[1];
		fscanf(fin, "%s", &stuNo);
		fscanf(fin, "%s", &stuName);
		fscanf(fin, "%s", className);
		fscanf(fin, "%s", className + 1);
		if (feof(fin))
			break;
		strcpy(objFileName, ".\\source\\");
		strcat(objFileName, classNo);
		strcat(objFileName, "-");
		strcat(objFileName, stuNo);
		strcat(objFileName, "\\");
		if (replace)
		{
			strcat(objFileName, fileName);
			status = replaceThisFile(&objFin, replString, objFileName, fileName, stuNo, stuName);
		}
		else if (all)
		{
			HANDLE file;
			WIN32_FIND_DATA fileData;
			//strcat(objFileName, "*");
			int objFileNamePos = strlen(objFileName);

			for (const char * const * p = exts;; p++)
			{
				if (!(*p))
					break;
				strcpy(objFileName + objFileNamePos, "*");
				strcpy(objFileName + objFileNamePos + 1, *p);
				file = FindFirstFile(objFileName, &fileData);
				if (INVALID_HANDLE_VALUE == file)
				{
					continue;
				}
				do
				{
					strcpy(objFileName + objFileNamePos, fileData.cFileName);
					checkThisFile(&objFin, objFileName, fileData.cFileName, stuNo, stuName, className);
				} while (FindNextFile(file, &fileData));
			}
		}
		else
		{
			strcat(objFileName, fileName);
			checkThisFile(&objFin, objFileName, fileName, stuNo, stuName, className);
		}

	}

	fclose(fin);
	
	if (replace)
	{
		fclose(repFin);
		free(replString);
	}
		

	return 0;
}

int loopUntilNotEmpty(FILE *f, const char * emptyCharList)
{
	//loop until get a non-empty char
	//returns true if ever got an empty char; false if never
	char probe;
	int probeNotEmpty;
	int everEmpty = false;

	for (; !feof(f);)
	{
		probe = fgetc(f);
		fseek(f, -1, SEEK_CUR);
		probeNotEmpty = true;
		for (const char *p = emptyCharList; *p && !feof(f); p++)
		{
			if (probe == *p)
			{
				probeNotEmpty = false;
				(!everEmpty) && (everEmpty = true);
				break;
			}
		}
		if (probeNotEmpty)
		{
			break;
		}
		fseek(f, 1, SEEK_CUR);
	}
	return everEmpty;
}
void readUntilEmpty(FILE *f, char *buffer, const char * emptyCharList)
{
	//read until get a empty char
	char probe;
	int probeNotEmpty;

	for (char *b = buffer; !feof(f); b++)
	{
		probe = fgetc(f);
		fseek(f, -1, SEEK_CUR);
		probeNotEmpty = true;
		for (const char *p = emptyCharList; *p && !feof(f); p++)
		{
			if (probe == *p)
			{
				probeNotEmpty = false;
				break;
			}
		}

		if (probeNotEmpty)
		{
			*b = probe;
		}
		else
		{
			*b = '\0';
			break;
		}
		fseek(f, 1, SEEK_CUR);
	}
}

int checkThisFileFun(FILE **f, const char *stuNo, const char * stuName, const char(*className)[LEN_MAX_CLASSNAME + 1])
{
	char probe;
	int status = 0;
	int classGood = false, nameGood = false, noGood = false, hasTail = false;
	char getInput[LEN_MAX_CLASSNAME + 50] = { 0 };
	int entryCount = 0;

	loopUntilNotEmpty((*f), emptyChar);
	probe = fgetc((*f));
	if (feof((*f)) || probe != '/')
	{
		status |= CHECK_INVALID;
		return status;
	}
	probe = fgetc((*f));
	if (probe != '*' && probe != '/')
	{
		status |= CHECK_INVALID;
		return status;
	}
	else
	{
		if (probe == '*')
			hasTail = true;
	}
	for (int i = 0; i < 3 && !feof((*f)); i++)
	{
		loopUntilNotEmpty((*f), emptyCharWithoutNewLine);
		readUntilEmpty((*f), getInput, emptyCharWithStar);
		if (strlen(getInput))
			entryCount++;
		if (strcmp(getInput, stuName) == 0)
		{
			//name satisfied
			nameGood = true;
			status |= CHECK_NAMEGOOD;

		}
		else if (strcmp(getInput, stuNo) == 0)
		{
			//no satisfied
			status |= CHECK_NOGOOD;

		}
		else if (strstr(getInput, className[0]) || strstr(getInput, className[1]))
		{
			//className satisfied
			status |= CHECK_CLASSGOOD;

		}
	}
	if (entryCount < 3)
		status |= CHECK_INCOMPLETE;
	return status;
}

int replaceThisFile(FILE **objF, const char *replString, const char * objFileName, const char * fileName, const char * stuNo, const char * stuName)
{
	//int status;
	*objF = fopen(objFileName, "rb+");
	printf("学生 %s - %s \t%s  \t: ", stuNo, stuName, fileName);
	if (!(*objF))
	{
		printf("文件不存在或无法打开");
	}
	else
	{
		//look for "int main()"
		int intPos = -1;
		char c;
		const char *check = intMain;
		while (!feof((*objF)))
		{
			c = fgetc((*objF));
			if (*check == '\0')
			{
				break;
			}
			else if (*check == ' ')
			{
				fseek((*objF), -1, SEEK_CUR);
				//must have emptychar
				if (!loopUntilNotEmpty((*objF), emptyChar))
				{
					intPos = -1;
					check = intMain;
				}
				else
				{
					check++;
				}
			}
			else if (*check == '\t')
			{
				//may have empty char
				fseek((*objF), -1, SEEK_CUR);
				loopUntilNotEmpty((*objF), emptyChar);
				check++;
			}
			else
			{
				if (c == *check)
				{
					if (intPos == -1)
						intPos = ftell((*objF));
					check++;
				}
				else
				{
					intPos = -1;
					check = intMain;
				}
			}
		}
		if (intPos == -1)
		{
			//int main() not Found
			printf("没有检测到int main()");
			fclose((*objF));

		}
		else
		{
			fseek((*objF), intPos - 1, SEEK_SET);
			fwrite(replString, 1, strlen(replString), (*objF));
			fclose((*objF));

			//objF.write(replString, strlen(replString));
			//int newLen = (int)(ftell((*objF)));
			int newLen = intPos - 1 + strlen(replString);
			//experimental::filesystem::resize_file(objFileName, newLen);
			int fh;
			if (_sopen_s(&fh, objFileName, _O_RDWR | _O_CREAT, SH_DENYNO, _S_IREAD | _S_IWRITE) == 0)
			{
				printf("%d -> %d ", _filelength(fh), newLen);
				if (_chsize(fh, newLen) == 0)
				{
					printf("替换成功(%d)", _filelength(fh));
				}
				else
				{
					printf("更改文件长度失败");
				}
			}
			else
			{

				printf("更改文件长度时打开失败");
			}
		}
		
	}
	printf("\n");
	return 0;
}