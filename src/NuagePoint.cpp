
#include "NuagePoint.hpp"
#include <iostream>
#include <cstdlib> 
#include <ctime>

#include <map>

NuagePoint::NuagePoint()
{
	nuage = std::vector<Point>();
}

NuagePoint::NuagePoint(Point point)
{
	nuage = std::vector<Point>();
	nuage.push_back(point);
}

NuagePoint::NuagePoint(std::vector<Point> _nuage)
{
	nuage = std::vector<Point>();
	copy(_nuage.begin(), _nuage.end(), nuage.begin());	
}

NuagePoint::NuagePoint(int nb_points, int maximumXY)
{
	nuage = std::vector<Point>();
	nuage.resize(nb_points);
	
	srand ( time(NULL) );
	
	for(int i=0; i<nb_points; i++)
	{
		nuage[i] = Point(rand()%(maximumXY), rand()%(maximumXY));	  
	}
}

NuagePoint::~NuagePoint()
{
  
}

	
Point NuagePoint::getPoint(int i) const
{
	return nuage[i];
}

void NuagePoint::setPoint(int i, Point& p)
{
	nuage[i] = p;
}

int NuagePoint::getTaille() const
{
	return nuage.size();
}

void NuagePoint::ajoutPoint(const Point& point)
{
	nuage.push_back(point);
}

	
void NuagePoint::afficher() const
{
	for(unsigned int i=0; i<nuage.size(); i++)
		nuage[i].afficher();
}

/* Cette procédure calcule les k-moyennes d'un nuage de points
 * Paramètres :
 * 	int k : le nombre de sous nuages de points que l'on veut trouver
 * 	int t : le nombre d'iterations max
 * 
 * 	Elle retourne une vector de nuages de points (les sous nuages de points)
 */	
