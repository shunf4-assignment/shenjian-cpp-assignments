/* 1652270 计算机2班 冯舜 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <windows.h>
#include <filesystem>
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
const char intMain[] = "int main\t()\t{";

int checkParam(int argc, char **argv);
void printUsage(char **argv);
int doThings(const char * const classNo, const char * const fileName, const char * replName, bool all, bool replace);
void printNotValidExt(const char * const filename);
int checkThisFileFun(fstream &f, const char *stuNo, const char * stuName, const char(*className)[LEN_MAX_CLASSNAME + 1]);
void checkThisFile(fstream &objFin, const char *objFileName, const char *shortFileName, const char *stuNo, const char*stuName, const char(*className)[LEN_MAX_CLASSNAME + 1]);
int replaceThisFile(fstream&objF, const char *replString, const char * objFileName, const char * fileName, const char * stuNo, const char * stuName);

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



void checkThisFile(fstream &objFin, const char *objFileName, const char *shortFileName, const char *stuNo, const char*stuName, const char(*className)[LEN_MAX_CLASSNAME + 1])
{
	int status;
	objFin.open(objFileName, ios::in | ios::binary);
	cout << "学生 " << stuNo << " - " << stuName << " \t" << shortFileName << "  \t: ";
	if (!objFin.is_open())
	{
		cout << "文件不存在或无法打开";
	}
	else
	{
		status = checkThisFileFun(objFin, stuNo, stuName, className);
		if (status == CHECK_INVALID)
		{
			cout << "未取到首行信息";
		}
		else
		{
			if (status & CHECK_INCOMPLETE)
			{
				cout << "首行信息不全";
			}
			else
			{
				if (!(status & CHECK_CLASSGOOD))
				{
					cout << "班级不匹配 ";
				}
				if (!(status & CHECK_NOGOOD))
				{
					cout << "学号不匹配 ";
				}
				if (!(status & CHECK_NAMEGOOD))
				{
					cout << "姓名不匹配 ";
				}
				if (status == (CHECK_CLASSGOOD | CHECK_NOGOOD | CHECK_NAMEGOOD))
					cout << "通过" ;
			}
		}
		objFin.close();
	}
	cout << endl;
}

int doThings(const char * const classNo, const char * const fileName, const char * replName, bool all, bool replace)
{
	ifstream fin;
	fstream objFin;
	ifstream repFin;
	int status;
	char dataFileName[LEN_MAX_FILENAME + 14] = { 0 };
	char replFileName[LEN_MAX_FILENAME + 14] = { 0 };
	char objFileName[LEN_MAX_FILENAME + LEN_MAX_CLASSNO * 2 + 20] = { 0 };
	char stuNo[LEN_MAX_CLASSNO + 1] = { 0 };
	char stuName[LEN_MAX_NAME + 1] = { 0 };
	char className[2][LEN_MAX_CLASSNAME + 1] = {0};
	char *replString;
	strcpy(dataFileName, ".\\source\\");
	strcat(dataFileName, classNo);
	strcat(dataFileName, ".dat");
	fin.open(dataFileName, ios::in | ios::binary);
	if (fin.is_open() == false)
	{
		cout << dataFileName << " not exist." << endl;
		return -2;
	}
	if (replace)
	{
		int replLen = 0;
		strcpy(replFileName, ".\\source\\");
		strcat(replFileName, replName);
		repFin.open(replFileName, ios::in | ios::binary);
		if (repFin.is_open() == false)
		{
			cout << replFileName << " not exist." << endl;
			return -2;
		}
		
		repFin.seekg(0, ios::end);
		replLen = unsigned(repFin.tellg());

		replString = new(nothrow) char[replLen + 1];
		if (!replString)
		{
			cout << "Memory allocation failed." << endl;
			return -1;
		}
		repFin.seekg(0, ios::beg);
		repFin.read(replString, replLen);
		replString[repFin.gcount()] = '\0';
	}
	for (;!fin.eof();)
	{
		fin >> stuNo >> stuName >> className[0] >> className[1];
		if (fin.eof())
			break;
		strcpy(objFileName, ".\\source\\");
		strcat(objFileName, classNo);
		strcat(objFileName, "-");
		strcat(objFileName, stuNo);
		strcat(objFileName, "\\");
		if (replace)
		{
			strcat(objFileName, fileName);
			status = replaceThisFile(objFin, replString, objFileName, fileName, stuNo, stuName);
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
					checkThisFile(objFin, objFileName, fileData.cFileName, stuNo, stuName, className);
				}
				while (FindNextFile(file, &fileData));
			}
		}
		else
		{
			strcat(objFileName, fileName);
			checkThisFile(objFin, objFileName, fileName, stuNo, stuName, className);
		}
		
	}
	
	fin.close();
	repFin.close();
	if(replace)
		delete[]replString;

	return 0;
}

bool loopUntilNotEmpty(fstream &f, const char * emptyCharList)
{
	//loop until get a non-empty char
	//returns true if ever got an empty char; false if never
	char probe;
	bool probeNotEmpty;
	bool everEmpty = false;

	for (; !f.eof();)
	{
		probe = f.peek();
		probeNotEmpty = true;
		for (const char *p = emptyCharList; *p && !f.eof(); p++)
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
		f.get();
	}
	return everEmpty;
}
void readUntilEmpty(fstream &f, char *buffer, const char * emptyCharList)
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

int checkThisFileFun(fstream &f, const char *stuNo, const char * stuName, const char(*className)[LEN_MAX_CLASSNAME + 1])
{
	char probe;
	int status = 0;
	bool classGood = false, nameGood = false, noGood = false, hasTail = false;
	char getInput[LEN_MAX_CLASSNAME + 50] = { 0 };
	int entryCount = 0;

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

int replaceThisFile(fstream&objF, const char *replString, const char * objFileName, const char * fileName, const char * stuNo, const char * stuName)
{
	//int status;
	objF.open(objFileName, ios::in |ios::out | ios::binary);
	cout << "学生 " << stuNo << " - " << stuName << " \t" << fileName << "  \t: ";
	if (!objF.is_open())
	{
		cout << "文件不存在或无法打开";
	}
	else
	{
		//look for "int main()"
		int intPos = -1;
		char c;
		const char *check = intMain;
		while (!objF.eof())
		{
			c = objF.get();
			if (*check == '\0')
			{
				break;
			}
			else if (*check == ' ')
			{
				objF.seekg((unsigned)objF.tellg() - 1,ios::beg);
				//must have emptychar
				if (!loopUntilNotEmpty(objF, emptyChar))
				{
					intPos = -1;
					check = intMain;
				}
				else
				{
					check++;
				}
			}
			else if(*check == '\t')
			{
				//may have empty char
				objF.seekg((unsigned)objF.tellg() - 1, ios::beg);
				loopUntilNotEmpty(objF, emptyChar);
				check++;
			}
			else
			{
				if (c == *check)
				{
					if(intPos == -1)
						intPos = int(objF.tellg());
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
			cout << "没有检测到int main()";
		}
		else
		{
			objF.seekp(intPos - 1, ios::beg);
			objF.write(replString, strlen(replString));
			int newLen = int(objF.tellp());
			experimental::filesystem::resize_file(objFileName, newLen);
			cout << "替换成功";

		}
		objF.close();
	}
	cout << endl;
	return 0;
}