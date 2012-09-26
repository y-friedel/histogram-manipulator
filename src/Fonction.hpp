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


	void normalisation(Histogramme* depart);
	void etirement(Histogramme* depart);
	void egalisation(Image* depart);
	
	void specification(Image* depart, Histogramme* cible);
	
	
	void correspondance(Image* image);

	void afficher();

};

#endif

