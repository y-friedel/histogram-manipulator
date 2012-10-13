#ifndef POINT_H
#define POINT_H

#include <vector>
#include <string>



class Point{
private :
	double x;
	double y;
	bool marque;

 public :
	Point();
	Point(double _x, double _y);
	Point(const Point& p);
	~Point();
	
	double getX() const;
	void setX(double _x);
	double getY() const;
	void setY(double _y);
	bool getMarque() const;
	void setMarque(bool _marque);
	
	bool egal(Point& p);
	double distance(const Point& p) const;
	
	void afficher() const;

};

#endif

