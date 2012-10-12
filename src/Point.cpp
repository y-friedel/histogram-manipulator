
#include "Point.hpp"
#include <iostream>
#include <complex>

Point::Point()
{
	x = 0;
	y = 0;
	marque = false;  
}

Point::Point(double _x, double _y)
{
	x = _x;
	y = _y;
	marque = false;
}

Point::Point(const Point& p)
{
	x = p.getX();
	y = p.getY();
	marque = p.getMarque();  
}

Point::~Point()
{
	
}
	
double Point::getX() const
{
	return x;
}
void Point::setX(double _x)
{
	x = _x;
}
double Point::getY() const
{	
	return y;
}
void Point::setY(double _y)
{
	y = _y;
}

bool Point::getMarque() const

{
	return marque;
}
void Point::setMarque(bool _marque)
{
	marque = _marque;
}

bool Point::egal(Point& p)
{
  //std::cout<<"ETAPE egal"<<std::endl;
	return ((x==p.getX())&&(y==p.getY()));
	
}

double Point::distance(Point p)
{
	double a = pow(p.getX()-x,2);
	double b = pow(p.getY()-y,2);
	double c = fabs(sqrt(a+b));
	return c;
  
}

void Point::afficher()
{
	std::cout<<"("<<x<<","<<y<<")"<<" "<<marque<<std::endl;
}
