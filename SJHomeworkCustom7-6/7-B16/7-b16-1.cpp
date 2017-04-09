/* 1652270 计算机2班 冯舜 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
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

const char * const exts[] = { ".cpp", ".c", ".h", NULL };
const char emptyChar[] = { '\t', ' ', '\n', '\r', '\0' };
const char emptyCharWithoutNewLine[] = { '\t', ' ',  '\0' };
const char emptyCharWithStar[] = { '\t', ' ', '\n', '\r', '*', '\0' };
int checkParam(int argc, char **argv);
void printUsage(char **argv);
int checkTitle(const char * const classNo, const char * const fileName);
int checkFileTitle(ifstream &f, const char *stuNo, const char * stuName, const char * className0, const char * className1)
;
void printNotValidExt(const char * const filename);
int checkTitleAll(const char * const classNo);
int replaceMain(const char * const classNo, const char * const fileName, const char * const repName);

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
			status = checkTitleAll(argv[2]);
		}
		else
		{
			status = checkTitle(argv[2], argv[3]);
		}
	}
	else if (status & MODE_REPLACE)
	{
		status = replaceMain(argv[2], argv[3], argv[4]);
	}

	return 0;
}

int checkParam(int argc, char **argv)
{
	//check if parameters are valid by number of args and pointers of args
	//returns mode code
	int status = 0;
	bool unableToUnderstand = false;
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
		bool notValidExt = true;
		bool fileValid = true;
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
				if ((q = strstr(argv[3], *p)) == NULL || (argv[3] + strlen(argv[3]) - q) != strlen(*p))
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
				cout << "Length of Class No(" << LEN_MAX_CLASSNO << ") or File Name(" << LEN_MAX_FILENAME << ") out of range!" << endl;
				status |= MODE_INVALID_PARAM;
				return status;
			}
			
		}
		return status;
	}
	//replace
	else
	{
		bool fileValid = true;
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
			cout << "Length of Class No(" << LEN_MAX_CLASSNO << ") or File Name(" << LEN_MAX_FILENAME << ") out of range!" << endl;
			status |= MODE_INVALID_PARAM;
			
		}
		return status;
	}
	
}

void printUsage(char **argv)
{
	cout << "Usage: " << endl;
	cout << "To check title: " << argv[0] << " -checktitle 100384 3-b1.cpp/all" << endl;
	cout << "To replace main function: " << argv[0] << " -replace 100384 4-2.cpp 4-2-m.cpp" << endl;
}

void printNotValidExt(const char * const filename)
{
	cout << "Error: " << filename << " is not a valid source file." << endl;
}

int checkTitleAll(const char * const classNo)
{
	return 0;
}

int replaceMain(const char * const classNo, const char * const fileName, const char * const repName)
{
	return 0;
}

int checkTitle(const char * const classNo, const char * const fileName)
{
	ifstream fin;
	ifstream objFin;
	int status;
	char dataFileName[LEN_MAX_FILENAME + 14] = { 0 };
	char objFileName[LEN_MAX_FILENAME + LEN_MAX_CLASSNO * 2 + 20] = { 0 };
	char stuNo[LEN_MAX_CLASSNO + 1] = { 0 };
	char stuName[LEN_MAX_NAME + 1] = { 0 };
	char className[2][LEN_MAX_CLASSNAME + 1] = {0};
	strcpy(dataFileName, ".\\source\\");
	strcat(dataFileName, classNo);
	strcat(dataFileName, ".dat");
	fin.open(dataFileName, ios::in);
	if (fin.is_open() == false)
	{
		cout << dataFileName << " not exist." << endl;
		return -2;
	}
	for (;!fin.eof();)
	{
		fin >> stuNo >> stuName >> className[0] >> className[1];
		strcpy(objFileName, ".\\source\\");
		strcat(objFileName, classNo);
		strcat(objFileName, "-");
		strcat(objFileName, stuNo);
		strcat(objFileName, "\\");
		strcat(objFileName, fileName);
		objFin.open(objFileName, ios::in);
		if (!objFin.is_open())
		{
			cout << "学生 " << stuNo << " - " << stuName << " : 文件不存在或无法打开" << endl;
		}
		else
		{
			status = checkFileTitle(objFin, stuNo, stuName, className[0], className[1]);
			if (status == CHECK_INVALID)
			{
				cout << "学生 " << stuNo << " - " << stuName << " : 未取到首行信息" << endl;
			}
			else
			{
				if (!(status & CHECK_CLASSGOOD))
				{
					cout << "学生 " << stuNo << " - " << stuName << " : 班级不匹配" << endl;
				}
				if (!(status & CHECK_NOGOOD))
				{
					cout << "学生 " << stuNo << " - " << stuName << " : 学号不匹配" << endl;
				}
				if (!(status & CHECK_NAMEGOOD))
				{
					cout << "学生 " << stuNo << " - " << stuName << " : 姓名不匹配" << endl;
				}
				if (status == (CHECK_CLASSGOOD | CHECK_NOGOOD | CHECK_NAMEGOOD))
					cout << "学生 " << stuNo << " - " << stuName << " : 通过" << endl;

			}
			objFin.close();
		}
	}
	return status;
	fin.close();
}

void loopUntilNotEmpty(ifstream &f, const char * emptyCharList)
{
	//loop until get a non-empty char
	char probe;
	bool probeNotEmpty;

	for (; !f.eof();)
	{
		probe = f.peek();
		probeNotEmpty = true;
		for (const char *p = emptyCharList; *p && !f.eof(); p++)
		{
			if (probe == *p)
			{
				probeNotEmpty = false;
				break;
			}
		}
		if (probeNotEmpty)
		{
			break;
		}
		f.get();
	}
}
void readUntilEmpty(ifstream &f, char *buffer, const char * emptyCharList)
{
	//read until get a empty char
	char probe;
	bool probeNotEmpty;

	for (char *b = buffer; !f.eof();b++)
	{
		probe = f.peek();
		probeNotEmpty = true;
		for (const char *p = emptyCharList; *p && !f.eof(); p++)
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
		f.get();
	}
}

int checkFileTitle(ifstream &f, const char *stuNo, const char * stuName, const char * className0, const char * className1)
{
	char probe;
	int status = 0;
	bool classGood = false, nameGood = false, noGood = false, hasTail = false;
	char getInput[LEN_MAX_CLASSNAME + 50] = { 0 };
	int entryCount = 0;
	//char commentTail[6] = { 0 };

	loopUntilNotEmpty(f, emptyChar);
	probe = f.get();
	if (f.eof() || probe != '/')
	{
		status |= CHECK_INVALID;
		return status;
	}
	probe = f.get();
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
	for (int i = 0; i < 3 && !f.eof(); i++)
	{
		loopUntilNotEmpty(f, emptyCharWithoutNewLine);
		readUntilEmpty(f, getInput, emptyCharWithStar);
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
		else if (strstr(getInput, className1) || strstr(getInput, className0))
		{
			//className satisfied
			status |= CHECK_CLASSGOOD;

		}
	}
	/*
	if (hasTail)
	{
		loopUntilNotEmpty(probe, f);
		commentTail[0] = probe;
		commentTail[1] = f.get();
		if (strcmp(commentTail, "\x2a/") != 0)
		{
			return CHECK_INVALID;
		}
	}
	*/
	return status;
}