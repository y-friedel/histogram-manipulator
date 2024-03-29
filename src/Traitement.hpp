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
	
	static void filtreMedian(const Image& depart, Image& arrivee);
	static void miroir(const Image& depart, Image& arrivee, int nb_pixels);
	static void couper_image(const Image& depart, Image& arrivee, int nb_pixels);
	
	static void diffusionErreur(const Image& depart, Image& arrivee);
	static void diffusionErreurMatrice(const Image& depart, Image& arrivee, MatriceErreur matrice);
	
	static void specificationDansImagette(const Image& depart, Image& arrivee, Histogramme& cible, int X_min, int X_max, int Y_min, int Y_max);
	static void versionGlissanteImagette(const Image& depart, Image& arrivee, Histogramme& cible, int nb_pixels);
	
	static void specificationDansPixel(const Image& depart, Image& arrivee, Histogramme& cible, int X_min, int X_max, int Y_min, int Y_max, int indice, int nb_pixels);
	static void versionGlissantePixel(const Image& depart, Image& arrivee, Histogramme& cible, int nb_pixels);
	
	
	

};

#endif

