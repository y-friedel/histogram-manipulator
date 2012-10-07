#ifndef MATRICE_H
#define MATRICE_H

#include <vector>
#include <string>



class Matrice{
private :
	int longueur;
	int compte;
	std::vector<int> valeurs;
	
 public :
	Matrice(std::vector<int> _valeurs, int _longueur);

	void setLongueur(int _longueur);
	int getLongueur() const;
};

#endif

