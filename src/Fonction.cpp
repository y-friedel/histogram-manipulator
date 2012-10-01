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

//Cette fonction se charge de remplacer les pixels dans l'image en fonction du tableau de correspondance
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

void Fonction::negatif(const Image& depart, Image &arrivee)
{
	for(int i=0; i<=valeur_max; i++)
	   valeurs[i] = 255-i;
  
	correspondance(depart, arrivee);
}


void Fonction::recadrage(const Image& depart, Image &arrivee)
{
	Histogramme histo = Histogramme(depart);
  
	int intensiteMax = histo.getIntensiteMax();
	int intensiteMin = histo.getIntensiteMin();

	int tailleDepart = intensiteMax-intensiteMin;
	
	//f(k)=255*(k-min)/(max-min)
	for(int k=0; k<=valeur_max; k++)
	{	
	    int difference = k-intensiteMin;
	    
	    if ((k-intensiteMin)<0)
		  difference = 0;
	    
	    valeurs[k] = 255*(difference)/tailleDepart;
	   
	}
	
	//On appelle la fonction de correspondance
	correspondance(depart, arrivee);
}


void Fonction::specification(const Image& depart, Image &arrivee, Histogramme& cible)
{
	

	//On calcul l'histogramme cumulé de l'histogramme de depart
	Histogramme cumulDepart = Histogramme(depart);
	cumulDepart.cumul(cumulDepart);	

	//On normalise l'histogramme cible (cumul de depart = cumul d'arrive)
	cible.setNombrePixels(cumulDepart.getValeur(valeur_max));
	
	//On calcul l'histogramme cumulé de l'histogramme cible
	Histogramme cumulCible;
	cible.cumul(cumulCible);			
	
	//On applique l'algorithme vu dans le cours
	int i=0;
	int j=0;

	while ((i!=valeur_max)&&(j<=valeur_max))
	{
		while ( cumulCible.getValeur(j) >= cumulDepart.getValeur(i))
		{
			valeurs[i] = j;	
			i++;
		}
		
		j++;		
	}

	//On appelle la fonction de correspondance
	correspondance(depart, arrivee);
}




void Fonction::egalisation(const Image& depart, Image &arrivee)
{
	//On fait l'histogramme de l'image
	Histogramme histo = Histogramme(depart);

	//On fait le cumum de l'histogramme de l'image
	Histogramme histoCumul;
	histo.cumul(histoCumul);
	
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
