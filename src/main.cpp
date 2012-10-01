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
	std::string exp = "./data/Hdepart.txt";

	im->load(input.c_str());

	Image* imcpy = new Image(im);
	Histogramme* histo = new Histogramme(im);
	histo->exporter_TXT(exp.c_str());

//	imcpy->saveBin(output.c_str());
	imcpy->saveAscii(output.c_str());
	histo->save("Histogramme");	

	std::vector<int> temp = std::vector<int>();

	//histogramme plat pour rs.pgm
	for(int i=0; i<28;i++)	temp.push_back(237);
	for(int i=28; i<256;i++)	temp.push_back(238);	  
	Histogramme* newHisto = new Histogramme(temp);    

	newHisto->setNombrePixels(50000);	 
	newHisto->save("Histogramme2");
    
	


	Fonction* fonction = new Fonction(255);
	
	
/*	Image* image = new Image();
	image->load("./data/bruit2.pgm");
	Image* image1 = new Image(image);
	
	image1 = fonction->specification(im, newHisto);
	image1->saveAscii("./data/specification.pgm");
	
	Histogramme* histo1 = new Histogramme(image1);
	histo1->exporter_TXT("./data/Hspecification.txt");
	
	image1 = fonction->egalisation(im);
	image1->saveAscii("./data/egalisation.pgm");
	
	Histogramme* histo2 = new Histogramme(image1);
	histo2->exporter_TXT("./data/Hegalisation.txt");	
	
	Image* image2;
	image2 = fonction->recadrage(im);
	image2->saveAscii("./data/recadrage.pgm");
	
	Histogramme* histo3 = new Histogramme(image2);
	histo3->exporter_TXT("./data/Hrecadrage.txt");
	
	image = image1->filtreMedian();
	image->saveAscii("./data/median.pgm");*/

	
	
	
	delete(histo);
	delete(im);
	delete(imcpy);
	delete(fonction);
	//delete(newHisto);
	/*delete(image);
	delete(image1);
	delete(image2);*/
	
	return 0;
}
