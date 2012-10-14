#include "Fonction.hpp"
#include <iostream>
#include <cstdlib>


Fonction::Fonction(int max)
{
	valeurs = std::vector<int>();
	valeurs.resize(max+1);

	valeur_max = max;
}

Fonction::~Fonction()
{

}

int Fonction::getValeur(int intensite)
{
      return valeurs[intensite];
  
}

/* Cette procédure se charge de remplacer les pixels dans l'image en fonction du tableau de correspondance
 * Paramètres :
 * 	Image de départ (qu'on ne change pas)
 * 	Image d'arrivée (à laquelle on va changer les attributs en fonction 
 * 			de l'image de départ et de la fonction de correspondance)
 * 
 * 	Pas besoin de s'inquieter de la taille ou de la valeur_max de l'image d'arrivée
 */
void Fonction::correspondance(const Image& depart, Image& arrivee)
{
	arrivee = Image(depart);
	int nb_Pixels = arrivee.getHauteur()*arrivee.getLargeur();
	
	//On remplace chaque pixel de l'image
	for(int i=0; i<nb_Pixels; i++)
	{     
	     arrivee.setPixel(i, valeurs[arrivee.getPixel(i)]);
	}  
}

int Fonction::correspondance2(const Image& depart, std::vector<int> intensites, int nb_intensite)
{
	/*arrivee = Image(depart);
	int nb_Pixels = arrivee.getHauteur()*arrivee.getLargeur();*/
	
	//On remplace chaque pixel de l'image
	/*for(int i=0; i<nb_Pixels; i++)
	{
	     arrivee.setPixel(i, intensites[i]);
	}  
	return */
}

/* Cette procédure renvoie un negatif de l'image de départ
 * Paramètres :
 * 	Image de départ (qu'on ne change pas)
 * 	Image d'arrivée (à laquelle on va changer les attributs en fonction 
 * 			de l'image de départ et de la fonction de correspondance)
 * 
 * 	Pas besoin de s'inquieter de la taille ou de la valeur_max de l'image d'arrivée
 */
void Fonction::negatif(const Image& depart, Image &arrivee)
{
	for(int i=0; i<=valeur_max; i++)
	   valeurs[i] = 255-i;
  
	correspondance(depart, arrivee);
}

/* Cette procédure renvoie un recadrage de l'image de départ
 * Paramètres :
 * 	Image de départ (qu'on ne change pas)
 * 	Image d'arrivée (à laquelle on va changer les attributs en fonction 
 * 			de l'image de départ et de la fonction de correspondance)
 * 
 * 	Pas besoin de s'inquieter de la taille ou de la valeur_max de l'image d'arrivée
 */
void Fonction::recadrage(const Image& depart, Image &arrivee)
{
	Histogramme histo = Histogramme(depart);
	
	int intensiteMax = histo.getIntensiteMax();
	int intensiteMin = histo.getIntensiteMin();
	int difference;
	int tailleDepart = intensiteMax-intensiteMin;
	
	//f(k)=255*(k-min)/(max-min)
	for(int k=0; k<=valeur_max; k++)
	{	
	    difference = k-intensiteMin;
	    
	    if (difference<0)
		  difference = 0;
	    
	    valeurs[k] = 255*(difference)/tailleDepart;
	}
	
	//On appelle la fonction de correspondance
	correspondance(depart, arrivee);
}

/* Cette procédure renvoie un recadrage de l'histogramme
 * Paramètres :
 * 	Histogramme de départ (qu'on ne change pas)
 * 	Histogramme d'arrivée (à laquelle on va changer les attributs en fonction 
 * 			de l'image de départ et de la fonction de correspondance)
 * 
 * 	Pas besoin de s'inquieter de la taille ou de la valeur_max de l'image d'arrivée
 */
void Fonction::etirement(const Histogramme& depart, Histogramme &arrivee)
{
	arrivee = Histogramme(depart.getValeurMax());
	valeurs.resize(depart.getValeurMax());
	
	double taille_depart = depart.getIntensiteMax()- depart.getIntensiteMin();
	double taille_fin = depart.getValeurMax();
	double frequence = 0;
	
	for(int i=0; i<taille_depart; i++)
	{
		arrivee.setValeur((int)frequence, depart.getValeur(i));
		frequence += taille_fin/taille_depart;
		valeurs[(int)frequence] = depart.getValeur(i);
	}
}

