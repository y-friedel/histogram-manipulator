#ifndef HISTO_H
#define HISTO_H

#include <vector>
#include <string>
#include "Image.hpp"

class Histogramme{
private :	
	int valeur_max;
	std::vector<int> valeurs;

 public :
	Histogramme(Image* img);
	Histogramme(Histogramme* histo);
	Histogramme(const std::string& fichier);
	~Histogramme();

	void afficher();
	int getValeur(int intensite) const;
	int getValeurMax() const;


	void exporter_PGM(const std::string& fichier);
	void exporter_TXT(const std::string& fichier);
	
	void save(const std::string& fichier);
};

#endif
