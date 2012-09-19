#ifndef HISTO_H
#define HISTO_H

#include <vector>
#include <string>
#include "Image.hpp"

class Histogramme{
private :	
	int valeur_max;
	Image* img;
	std::vector<int> valeurs;

 public :
	Histogramme(Image* img);
	~Histogramme();

	void afficher();
	int getValeur(int intensite) const;

	void exporter_PGM(const std::string& fichier);
	void exporter_TXT(const std::string& fichier);

};

#endif
