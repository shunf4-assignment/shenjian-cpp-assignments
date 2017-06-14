/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include "7-ds-b12-double1.h"
#include <cmath>

ApproxDouble::ApproxDouble(double real_)
{
	real = real_;
}

ApproxDouble::operator double() const
{
	return real;
}

bool operator==(const ApproxDouble & a1, const ApproxDouble & a2)
{
	return fabs(a1 - a2) < 1e-6;
}

ApproxDouble::operator double&()
{
	return real;
}