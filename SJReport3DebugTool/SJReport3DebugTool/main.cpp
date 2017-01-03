#include <iostream>
#include <cmath>
using namespace std;

int global = 2;
extern int externalGlobal;
static int staticGlobal = 3;

int function(int n)
{
	static int staticInt = 5;
	staticInt += n;
	return staticInt;
}
void outerFun();
int main()
{
	int i;
	int ia[] = { 1,2,3,4,5 };
	double d;
	char c = 'y';
	char str[] = "Star";
	int *pi = &i;
	char *pc = &c;
	char *ps = str + 2;
	i = 3;
	cout << function(i) << endl;
	cout << sqrt(i) << endl;
	outerFun();
	return 0;
}