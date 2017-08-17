/* 1652270 计算机2班 冯舜 */
#include "7-ds-b12-linear_list_L.cpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
using namespace std;

inline int randomInt(int min, int max)
{
	return static_cast<int>(round(rand() / 32768. * (max - min)) + min);
}

template<>
bool isElemEqual<const char *>(const char * const &e1, const char * const  &e2)
{
	return (strcmp(e1, e2) == 0);
}

template<>
bool isElemEqual<char *>(char * const &e1, char * const  &e2)
{
	return isElemEqual(static_cast<const char * const &>(e1), static_cast<const char * const &>(e2));
}

template<>
bool isElemEqual<student *>(student * const &s1, student * const  &s2)
{
	return *s1 == *s2;
}

template<> void elemCopy<char *, const char *>(char *&dstStr, const char * const &srcStr)
{
	try
	{
		elemFree(dstStr);
		unsigned len = strlen(srcStr);
		dstStr = new char[len + 1];
		strcpy_s(dstStr, len + 1, srcStr);
	}
	catch (std::bad_alloc &exp)
	{
		std::cerr << exp.what() << std::endl;
		std::cerr << "系统内存不足，程序无法继续工作。" << std::endl;
		throw exp;
	}
}

template<> void elemCopy<char *, char *>(char *&dstStr, char * const &srcStr)
{
	elemCopy(dstStr, static_cast<const char * const &>(srcStr));
}

template<>
void elemCopy<student *, const student *>(student * &dstStu, const student * const &srcStu)
{
	try
	{
		elemFree(dstStu);
		dstStu = new student{ *srcStu };
	}
	catch (std::bad_alloc &exp)
	{
		std::cerr << exp.what() << std::endl;
		std::cerr << "系统内存不足，程序无法继续工作。" << std::endl;
		throw exp;
	}
}

template<>
void elemCopy<student *, student *>(student * &dstStu, student * const &srcStu)
{
	elemCopy(dstStu, static_cast<const student * const &>(srcStu));
}

std::ostream & operator<<(std::ostream & out, const student *& s);

std::ostream & operator<<(std::ostream & out, student *& s)
{
	out << reinterpret_cast<const student *&>(s);
	return out;
}

template<typename T>
Status myVisit(T e, bool first)
{
	static unsigned times = 0;
	if (first)
	{
		times = 0;
	}
	cout << setw(6) << e << " => ";
	
	times++;
	/*if (times % 10 == 0)
	{
		cout << endl;
	}*/
	return STAT_OK;
}

#define TYPE_INT 0
#define TYPE_DOUBLE1 1
#define TYPE_STRING 2
#define TYPE_PCHAR 3
#define TYPE_STUDENT 4
#define TYPE_PSTUDENT 5

