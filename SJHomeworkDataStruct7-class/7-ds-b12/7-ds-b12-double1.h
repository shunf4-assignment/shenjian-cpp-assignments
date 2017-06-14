/* 1652270 �����2�� ��˴ */
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