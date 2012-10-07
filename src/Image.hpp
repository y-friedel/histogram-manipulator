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
	Image(const Image& im);
	Image(const std::string& fichier);
	Image(const std::vector<int> _valeurs, bool _format, int _largeur, int _hauteur, int _valeur_max);
	~Image();
	void afficher();
	int getPixel(int x, int y) const;
	int getPixel(int v) const;
	void setPixel(int x, int y, int valeur);
	void setPixel(int v, int valeur);

	bool getFormat() const;
	void setFormat(bool _format);
	int getValeurMax() const;
	void setValeurMax(int _valeur_max);
	int getLargeur() const;
	void setLargeur(int _largeur);
	int getHauteur() const;
	void setHauteur(int _hauteur);

	Image& filtreMedian();
	
	void load(const std::string& fichier);
	void saveAscii(const std::string& fichier);
	void saveBin(const std::string& fichier);

};

#endif

