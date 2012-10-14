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
	Histogramme();
	Histogramme(int _valeur_max);
	Histogramme(const Image& img);
	Histogramme(const Histogramme& histo);
	Histogramme(std::vector<int> _valeurs);
	Histogramme(const std::string& fichier);
	~Histogramme();

	void afficher();
	int getValeur(int intensite) const;
	void setValeur(int intensite, int valeur);
	int getValeurMax() const;
	int getIntensiteMin() const;
	int getIntensiteMax() const;
	
	std::vector<int> retrecirHistogramme();
	void agrandirHistogramme(std::vector<int> intensites, int nb_intensite);
	
	void setNombrePixels(int nombrePixels);	
	void setNombrePixelsPixel(int nombrePixels, int nb_intensite);	

	void cumul();

	void exporter_PGM(const std::string& fichier);
	void exporter_TXT(const std::string& fichier);
	
	void save(const std::string& fichier);
};

#endif
