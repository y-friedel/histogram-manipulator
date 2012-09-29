#include "Image.hpp"
#include "Histogramme.hpp"
#include "Fonction.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		std::cout << "wrong parameter" << std::endl;
		return -1;	
	}
		std::string input = std::string(argv[1]);
		std::string output = std::string(argv[2]);

	Image* im = new Image();
	std::string exp = "./data/histoV2.pgm";

	im->load(input.c_str());

	Image* imcpy = new Image(im);
	Histogramme* histo = new Histogramme(im);
	//im->afficher();
	//im->negatif();
	histo->exporter_PGM(exp.c_str());

//	imcpy->saveBin(output.c_str());
	imcpy->saveAscii(output.c_str());
	//histo->afficher();
	histo->save("Histogramme");	

	std::vector<int> temp = std::vector<int>();

	
	for(int i=0; i<28;i++)	temp.push_back(237);
	for(int i=28; i<256;i++)	temp.push_back(238);	  
	Histogramme* newHisto = new Histogramme(temp);     
	newHisto->save("Histogramme2");
    
	
	Fonction* fonction = new Fonction(255);
	
	Image* image1;
	
	image1 = fonction->specification(im, newHisto);
	image1->saveAscii("./data/specification.pgm");
	fonction->afficher();
	
	Histogramme* histo1 = new Histogramme(image1);
	histo1->exporter_PGM("./data/Hspecification.pgm");
	
	image1 = fonction->egalisation(im);
	image1->saveAscii("./data/egalisation.pgm");
	
	Histogramme* histo2 = new Histogramme(image1);
	histo2->exporter_PGM("./data/Hegalisation.pgm");
	
	
	Image* image2;
	image2 = fonction->negatif(im);
	image2->saveAscii("./data/negatif.pgm");
	
	
	delete(histo);
	delete(im);
	delete(imcpy);
	delete(newHisto);
	delete(fonction);

	return 0;
}
