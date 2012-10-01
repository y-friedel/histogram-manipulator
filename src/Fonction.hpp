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

	//Histogramme* aPriori();
	
	int getValeur(int intensite);
	void correspondance(const Image& depart, Image& arrivee);


	void negatif(const Image& depart, Image &arrivee);
	void recadrage(const Image& depart, Image &arrivee);
	
	void specification(const Image& depart, Image &arrivee, Histogramme& cible);
	void egalisation(const Image& depart, Image &arrivee);	
		
	void afficher();

};

#endif

