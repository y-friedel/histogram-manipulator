#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include <vector>
#include <string>
#include "Image.hpp"

class Traitement{	
public :
	Traitement();

	~Traitement();
	

	Image& filtreMedian(Image& im);

};

#endif

