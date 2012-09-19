#include "Histogramme.hpp"
#include <iostream>
#include <fstream>

Histogramme::Histogramme(Image* _img)
{
	img = _img;
	valeur_max = img->getValeurMax();
	valeurs.resize(valeur_max+1);
	fill(valeurs.begin(), valeurs.end(), 0);
	for(int i = 0; i<(img->getLargeur() * img->getHauteur()); i++)
	{
		valeurs[img->getPixel(i)] = valeurs[img->getPixel(i)] + 1;
		//std::cout << /*img->getPixel(i)*/ img->getValeurMax() << std::endl;
	}

}

Histogramme::~Histogramme()
{

}

void Histogramme::afficher()
{
	int val=0;
	int taille = 0;
	std::string line = "";
	for(std::vector<int>::iterator i = valeurs.begin(); i != valeurs.end(); i++) 
	{
		taille = (*i)/10;
		line.resize(taille);
		fill(line.begin(), line.end(), '*');
	     	std::cout << val << " " << line << std::endl;
		val++;
	}


}

void Histogramme::exporter_TXT(const std::string& fichier)
{
		std::ofstream file;
		char* cfichier = (char*)fichier.c_str();

		file.open(cfichier);

		for(int i=0; i<=valeur_max; i++)
		{
			file << i << " " << valeurs[i] << std::endl;
		}

		file.close();
}

void Histogramme::exporter_PGM(const std::string& fichier)
{
		int LARGEUR_MAX = 1000;
		std::ofstream file;
		char* cfichier = (char*)fichier.c_str();

		file.open(cfichier);

		//Caractéristiques du PGM
		file << "P2" << std::endl;
		file << LARGEUR_MAX << " " << (2*valeur_max) +1 << std::endl;
		file << valeur_max << std::endl;

			//On met une ligne de blanc
			for(int j = 0; j < LARGEUR_MAX; j++)
			{
				file << "255" << std::endl;
			}		

		//Pour chaque valeur d'intensité
		for(int i=0; i<=valeur_max; i++)
		{
			//On met "n" 255 sur la ligne
			for(int j = 0; j < valeurs[i]; j++)
			{
				file << "0" << std::endl;
			}
			//On finit avec du blanc
			for(int j = valeurs[i]; j < LARGEUR_MAX; j++)
			{
				file << "255" << std::endl;
			}
			//On met une ligne de blanc
			for(int j = 0; j < LARGEUR_MAX; j++)
			{
				file << "255" << std::endl;
			}		

		}

		file.close();
}
