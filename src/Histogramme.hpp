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
	Histogramme(std::vector<int> _valeurs);
	Histogramme(const std::string& fichier);
	~Histogramme();

	void afficher();
	int getValeur(int intensite) const;
	void setValeur(int intensite, int valeur);
	int getValeurMax() const;
	int getIntensiteMin() const;
	int getIntensiteMax() const;

	void setNombrePixels(int nombrePixels);	

	Histogramme* cumul();

	void exporter_PGM(const std::string& fichier);
	void exporter_TXT(const std::string& fichier);
	
	void save(const std::string& fichier);
};

#endif
