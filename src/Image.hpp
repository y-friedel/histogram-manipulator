#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

class Image{
private :
	bool format;
	int largeur;
	int hauteur;
	int valeur_max;
	std::vector<int> valeurs;

 public :
	Image();
	Image(std::string fichier);
	Image(Image* im);
	~Image();
	void afficher();
	int getPixel(int x, int y) const;
	void setPixel(int x, int y, int valeur);

	void load(const std::string& fichier);
	void save(const std::string& fichier);

	//Filtre a effacer
	void negatif();
	

};

#endif

