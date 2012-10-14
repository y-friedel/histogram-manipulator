#include "Traitement.hpp"
#include <iostream>
#include <cstdlib> 
#include <complex>

	Traitement::Traitement()
	{

	}

	Traitement::~Traitement()
	{
	    
	}
	
/* Cette procédure s'occupe du filtre médian
 * Paramètres :
 * 	Image de départ (qu'on ne change pas)
 * 	Image d'arrivée (à laquelle on va changer les attributs en fonction de l'image de départ et de la fonction)
 * 
 * 	Donc pas besoin de s'inquieter de la taille ou de la valeur_max de l'image d'arrivée
 */
void Traitement::filtreMedian(const Image& depart, Image& arrivee)
{
	arrivee = Image(depart);

	int median;
	
	//création du tableau
	std::vector<int> tableau = std::vector<int>();
  
	for(int i=0; i< depart.getLargeur()*depart.getHauteur(); i++)
	{
		tableau.clear();
		
		tableau.push_back(depart.getPixel(i));
		
		//1. on remplit du tableau
		//début de ligne
		if (i%depart.getLargeur()==0)
		{
			tableau.push_back(depart.getPixel(i+1));
			//debut de colonne
			if (i<depart.getLargeur())
			{
				tableau.push_back(depart.getPixel(i+depart.getLargeur()));
				tableau.push_back(depart.getPixel(i+depart.getLargeur()+1));	
			}
			//fin de colonne
			else if (i>=depart.getLargeur()*(depart.getHauteur()-1))
			{
				tableau.push_back(depart.getPixel(i-depart.getLargeur()));
				tableau.push_back(depart.getPixel(i-depart.getLargeur()+1));
			}else
			{
				tableau.push_back(depart.getPixel(i+depart.getLargeur()));
				tableau.push_back(depart.getPixel(i+depart.getLargeur()+1));
				tableau.push_back(depart.getPixel(i-depart.getLargeur()));
				tableau.push_back(depart.getPixel(i-depart.getLargeur()+1));
			}
		
			
			
		}else if (i%depart.getLargeur()==depart.getLargeur()-1) //fin de ligne
		{
			tableau.push_back(depart.getPixel(i-1));
			//debut de colonne
			if (i<depart.getLargeur())
			{
				tableau.push_back(depart.getPixel(i+depart.getLargeur()));
				tableau.push_back(depart.getPixel(i+depart.getLargeur()-1));
			} 
			//fin de colonne
			else if (i>depart.getLargeur()*(depart.getHauteur()-1))
			{
				tableau.push_back(depart.getPixel(i-depart.getLargeur()));
				tableau.push_back(depart.getPixel(i-depart.getLargeur()-1));
			}else
			{
				tableau.push_back(depart.getPixel(i+depart.getLargeur()));
				tableau.push_back(depart.getPixel(i+depart.getLargeur()-1));
				tableau.push_back(depart.getPixel(i-depart.getLargeur()));
				tableau.push_back(depart.getPixel(i-depart.getLargeur()-1));
			
			}
		}else
		{	
		  
			tableau.push_back(depart.getPixel(i-1));
			tableau.push_back(depart.getPixel(i+1));
			
			//debut de colonne
			if (i<depart.getLargeur())
			{
				tableau.push_back(depart.getPixel(i+depart.getLargeur()));
				tableau.push_back(depart.getPixel(i+depart.getLargeur()+1));
				tableau.push_back(depart.getPixel(i+depart.getLargeur()-1));
			}
			//fin de colonne
			else if (i>depart.getLargeur()*(depart.getHauteur()-1))
			{
				tableau.push_back(depart.getPixel(i-depart.getLargeur()));
				tableau.push_back(depart.getPixel(i-depart.getLargeur()+1));
				tableau.push_back(depart.getPixel(i-depart.getLargeur()-1));
			}else
			{	
				tableau.push_back(depart.getPixel(i-depart.getLargeur()));
				tableau.push_back(depart.getPixel(i-depart.getLargeur()+1));
				tableau.push_back(depart.getPixel(i-depart.getLargeur()-1));
				
				tableau.push_back(depart.getPixel(i+depart.getLargeur()));
				tableau.push_back(depart.getPixel(i+depart.getLargeur()+1));
				tableau.push_back(depart.getPixel(i+depart.getLargeur()-1));	
			}
		}
		
		//2. on trie le tableau		
		int temp;
		int longueur = tableau.size();

		bool echange;

		do
		{
			echange = false;
			for(int j=0; j<longueur-1; j++)
			{
				if(tableau[j]>tableau[j+1])
				{
					temp = tableau[j];
					tableau[j] = tableau[j+1];
					tableau[j+1] = temp;
					echange = true;
				}
			}
			longueur--;
		}
		while(echange);
		
		
		//3. on prend le median
		median = tableau[tableau.size()/2];
		
		//4. on remplace l'intensité du pixel par le median
		arrivee.setPixel(i, median);
		
	}

}

