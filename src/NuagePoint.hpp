
#ifndef NUAGEPOINT_H
#define NUAGEPOINT_H

#include <vector>
#include <string>
#include "Point.hpp"



class NuagePoint{
private :
	std::vector<Point> nuage;

 public :
	NuagePoint();
	NuagePoint(Point point);
	NuagePoint(std::vector<Point> _nuage);
	NuagePoint(int nb_points, int maximumXY);
	~NuagePoint();
	
	Point getPoint(int i) const;
	void setPoint(int i, Point& p);
	int getTaille() const;
	
	void ajoutPoint(const Point& point);
	
	void afficher() const;
	
	std::vector<NuagePoint> k_moyennes(int k, int t);

};

#endif

