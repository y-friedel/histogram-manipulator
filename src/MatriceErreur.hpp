#ifndef MATRICEERREUR_H
#define MATRICEERREUR_H

#include <vector>
#include <string>



class MatriceErreur{
private :
	int nb_pixels_cote;
	int compte;
	std::vector<int> tableau_gauche;
	std::vector<int> tableau_droit;
	
 public :
	MatriceErreur(std::vector<int> _tableau_gauche, std::vector<int> _tableau_droit, int _nb_pixels_cote);

	
	void setNbPixelsCote(int _nb_pixels_cote);
	int getNbPixelsCote() const;
	int getCompte() const;
	void setValeurGauche(int i, int valeur);
	int getValeurGauche(int i) const;
	void setValeurDroit(int i, int valeur);
	int getValeurDroit(int i) const;
};

#endif

