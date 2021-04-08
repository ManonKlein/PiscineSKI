#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Trajet.h"

class Trajet;
/*On fait une classe Sommet pour g�rer
les diff�rents sommets � traiter du graphe */

class Sommet
{
    ///Partie priv�e de la classe sommet || Cela correspond aux attributs de la classe
    private :

        int m_SnumeroPoint;             //int pour l'id d'un point
        std::string m_SnomLieuPoint;    //string pour le nom du point
        int m_SaltitudePoint;           //l'altitude du point
        int m_nbrSommet;                //nombre de sommet totale

        std::vector<Trajet*> m_trajets;
        std::pair<double, Sommet*> m_avant;
        int m_dist;

    ///Partie publique de la classe Sommet || On a donc les m�thodes, les fonctions, les constructeurs, les destructeurs, les getteurs et les setteurs.
    public :

        Sommet();                                                                     //Constructeur par d�faut
        Sommet(int SnumeroPoint, std::string SnomLieuPoint, int SaltitudePoint);      //Constructeur surcharg�
        Sommet(int nbrSommet);                                                        //constructeur surcharg� bis
        ~Sommet();                                                                    //destructeur

        /// ____________________GETTER__________________________
        int getterSnumeroPoint();               //Getteur pour r�cuperer le numeros des points
        std::string getterSnomLieuPoint();      //Getteur pour r�cuperer le nom du lieu
        int getterSaltitudePoint();             //Getteur pour r�cuperer l'altitude

        int getterSnbrSommet();
        int getDist();
        std::vector<Trajet*> getTrajets();


        std::pair<double, Sommet*> getAvant();



        ///__________________________________SETTER____________________________
        void setterSnumeroPoint(int SnumeroPoint);              //Setter pour modifier l'entier
        void setterSnomLieuPoint(std::string SnomLieuPoint);    //Setter pour modifier l'entier
        void setterSaltitudePoint(int SaltitudePoint);          //Setter pour modifier l'entier

        void setterSmarque(int marque); ///BFS

        void ajouterTrajet(Trajet* nouveauTrajet);
        void setDist(int nouvelleDist);

        void setterPred(std::pair<double, Sommet*> nouveauPred);


        ///__________________________________FONCTION_____________________________________



                                                                                             //Destructeur pour lib�rer la m�moire
};

#endif // SOMMET_H_INCLUDED
