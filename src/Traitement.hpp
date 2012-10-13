#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include <vector>
#include <string>
#include "Image.hpp"
#include "Histogramme.hpp"
#include "Fonction.hpp"
#include "Matrice.hpp"

class Traitement{	
public :
	Traitement();

	~Traitement();
	

	void filtreMedian(const Image& depart, Image& arrivee);
	void miroir(const Image& depart, Image& arrivee, int nb_pixels);
	
	void diffusionErreur(const Image& depart, Image& arrivee);
	void diffusionErreurMatrice(const Image& depart, Image& arrivee, Matrice matrice);
	
	void specificationDansFenetre(const Image& depart, Image& arrivee, Histogramme& cible, int X_min, int X_max, int Y_min, int Y_max);
	void versionGlissante(const Image& depart, Image& arrivee, Histogramme& cible, int pixel_Cote);
	
	
	

};

#endif