/* Cette procédure renvoie une image dont les cotés ont été ajoutés en miroir (de la taille nb_pixels)
 * Paramètres :
 * 	Image de départ (qu'on ne change pas)
 * 	Image d'arrivée (à laquelle on va changer les attributs en fonction de l'image de départ et du miroir
 * 
 * 	Donc pas besoin de s'inquieter de la taille ou de la valeur_max de l'image d'arrivée
 */
void Traitement::miroir(const Image& depart, Image& arrivee, int nb_pixels)
{
	arrivee = Image(depart);
	arrivee.setLargeur(depart.getLargeur()+2*nb_pixels);
	arrivee.setHauteur(depart.getHauteur()+2*nb_pixels);

	//on s'occcupe de l'image
	for(int j=0; j< depart.getHauteur(); j++)
	{
		for(int i=0; i< depart.getLargeur(); i++)
		{    
			arrivee.setPixel((arrivee.getLargeur())*(j+nb_pixels)+i+nb_pixels, depart.getPixel(depart.getLargeur()*j+i));
		}
	}
	
	//on s'occupe du miroir
	for(int i=0; i<nb_pixels; i++)
	{
		//bord du haut
		for(int j=0; j< depart.getLargeur(); j++)
		{ 
			//bord du haut
				arrivee.setPixel(arrivee.getLargeur()*i+nb_pixels+j, depart.getPixel(depart.getLargeur()*(nb_pixels-i-1)+j));
			//bord du bas
				arrivee.setPixel(arrivee.getLargeur()*(i+depart.getHauteur()+nb_pixels)+j+nb_pixels, depart.getPixel(depart.getLargeur()*(depart.getHauteur()-i-1)+j));
		}
		
		for(int j=0; j< depart.getHauteur(); j++)
		{
			//bord de gauche
				arrivee.setPixel(arrivee.getLargeur()*(j+nb_pixels)+i, depart.getPixel(depart.getLargeur()*j+(nb_pixels-i-1)));
			//bord de droite
				arrivee.setPixel(arrivee.getLargeur()*(j+nb_pixels)+i+depart.getLargeur()+nb_pixels, depart.getPixel(depart.getLargeur()*j+(depart.getLargeur()-i-1)));
		}
		
		for(int j=0; j<nb_pixels; j++)
		{
			//coin haut gauche
				arrivee.setPixel(arrivee.getLargeur()*j+i, depart.getPixel(depart.getLargeur()*(nb_pixels-j-1)+nb_pixels-i-1));
			//coin haut droit
				arrivee.setPixel(arrivee.getLargeur()*j+i+depart.getLargeur()+nb_pixels, depart.getPixel(depart.getLargeur()*(nb_pixels-j-1)+depart.getLargeur()-1-i));
			//coin bas gauche
				arrivee.setPixel(arrivee.getLargeur()*(i+depart.getHauteur()+nb_pixels)+j, depart.getPixel(depart.getLargeur()*(depart.getHauteur()-i-1)+nb_pixels-j-1));
			//coin bas droite
				arrivee.setPixel(arrivee.getLargeur()*(i+depart.getHauteur()+nb_pixels)+j+depart.getLargeur()+nb_pixels, depart.getPixel(depart.getLargeur()*(depart.getHauteur()-i-1)+depart.getLargeur()-1-j));
		}
	}
}


void Traitement::couper_image(const Image& depart, Image& arrivee, int nb_pixels)
{
	arrivee.setHauteur(depart.getHauteur()-2*nb_pixels);
	arrivee.setLargeur(depart.getLargeur()-2*nb_pixels);

	for(int j=0; j<arrivee.getHauteur(); j++)
	{
		for(int i=0; i<arrivee.getLargeur(); i++)
		{
			arrivee.setPixel(j*arrivee.getLargeur()+i, depart.getPixel((j+nb_pixels)*depart.getLargeur()+i+nb_pixels));
		}
	}
}

