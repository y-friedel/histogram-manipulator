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

	for(std::vector<int>::iterator i = valeurs.begin(); i != valeurs.end(); ++i) 
	{
	     	std::cout << *i << std::endl;
	}

}



/*
void Fonction::etirement(Histogramme* depart)
{
	int intensiteMax = depart->getIntensiteMax();
	int intensiteMin = depart->getIntensiteMin();

	int tailleDepart = intensiteMax-intensiteMin;
	

	double frequence = (double)(tailleDepart/valeur_max);

	valeurs[0] = depart->getValeur(intensiteMin);

	for (int i=1; i<=tailleDepart;i= i++)
	{
		valeurs[i] = (valeur_max/(intensiteMax-intensiteMin))*(i-intensiteMin);
	}
	
}
*/






void Fonction::specification(Image* depart, Histogramme* cible)
{
	
	Histogramme* cumulCible;
	Histogramme* cumulDepart = new Histogramme(depart);
	cumulDepart->exporter_PGM("Depart.pgm");

	cumulCible = cible->cumul();	
	cumulDepart = cumulDepart->cumul();	
	
	
	//cumulCible->exporter_PGM("cumulCible.pgm");
	//cumulDepart->exporter_PGM("CumulDepart.pgm");
	cible->afficher();
	//cible->exporter_PGM("cible.pgm");
	
	int i=0;
	int j=0;

	while ((i!=valeur_max)&&(j!=valeur_max))
	{

		while ( cumulCible->getValeur(j) > cumulDepart->getValeur(i))
		{
			valeurs[i] = j;	
			i++;
		}
		
		j++;
	}

	correspondance(depart);
	
}


void Fonction::egalisation(Image* image)
{
	
	Histogramme* histo = new Histogramme(image);
	
	Histogramme* histoCumul;
	histoCumul = histo->cumul();
	
	int nb_Pixels = histoCumul->getValeur(valeur_max);
	

	
	for(int k=0; k<=valeur_max; k++)
	{
	    valeurs[k] = 255-255*histoCumul->getValeur(k)/nb_Pixels;	    
	}
	
	
	correspondance(image);
    
}
	
	
void Fonction::correspondance(Image* image)
{
  
	int nb_Pixels = image->getHauteur()*image->getLargeur();
	
	
	for(int i=0; i<nb_Pixels; i++)
	{     
	     image->setPixel(i, valeurs[image->getPixel(i)]);
	}
	
	image->saveAscii("./data/GNA.pgm");
  
}
	
