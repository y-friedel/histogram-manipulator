#include "Image.hpp"
#include "Histogramme.hpp"
#include "Fonction.hpp"
#include "Traitement.hpp"
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

	Image im = Image();
	std::string exp = "./data/Hdepart.txt";

	im.load(input.c_str());

	Image imcpy = Image(im);
	Histogramme histo = Histogramme(im);
	histo.exporter_TXT(exp.c_str());

//	imcpy->saveBin(output.c_str());
	imcpy.saveAscii(output.c_str());
	histo.save("Histogramme_esper");	

	std::vector<int> temp = std::vector<int>();

	//histogramme plat
	for(int i=0; i<256;i++)	temp.push_back(1);
	  
	Histogramme newHisto = Histogramme(temp);    

	//newHisto.setNombrePixels(50000);	 
	newHisto.save("Histogramme2");
    
	Fonction fonction = Fonction(255);
	
	
	Image image = Image("./data/rs.pgm");
	
	Image image1 = Image(image);
	fonction.specification(im, image1, newHisto);
	image1.saveAscii("./data/specification.pgm");

	Histogramme histo1 = Histogramme(image1);
	histo1.exporter_TXT("./data/Hspecification.txt");
	
	fonction.egalisation(im, image1);
	image1.saveAscii("./data/egalisation.pgm");
	
	Histogramme histo2 = Histogramme(image1);
	histo2.exporter_TXT("./data/Hegalisation.txt");	
	
	Image image2;
	fonction.recadrage(im, image2);
	image2.saveAscii("./data/recadrage.pgm");
	
	Histogramme histo3 = Histogramme(image2);
	histo3.exporter_TXT("./data/Hrecadrage.txt");
	
	Traitement traitement = Traitement();
	traitement.diffusionErreur(image, image1);
	image1.saveAscii("./data/versionGlissante.pgm");
	
	
	return 0;
}
