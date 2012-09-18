#include "Image.hpp"
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

	std::cout << "testmain" << std::endl;

	Image im = Image();

	im.load(input.c_str());

	im.afficher();
	
	im.negatif();
	
	im.save(output.c_str());

	return 0;
}