std::vector<NuagePoint> NuagePoint::k_moyennes(int k, int t)
{
    Point temporaire;
    int alea;
    srand ( time(NULL) );

    std::vector<NuagePoint> classes = std::vector<NuagePoint>();
    std::vector<Point> centres = std::vector<Point>();

    std::vector<int> index_centres = std::vector<int>();
    std::vector<Point> anciens_centres = std::vector<Point>();

    std::vector<double> distances = std::vector<double>();
    std::vector<int> index_distances = std::vector<int>();

    std::vector<double> moyennes_distances = std::vector<double>();
    std::vector<int> index_moyennes_distances = std::vector<int>();

    bool stabilisation = false;
    int temp;
    int temp2;
    int longueur;
    bool echange;
    double moyenne;
    bool est_centre;
    Point p;
    distances.resize(k);
    anciens_centres.resize(k);
    index_distances.resize(k);

    //choix des k aléatoires
    for(int i=0; i<k; i++)
    {
        alea = rand()%(nuage.size());
        temporaire = getPoint(alea);
        classes.push_back(NuagePoint(temporaire));
        centres.push_back(temporaire);
        index_centres.push_back(alea);
	}

    //k-moyennes
    for(int nb_iteration=0; nb_iteration<t; nb_iteration++)
    {
      std::cout<<nb_iteration<<std::endl;
        for(unsigned int i=0; i<nuage.size(); i++)
        {
            est_centre = false;

            for(unsigned int j=0; j<centres.size(); j++)
            {
                if(centres[j].egal(nuage[i]))
                {
                      est_centre = true;
                      break;
                }
            }

            if(est_centre)
            {
                p = nuage[i];
                p.setMarque(true);
                nuage[i] = p;
            }
            else
            {
                p = nuage[i];
                p.setMarque(false);
                nuage[i] = p;
            }
        }

        //on affecte les points aux classes selon la distance
        for(unsigned int i=0; i<nuage.size(); i++)
        {
            if(nuage[i].getMarque()==false)
            {	//on calcule les distances
                for(int j=0; j<k; j++)
                {
                    distances[j] = nuage[i].distance(centres[j]);
                    index_distances[j] = j;
                }

                //on trie les distances
                longueur = distances.size();

                do
                {
                    echange = false;
                    for(int j=0; j<longueur-1; j++)
                    {
                        if(distances[j]>distances[j+1])
                        {
                            temp = distances[j];
                            distances[j] = distances[j+1];
                            distances[j+1] = temp;

                            temp2 = index_distances[j];
                            index_distances[j] = index_distances[j+1];
                            index_distances[j+1] = temp2;

                            echange = true;
                        }
                    }
                    longueur--;
                }
                while(echange);

                //on regarde le centre plus proche
                classes[index_distances[0]].ajoutPoint(nuage[i]);
            }
        }

        //recalcul des centres
        copy(centres.begin(), centres.end(), anciens_centres.begin());

        for(int i=0; i<k; i++)
        {
            moyennes_distances.resize(classes[i].getTaille());
            index_moyennes_distances.resize(classes[i].getTaille());

            for(int j=0; j<classes[i].getTaille(); j++)
            {
                moyenne = 0;

                for(int k=0; k<classes[i].getTaille(); k++)
                {
                    moyenne += classes[i].getPoint(j).distance(classes[i].getPoint(k));
                }
                moyennes_distances[j]= moyenne;
                index_moyennes_distances[j] = j;
            }
            //on trie les moyennes
            longueur = moyennes_distances.size();

            do
            {
                echange = false;
                for(int j=0; j<longueur-1; j++)
                {
                    if(moyennes_distances[j]>moyennes_distances[j+1])
                    {
                        temp = moyennes_distances[j];
                        moyennes_distances[j] = moyennes_distances[j+1];
                        moyennes_distances[j+1] = temp;

                        temp2 = index_moyennes_distances[j];
                        index_moyennes_distances[j] = index_moyennes_distances[j+1];
                        index_moyennes_distances[j+1] = temp2;

                        echange = true;
                    }
                }
                longueur--;
            }
            while(echange);

            centres[i] = classes[i].getPoint(index_moyennes_distances[0]);
        }

        //Ovérifie si les centres sont stabilisés
        for(int i=0; i<k; i++)
        {
            if(!centres[i].egal(anciens_centres[i]))
            {
                stabilisation = false;
                break;
            }
            else
            {
                stabilisation = true;
            }
        }

        if(stabilisation)
            break;

        //On vide nos classes
        if (nb_iteration != t-1)
        {
            classes.clear();
            classes.resize(k);
        }

        //On remplie nos classes avec les nouveaux centres
        for(int i=0; i<k; i++)
        {
            classes[i] = centres[i];
        }
    }

    return classes;
}
int iter = 0;
std::vector<NuagePoint> NuagePoint::k_moyennes_m(unsigned int k,unsigned int t)
{
    Point temporaire;
    int alea;
    srand ( time(NULL) );

    std::vector<NuagePoint> classes = std::vector<NuagePoint>();

    std::vector<Point> v_centres = std::vector<Point>();
    std::vector<Point> v_anciens_centres = std::vector<Point>();
    
    
    std::multimap<int, double> m_distances = std::multimap<int, double>();
    std::multimap<int, double> m_moyennes_distances = std::multimap<int, double>();

    bool stabilisation = false;
    double temp;
    int longueur;
    bool echange;
    double moyenne;
    bool est_centre;
    Point p;
    
    std::vector<Point>::iterator it;

    //choix des k aléatoires
    for(unsigned int i=0; i<k; i++)
    {
        alea = rand()%(nuage.size());
        temporaire = getPoint(alea);
        classes.push_back(NuagePoint(temporaire));
        temporaire.afficher();
        v_centres.push_back(temporaire);
    }

    //k-moyennes
    for(unsigned int nb_iteration=0; nb_iteration<t; nb_iteration++)
    {
      std::cout<<nb_iteration<<std::endl;
        for(unsigned int i=0; i<nuage.size(); i++)
        {
            est_centre = false;

            /*m_centres.size()*/
            for(it = v_centres.begin(); it != v_centres.end(); it++)
            {
                if((*it).egal(nuage[i]))
                {
                      est_centre = true;
                      break;
                }
            }

            if(est_centre)
            {
                p = nuage[i];
                p.setMarque(true);
                nuage[i] = p;
            }
            else
            {
                p = nuage[i];
                p.setMarque(false);
                nuage[i] = p;
            }
        }

        //on affecte les points aux classes selon la distance
        for(unsigned int i=0; i<nuage.size(); i++)
        {
            if(nuage[i].getMarque()==false)
            {	
				//on calcule les distances
                for(unsigned int j=0; j<k; j++)
                {
                    m_distances.erase(j);
                    m_distances.insert(std::make_pair(j, nuage[i].distance((v_centres[j]))));
                    //distances[j] = nuage[i].distance(centres[j]);
                    //index_distances[j] = j;
                }

                //on trie les distances
                //longueur = distances.size();
                //longueur = m_distances.size();
                unsigned int index_min = 0;
                for(unsigned int j=0; j<m_distances.size(); j++)
                {
					if(m_distances.find(j)->second <= m_distances.find(index_min)->second)
                    {
						index_min = j;
					}
				}
					
                /*do
                {
                    echange = false;
                    for(int j=0; j<longueur-1; j++)
                    {						
                        //if(distances[j]>distances[j+1])
                        if(m_distances.find(j)->second > m_distances.find(j+1)->second)
                        {
                            temp = m_distances.find(j)->second;
                            m_distances.erase(j);
                            m_distances.insert(std::make_pair(j, m_distances.find(j+1)->second));
                            m_distances.erase(j+1);
                            m_distances.insert(std::make_pair(j+1, temp));

                            echange = true;
                        }
                    }
                    longueur--;
                }
                while(echange);*/

                //on regarde le centre plus proche
                //classes[index_distances[0]].ajoutPoint(nuage[i]);
                classes[index_min].ajoutPoint(nuage[i]);
                std::cout << "LAUL " << m_distances.begin()->second << std::endl;


            }
        }

        //recalcul des centres
        //copy(centres.begin(), centres.end(), anciens_centres.begin());

       // copy(m_centres.begin(), m_centres.end(), m_anciens_centres.begin());

        v_anciens_centres = std::vector<Point>(v_centres);

        for(unsigned int i=0; i<k; i++)
        {
            //m_moyennes_distances.resize(classes[i].getTaille());
            //index_moyennes_distances.resize(classes[i].getTaille());

            for(int j=0; j<classes[i].getTaille(); j++)
            {
                moyenne = 0;

                for(int k=0; k<classes[i].getTaille(); k++)
                {
                    moyenne += classes[i].getPoint(j).distance(classes[i].getPoint(k));
                }
                //moyennes_distances[j]= moyenne;
                //index_moyennes_distances[j] = j;
                m_moyennes_distances.erase(j);
                m_moyennes_distances.insert(std::make_pair(j, moyenne));
            }
            //on trie les moyennes
            longueur = m_moyennes_distances.size();

            do
            {
                echange = false;
                for(int j=0; j<longueur-1; j++)
                {
                    //if(moyennes_distances[j] > moyennes_distances[j+1])
                    if(m_moyennes_distances.find(j)->second > m_moyennes_distances.find(j+1)->second)
                    {
                        //temp = moyennes_distances[j];
                        //moyennes_distances[j] = moyennes_distances[j+1];
                        //moyennes_distances[j+1] = temp;

                        //temp2 = index_moyennes_distances[j];
                        //index_moyennes_distances[j] = index_moyennes_distances[j+1];
                        //index_moyennes_distances[j+1] = temp2;

                        temp = m_moyennes_distances.find(j)->second;
                        m_moyennes_distances.erase(j);
                        m_moyennes_distances.insert(std::make_pair(j, m_moyennes_distances.find(j+1)->second));
                        m_moyennes_distances.erase(j+1);
                        m_moyennes_distances.insert(std::make_pair(j+1, temp));

                        echange = true;
                    }
                }
                longueur--;
            }
            while(echange);

            //centres[i] = classes[i].getPoint(index_moyennes_distances[0]);
            v_centres[i] = classes[i].getPoint(m_moyennes_distances.begin()->first);
        }

        //Ovérifie si les centres sont stabilisés
        for(unsigned int i=0; i<k; i++)
        {
            //if(!centres[i].egal(anciens_centres[i]))
            if(!v_centres[i].egal(v_anciens_centres[i]))
            {
                stabilisation = false;
                break;
            }
            else
            {
                stabilisation = true;
            }
        }

        if(stabilisation)
            break;

        //On vide nos classes
        if (nb_iteration != t-1)
        {
            classes.clear();
            classes.resize(k);
        }

        //On remplie nos classes avec les nouveaux centres
        for(unsigned int i=0; i<k; i++)
        {
            //classes[i] = centres[i];
            classes[i] = v_centres[i];
        }
    }

    return classes;
}

