#include "Image.hpp"
#include "Histogramme.hpp"
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
	im->negatif();
	imcpy->saveBin(output.c_str());

	delete(histo);
	delete(im);
	delete(imcpy);

	return 0;
}
