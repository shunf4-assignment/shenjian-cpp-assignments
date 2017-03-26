/* 1652270 计算机2班 冯舜 */
#include <cstring>
#include <iostream>
using namespace std;

void printUsage(const char * const procName);
bool checkIsAllNum(const char * const str, int * const num);
bool checkIsAllNum(const char * const str, int * const num);
bool checkIsIP(const char * const str);

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		printUsage(argv[0]);
		return 0;
	}
	const int lDef = 100;
	const int nDef = 128;
	const int tDef = 0;
	int l = lDef, n = nDef, t = tDef;
	bool optionsValid = true;
	char *ip = NULL;

	// IP number
	optionsValid = optionsValid && checkIsIP(argv[argc - 1]);
	if (!optionsValid) {
		cout << "IP 地址错误。" << endl;
		ip = (char *)-1;
	}
	else
	{
		ip = argv[argc - 1];
	}

	for (int i = 1; i < argc - 1 && optionsValid; i++)
	{
		if (argv[i][0] == '-')
		{
			//接收到一个参数
			if (strcmp(argv[i], "-l") == 0)
			{
				// -l
				if (i >= argc - 2 || strcmp(argv[i + 1], "-l") == 0 || strcmp(argv[i + 1], "-n") == 0)
				{
					//没有下一个参数了
					cout << "-l: 缺少参数。" << endl;
					optionsValid = false;
					break;
				}
				i++;
				//optionsValid = optionsValid && checkIsAllNum(argv[i], &l);
				//optionsValid = optionsValid && (l >= 64 && l <= 64000);
				if (!(checkIsAllNum(argv[i], &l)&& (l >= 64 && l <= 64000)))
				{
					//cout << "-l: 参数错误。参数必须为 64 - 64000 的整数。" << endl;
					//break;
					l = lDef;
				}
			}
			else if (strcmp(argv[i], "-n") == 0)
			{
				// -n
				if (i >= argc - 2 || strcmp(argv[i + 1], "-l") == 0 || strcmp(argv[i + 1], "-n") == 0)
				{
					//没有下一个参数了
					cout << "-n: 缺少参数。" << endl;
					optionsValid = false;
					break;
				}
				i++;
				//optionsValid = optionsValid && ;
				//optionsValid = optionsValid && (n >= 1 && n <= 10000);
				if (!(checkIsAllNum(argv[i], &n) && (n >= 1 && n <= 10000)))
				{
					//cout << "-n: 参数错误。参数必须为 1 - 10000 的整数。" << endl;
					//break;
					n = nDef;
				}
			}
			else if (strcmp(argv[i], "-t") == 0)
			{
				// -t
				t = 1;
			}
		}
		else // if (argv[i][0] >= '0' && argv[i][0] <= '9')
		{
			;
		}
		/*else
		{
			optionsValid = false;
			break;
		}
		*/
	}
	if (ip == NULL && optionsValid)
	{
		cout << "错误：未输入 IP 地址。" << endl;
		optionsValid = false;
	}
	if (!optionsValid)
	{
		printUsage(argv[0]);
		return 1;
	}
	else
	{
		cout << "ping " << ip << " 成功。";
		cout << "l 值为：" << l << ", n 值为：" << n << ", t 值为：" << t << "。" << endl;
	}
	return 0;
}

void printUsage(const char * const procName)
{
	cout << "用法：" << endl;
	cout << "" << procName << " [-l 大小 = 100] [-n 数量 = 128] [-t] 127.0.0.1" << endl;
	return;
}

bool checkIsAllNum(const char * const str, int * const num)
{
	if (strlen(str) == 0)
	{
		return false;
	}
	for (const char *p = str; *p; p++)
	{
		if (!(*p >= '0' && *p <= '9'))
		{
			return false;
		}
	}
	if(num)
		*num = atoi(str);
	return true;
}

bool checkIsIP(const char * const str)
{
	const char *start = str;
	const char *end = str;
	int segment = 0;
	int thisSeg;
	if (strlen(str) == 0)
		return false;
	for (; segment < 4; segment++)
	{
		for (; *end; end++)
		{
			if (!(*end >= '0' && *end <= '9'))
			{
				break;
			}
		}
		if (end - start <= 0 || end - start >= 4)
		{
			return false;
		}
		if (*end != '.')
		{
			if (segment == 3 && *end == '\0')
			{
				;
			}
			else
				return false;
		}
		else
		{
			end++;
		}
		thisSeg = atoi(start);
		if (thisSeg < 0 || thisSeg > 255)
		{
			return false;
		}
		start = end;
	}
	return true;
}