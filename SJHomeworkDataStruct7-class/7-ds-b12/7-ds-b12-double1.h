/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#pragma once

class ApproxDouble
{
private:
	double real;
public:
	ApproxDouble(double real_);
	ApproxDouble() : real(0.) {}
	operator double() const;
	operator double&();
	friend bool operator==(const ApproxDouble &a1, const ApproxDouble &a2);
};

typedef ApproxDouble double1;