#include "Traitement.hpp"


	Traitement::Traitement()
	{

	}

	Traitement::~Traitement()
	{
	    
	}




Image& Traitement::filtreMedian(Image& im)
{
	Image image = Image(im);
	std::vector<int> nouvelles_valeurs = std::vector<int>();
	int median;
	
	//création du tableau
	std::vector<int> tableau = std::vector<int>();
  
	for(int i=0; i< im.getLargeur()*im.getHauteur(); i++)
	{
		tableau.clear();
		
		tableau.push_back(im.getPixel(i));
		
		//1. on remplit du tableau
		//début de ligne
		if (i%im.getLargeur()==0)
		{
			tableau.push_back(im.getPixel(i+1));
			//debut de colonne
			if (i<im.getLargeur())
			{
				tableau.push_back(im.getPixel(i+im.getLargeur()));
				tableau.push_back(im.getPixel(i+im.getLargeur()+1));	
			}
			//fin de colonne
			else if (i>=im.getLargeur()*(im.getHauteur()-1))
			{
				tableau.push_back(im.getPixel(i-im.getLargeur()));
				tableau.push_back(im.getPixel(i-im.getLargeur()+1));
			}else
			{
				tableau.push_back(im.getPixel(i+im.getLargeur()));
				tableau.push_back(im.getPixel(i+im.getLargeur()+1));
				tableau.push_back(im.getPixel(i-im.getLargeur()));
				tableau.push_back(im.getPixel(i-im.getLargeur()+1));
			}
		
			
			
		}else if (i%im.getLargeur()==im.getLargeur()-1) //fin de ligne
		{
			tableau.push_back(im.getPixel(i-1));
			//debut de colonne
			if (i<im.getLargeur())
			{
				tableau.push_back(im.getPixel(i+im.getLargeur()));
				tableau.push_back(im.getPixel(i+im.getLargeur()-1));
			} 
			//fin de colonne
			else if (i>im.getLargeur()*(im.getHauteur()-1))
			{
				tableau.push_back(im.getPixel(i-im.getLargeur()));
				tableau.push_back(im.getPixel(i-im.getLargeur()-1));
			}else
			{
				tableau.push_back(im.getPixel(i+im.getLargeur()));
				tableau.push_back(im.getPixel(i+im.getLargeur()-1));
				tableau.push_back(im.getPixel(i-im.getLargeur()));
				tableau.push_back(im.getPixel(i-im.getLargeur()-1));
			
			}
		}else
		{	
		  
			tableau.push_back(im.getPixel(i-1));
			tableau.push_back(im.getPixel(i+1));
			
			//debut de colonne
			if (i<im.getLargeur())
			{
				tableau.push_back(im.getPixel(i+im.getLargeur()));
				tableau.push_back(im.getPixel(i+im.getLargeur()+1));
				tableau.push_back(im.getPixel(i+im.getLargeur()-1));
			}
			//fin de colonne
			else if (i>im.getLargeur()*(im.getHauteur()-1))
			{
				tableau.push_back(im.getPixel(i-im.getLargeur()));
				tableau.push_back(im.getPixel(i-im.getLargeur()+1));
				tableau.push_back(im.getPixel(i-im.getLargeur()-1));
			}else
			{	
				tableau.push_back(im.getPixel(i-im.getLargeur()));
				tableau.push_back(im.getPixel(i-im.getLargeur()+1));
				tableau.push_back(im.getPixel(i-im.getLargeur()-1));
				
				tableau.push_back(im.getPixel(i+im.getLargeur()));
				tableau.push_back(im.getPixel(i+im.getLargeur()+1));
				tableau.push_back(im.getPixel(i+im.getLargeur()-1));	
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
		//nouvelles_valeurs.push_back(median);
		image.setPixel(i, median);
	}
	
	//Image* image = new(
	return image;
}