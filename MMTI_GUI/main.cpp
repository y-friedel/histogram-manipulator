#include <QtGui/QApplication>
//#include "qmlapplicationviewer.h"

#include "Image.hpp"
#include "Histogramme.hpp"
#include "Fonction.hpp"
#include "Traitement.hpp"
#include "Point.hpp"
#include "NuagePoint.hpp"
#include "Matrice.hpp"
#include <iostream>

#include "MainWindow.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
	bool graphic = 0;
	if(graphic)
	{
	
		/*    QScopedPointer<QApplication> app(createApplication(argc, argv));

		    QmlApplicationViewer viewer;
		    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
		    viewer.setMainQmlFile(QLatin1String("qml/MMTI_GUI/main.qml"));
		    viewer.showExpanded();

		    QString nomImage("src_name");
		    //viewer.rootContext()->setContextProperty("src_name", nomImage);


		    return app->exec();*/

		    QApplication app(argc, argv);
		    MainWindow m;
		    m.show();
		    return app.exec();
	}else{
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
		
		
		Image image = Image("./data/rs4.pgm");
		Image image1 = Image(image);

		/*fonction.negatif(im, image1);
		im.saveAscii("./data/t1a.pgm");
		image1.saveAscii("./data/t1b.pgm");
			fonction.negatif(im, image1);
		im.saveAscii("./data/t2a.pgm");
		image1.saveAscii("./data/t2b.pgm");*/


		Histogramme histo1 = Histogramme(image1);
		histo1.exporter_TXT("./data/Hspecification.txt");
		
		fonction.egalisation(im, image1);
		image1.saveAscii("./data/egalisation.pgm");
		
		Histogramme histo2 = Histogramme(image1);
		histo2.exporter_TXT("./data/Hegalisation.txt");	
		
		
	/*	Image image2;
		fonction.recadrage(im, image2);
		image2.saveAscii("./data/recadrage.pgm");
		
		Histogramme histo3 = Histogramme(image2);
		histo3.exporter_TXT("./data/Hrecadrage.txt");*/
		
		Traitement traitement = Traitement();
		/*traitement.miroir(image, image1, 2);
		image1.saveAscii("./data/miroir.pgm");
		
		traitement.couper_image(image1, image, 2);
		image.saveAscii("./data/couper_image.pgm");
		*/
		int t1 = clock();
		//fonction.specification(image, image1, newHisto);
		
		std::vector<int> tableau_gauche = std::vector<int>();
		tableau_gauche.push_back(2);
		tableau_gauche.push_back(4);
		tableau_gauche.push_back(1);
		tableau_gauche.push_back(2);
		
		std::vector<int> tableau_droit = std::vector<int>();
		tableau_droit.push_back(0);
		tableau_droit.push_back(8);
		tableau_droit.push_back(4);
		tableau_droit.push_back(8);
		tableau_droit.push_back(4);
		tableau_droit.push_back(2);
		tableau_droit.push_back(4);
		tableau_droit.push_back(2);
		tableau_droit.push_back(1);
		
		Matrice stucki = Matrice(tableau_gauche, tableau_droit, 2);
		std::cout<<stucki.getCompte()<<std::endl;
		
		traitement.diffusionErreurMatrice(image, image1, stucki);
		image1.saveAscii("./data/diffusionErreurMatrice.pgm");
		
		
	/*	traitement.versionGlissante(image, image1, newHisto, 3);
		int t2 = clock();
		std::cout<<(((float)t2/CLOCKS_PER_SEC)-((float)t1/CLOCKS_PER_SEC))<<std::endl;
		image1.saveAscii("./data/versionGlissante.pgm");
		
		Histogramme nepastoucher = Histogramme("./data/nepastoucher.txt");*/
		
		
		/*newHisto.setNombrePixels(16, 8);
		newHisto.exporter_TXT("./data/nepastoucher2.txt");	*/
		//traitement.versionGlissante(image, image1, newHisto, 1);
	//traitement.specificationDansFenetre(image, image1, newHisto, 2, 5, 0, 1);


		//image1.saveAscii("./data/versionGlissante.pgm");
		
		//NuagePoint nuage = NuagePoint(10000, 5000);
	/*	NuagePoint nuage = NuagePoint();
		nuage.ajoutPoint(Point(1,1));
		nuage.ajoutPoint(Point(2,2));
		nuage.ajoutPoint(Point(3,3));
		nuage.ajoutPoint(Point(3,1));
		nuage.ajoutPoint(Point(1,3));
		
		nuage.ajoutPoint(Point(5,7));
		nuage.ajoutPoint(Point(6,6));
		nuage.ajoutPoint(Point(6,7));
		nuage.ajoutPoint(Point(6,8));	
		nuage.ajoutPoint(Point(7,6));
		nuage.ajoutPoint(Point(7,7));
		nuage.ajoutPoint(Point(7,8));
		
		nuage.ajoutPoint(Point(9,3));
		nuage.ajoutPoint(Point(9,4));
		nuage.ajoutPoint(Point(10,4));
		nuage.ajoutPoint(Point(11,2));
		nuage.ajoutPoint(Point(11,3));
		nuage.ajoutPoint(Point(12,2));
		
		//nuage.afficher();
		std::vector<NuagePoint> table_nuage_points = std::vector<NuagePoint>();
		unsigned int nbcluster = 3;
		int t1 = clock();

        table_nuage_points = nuage.k_moyennes_m(nbcluster, 100);

		int t2 = clock();
		for(int i=0; i<nbcluster; i++)
		{
			table_nuage_points[i].afficher();
			std::cout<<std::endl;
		  
		}
		
		std::cout<<(((float)t2/CLOCKS_PER_SEC)-((float)t1/CLOCKS_PER_SEC))<<std::endl;
	*/
	return 0;
	}		



}
