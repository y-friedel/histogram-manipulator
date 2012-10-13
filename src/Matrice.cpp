#include "Matrice.hpp"
#include <iostream>

Matrice::Matrice(std::vector<int> _tableau_gauche, std::vector<int> _tableau_droit, int _nb_pixels_cote)
{

	nb_pixels_cote = _nb_pixels_cote;
	
	tableau_gauche.resize(_tableau_gauche.size());
	copy(_tableau_gauche.begin(), _tableau_gauche.end(), tableau_gauche.begin());
	
	tableau_droit.resize(_tableau_droit.size());
	copy(_tableau_droit.begin(), _tableau_droit.end(), tableau_droit.begin());
	
	
	
	compte = 0;
	
	for(unsigned int i=0; i<tableau_gauche.size();i++)
	{
		compte += tableau_gauche[i];	  
	}
	for(unsigned int i=0; i<tableau_droit.size();i++)
	{
		compte += tableau_droit[i];	  
	}
}

void Matrice::setNbPixelsCote(int _nb_pixels_cote)
{
	nb_pixels_cote = _nb_pixels_cote;
}

int Matrice::getNbPixelsCote() const
{
	return nb_pixels_cote;
}

int Matrice::getCompte() const
{
	return compte;
}

void Matrice::setValeurGauche(int i, int valeur)
{
	tableau_gauche[i] = valeur;
}

int Matrice::getValeurGauche(int i) const
{
	return tableau_gauche[i];  
}

void Matrice::setValeurDroit(int i, int valeur)
{
	tableau_droit[i] = valeur;
}

int Matrice::getValeurDroit(int i) const
{
	return tableau_droit[i];  
}