/* Cette procédure s'occupe de la diffusion d'erreur
 * Paramètres :
 * 	Image de départ (qu'on ne change pas)
 * 	Image d'arrivée (à laquelle on va changer les attributs en fonction de l'image de départ et de la fonction)
 * 
 * 	Donc pas besoin de s'inquieter de la taille ou de la valeur_max de l'image d'arrivée
 */
void Traitement::diffusionErreur(const Image& depart, Image& arrivee)
{
	arrivee = Image(depart);
	
	int moyenne = depart.getValeurMax()/2;
  
	for(int i=0; i< depart.getLargeur()*depart.getHauteur(); i++)
	{
		if(depart.getPixel(i)<=moyenne)
			arrivee.setPixel(i,0);
		else
			arrivee.setPixel(i,depart.getValeurMax());
	}
}

/* Cette procédure s'occupe de la diffusion d'erreur par matrice
 * Paramètres :
 * 	Image de départ (qu'on ne change pas)
 * 	Image d'arrivée (à laquelle on va changer les attributs en fonction de l'image de départ et de la fonction)
 * 	MatriceErreur dont on va se servir pour la diffusion d'erreur
 * 
 * 	Pas besoin de s'inquieter de la taille ou de la valeur_max de l'image d'arrivée
 */
void Traitement::diffusionErreurMatrice(const Image& depart, Image& arrivee, MatriceErreur matrice)
{
	arrivee = Image(depart);
	int nouveau_px;
	int ancien_px;
	double repercussion;
	int moyenne = depart.getValeurMax()/2;
	
	Traitement traitement = Traitement();
	traitement.miroir(depart, arrivee, matrice.getNbPixelsCote());
	
	int erreur;
	int nb_pixels_cote = matrice.getNbPixelsCote();
	int nouvelle_valeur;
	int indice;
	
	for(int j=nb_pixels_cote; j< depart.getHauteur()+nb_pixels_cote; j++)
	{
		for(int i=nb_pixels_cote; i< depart.getLargeur()+nb_pixels_cote; i++)
		{
			ancien_px = arrivee.getPixel(arrivee.getLargeur()*j+i);
			
			for(int k=0; k<nb_pixels_cote+1; k++)
			{
				for(int l=0; l<nb_pixels_cote+1; l++)
				{
					if((k!=0)&&(l!=0))
					{ 
						indice = arrivee.getLargeur()*(j)+(l+i);
					  
						if(ancien_px<=moyenne)
							nouveau_px = 0;
						else
							nouveau_px = depart.getValeurMax();
					  
						erreur = ancien_px - nouveau_px;
						repercussion = matrice.getValeurDroit(k*(nb_pixels_cote+1)+l)/matrice.getCompte();
						nouveau_px = arrivee.getPixel(indice) + erreur*matrice.getValeurDroit(k*(nb_pixels_cote+1)+l)/matrice.getCompte();
						arrivee.setPixel(indice, abs(nouveau_px));
					}
				}
				
				for(int k=0; k<nb_pixels_cote; k++)
				{
				  
					for(int l=0; l<nb_pixels_cote; l++)
					{
						indice = arrivee.getLargeur()*(j+1)+(l+i-nb_pixels_cote);
					  
						if(ancien_px<=moyenne)
							nouveau_px = 0;
						else
							nouveau_px = depart.getValeurMax();
					  
						erreur = ancien_px - nouveau_px;
						nouveau_px = arrivee.getPixel(indice) + erreur*matrice.getValeurGauche(k*(nb_pixels_cote-1)+l)/matrice.getCompte();
						arrivee.setPixel(indice, abs(nouveau_px));
					}
				}
			}
			
			if(arrivee.getPixel(arrivee.getLargeur()*j+i)<=moyenne)
				arrivee.setPixel(arrivee.getLargeur()*j+i,0);
			else
				arrivee.setPixel(arrivee.getLargeur()*j+i, arrivee.getValeurMax());	
		}		
	}	

	Image temp = Image(arrivee);
	couper_image(temp, arrivee, nb_pixels_cote);
}

/* Cette procédure s'occupe de la version glissante de la specification d'histogramme
 * Paramètres :
 * 	Image de départ (qu'on ne change pas)
 * 	Image d'arrivée (à laquelle on va changer les attributs en fonction de l'image de départ et de la fonction)
 * 	Histogramme cible dont on va se servir pour la specification
 * 	X_min et X_max déterminent l'intervalle x de la fenetre
 * 	Y_min et Y_max déterminent l'intervalle y de la fenetre
 * 
 * 	Pas besoin de s'inquieter de la taille ou de la valeur_max de l'image d'arrivée
 */
