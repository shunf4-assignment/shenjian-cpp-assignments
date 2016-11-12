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
	//��-0ת��0�����򷵻�ԭ��������
	return fabs(x) < 1e-8 ? 0 : x;
}