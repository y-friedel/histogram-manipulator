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

	Image* negatif(Image* depart);
	Image* recadrage(Image* depart);
	
	
	Image* egalisation(Image* depart);	
	Image* specification(Image* depart, Histogramme* cible);
		
	Image* correspondance(Image* image);

	void afficher();

};

#endif

