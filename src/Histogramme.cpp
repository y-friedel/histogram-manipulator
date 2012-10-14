#include "Histogramme.hpp"
#include <iostream>
#include <fstream>

Histogramme::Histogramme()
{
	valeur_max=0;
	valeurs.resize(0);
	
}

Histogramme::Histogramme(int _valeur_max)
{
	valeur_max=_valeur_max;
	valeurs.resize(_valeur_max);
	
}

Histogramme::Histogramme(const Image& _img)
{
	valeur_max = _img.getValeurMax();
	valeurs.resize(valeur_max+1);
	fill(valeurs.begin(), valeurs.end(), 0);
	for(int i = 0; i<(_img.getLargeur() * _img.getHauteur()); i++)
	{
		valeurs[_img.getPixel(i)] = valeurs[_img.getPixel(i)] + 1;
	}

}

void Histogramme::setValeur(int intensite, int valeur)
{
	valeurs[intensite] = valeur;
}


Histogramme::Histogramme(const Histogramme& histo)
{

	valeur_max = histo.valeur_max;
	for(std::vector<int>::const_iterator i = histo.valeurs.begin(); i != histo.valeurs.end(); i++) 
	{
		valeurs.push_back(*i);
	}

}


Histogramme::Histogramme(std::vector<int> _valeurs)
{

	valeurs = std::vector<int>();
	valeurs.resize(_valeurs.size());
	copy(_valeurs.begin(), _valeurs.end(), valeurs.begin());	
	valeur_max = valeurs.size()-1;
}

void Histogramme::setNombrePixels(int nombrePixels, int nb_intensite)
{
	int cumul;
	int val_cumul = 0;
	int reste;

	Histogramme histo = Histogramme(valeurs);

	int frequence = valeur_max/(nb_intensite+1);

	valeurs.resize(nb_intensite);

	valeur_max = nb_intensite-1;
	
	for(int i=0; i<=nb_intensite-1; i++)
	{
		cumul = 0;
		for(int j=i; j<frequence+i; j++)
		      cumul += histo.getValeur(j);
		valeurs[i] = cumul;
		//std::cout<<cumul<<std::endl;
	}



	cumul = 0;
	for(int i=0; i<=valeur_max; i++)
	{
		cumul += valeurs[i]; 
	}
	
	if(cumul<valeur_max)
	{
		for(int i=0; i<=cumul; i++)
		{
			valeurs[i] = 1;
		}	  
	}
	else
	{
		for(int i=0; i<=valeur_max; i++)
		{
			setValeur(i, nombrePixels*valeurs[i]);
			setValeur(i, valeurs[i]/cumul);
			val_cumul += valeurs[i];
		}
		reste = nombrePixels-val_cumul;

		for(int i=0; reste>0; i++)
		{
			setValeur(i, valeurs[i]+1);
			reste--;
		}
	}
}


Histogramme::Histogramme(const std::string& fichier)
{
	std::cout << "load " << fichier << std::endl;

	std::string buffer_string = ""; //Pour récupérer les donnees
	char* cfichier = (char*)fichier.c_str();
	std::ifstream fichierHisto(cfichier, std::ios::in);  // on ouvre en lecture
 	
	int val_file;
        if(fichierHisto)  // si l'ouverture a fonctionné
        {
                std::string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue
          
		//1ere iteration
		fichierHisto >> val_file;
		fichierHisto >> val_file;

		while(!fichierHisto.eof())
		{
			valeurs.push_back(val_file);	
			std::getline(fichierHisto, contenu);
			fichierHisto >> val_file;
			fichierHisto >> val_file;
		}
		
		
		
	}
	
	valeur_max = valeurs.size()-1;
	
	std::cout << "load OK" << std::endl;
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

void Histogramme::save(const std::string& fichier)
{
	std::ofstream file;
	char* cfichier = (char*)fichier.c_str();

	file.open(cfichier);

	int compt = 0;
	for(std::vector<int>::iterator i = valeurs.begin(); i != valeurs.end(); i++) 
	{
		
		file << compt << '\t' << *i << std::endl;
		compt++;
	}
	
	
	file.close();
	

}


int Histogramme::getValeur(int intensite) const
{
	return valeurs[intensite];
}

int Histogramme::getValeurMax() const
{
	return valeur_max;
}


int Histogramme::getIntensiteMin() const
{
	int minimum = -1; 

	for(int i=0; i<=valeur_max; i++)
	{
		if(valeurs[i]>0)
		{
			minimum = i;
			break;
		}
	}
	
	return minimum;
}


int Histogramme::getIntensiteMax() const
{
	int maximum = -1; 

	for(int i=valeur_max; i>=0; i--)
	{
		if(valeurs[i]>0)
		{
			maximum = i;
			break;
		}
	}
	
	return maximum;
}


std::vector<int> Histogramme::retrecirHistogramme()
{
	std::vector<int> _valeurs = std::vector<int>();
	std::vector<int> intensites = std::vector<int>();

	int compt = 0;
	
	for(int i=0; i<=valeur_max; i++)
	{
		if(valeurs[i] != 0)
		{
			_valeurs.push_back(valeurs[i]);
			intensites.push_back(i);
			compt += valeurs[i];
		}
	}
	valeurs = _valeurs;
	valeur_max = _valeurs.size()-1;

	return intensites;
}


void Histogramme::agrandirHistogramme(std::vector<int> intensites, int nb_intensite)
{	
	std::vector<int> _valeurs = valeurs;
	valeurs.clear();
	valeurs.resize(nb_intensite);	
	valeur_max = nb_intensite;
	
	for(int i=0; i<intensites.size(); i++)
		valeurs[intensites[i]] = _valeurs[i];
}


void Histogramme::cumul()
{	
	int cumul = 0;

	for(int i=0; i<=valeur_max; i++)
	{
		cumul += getValeur(i);
		setValeur(i, cumul);
	}
}






