#include <iostream>
using namespace std;
int main() {

	double a=0;
	int i=0;
	double b=1;
	while (i <= 10000)
	{
		i++;
		b = b * 3;
		a += 1. / (b + 1);
	}
	cout << a << endl;
}