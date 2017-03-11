#include <iostream>
using namespace std;

void swap(int *x, int *y)
{
	int *t;
	*t = *x;
	*x = *y;
	*y = *t;
}

int main()
{
	int i = 10, j = 15;
	cout << "i=" << i << ", j=" << j << endl;
	swap(&i, &j);
	cout << "i=" << i << ", j=" << j << endl;
	return 0;
}