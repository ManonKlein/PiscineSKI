#ifndef TRAJET_H_INCLUDED
#define TRAJET_H_INCLUDED

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include "Sommet.h"



/* On fait une classe Arete Pour gérer les aretes qui se trouvent entre les sommets. */

class Trajet
{
    ///Partie privée de la classe sommet || Cela correspond aux attributs de la classe
    private :

        int m_TnumeroTrajet;            //numero du trajet en int
        std::string m_TnomTrajet;       //nom du trajet en string
        std::string m_TtypeTrajet;      //type du trajet en string
        int m_TpointDepart;             //point initial du trajet
        int m_TpointArrivee;            //point final du trajet
        float m_TtempsTrajet;           //temps du trajet



    ///Partie publique de la classe Arêtes. || On a donc les méthodes, les fonctions, les constructeurs, les destructeurs, les getteurs et les setteurs.
    public :

        Trajet(); //Constructeur par défaut, sans parametres
        Trajet(int TnumeroTrajet, std::string TnomTrajet, std::string TtypeTrajet,int TpointDepart, int TpointArrivee, float TtempsTrajet); //Constructeur surchargé, pour initialiser les attributs.

        ///_________________GETTER_______________________
        int getterNumeroTrajet();                       //Getteur pour récuperer le numero du trajet
        std::string getterNomTrajet();                  //Getteur pour récuperer le nom du trajet
        std::string getterTypeTrajet();                 //Getteur pour récuperer le type de trajet
        int getterPointDepart();                        //Getteur pour récuperer le point de depart du trajet
        int getterPointArrivee();                       //Getteur pour récuperer le point d'arrivee du trajet
        float getterTempsTrajet();

        ///_________________SETTER____________________________
        void setterTempsTrajet(float temps);

        ///________________FONCTION_____________________________
        void affichageTrajet(); //Fonction pour afficher les aretes et les sommets qu'elles relient.
};

#endif // TRAJET_H_INCLUDED
