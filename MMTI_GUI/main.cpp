#include <QtGui/QApplication>
#include <cstdio>
//#include "qmlapplicationviewer.h"

#include "Image.hpp"
#include "Histogramme.hpp"
#include "Fonction.hpp"
#include "Traitement.hpp"
#include "Point.hpp"
#include "NuagePoint.hpp"
#include "MatriceErreur.hpp"
#include <iostream>

#include "MainWindow.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    int option;
    int choix = 0;
    while ((option = getopt(argc, argv, "gdh")) != EOF)
    {
            switch (option)
            {
              case 'g':
                choix = 1;
                break;
              case 'd':
                choix = 2;
                break;
              case 'h':
				std::cout <<std::endl<< "Parameters : " << std::endl;
				std::cout << "\tFilter Mode :\t./projet Filter Input Output" << std::endl;
				std::cout << "\tGraphic Mode :\t./projet -g" << std::endl;
				std::cout << "\tDemo :\t\t./projet -d" << std::endl << std::endl;
				
				std::cout << "Filter list :" << std::endl;
				std::cout << "\t- Negatif" << std::endl;
				std::cout << "\t- Egalisation" << std::endl;
				std::cout << "\t- Recadrage" << std::endl;
				std::cout << "\t- Median" << std::endl;
				std::cout << "\t- Diffusion" << std::endl << std::endl;
				
				std::cout << "Input example :" << std::endl;
				std::cout << "\t./data/rs2.pgm" << std::endl << std::endl;
				
				std::cout << "Output example :" << std::endl;
				std::cout << "\t./results/rs2_eg.pgm" << std::endl << std::endl;;
				return 0;
                break;
            }
    }
    
	if(choix ==0)
	{
        std::cout << "Traitement" << std::endl;
        
        //On prend les arguments
        if(argc != 4)
		{
			std::cout << "Type \"./projet -h\" for help" << std::endl;
			return -1;	
		}
		std::string traitement = std::string(argv[1]);
		std::string input = std::string(argv[2]);
		std::string output = std::string(argv[3]);
		
		std::transform(traitement.begin(), traitement.end(), traitement.begin(), ::tolower);
		
		Image in = Image(input);
		Image out = Image();
		if(traitement == "negatif")
		{
			std::cout << "Negatif" << std::endl;
			Fonction neg = Fonction(255);
			neg.negatif(in, out);
		}
		else if (traitement == "egalisation")
		{
			std::cout << "Egalisation" << std::endl;
			Fonction eg = Fonction(255);
			eg.egalisation(in, out);
		}
		else if (traitement == "recadrage")
		{
			std::cout << "Recadrage" << std::endl;
			Fonction re = Fonction(255);
			re.recadrage(in, out);
		}
		else if (traitement == "median")
		{
			std::cout << "Median" << std::endl;
			Traitement::filtreMedian(in, out);
		}		
		else if (traitement == "diffusion")
		{
			std::cout << "Diffusion" << std::endl;
			Traitement::diffusionErreur(in, out);
		}
		out.saveBin(output.c_str());	
		
	}
	else if(choix ==1)
	{
		QApplication app(argc, argv);
		MainWindow m;
        m.show();
        return app.exec();
	}
	else if(choix ==2)
	{
        std::cout << "==DEMO==" << std::endl;
        
		Image rs_dark = Image("./data/rs2.pgm");
		Image ship = Image("./data/bruit.pgm");
		Image output = Image();
		Fonction eg = Fonction(255);
		eg.egalisation(rs_dark, output);
		rs_dark.saveBin("./results/squirell.pgm");
		output.saveBin("./results/squirell_egalisation.pgm");
		eg.recadrage(rs_dark, output);
		output.saveBin("./results/squirell_recadrage.pgm");
		
		//histogramme plat
		Histogramme h_plat = Histogramme(std::vector<int>(256,1));
		eg.specification(rs_dark, output, h_plat);
		output.saveBin("./results/squirell_egalisation_histo.pgm");
		
		//Median
		Traitement::filtreMedian(ship, output);
		ship.saveBin("./results/ship.pgm");
		output.saveBin("./results/ship_median.pgm");
		
		Traitement::versionGlissanteImagette(rs_dark, output, h_plat, 30);
		output.saveBin("./results/squirell_fenetre_imagette.pgm");
		
		//~ Traitement::versionGlissantePixel(rs_dark, output, h_plat, 2);
		//~ output.saveBin("./results/squirell_fenetre_pixel.pgm");
		
		Traitement::diffusionErreur(rs_dark, output);
		output.saveBin("./results/squirell_diff_err.pgm");
		
		std::cout << "Results in \"./Results\" Folder" << std::endl;		
    }
}
