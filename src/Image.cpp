#include "Image.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>

Image::Image()
{
	valeurs = std::vector<int>();
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
	
void Image::setPixel(int x, int y, int valeur)
{
	valeurs[x + largeur*y] = valeur;
}

void Image::load(const std::string& fichier)
{
	std::cout << "test " << fichier << std::endl;

	std::string buffer_string = ""; //Pour récupérer les donnees
	char* cfichier = (char*)fichier.c_str();
	std::ifstream fichierPGM(cfichier, std::ios::in);  // on ouvre en lecture
 
        if(fichierPGM)  // si l'ouverture a fonctionné
        {
                std::string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue
                std::getline(fichierPGM, contenu);  // on met dans "contenu" la ligne
		format = (contenu == "P2"); // 1ere ligne = format

		std::getline(fichierPGM, contenu);  // Largeur et hauteur
		int i=0;		
		for(i; contenu[i] != ' '; i++) //On isole la largeur
		{
			buffer_string += contenu[i];
		}

		largeur = atoi(buffer_string.c_str());
		buffer_string = "";
		for(i; contenu[i] != '\0'; i++) //On isole la largeur
		{
			buffer_string += contenu[i];
		}
		hauteur = atoi(buffer_string.c_str());
		
		std::getline(fichierPGM, contenu);  // Valeur max

		for(int i=0; i< largeur*hauteur; i++)
		{
			std::getline(fichierPGM, contenu);  // Valeur courante
			valeurs.push_back(atoi(contenu.c_str()));
		}

		
		
	}

}

void Image::save(const std::string& fichier)
{
		valeur_max = 255;
		std::ofstream file;
		char* cfichier = (char*)fichier.c_str();

		file.open(cfichier);

		std::string nom_format;
		
		if (format)
		{
			nom_format = "P2";
		}
		else
		{
			nom_format = "P5";
		}

		file << nom_format << std::endl;
		file << largeur << " " << hauteur << std::endl;
		file << valeur_max << std::endl;

		for(std::vector<int>::iterator i = valeurs.begin(); i != valeurs.end(); ++i) {
     			file << *i << std::endl;
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

	
