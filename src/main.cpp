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
	std::string exp = "./data/histo.pgm";

	im->load(input.c_str());

	//im->afficher();

	Histogramme* histo = new Histogramme(im);
	histo->afficher();
	im->negatif();
	histo->exporter_PGM(exp.c_str());
	im->save(output.c_str());

	delete(histo);
	delete(im);

	return 0;
}
