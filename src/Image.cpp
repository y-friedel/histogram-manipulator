#include "Image.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>

Image::Image()
{
	valeurs = std::vector<int>();
}

Image::Image(Image* im)
{
	format = false;
	largeur = im->getLargeur();
	hauteur = im->getHauteur();
	valeurs.resize(largeur*hauteur);
	valeur_max = im->getValeurMax();
	copy(im->valeurs.begin(), im->valeurs.end(), valeurs.begin());
}

Image::~Image()
{

}

void Image::afficher()
{
	std::cout << "format : " << format << " largeur : " << largeur << " hauteur : " << hauteur << std::endl;
	std::cout << "valeurs :"<< std::endl;
		
	for(std::vector<int>::iterator i = valeurs.begin(); i != valeurs.begin()+100; ++i) 
	{
	     	std::cout << *i << std::endl;
	}

}

int Image::getPixel(int x, int y) const
{
	return valeurs[x + largeur*y];
}

int Image::getPixel(int v) const
{
	return valeurs[v];
}
	
void Image::setPixel(int x, int y, int valeur)
{
	valeurs[x + largeur*y] = valeur;
}

void Image::setPixel(int v, int valeur)
{
	valeurs[v] = valeur;
}

int Image::getValeurMax() const
{
	return valeur_max;
}

int Image::getLargeur() const
{
	return largeur;
}

int Image::getHauteur() const
{
	return hauteur;
}


void Image::load(const std::string& fichier)
{
	std::cout << "load " << fichier << std::endl;

	std::string buffer_string = ""; //Pour récupérer les donnees
	char* cfichier = (char*)fichier.c_str();
	std::ifstream fichierPGM(cfichier, std::ios::in);  // on ouvre en lecture
 
        if(fichierPGM)  // si l'ouverture a fonctionné
        {
                std::string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue
                std::getline(fichierPGM, contenu);  // on met dans "contenu" la ligne
		format = (contenu == "P2"); // 1ere ligne = format

		fichierPGM >> largeur;
		fichierPGM >> hauteur;

		std::getline(fichierPGM, contenu);  // Valeur max
		fichierPGM >> valeur_max;	
		
		valeurs.resize(largeur*hauteur);
		std::getline(fichierPGM, contenu);
		
		char temp;
		unsigned char utemp;
		for(int i=0; i< largeur*hauteur; i++)
		{
			if(format)
			{
				fichierPGM >> valeurs[i];
				std::getline(fichierPGM, contenu);  // Valeur courante
			}else{
				fichierPGM.read(&temp, 1);			
				utemp = (unsigned char)temp;
				valeurs[i] = (int)utemp;
			}
		}

		
		
	}
	std::cout << "load OK" << std::endl;
}

void Image::saveAscii(const std::string& fichier)
{
		valeur_max = 255;
		std::ofstream file;
		char* cfichier = (char*)fichier.c_str();

		file.open(cfichier);

		std::string nom_format;
		nom_format = "P2";


		file << nom_format << std::endl;
		file << largeur << " " << hauteur << std::endl;
		file << valeur_max << std::endl;

		for(std::vector<int>::iterator i = valeurs.begin(); i != valeurs.end(); ++i) {
     			file << *i << std::endl;
		}
		file.close();
		
}

void Image::saveBin(const std::string& fichier)
{
		valeur_max = 255;
		std::ofstream file;
		char* cfichier = (char*)fichier.c_str();

		file.open(cfichier);

		std::string nom_format;
		nom_format = "P5";


		file << nom_format << std::endl;
		file << largeur << " " << hauteur << std::endl;
		file << valeur_max << std::endl;

		for(std::vector<int>::iterator i = valeurs.begin(); i != valeurs.end(); ++i) {

     			file << (char)*i;
		}
		file.close();
		
}

void Image::negatif()
{
	for(std::vector<int>::iterator i = valeurs.begin(); i != valeurs.end(); i++)
	{
		*i = 255 - *i;
	}
}
/**/
