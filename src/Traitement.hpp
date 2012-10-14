#ifndef TRAITEMENT_H
#define TRAITEMENT_H

#include <vector>
#include <string>
#include "Image.hpp"
#include "Histogramme.hpp"
#include "Fonction.hpp"
#include "MatriceErreur.hpp"

class Traitement{	
public :
	Traitement();
	~Traitement();
	
	void filtreMedian(const Image& depart, Image& arrivee);
	void miroir(const Image& depart, Image& arrivee, int nb_pixels);
	void couper_image(const Image& depart, Image& arrivee, int nb_pixels);
	
	void diffusionErreur(const Image& depart, Image& arrivee);
	void diffusionErreurMatrice(const Image& depart, Image& arrivee, MatriceErreur matrice);
	
	void specificationDansFenetre(const Image& depart, Image& arrivee, Histogramme& cible, int X_min, int X_max, int Y_min, int Y_max, int indice, int nb_pixels);
	void versionGlissante(const Image& depart, Image& arrivee, Histogramme& cible, int nb_pixels);
	
	
	

};

#endif

