/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include "7-ds-b12-student.h"

std::ostream& operator<< (std::ostream& out, const student &s)
{
	out << "[(" << s.num << ")<" << s.score << ">" << s.name << "," << s.sex << "," << s.addr << "]";
	return out;
}


bool student::operator==(const student & s2) const
{
	return num == s2.num;
}

std::istream & operator >> (std::istream & in, student & s)
{
	in >> s.num >> s.name >> s.sex >> s.score >> s.addr;
	return in;
}

std::ostream & operator<<(std::ostream & out, const student *& s)
{
	out << static_cast<const void *>(s) << "->" << "[(" << s->num << ")<" << s->score << ">" << s->name << "," << s->sex << "," << s->addr << "]";
	return out;
}

std::istream & operator >> (std::istream & in, student *& s_)
{
	student &s = *s_;
	in >> s.num >> s.name >> s.sex >> s.score >> s.addr;
	return in;
}