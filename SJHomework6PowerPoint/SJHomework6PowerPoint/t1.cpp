#include <iostream>
using namespace std;
#define PI 3.14159

double SL(double R, double *L)
{
	double S;
	S = PI*R*R;
	*L = 2 * PI*R;
	return S;
}

int main()
{
	double s, l, r = 3;
	s = SL(r, &l);
	cout << "s = " << s << endl;
	cout << "l = " << l << endl;
	return 0;
}
