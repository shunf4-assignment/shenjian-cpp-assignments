/* 1652270 ¼ÆËã»ú2°à ·ëË´ */
#include <iostream>
using namespace std;

const double pi = 3.1415926;

class Shape
{
protected:
public:
	virtual double area()
	{
		return double();
	}
};

class Circle : public Shape
{
protected:
	double radius;
public:
	Circle(double radius_);
	double area();
};

class Rectangle : public Shape
{
protected:
	double width;
	double height;
public:
	Rectangle(double w_, double h_);
	double area();
};

class Square : public Shape
{
protected:
	double side;
public:
	Square(double side_);
	double area();
};

class Trapezoid : public Shape
{
protected:
	double upperBase;
	double lowerBase;
	double height;
public:
	Trapezoid(double upB, double lrB, double h);
	double area();
};

class Triangle : public Shape
{
protected:
	double base;
	double height;
public:
	Triangle(double b, double h);
	double area();
};

int main()
{
	Circle		c1(1);
	Square		s1(3);
	Rectangle	r1(2.5, 4.0);
	Trapezoid	t1(3.5, 6.5, 4.0);
	Triangle	t2(5.0, 4.0);

	Shape *s[5] = { &c1, &s1, &r1, &t1, &t2 };

	for (int i = 0; i < 5; i++)
	{
		cout << s[i]->area() << endl;
	}
	
	return 0;
}

Circle::Circle(double radius_) : radius(radius_)
{
}

double Circle::area()
{
	return pi * radius * radius;
}

Rectangle::Rectangle(double w_, double h_) : width(w_), height(h_)
{
}

double Rectangle::area()
{
	return width * height;
}

Square::Square(double side_) : side(side_)
{
}

double Square::area()
{
	return side * side;
}

Trapezoid::Trapezoid(double upB, double lrB, double h) : upperBase(upB), lowerBase(lrB), height(h)
{
}

double Trapezoid::area()
{
	return (upperBase + lowerBase) * height / 2;
}

Triangle::Triangle(double b, double h) : base(b), height(h)
{
}

double Triangle::area()
{
	return base * height / 2;
}
