/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include <iostream>
#include <cmath>
using namespace std;
#define FS_SLICES 1e7

class integral
{
protected:
	double(*fun)(double x);
	double lowerLimit;
	double upperLimit;

public:
	integral();
	double value();
	friend istream& operator >> (istream &in, integral &i);
};

class integral_sin : public integral
{
protected:

public:
	integral_sin();
};

class integral_cos : public integral
{
protected:

public:
	integral_cos();
};

class integral_exp : public integral
{
protected:

public:
	integral_exp();
};

int main()
{
	integral_sin s1;
	integral_cos s2;
	integral_exp s3;
	integral *p;

	cin >> s1;
	p = &s1;
	cout << p->value() << endl;

	cin >> s2;
	p = &s2;
	cout << p->value() << endl;

	cin >> s3;
	p = &s3;
	cout << p->value() << endl;

	return 0;
}

integral::integral() : lowerLimit(0), upperLimit(0), fun(nullptr)
{
}

double integral::value()
{
	double value = 0;
	double dx = (upperLimit - lowerLimit) / FS_SLICES;
	int sign = (upperLimit > lowerLimit ? 1 : 0);
	while (sign ? ((upperLimit - lowerLimit) > 0) : ((upperLimit - lowerLimit) < 0))
	{
		value += dx * fun(lowerLimit);
		lowerLimit += dx;
	}
	return value;
}

istream & operator >> (istream & in, integral & i)
{
	in >> i.lowerLimit >> i.upperLimit;
	return in;
}

integral_sin::integral_sin() : integral()
{
	fun = sin;
}

integral_cos::integral_cos() : integral()
{
	fun = cos;
}

integral_exp::integral_exp() : integral()
{
	fun = exp;
}
