#ifndef TRAJET_H_INCLUDED
#define TRAJET_H_INCLUDED

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include "Sommet.h"



/* On fait une classe Arete Pour g�rer les aretes qui se trouvent entre les sommets. */

class Trajet
{
    ///Partie priv�e de la classe sommet || Cela correspond aux attributs de la classe
    private :

        int m_TnumeroTrajet;            //numero du trajet en int
        std::string m_TnomTrajet;       //nom du trajet en string
        std::string m_TtypeTrajet;      //type du trajet en string
        int m_TpointDepart;             //point initial du trajet
        int m_TpointArrivee;            //point final du trajet
        float m_TtempsTrajet;           //temps du trajet



    ///Partie publique de la classe Ar�tes. || On a donc les m�thodes, les fonctions, les constructeurs, les destructeurs, les getteurs et les setteurs.
    public :

        Trajet(); //Constructeur par d�faut, sans parametres
        Trajet(int TnumeroTrajet, std::string TnomTrajet, std::string TtypeTrajet,int TpointDepart, int TpointArrivee, float TtempsTrajet); //Constructeur surcharg�, pour initialiser les attributs.

        ///_________________GETTER_______________________
        int getterNumeroTrajet();                       //Getteur pour r�cuperer le numero du trajet
        std::string getterNomTrajet();                  //Getteur pour r�cuperer le nom du trajet
        std::string getterTypeTrajet();                 //Getteur pour r�cuperer le type de trajet
        int getterPointDepart();                        //Getteur pour r�cuperer le point de depart du trajet
        int getterPointArrivee();                       //Getteur pour r�cuperer le point d'arrivee du trajet
        float getterTempsTrajet();

        ///_________________SETTER____________________________
        void setterTempsTrajet(float temps);

        ///________________FONCTION_____________________________
        void affichageTrajet(); //Fonction pour afficher les aretes et les sommets qu'elles relient.
};

#endif // TRAJET_H_INCLUDED
