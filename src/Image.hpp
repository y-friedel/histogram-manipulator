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
	Image(Image* im);
	Image(std::string fichier);
	~Image();
	void afficher();
	int getPixel(int x, int y) const;
	int getPixel(int v) const;
	void setPixel(int x, int y, int valeur);
	void setPixel(int v, int valeur);

	int getValeurMax() const;
	int getLargeur() const;
	int getHauteur() const;

	void load(const std::string& fichier);
	void saveAscii(const std::string& fichier);
	void saveBin(const std::string& fichier);
	
	

	//Filtre a effacer
	void negatif();
	

};

#endif