/* Cette procédure renvoie une amélioration de l'image de départ par spécification d'histogramme
 * Paramètres :
 * 	Image de départ (qu'on ne change pas)
 * 	Image d'arrivée (à laquelle on va changer les attributs en fonction 
 * 			de l'image de départ et de la fonction de correspondance)
 * 	Histogramme cible dont on va se servir pour la specification
 * 
 * 	Pas besoin de s'inquieter de la taille ou de la valeur_max de l'image d'arrivée
 */
void Fonction::specification(const Image& depart, Image &arrivee, Histogramme& cible)
{ 
	//cumulDepart sera l'histogramme cumulé de l'image depart
	Histogramme cumulDepart = Histogramme(depart);
	//On calcul l'histogramme cumulé de l'histogramme de depart	
	cumulDepart.cumul();
	//On normalise l'histogramme cible (cumul de depart = cumul d'arrive)
	cible.setNombrePixels(cumulDepart.getValeur(valeur_max), valeur_max);

	//cible.exporter_TXT("cible.txt");
	//On calcul l'histogramme cumulé de l'histogramme cible
	//Histogramme cumulCible = Histogramme(cible);
	cible.cumul();
	//On applique l'algorithme vu dans le cours
	int i=0;
	int j=0;

	while ((i!=valeur_max)&&(j!=valeur_max+1))
	{
		while ( cible.getValeur(j) > cumulDepart.getValeur(i))
		{
			valeurs[i] = j;	
			i++;
		}		
		j++;		
	}

	//On appelle la fonction de correspondance
	correspondance(depart, arrivee);
}
//const Image& depart, Image &arrivee, const Histogramme& depart, std::vector<int> intensites, Histogramme& cible)

int Fonction::specification2(const Image& depart, const Histogramme& histo_depart, std::vector<int> intensites, Histogramme& cible, int nb_intensite, int nb_pixels)
{ 
	Histogramme temp = Histogramme(cible);
	int milieu;
  
	//cumulDepart sera l'histogramme cumulé de l'image depart
	Histogramme cumulDepart = Histogramme(histo_depart);

	//On calcul l'histogramme cumulé de l'histogramme de depart	
	cumulDepart.cumul();

	//On normalise l'histogramme cible (cumul de depart = cumul d'arrive)
	temp.setNombrePixels(cumulDepart.getValeur(cumulDepart.getValeurMax()), cumulDepart.getValeurMax());

	//On calcul l'histogramme cumulé de l'histogramme cible
	temp.cumul();
	
	
	//On applique l'algorithme vu dans le cours
	int i=0;
	int j=0;

	while ((i!=valeur_max)&&(j!=valeur_max+1))
	{
		while ( temp.getValeur(j) > cumulDepart.getValeur(i))
		{
			valeurs[i] = j;	
			i++;
		}		
		j++;		
	}

	milieu = depart.getPixel(nb_pixels+nb_pixels*depart.getLargeur());
	/*std::cout<<"LA : "<<nb_pixels<< " " <<depart.getLargeur()<<std::endl;
	std::cout<<nb_pixels+nb_pixels*depart.getLargeur()<<std::endl;*/
	int valeur;
	
	for(int i=0; i<=valeur_max; i++)
	{
		if(intensites[i]==milieu)
			valeur = i;
	}
	
	return intensites[valeurs[i]];
	
	
	//return correspondance2(depart, intensites, nb_intensite);
}



/* Cette procédure renvoie une égalisation de l'image de départ
 * Paramètres :
 * 	Image de départ (qu'on ne change pas)
 * 	Image d'arrivée (à laquelle on va changer les attributs en fonction 
 * 			de l'image de départ et de la fonction de correspondance)
 * 
 * 	Pas besoin de s'inquieter de la taille ou de la valeur_max de l'image d'arrivée
 */
void Fonction::egalisation(const Image& depart, Image &arrivee)
{
	//On fait l'histogramme de l'image
	Histogramme histo = Histogramme(depart);

	//On fait le cumul de l'histogramme de l'image
	Histogramme histoCumul = Histogramme(histo);
	histoCumul.cumul();
	
	//le nombre de pixel peut être trouvé grace au cumul d'histogramme (la valeur de fin)
	int nb_Pixels = histoCumul.getValeur(valeur_max);
	
	//On construit notre tableau de correspondance à l'aide
	//de la formule f(k) = 255-255*(k-min)/(max-min) 
	for(int k=0; k<=valeur_max; k++)
	{
	    valeurs[k] = 255*histoCumul.getValeur(k)/nb_Pixels;
	}
	
	//On appelle la fonction de correspondance
	correspondance(depart, arrivee);
}


void Fonction::afficher()
{

	for(int i=0; i<=valeur_max; i++)
	{
	     	std::cout << i << " >> "<< valeurs[i] << std::endl;
	}

}
