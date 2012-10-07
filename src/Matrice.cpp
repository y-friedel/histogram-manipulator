#include "Matrice.hpp"
#include <iostream>

Matrice::Matrice(std::vector<int> _valeurs, int _longueur)
{

	longueur = _longueur;
	valeurs.resize(_valeurs.size());
	copy(_valeurs.begin(), _valeurs.end(), valeurs.begin());
	
	compte = 0;
	
	for(int i=0; i<valeurs.size();i++)
	{
		compte += valeurs[i];	  
	}
}

void Matrice::setLongueur(int _longueur)
{
	longueur = _longueur;
}

int Matrice::getLongueur() const
{
	return longueur;
}