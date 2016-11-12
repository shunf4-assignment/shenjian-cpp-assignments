#pragma once
#include <iostream>
using namespace std;
#include <cmath>
void linearEquation(double b, double c);
void positiveDelta(double a, double b, double D);
void zeroDelta(double a, double b);
void negativeDelta(double a, double b, double D);
inline double negativeZeroToZero(double x)
{
	//将-0转成0，否则返回原来的数字
	return fabs(x) < 1e-8 ? 0 : x;
}