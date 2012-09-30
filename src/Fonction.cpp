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

void Fonction::afficher()
{

	for(int i=0; i<=valeur_max; i++)
	{
	     	std::cout << i << " >> "<< valeurs[i] << std::endl;
	}

}

Image* Fonction::negatif(Image* image)
{
	for(int i=0; i<=valeur_max; i++)
	   valeurs[i] = 255-i;
  
	Image* resultat = correspondance(image);
	return resultat;
}


Image* Fonction::recadrage(Image* depart)
{
	Histogramme* histo = new Histogramme(depart);
  
	int intensiteMax = histo->getIntensiteMax();
	int intensiteMin = histo->getIntensiteMin();

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
	Image* resultat = correspondance(depart);
	return resultat;
}


Image* Fonction::specification(Image* depart, Histogramme* cible)
{
	//On calcul l'histogramme cumulé de l'histogramme de depart
	Histogramme* cumulDepart = new Histogramme(depart);
	cumulDepart = cumulDepart->cumul();	
	
	//On calcul l'histogramme cumulé de l'histogramme cible
	Histogramme* cumulCible;
	cumulCible = cible->cumul();			
	
	//On applique l'algorithme vu dans le cours
	
	int i=0;
	int j=0;

	while ((i!=valeur_max)&&(j<=valeur_max))
	{

		while ( cumulCible->getValeur(j) >= cumulDepart->getValeur(i))
		{
			valeurs[i] = j;	
			i++;
		}
		
		j++;
		
	}

	//On appelle la fonction de correspondance
	Image* resultat = correspondance(depart);
	return resultat;
	
}




Image* Fonction::egalisation(Image* image)
{
	//On fait l'histogramme de l'image
	Histogramme* histo = new Histogramme(image);

	//On fait le cumum de l'histogramme de l'image
	Histogramme* histoCumul;
	histoCumul = histo->cumul();
	
	//le nombre de pixel peut être trouvé grace au cumul d'histogramme (la valeur de fin)
	int nb_Pixels = histoCumul->getValeur(valeur_max);
	
	//On construit notre tableau de correspondance à l'aide
	//de la formule f(k) = 255-255*(k-min)/(max-min) 
	for(int k=0; k<=valeur_max; k++)
	{
	    valeurs[k] = 255*histoCumul->getValeur(k)/nb_Pixels;
	}
	
	//On appelle la fonction de correspondance
	Image* resultat = correspondance(image);
	return resultat;
	
}
	
//Cette fonction se charge de remplacer les pixels dans l'image en fonction du tableau de correspondance
Image* Fonction::correspondance(Image* image)
{
	Image* resultat = new Image(image);
	int nb_Pixels = resultat->getHauteur()*resultat->getLargeur();
	
	//On remplace chaque pixel de l'image
	for(int i=0; i<nb_Pixels; i++)
	{     
	     resultat->setPixel(i, valeurs[resultat->getPixel(i)]);
	}
	
	return resultat;
  
}
	