void Traitement::specificationDansFenetre(const Image& depart, Image& arrivee, Histogramme& cible, int X_min, int X_max, int Y_min, int Y_max)
{

	//On créé une nouvelle image à la taille de la fenetre
	int largeur = X_max-X_min+1;
	int hauteur = Y_max-Y_min+1;
	
	int largeur_Depart = depart.getLargeur();
	std::vector<int> valeurs = std::vector<int>();
	
	valeurs.resize(largeur*hauteur);

	for(int j=Y_min; j<=Y_max; j++)
	{
		for(int i=X_min; i<=X_max; i++)
		{
			valeurs[(j-Y_min)*largeur+i-X_min] = depart.getPixel(largeur_Depart*j+i);
		}
	}

	Image fenetre = Image(valeurs, depart.getFormat(), largeur, hauteur, depart.getValeurMax());
	
	Histogramme histo_fenetre = Histogramme(fenetre);

	std::vector<int> intensites = std::vector<int>();

	intensites = histo_fenetre.retrecirHistogramme();

	//on appelle specification sur notre fenetre
	Fonction fonction = Fonction(intensites.size());

	fonction.specification2(fenetre, fenetre, histo_fenetre, intensites, cible, depart.getValeurMax());

	//On remplace les pixels dans notre nouvelle image	
	for(int j=Y_min; j<=Y_max; j++)
	{
		for(int i=X_min; i<=X_max; i++)
		{ 
			arrivee.setPixel(depart.getLargeur()*j+i, fenetre.getPixel((j-Y_min)*largeur+i-X_min));
		}	  
	}	
	
}


void Traitement::versionGlissante(const Image& depart, Image& arrivee, Histogramme& cible, int nb_pixels)
{
	miroir(depart, arrivee, nb_pixels);
	Image temp = Image(arrivee);
	Image fenetre;
	fenetre.setHauteur(nb_pixels*2+1);
	fenetre.setLargeur(nb_pixels*2+1);
	
	for(int j=0; j< depart.getHauteur()+nb_pixels; j++)
	{
		for(int i=0; i< depart.getLargeur()+nb_pixels; i++)
		{
			specificationDansFenetre(arrivee, temp, cible, i, i+nb_pixels, j, j+nb_pixels);
			
		}
		
	}

	//specificationDansFenetre(arrivee, arrivee, cible, 0, nb_pixels, 0, nb_pixels);
  
//Image temp = Image(arrivee);
	couper_image(temp, arrivee, nb_pixels);
	
	//arrivee.saveAscii("./data/versionGlissante.pgm");

 // couper_image(temp, arrivee, nb_pixels);

  
	/*arrivee = Image(depart);

	for(int j=0; j< depart.getHauteur(); j++)
	{
		for(int i=0; i< depart.getLargeur(); i++)
		{
		//début de ligne
			if (i==0)
			{
				//debut de colonne
				if (j==0)
				{
std::cout<<"ETAPE : 1"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, 0, pixel_Cote, 0, pixel_Cote);				
				}
				//fin de colonne
				else if (j==depart.getHauteur())
				{
std::cout<<"ETAPE : 2"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, 0, pixel_Cote, j-pixel_Cote, j);
				}else
				{
std::cout<<"ETAPE : 3"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, 0, pixel_Cote, j-pixel_Cote, j+pixel_Cote);
				}
		

			}else if (i==depart.getLargeur()) //fin de ligne
			{
				//debut de colonne
				if (j==0)
				{
std::cout<<"ETAPE : 4"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, i-pixel_Cote, i, 0, pixel_Cote);	
				}
				//fin de colonne
				else if (j==depart.getHauteur())
				{
std::cout<<"ETAPE : 5"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, i-pixel_Cote, i, j-pixel_Cote, j);
				}else
				{
std::cout<<"ETAPE : 6"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, i-pixel_Cote, i, j-pixel_Cote, j+pixel_Cote);
				}
			}else
			{		
				//debut de colonne
				if (j==0)
				{
std::cout<<"ETAPE : 7"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, i-pixel_Cote, i+pixel_Cote, 0, pixel_Cote);	
				}
				//fin de colonne
				else if (j==depart.getHauteur())
				{
std::cout<<"ETAPE : 8"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, i-pixel_Cote, i+pixel_Cote, j-pixel_Cote, j);
				}else
				{
std::cout<<"ETAPE : 9"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, i-pixel_Cote, i+pixel_Cote, j-pixel_Cote, j+pixel_Cote);
				}
			}
		}
	}*/

}





