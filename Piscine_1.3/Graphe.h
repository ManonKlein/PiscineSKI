#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include "Sommet.h"
#include "Trajet.h"
#include <map>

/*On fait une classe graphe pour manipuler le graphe
Cette classe est en lien avec la classe sommet. */

class Graphe
{
    ///On a la partie privée || On y déclare les attributs de la classe
    private :

    std::vector<Sommet*> m_graphe_points;             //On a un attribut vector de type pointeurs sur sommet, Cela correspond à la liste des sommets
    std::vector<Trajet*> m_liste_trajet;              //On a un attribut vector de type pointeurs sur les aretes//Cela correspond à la liste des aretes

    ///variable algo dijkstra
    std::priority_queue<std::pair<float,Sommet*>> m_file;            ////On déclare la priority_queue


    ///On a ensuite la partie publique || Elle permet d'avoir les méthodes, fonctions, constructeurs , destrcteurs, getteur, setter, et autre
    public :

        Graphe();                           //Constructeur par défaut sans paramètres
        Graphe(std::string myfile);         //Constructeur surchargé
        ~Graphe();                          //Destructeur


        ///_____________________________Getter_____________________________________
        int getter_ordre();                                    //On obtient l'ordre
        int getter_nombreChemin();                             //on recupere le nombre de chemin
        Sommet * getter_points(int point);                     //On récupère la liste des sommets
        std::vector <Sommet*> getterTab();                     //Getteur de type vector pour récuperer la liste complete sommets.
        std::vector<Trajet*>  getter_listeTrajet();            //Getteur pour récuperer la liste totale d'aretes
        Trajet * getter_unTrajet(int numero);                  //Méthode pour récuperer l'arete avec un numéro précis.

        ///____________________________setter_____________________________________
        void settergraphe_points(std::vector<Sommet*> graphe_points);
        std::priority_queue<std::pair<float,Sommet*>> getter_file();


        ///_________________________ Méthodes et fonctions de la classe graphe
        void trajetSommetDepartEtArrive();              //fonction pour trouver les sommets à partir d'un trajet choisi
        void SommettrajetDepartEtArrive();              //fonction pour trouver les trajets relié à un sommet choisi
        float tempsMinutesSecondes(float temps);        //conversion d'un temps en secondes en minutes et secondes
        void calculTempsTrajet();                       //calcul du temps de chaque trajet et push dans la classe trajet


        void algo_Dijkstra(int i, int j);
        void algo_BSFinteressant();

        void affichage();

        Sommet* rechercherPoint(int choix);                              //affichage du menu et de chaque fonctions

} ;

#endif // GRAPHE_H_INCLUDED