int main()
{
#define TYPE_CURRENT TYPE_PSTUDENT //修改此句
	/*
	*	请将上一句的宏定义改成想要的类型以实现类型切换。
	*	修改后的宏定义将只影响 main 函数中的 typedef 和测试数据的生成和展示，不会变动操作数据的内部过程。
	*/
	stringstream s;
	const int testCount = 15;
	srand(unsigned(time(0)));
#if TYPE_CURRENT == TYPE_INT
	typedef int testType; 
	/* 建立链表数据 */
	for (int i = 0; i < testCount; i++)
		s << (i) << ' ';
	/* 测试locate函数用数据 */
	s << randomInt(1, testCount - 2) << ' ';
	/* 测试pop函数用数据 */
	s << randomInt(1, testCount - 2) << ' ';

#elif TYPE_CURRENT == TYPE_DOUBLE1
	typedef double1 testType;
	/* 建立链表数据 */
	for (int i = 0; i < testCount; i++)
	{
		s << (log2(i +1)) << ' ';
	}
	/* 测试locate函数用数据 */
	s << log2(randomInt(1, testCount - 2) + 1) << ' ';
	/* 测试pop函数用数据 */
	s << randomInt(1, testCount - 2) << ' ';
#elif TYPE_CURRENT == TYPE_STRING
	typedef string testType;
	/* 建立链表数据 */
	stringstream tmp[testCount];
	for (int i = 0; i < testCount; i++)
	{
		tmp[i].clear();
		for (int j = 0; j < 7; j++)
		{
			tmp[i] << char('a' + randomInt(0, 25));
		}
		s << tmp[i].str() << ' ';
	}
	/* 测试locate函数用数据 */
	s << tmp[randomInt(1, testCount - 2)].str() << ' ';
	/* 测试pop函数用数据 */
	s << randomInt(1, testCount - 2) << ' ';
#elif TYPE_CURRENT == TYPE_PCHAR
	typedef char *testType;
	/* 建立链表数据 */
	stringstream tmp[testCount];
	for (int i = 0; i < testCount; i++)
	{
		tmp[i].clear();
		for (int j = 0; j < 5; j++)
		{
			tmp[i] << char('a' + randomInt(0, 25));
		}
		s << tmp[i].str() << ' ';
}
	/* 测试locate函数用数据 */
	s << tmp[randomInt(1, testCount - 2)].str() << ' ';
	/* 测试pop函数用数据 */
	s << randomInt(1, testCount - 2) << ' ';
#elif TYPE_CURRENT == TYPE_STUDENT
	typedef student testType;
	/* 建立链表数据 */
	stringstream name_[testCount];
	char sex_[testCount];
	stringstream addr_[testCount];
	for (int i = 0; i < testCount; i++)
	{
		s << i << ' ';
		for (int j = 0; j < 5; j++)
		{
			name_[i] << char('a' + randomInt(0, 25));
		}
		sex_[i] = ((rand() % 2) ? 'F' : 'M');
		for (int j = 0; j < 8; j++)
		{
			addr_[i] << char('A' + randomInt(0, 25));
		}
		s << name_[i].str() << ' ';
		s << sex_[i] << ' ';
		s << log(i + 1) << ' ';
		s << addr_[i].str() << ' ';
	}
	/* 测试locate函数用数据 */
	int randint_ = randomInt(1, testCount - 2);
	s << randint_ << ' ' << name_[randint_].str() << ' ' << sex_[randint_] << ' ' << log(randint_ + 1) << ' ' << addr_[randint_].str() << ' ';
	/* 测试pop函数用数据 */
	s << randomInt(1, testCount - 2) << ' ';
#elif TYPE_CURRENT == TYPE_PSTUDENT
	typedef struct student *testType;
	/* 建立链表数据 */
	stringstream name_[testCount];
	char sex_[testCount];
	stringstream addr_[testCount];
	for (int i = 0; i < testCount; i++)
	{
		s << i << ' ';
		for (int j = 0; j < 5; j++)
		{
			name_[i] << char('a' + randomInt(0, 25));
		}
		sex_[i] = ((rand() % 2) ? 'F' : 'M');
		for (int j = 0; j < 8; j++)
		{
			addr_[i] << char('A' + randomInt(0, 25));
		}
		s << name_[i].str() << ' ';
		s << sex_[i] << ' ';
		s << log(i + 1) << ' ';
		s << addr_[i].str() << ' ';
	}
	/* 测试locate函数用数据 */
	int randint_ = randomInt(1, testCount - 2);
	s << randint_ << ' ' << name_[randint_].str() << ' ' << sex_[randint_] << ' ' << log(randint_ + 1) << ' ' << addr_[randint_].str() << ' ';
	/* 测试pop函数用数据 */
	s << randomInt(1, testCount - 2) << ' ';

#endif

	auto backup = cin.rdbuf();
	s.seekg(0, ios::beg);
	cin.set_rdbuf(s.rdbuf());
	
	LinkList<testType> L;
#if TYPE_CURRENT == TYPE_PCHAR 
#define PCHAR_MAX 30
	// only e1 is used to receive input
	char e1[PCHAR_MAX] = "";
	testType e2{}, e3{}, e4{};
#elif TYPE_CURRENT == TYPE_PSTUDENT
	testType e1;
	try
	{
		e1 = new student;
	}
	catch (bad_alloc &exp)
	{
		cerr << exp.what() << endl;
		return 0;
	}
	testType e2{}, e3{}, e4{};
#else
	testType e1{}, e2{}, e3{}, e4{};
#endif
	int index;

	/* Step 1: Input Data and Create Link-list. */
	cout << "请输入 " << testCount << " 个/组测试数据。" << endl;
	for (int i = 0; i < testCount; i++)
	{
		cin >> e1;
		L.insert(e1, L.length());
	}
	/* Step 1-1: Print the just-created linklist. */
	cout << "建立好的链表如下：" << endl;
	L.traverse(myVisit<testType>);
	cout << endl << "链表空吗？ " << L.isEmpty() << endl;

	cout << "请按任意键进入下一过程。" << endl;
	system("pause");
	cout << endl << endl;


	/* Step 2: randomly Select */
	int randint = randomInt(0, testCount - 1);
	cout << "取第 " << randint << " 位的数据。" << endl;
	L.get(e2, randint);
	cout << e2 << endl;

	randint = randomInt(0, testCount -1 );
	cout << "取第 " << randint << " 位的数据。" << endl;
	e3 = L[randint];
	cout << e3 << endl;
	e3 = testType{};

	cout << "请按任意键进入下一过程。" << endl;
	system("pause");
	cout << endl << endl;

	/* Step 3: search and locate */
	cout << "请输入要在链表中查找的元素：";
	cin >> e1;
	cout << "尝试定位元素 " << e1 << " 在链表中。" << endl;

	int locateIndex = L.locate(e1);
	cout << "定位得到：第 " << locateIndex << " 个元素。" << endl;

	cout << "请按任意键进入下一过程。" << endl;
	system("pause");
	cout << endl << endl;

	/* Step 4: prior and next */
	cout << "刚刚获得的元素，它的上一个元素是：" << endl;
	L.prior(e3, e1);
	cout << e3 << endl;

	cout << "刚刚获得的元素，它的下一个元素是：" << endl;
	L.next(e4, e1);
	cout << e4 << endl;

	cout << "请按任意键进入下一过程。" << endl;
	system("pause");
	cout << endl << endl;

	/* Step 5: delete or pop */
	cout << "请输入要删除的元素标号：";
	cin >> index;
	cout << endl;
	cout << "删除元素 " << index << "。";
	cout << "删除状态：" << L.pop(e2, index) << endl;
	cout << "刚刚删除的元素是：" << e2 << endl;
	L.traverse(myVisit);
	cout << endl;

	cout << "删除首元。";
	cout << "删除状态：" << L.pop(e2, 0) << endl;
	cout << "刚刚删除的元素是：" << e2 << endl;
	L.traverse(myVisit);
	cout << endl;

	cout << "删除末元。";
	cout << "删除状态：" << L.pop(e2, L.length() - 1) << endl;
	cout << "刚刚删除的元素是：" << e2 << endl;
	L.traverse(myVisit);
	cout << endl;

	cout << "请按任意键进入下一过程。" << endl;
	system("pause");
	cout << endl << endl;

	/* Step 6: clear and free */
	L.clear();
	cout << "清除后，L：" << endl;
	L.traverse(myVisit);
	cout << endl;
	cout << "L 的长度是 " << L.length() << "，L 空吗？" << L.isEmpty() << endl;

	cin.set_rdbuf(backup);

	return 0;
}