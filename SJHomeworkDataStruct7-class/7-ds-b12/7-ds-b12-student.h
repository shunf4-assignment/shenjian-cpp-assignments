/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#pragma once
#include <string>
#include "7-ds-b12-double1.h"
#include <iostream>

struct student
{
private:
	int num;
	std::string name;
	char sex;
	double1 score;
	std::string addr;

public:
	student()
		: num(0), name(""), sex('M'), score(0), addr("")
	{
	}
	student(int num_, const std::string &name_, char sex_, double1 score_, const std::string& addr_)
		:	num(num_), name(name_), sex(sex_), score(score_), addr(addr_)
	{
	}

	friend std::ostream& operator<< (std::ostream& out, const student &s);
	friend std::istream& operator>> (std::istream& in, student &s);

	friend std::ostream& operator<< (std::ostream& out, const student *&s);
	friend std::istream& operator >> (std::istream& in, student *&s);

	bool operator==(const student& s2) const;
};


