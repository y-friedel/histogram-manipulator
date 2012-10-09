#include "Traitement.hpp"
#include <iostream>

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
 * 	Matrice dont on va se servir pour la diffusion d'erreur
 * 
 * 	Pas besoin de s'inquieter de la taille ou de la valeur_max de l'image d'arrivée
 */
void Traitement::diffusionErreurMatrice(const Image& depart, Image& arrivee, Matrice matrice)
{
	arrivee = Image(depart);
	
	//On applique diffusion d'erreur sur depart
	//arrivee devient l'image avec les erreurs diffusées
	diffusionErreur(depart, arrivee);
	
	int erreur;
	int indice;
	
	for(int j=0; j<= depart.getHauteur(); j++)
	{
		for(int i=0; i< depart.getLargeur(); i++)
		{
			indice = depart.getLargeur()*j+i;
			erreur = depart.getPixel(indice)*arrivee.getPixel(indice);
			
			   //A remplir
		}		
	}	
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
	arrivee = Image(depart);
	
	//On créé une nouvelle image à la taille de la fenetre
	int largeur = X_max-X_min+1;
	int hauteur =Y_max-Y_min+1;
	
	std::vector<int> valeurs = std::vector<int>();
	valeurs.resize(largeur*hauteur);
	
	for(int j=Y_min; j<=Y_max; j++)
	{
		for(int i=X_min; i<=X_max; i++)
		{
			valeurs[j*largeur+i] = arrivee.getPixel(depart.getLargeur()*j+i);
		}
	}
	
	Image fenetre = Image(valeurs, depart.getFormat(), largeur, hauteur, depart.getValeurMax());
	//fenetre.saveAscii("./data/fenetre.pgm");
	fenetre.afficher();
	
	//on appelle specification sur notre fenetre
	Fonction fonction = Fonction(fenetre.getValeurMax());
std::cout<<"LA"<<std::endl;
	fonction.specification(fenetre, fenetre, cible);
std::cout<<"LA2"<<std::endl;
	//fenetre.saveAscii("./data/specification.pgm");
	
	//On remplace les pixels dans notre nouvelle image
	int compteur_fenetre = 0;
	
	for(int j=Y_min; j< Y_max; j++)
	{

		for(int i=X_min; i< X_max; i++)
		{ 
			arrivee.setPixel(depart.getLargeur()*j+i, fenetre.getPixel(compteur_fenetre));
			compteur_fenetre++;
		}	  

	}

}


void Traitement::versionGlissante(const Image& depart, Image& arrivee, Histogramme& cible, int pixel_Cote)
{
	arrivee = Image(depart);

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
std::cout<<"1"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, 0, pixel_Cote, 0, pixel_Cote);				
				}
				//fin de colonne
				else if (j==depart.getHauteur())
				{
std::cout<<"2"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, 0, pixel_Cote, j-pixel_Cote, j);
				}else
				{
std::cout<<"3"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, 0, pixel_Cote, j-pixel_Cote, j+pixel_Cote);
				}
		

			}else if (i==depart.getLargeur()) //fin de ligne
			{
				//debut de colonne
				if (j==0)
				{
std::cout<<"4"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, i-pixel_Cote, i, 0, pixel_Cote);	
				}
				//fin de colonne
				else if (j==depart.getHauteur())
				{
std::cout<<"5"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, i-pixel_Cote, i, j-pixel_Cote, j);
				}else
				{
std::cout<<"6"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, i-pixel_Cote, i, j-pixel_Cote, j+pixel_Cote);
				}
			}else
			{		
				//debut de colonne
				if (j==0)
				{
std::cout<<"7"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, i-pixel_Cote, i+pixel_Cote, 0, pixel_Cote);	
				}
				//fin de colonne
				else if (j==depart.getHauteur())
				{
std::cout<<"8"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, i-pixel_Cote, i+pixel_Cote, j-pixel_Cote, j);
				}else
				{
std::cout<<"9"<<std::endl;
					specificationDansFenetre(arrivee, arrivee, cible, i-pixel_Cote, i+pixel_Cote, j-pixel_Cote, j+pixel_Cote);
				}
			}
		}
	}
}





