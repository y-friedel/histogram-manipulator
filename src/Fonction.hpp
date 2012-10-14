#ifndef FONCTION_H
#define FONCTION_H

#include <vector>
#include <string>
#include "Histogramme.hpp"
#include "Image.hpp"

class Fonction{
private :
	int valeur_max;
	std::vector<int> valeurs;

public :
	Fonction(int max);

	~Fonction();
	
	int getValeur(int intensite);
	void correspondance(const Image& depart, Image& arrivee);
    //int correspondance2(const Image& depart, std::vector<int> intensites, int nb_intensite);

	void negatif(const Image& depart, Image &arrivee);
	void recadrage(const Image& depart, Image &arrivee);
	void etirement(const Histogramme& depart, Histogramme &arrivee);
	
	void specification(const Image& depart, Image &arrivee, Histogramme& cible);
	int specificationPixel(const Image& depart, const Histogramme& histo_depart, std::vector<int> intensites, Histogramme& cible, int nb_intensite, int nb_pixels);
	
	void egalisation(const Image& depart, Image &arrivee);	
	
	
		
	void afficher();

};

#endif

