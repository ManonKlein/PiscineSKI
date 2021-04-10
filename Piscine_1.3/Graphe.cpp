#include "Graphe.h"

/// _____________________________ CONSTRUCTEUR, CONSTRUCTEUR SURCHARGE ET DESCTRUCTEUR ____________________________

///Méthode d'initialisation de la classe Graphe --> Cosntructeur
Graphe::Graphe()
{
    //Vide
}

///Méthode pour ouvrir le fichier a traiter
Graphe::Graphe(std::string myfile)
{
    std::ifstream ifs{myfile};

    /* On a une premiere fonction pour déclarer le fichier On l'ouvre,
    On vérifie son ouverture correcte et on le manipule. */

    if (!ifs)
    {
        std::cout << "Impossible d'ouvrir en lecture " << std::endl;
    }

    ///initialisation nombre de points
    int nombrePoints=0;         //On utilise un entier pour récuperer l'ordre du graphe.
    ifs >> nombrePoints;        //on recupere l'ordre dans le fichier



    ///On initialise les points leurs numeros, le nom et l'altitude
    int numeroPoint;
    std::string nomLieuPoint;
    int altitudePoint;


    /// POUR BFS CA %ARCHE PAS CONNARD__________________BFS__________________BFS____________________BFS________________BFS
//   m_V = m_graphe_points.size();




    for (int i=0; i<nombrePoints; i++)      // On fait une boucle pour i allant de 0 au nombre de points
    {
        ifs >> numeroPoint;                 //on recuper le numero du point dans le fichier txt
        ifs >> nomLieuPoint;                //on recupere le nom du lieu du point dans le fichier txt
        ifs >> altitudePoint;               //on recupere l'altitude du point dans le fichier txt
        m_graphe_points.push_back(new Sommet(numeroPoint, nomLieuPoint, altitudePoint));

        //adj.push_back(new Sommet(numeroPoint, nomLieuPoint, altitudePoint));
        // adj.push_back(new Sommet());
        ///BFS BFS BFS BFS BFS
        this->m_V= nombrePoints;
        adj = new std::list<Sommet>[m_V];
        adj[i].push_back(Sommet(numeroPoint, nomLieuPoint, altitudePoint));                // ajouter l'arrete a la liste adj*/
    }






    ///On déclare un entier pour obtenir la taille du graphe
    int nombreChemin = 0;
    ifs >> nombreChemin;               //On recupere la taille dans le fichier

    ///on declare un entier pour
    int numeroTrajet;
    std::string nomTrajet;
    std::string typeTrajet;
    int pointDepart;
    int pointArrivee;
    for(int j=0; j<nombreChemin; j++)
    {
        ifs>> numeroTrajet;
        ifs>> nomTrajet;
        ifs>>typeTrajet;
        ifs>>pointDepart;
        ifs>>pointArrivee;
        m_liste_trajet.push_back(new Trajet(numeroTrajet,nomTrajet,typeTrajet,pointDepart,pointArrivee,0));
        rechercherPoint(pointDepart)->ajouterTrajet(m_liste_trajet.back());
    }
    calculTempsTrajet();
}

///Méthode pour libérer la mémoire --> Destructeur
Graphe::~Graphe()
{
    for (auto s : m_graphe_points)
    {
        delete s;                       //On libère la mémoire
    }

}

void Graphe::Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void Graphe::gotoligcol( int lig, int col )
{
// ressources
    COORD mycoord;

    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

/// ______________________________________________ GETTER VARIABLE ______________________________________________

/*Fonction pour retourner et garde tous les sommets du graphe afin de pourvoir les manipuler
//Ils sont initaliement des attributs, dans la partie privée de la classe On ne peut donc pas les manipuler. */


///Fonction pour récupérer l'ordre du graphe || Comme il s'agit d'un attribut privé, on utilse un getteur.
int Graphe::getter_ordre()
{
    return m_graphe_points.size();
    //On utilise un return
}

///Fonction pour récuperer un point dans la liste
Sommet * Graphe::getter_points(int point)
{
    return m_graphe_points[point]; //On utilise un return
}

///Fonction pour récuperer l'ensemble des sommets du graphes.
std::vector <Sommet*> Graphe::getterTab()
{
    return m_graphe_points; //On utilise un return
}


void Graphe::settergraphe_points(std::vector<Sommet*> graphe_points)
{
    m_graphe_points= graphe_points;
}


///Fonction pour avoir un acces illimité à toutes les aretes du graph || Ils sont initaliement des attributs, dans la partie privée de la classe
///On ne peut donc pas les manipuler.
std::vector <Trajet*> Graphe::getter_listeTrajet()
{
    return m_liste_trajet;                   //On utilise un return, cela forme un getteur.
}

///Fonction qui sert de getteur || Permet de récuperer les aretes du graphe dans leur totalité
Trajet*Graphe::getter_unTrajet(int numero)
{
    return m_liste_trajet[numero]; //On utilise un return
}

std::priority_queue<std::pair<float,Sommet*>> Graphe::getter_file()
{
    return m_file;
}



///_________________________________________ FONCTION ___________________________________________________

///fonction pour trouver a partir d'un NUMERO /NOM de trajet les sommets qui le precede ou qui le suive
void Graphe::trajetSommetDepartEtArrive()
{
    int choix;
    do
    {
        gotoligcol(5,30);
        Color(11,0);
        std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////";
        gotoligcol(6,30);
        Color(9,0);
        std::cout << "//'                                                                                                                  '//";
        Color(15,0);
        gotoligcol(7,30);
        std::cout << "//                                   Que voulez vous faire ?                                                          //";
        gotoligcol(8,30);
        std::cout << "//                                                                                                                    //";
        gotoligcol(9,30);
        std::cout << "// 1. A partir du NUMERO du trajet trouver le point de depart et d'arriver de ce trajet                               //";
        gotoligcol(10,30);
        std::cout << "// 2. A partir du NOM du trajet trouver le point de depart et d'arriver de ce trajet                                  //";
        gotoligcol(11,30);
        std::cout << "// 3. Quitter la selection                                                                                            //";
        gotoligcol(12,30);
        std::cout << "//                                                                                                                    //";
        gotoligcol(13,30);
        std::cout << "//        Choix :                                                                                                     //";
        gotoligcol(14,30);
        Color(9,0);
        std::cout << "//'                                                                                                                  '//";
        gotoligcol(15,30);
        Color(11,0);
        std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////";
        Color(15,0);
        do
        {
            gotoligcol(13,49);
            std::cout<<"                   ";
            gotoligcol(13,49);
            std::cin >> choix;
        }
        while((choix<1) || (choix>3));


        //Fonction switch pour que l'utilisateur puisse choisir ce qu'il souhaite faire.
        switch(choix)
        {
        case 1:
        {
            int numtraj;
            gotoligcol(17,30);
            std::cout<<"Vous avez choisi de choisir a partir du numero de trajet " <<std::endl;
            gotoligcol(18,30);
            std::cout<<"Veuillez saisir le numero : ";
            do
            {
                gotoligcol(18,58);
                std::cout<<"                   ";
                gotoligcol(18,58);
                Color(11,0);
                std::cin >> numtraj;
            }
            while((choix<1) || (choix>95));
            Color(15,0);

            int pointdepart,pointarrivee;
            std::string nompointdepart, nompointarrivee;
            for (auto l : m_liste_trajet)
            {
                if (l->getterNumeroTrajet() == numtraj)
                {
                    pointdepart = l->getterPointDepart();                   //on recupere le point de depart de ce trajet
                    pointarrivee = l->getterPointArrivee();                 //on recupere le point d'arrivee de ce trajet
                    for (auto m : m_graphe_points)                          //on parcours la liste des points
                    {
                        if(pointdepart == m->getterSnumeroPoint())          //si le point correspond au point de depart
                        {
                            nompointdepart = m->getterSnomLieuPoint();      //on recupere le nom du point de depart
                        }
                        if(pointarrivee == m->getterSnumeroPoint())         //si le point correspon au point de depart
                        {
                            nompointarrivee = m->getterSnomLieuPoint();     //on recupere le nom du point d'arrivee
                        }

                    }

                    gotoligcol(20,30);
                    Color(11,0);
                    std::cout<<" A partir du trajet numero "<<numtraj;

                    Color(15,0);
                    gotoligcol(21,30);
                    std::cout<<" -le point de depart de ce trajet est le numero :"<<pointdepart<<" qui corssepond a "<<nompointdepart;
                    gotoligcol(22,30);
                    std::cout<<" -le point d'arrivee de ce trajet est le numero :"<<pointarrivee<<" qui correspond a "<<nompointarrivee;


                }
            }
            /*Avec ces fonctions, l'utilisateur peut appuyer sur n'importe quelle touche pour continuer,
            cela va nettoyer la console */

            //On saute une ligne
            gotoligcol(24,70);
            system("pause");
            system("cls");
        }
        break;

        case 2:
        {
            std::string nomtraj;
            gotoligcol(17,30);
            std::cout<<"Vous avez choisi de choisir a partir du nom de trajet ";
            gotoligcol(18,30);
            std::cout<<"Veuillez saisir le nom du trajet : ";
            do
            {
                gotoligcol(18,66);
                std::cout<<"                   ";
                gotoligcol(18,66);
                Color(11,0);
                std::cin >> nomtraj;
            }
            while((choix<1) || (choix>95));
            Color(15,0);

            int pointdepart,pointarrivee;
            std::string nompointdepart, nompointarrivee;
            for (auto l : m_liste_trajet)
            {
                if (l->getterNomTrajet() == nomtraj)
                {
                    pointdepart = l->getterPointDepart();                   //on recupere le point de depart de ce trajet
                    pointarrivee = l->getterPointArrivee();                 //on recupere le point d'arrivee de ce trajet
                    for (auto m : m_graphe_points)                          //on parcours la liste des points
                    {
                        if(pointdepart == m->getterSnumeroPoint())          //si le point correspond au point de depart
                        {
                            nompointdepart = m->getterSnomLieuPoint();      //on recupere le nom du point de depart
                        }
                        if(pointarrivee == m->getterSnumeroPoint())         //si le point correspon au point de depart
                        {
                            nompointarrivee = m->getterSnomLieuPoint();     //on recupere le nom du point d'arrivee
                        }

                    }
                    gotoligcol(20,30);
                    Color(11,0);
                    std::cout<<" A partir du trajet nomme "<<nomtraj;
                    Color(15,0);
                    gotoligcol(21,30);
                    std::cout<<" -le point de depart de ce trajet est le numero :"<<pointdepart<<" qui correspond a "<<nompointdepart;
                    gotoligcol(22,30);
                    std::cout<<" -le point d'arrivee de ce trajet est le numero :"<<pointarrivee<<" qui correspond a "<<nompointarrivee;

                }
            }

            /*Avec ces fonctions, l'utilisateur peut appuyer sur n'importe quelle touche pour continuer,
            cela va nettoyer la console */

            //On saute une ligne
            gotoligcol(24,70);
            system("pause");
            system("cls");
        }
        break;

        case 3:

            break;

        } //fin du switch
    }
    while(choix != 3);
}

///fonction pour trouver a partir d'un NUMERO/NOM d'un SOMMET tous les trajets qui en partent et qui permettent d'y arriver
void Graphe::SommettrajetDepartEtArrive()
{
    int choix;
    do
    {

        gotoligcol(5,30);
        Color(11,0);
        std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////";
        gotoligcol(6,30);
        Color(9,0);
        std::cout << "//'                                                                                                                  '//";
        Color(15,0);
        gotoligcol(7,30);
        std::cout << "//                                   Que voulez vous faire ?                                                          //";
        gotoligcol(8,30);
        std::cout << "//                                                                                                                    //";
        gotoligcol(9,30);
        std::cout << "// 1. A partir du NUMERO du point trouver les trajets qui en partent et qu'y permettent d'y arriver                   //";
        gotoligcol(10,30);
        std::cout << "// 2. A partir du NOM du lieu trouver les trajets qui en partent et qu'y permettent d'y arriver                       //";
        gotoligcol(11,30);
        std::cout << "// 3. Quitter la selection                                                                                            //";
        gotoligcol(12,30);
        std::cout << "//                                                                                                                    //";
        gotoligcol(13,30);
        std::cout << "//        Choix :                                                                                                     //";
        gotoligcol(14,30);
        Color(9,0);
        std::cout << "//'                                                                                                                  '//";
        gotoligcol(15,30);
        Color(11,0);
        std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////";
        Color(15,0);
        do
        {
            gotoligcol(13,49);
            std::cout<<"                   ";
            gotoligcol(13,49);
            std::cin >> choix;
        }
        while((choix<1) || (choix>3));


        //Fonction switch pour que l'utilisateur puisse choisir ce qu'il souhaite faire.
        switch(choix)
        {
        case 1:
        {
            int numpoint;
            gotoligcol(17,30);
            std::cout<<"Vous avez choisi de choisir a partir du numero du point " <<std::endl;
            gotoligcol(18,30);
            std::cout<<"Veuillez saisir le numero : ";
            do
            {
                gotoligcol(18,58);
                std::cout<<"                   ";
                gotoligcol(18,58);
                Color(11,0);
                std::cin >> numpoint;
            }
            while((choix<1) || (choix>37));
            Color(15,0);

            int trajetQuiArriveINT, trajetQuiPartINT;
            std::string trajetQuiArrive, trajetQuiPart;
            gotoligcol(20,0);
            for (auto m : m_liste_trajet)                           //on parcours la liste des trajets
            {
                if(numpoint == m->getterPointDepart())              //si le point correspond au point de depart
                {
                    trajetQuiArriveINT=m->getterNumeroTrajet();     //on recupere le numero du trajet
                    trajetQuiArrive = m->getterNomTrajet();         //on recupere le nom du trajet

                    std::cout<<" Le trajet numero : "<<trajetQuiArriveINT<<" nomme : "<<trajetQuiArrive<<" part du point choisi";
                    std::cout<<" "<<std::endl;
                }

                if(numpoint == m->getterPointArrivee())             //si le point correspond au point de depart
                {
                    trajetQuiPartINT=m->getterNumeroTrajet();       //on recupere le numero du trajet
                    trajetQuiPart = m->getterNomTrajet();           //on recupere le nom du trajet
                    std::cout<<" Le trajet numero : "<<trajetQuiPartINT<<" nomme : "<<trajetQuiPart<<" arrive au point choisi";
                    std::cout<<" "<<std::endl;
                }

            }
            /*Avec ces fonctions, l'utilisateur peut appuyer sur n'importe quelle touche pour continuer,
            cela va nettoyer la console */

            //On saute une ligne
            gotoligcol(34,70);
            system("pause");
            system("cls");
        }
        break;

        case 2:
        {
            std::string nompoint;
            gotoligcol(17,30);
            std::cout<<"Vous avez choisi de choisir a partir du numero du point " <<std::endl;
            gotoligcol(18,30);
            std::cout<<"Veuillez saisir le nom du point :  ";
            do
            {
                gotoligcol(18,64);
                std::cout<<"                   ";
                gotoligcol(18,64);
                Color(11,0);
                std::cin >> nompoint;
            }
            while((choix<1) || (choix>37));
            Color(15,0);

            int trajetQuiArriveINT, trajetQuiPartINT;
            std::string trajetQuiArrive, trajetQuiPart;
            int numpoint;
            gotoligcol(20,0);
            for (auto z : m_graphe_points)
            {
                if(nompoint== z->getterSnomLieuPoint())
                {
                    numpoint= z->getterSnumeroPoint();
                }
            }
            for (auto m : m_liste_trajet)                           //on parcours la liste des trajets
            {
                if(numpoint == m->getterPointDepart())              //si le point correspond au point de depart
                {
                    trajetQuiArriveINT=m->getterNumeroTrajet();     //on recupere le numero du trajet
                    trajetQuiArrive = m->getterNomTrajet();         //on recupere le nom du trajet
                    std::cout<<" Le trajet numero : "<<trajetQuiArriveINT<<" nomme : "<<trajetQuiArrive<<" part du point choisi";
                    std::cout<<" "<<std::endl;
                }

                if(numpoint == m->getterPointArrivee())             //si le point correspond au point de depart
                {
                    trajetQuiPartINT=m->getterNumeroTrajet();       //on recupere le numero du trajet
                    trajetQuiPart = m->getterNomTrajet();           //on recupere le nom du trajet
                    std::cout<<" Le trajet numero : "<<trajetQuiPartINT<<" nomme : "<<trajetQuiPart<<" arrive au point choisi";
                    std::cout<<" "<<std::endl;
                }

            }
            /*Avec ces fonctions, l'utilisateur peut appuyer sur n'importe quelle touche pour continuer,
            cela va nettoyer la console */

            //On saute une ligne
            gotoligcol(34,70);
            system("pause");
            system("cls");
        }
        break;

        case 3:

            break;

        } //fin du switch
    }
    while(choix != 3);
}

///fonction convertion de secondes en minutes-secondes
float Graphe::tempsMinutesSecondes(float temps)
{
    int tempsMinutes;
    float tempsSecondes;
    float tempsFinal;
    tempsMinutes=temps/60;
    tempsSecondes= temps-tempsMinutes*60;
    tempsFinal = tempsMinutes + (tempsSecondes * 0.01);

    tempsFinal=round(tempsFinal*100)/100;
    return tempsFinal;


}

///fonction pour calculer le temps pour chaque trajet
void Graphe::calculTempsTrajet()
{
    std::string pisteVerte="V", pisteBleue = "B", pisteRouge ="R", pisteNoire="N", pisteKL="KL", snowpark="SURF";
    std::string telepherique="TPH", telecabine ="TC", telesiegeD ="TSD", telesiege ="TS", teleski="TK";
    std::string bus="BUS", arc1600="1600", arc1800="arc1800", arc2000="arc200";
    float pointdepart, pointarrivee, altitudedepart,altitudearrivee, altitudeTrajet, tempsTrajet;

    for (auto k : m_liste_trajet)//on parcours la liste des trajets
    {
        /// __________________________DESCENTE __________________________
        /// PISTE VERTE
        if (  (k->getterTypeTrajet())  == (std::string) pisteVerte) //si le trajet est une piste Verte
        {

            pointdepart = k->getterPointDepart();                   //on recupere le point de depart de ce trajet
            pointarrivee = k->getterPointArrivee();                 //on recupere le point d'arrivee de ce trajet
            for (auto s : m_graphe_points)                          //on parcours la liste des points
            {
                if(pointdepart == s->getterSnumeroPoint())          //si le point correspon au point de depart
                {
                    altitudedepart = s->getterSaltitudePoint();     //on recupere l'altiude de depart
                }

                if(pointarrivee == s->getterSnumeroPoint())         //si le point correspond au point d'arrivee
                {
                    altitudearrivee = s->getterSaltitudePoint();    //on recupere l'altitude du point d'arrivee
                }
            }
            altitudeTrajet = (altitudedepart) - (altitudearrivee);  //on fait une soustraction afin d'avoir le denivelé
            tempsTrajet= (altitudeTrajet/100) *5*60;                //denivele/100 afin d'avoir le temps de trajet en seconde
            tempsTrajet=tempsMinutesSecondes(tempsTrajet);          //on le converti en minute seconde
            k->setterTempsTrajet(tempsTrajet);                      // on le push

        }

        /// PISTE BLEU
        if (  (k->getterTypeTrajet())  == (std::string) pisteBleue ) //si le trajet est une piste bleu
        {
            pointdepart = k->getterPointDepart();                   //on recupere le point de depart de ce trajet
            pointarrivee = k->getterPointArrivee();                 //on recupere le point d'arrivee de ce trajet
            for (auto s : m_graphe_points)                          //on parcours la liste des points
            {
                if(pointdepart == s->getterSnumeroPoint())          //si le point correspon au point de depart
                {
                    altitudedepart = s->getterSaltitudePoint();     //on recupere l'altiude de depart
                }

                if(pointarrivee == s->getterSnumeroPoint())         //si le point correspond au point d'arrivee
                {
                    altitudearrivee = s->getterSaltitudePoint();    //on recupere l'altitude du point d'arrivee
                }
            }
            altitudeTrajet = (altitudedepart) - (altitudearrivee);  //on fait une soustraction afin d'avoir le denivelé
            tempsTrajet= (altitudeTrajet/100) *4*60;                //denivele/100 afin d'avoir le temps de trajet en seconde
            tempsTrajet=tempsMinutesSecondes(tempsTrajet);          //on le converti en minute seconde
            k->setterTempsTrajet(tempsTrajet);                      // on le push

        }

        /// PISTE ROUGE
        if (  (k->getterTypeTrajet())  == (std::string) pisteRouge ) //si le trajet est une piste rouge
        {
            pointdepart = k->getterPointDepart();                   //on recupere le point de depart de ce trajet
            pointarrivee = k->getterPointArrivee();                 //on recupere le point d'arrivee de ce trajet
            for (auto s : m_graphe_points)                          //on parcours la liste des points
            {
                if(pointdepart == s->getterSnumeroPoint())          //si le point correspon au point de depart
                {
                    altitudedepart = s->getterSaltitudePoint();     //on recupere l'altiude de depart
                }

                if(pointarrivee == s->getterSnumeroPoint())         //si le point correspond au point d'arrivee
                {
                    altitudearrivee = s->getterSaltitudePoint();    //on recupere l'altitude du point d'arrivee
                }
            }
            altitudeTrajet = (altitudedepart) - (altitudearrivee);  //on fait une soustraction afin d'avoir le denivelé
            tempsTrajet= (altitudeTrajet/100) *3*60;                //denivele/100 afin d'avoir le temps de trajet en seconde
            tempsTrajet=tempsMinutesSecondes(tempsTrajet);          //on le converti en minute seconde
            k->setterTempsTrajet(tempsTrajet);                      // on le push
        }

        /// PISTE NOIRE
        if (  (k->getterTypeTrajet())  == (std::string) pisteNoire ) //si le trajet est une piste Noire
        {
            pointdepart = k->getterPointDepart();                   //on recupere le point de depart de ce trajet
            pointarrivee = k->getterPointArrivee();                 //on recupere le point d'arrivee de ce trajet
            for (auto s : m_graphe_points)                          //on parcours la liste des points
            {
                if(pointdepart == s->getterSnumeroPoint())          //si le point correspon au point de depart
                {
                    altitudedepart = s->getterSaltitudePoint();     //on recupere l'altiude de depart
                }

                if(pointarrivee == s->getterSnumeroPoint())         //si le point correspond au point d'arrivee
                {
                    altitudearrivee = s->getterSaltitudePoint();    //on recupere l'altitude du point d'arrivee
                }
            }
            altitudeTrajet = (altitudedepart) - (altitudearrivee);  //on fait une soustraction afin d'avoir le denivelé
            tempsTrajet= (altitudeTrajet/100) *2*60;                //denivele/100 afin d'avoir le temps de trajet en seconde
            tempsTrajet=tempsMinutesSecondes(tempsTrajet);          //on le converti en minute seconde
            k->setterTempsTrajet(tempsTrajet);                      // on le push
        }

        /// PISTE KL
        if (  (k->getterTypeTrajet())  == (std::string) pisteKL ) //si le trajet est une piste KL
        {
            pointdepart = k->getterPointDepart();                   //on recupere le point de depart de ce trajet
            pointarrivee = k->getterPointArrivee();                 //on recupere le point d'arrivee de ce trajet
            for (auto s : m_graphe_points)                          //on parcours la liste des points
            {
                if(pointdepart == s->getterSnumeroPoint())          //si le point correspon au point de depart
                {
                    altitudedepart = s->getterSaltitudePoint();     //on recupere l'altiude de depart
                }

                if(pointarrivee == s->getterSnumeroPoint())         //si le point correspond au point d'arrivee
                {
                    altitudearrivee = s->getterSaltitudePoint();    //on recupere l'altitude du point d'arrivee
                }
            }
            altitudeTrajet = (altitudedepart) - (altitudearrivee);  //on fait une soustraction afin d'avoir le denivelé
            tempsTrajet= (altitudeTrajet/100) *2;                   //denivele/100 afin d'avoir le temps de trajet en seconde
            tempsTrajet=tempsMinutesSecondes(tempsTrajet);          //on le converti en minute seconde
            k->setterTempsTrajet(tempsTrajet);                      // on le push
        }

        /// SNOWPARK
        if (  (k->getterTypeTrajet())  == (std::string) snowpark) //si le trajet est une piste snowpark
        {
            pointdepart = k->getterPointDepart();                   //on recupere le point de depart de ce trajet
            pointarrivee = k->getterPointArrivee();                 //on recupere le point d'arrivee de ce trajet
            for (auto s : m_graphe_points)                          //on parcours la liste des points
            {
                if(pointdepart == s->getterSnumeroPoint())          //si le point correspon au point de depart
                {
                    altitudedepart = s->getterSaltitudePoint();     //on recupere l'altiude de depart
                }

                if(pointarrivee == s->getterSnumeroPoint())         //si le point correspond au point d'arrivee
                {
                    altitudearrivee = s->getterSaltitudePoint();    //on recupere l'altitude du point d'arrivee
                }
            }
            altitudeTrajet = (altitudedepart) - (altitudearrivee);  //on fait une soustraction afin d'avoir le denivelé
            tempsTrajet= (altitudeTrajet/100) *10*60;                //denivele/100 afin d'avoir le temps de trajet en seconde
            tempsTrajet=tempsMinutesSecondes(tempsTrajet);          //on le converti en minute seconde
            k->setterTempsTrajet(tempsTrajet);                      // on le push
        }



        /// ____________________________DESCENTE _______________________________________

        /// TELEPHERIQUE
        if (  (k->getterTypeTrajet())  == (std::string) telepherique) //si le trajet est un telepherique
        {
            pointdepart = k->getterPointDepart();                   //on recupere le point de depart de ce trajet
            pointarrivee = k->getterPointArrivee();                 //on recupere le point d'arrivee de ce trajet
            for (auto s : m_graphe_points)                          //on parcours la liste des points
            {
                if(pointdepart == s->getterSnumeroPoint())          //si le point correspon au point de depart
                {
                    altitudedepart = s->getterSaltitudePoint();     //on recupere l'altiude de depart
                }

                if(pointarrivee == s->getterSnumeroPoint())         //si le point correspond au point d'arrivee
                {
                    altitudearrivee = s->getterSaltitudePoint();    //on recupere l'altitude du point d'arrivee
                }
            }
            altitudeTrajet = (altitudearrivee) - (altitudedepart);  //on fait une soustraction afin d'avoir le denivelé
            tempsTrajet= ((altitudeTrajet/100) *2*60)+4*60;         //denivele/100 afin d'avoir le temps de trajet en seconde
            tempsTrajet=tempsMinutesSecondes(tempsTrajet);          //on le converti en minute seconde
            k->setterTempsTrajet(tempsTrajet);                      // on le push
        }

        /// TELECABINE
        if (  (k->getterTypeTrajet())  == (std::string) telecabine) //si le trajet est une telecabine
        {
            pointdepart = k->getterPointDepart();                   //on recupere le point de depart de ce trajet
            pointarrivee = k->getterPointArrivee();                 //on recupere le point d'arrivee de ce trajet
            for (auto s : m_graphe_points)                          //on parcours la liste des points
            {
                if(pointdepart == s->getterSnumeroPoint())          //si le point correspon au point de depart
                {
                    altitudedepart = s->getterSaltitudePoint();     //on recupere l'altiude de depart
                }

                if(pointarrivee == s->getterSnumeroPoint())         //si le point correspond au point d'arrivee
                {
                    altitudearrivee = s->getterSaltitudePoint();    //on recupere l'altitude du point d'arrivee
                }
            }
            altitudeTrajet = (altitudearrivee) - (altitudedepart);  //on fait une soustraction afin d'avoir le denivelé
            tempsTrajet= ((altitudeTrajet/100) *3*60) +2*60;        //denivele/100 afin d'avoir le temps de trajet en seconde
            tempsTrajet=tempsMinutesSecondes(tempsTrajet);          //on le converti en minute seconde
            k->setterTempsTrajet(tempsTrajet);                      // on le push
        }
        /// TELESIAGE D
        if (  (k->getterTypeTrajet())  == (std::string) telesiegeD) //si le trajet est un telesiege D
        {
            pointdepart = k->getterPointDepart();                   //on recupere le point de depart de ce trajet
            pointarrivee = k->getterPointArrivee();                 //on recupere le point d'arrivee de ce trajet
            for (auto s : m_graphe_points)                          //on parcours la liste des points
            {
                if(pointdepart == s->getterSnumeroPoint())          //si le point correspon au point de depart
                {
                    altitudedepart = s->getterSaltitudePoint();     //on recupere l'altiude de depart
                }

                if(pointarrivee == s->getterSnumeroPoint())         //si le point correspond au point d'arrivee
                {
                    altitudearrivee = s->getterSaltitudePoint();    //on recupere l'altitude du point d'arrivee
                }
            }
            altitudeTrajet = (altitudearrivee)- (altitudedepart);   //on fait une soustraction afin d'avoir le denivelé
            tempsTrajet= ((altitudeTrajet/100) *3*60)+1*60;         //denivele/100 afin d'avoir le temps de trajet en seconde
            tempsTrajet=tempsMinutesSecondes(tempsTrajet);          //on le converti en minute seconde
            k->setterTempsTrajet(tempsTrajet);                      // on le push
        }
        /// TELESIEGE
        if (  (k->getterTypeTrajet())  == (std::string) telesiege) //si le trajet est un telesiege
        {
            pointdepart = k->getterPointDepart();                   //on recupere le point de depart de ce trajet
            pointarrivee = k->getterPointArrivee();                 //on recupere le point d'arrivee de ce trajet
            for (auto s : m_graphe_points)                          //on parcours la liste des points
            {
                if(pointdepart == s->getterSnumeroPoint())          //si le point correspon au point de depart
                {
                    altitudedepart = s->getterSaltitudePoint();     //on recupere l'altiude de depart
                }

                if(pointarrivee == s->getterSnumeroPoint())         //si le point correspond au point d'arrivee
                {
                    altitudearrivee = s->getterSaltitudePoint();    //on recupere l'altitude du point d'arrivee
                }
            }
            altitudeTrajet = (altitudearrivee) - (altitudedepart);  //on fait une soustraction afin d'avoir le denivelé
            tempsTrajet= ((altitudeTrajet/100) *4*60)+1*60;         //denivele/100 afin d'avoir le temps de trajet en seconde
            tempsTrajet=tempsMinutesSecondes(tempsTrajet);          //on le converti en minute seconde
            k->setterTempsTrajet(tempsTrajet);                      // on le push
        }
        /// TELESKI
        if (  (k->getterTypeTrajet())  == (std::string) teleski) //si le trajet est une piste snowpark
        {
            pointdepart = k->getterPointDepart();                   //on recupere le point de depart de ce trajet
            pointarrivee = k->getterPointArrivee();                 //on recupere le point d'arrivee de ce trajet
            for(auto s : m_graphe_points)                           //on parcours la liste des points
            {
                if(pointdepart == s->getterSnumeroPoint())          //si le point correspon au point de depart
                {
                    altitudedepart = s->getterSaltitudePoint();     //on recupere l'altiude de depart
                }

                if(pointarrivee == s->getterSnumeroPoint())         //si le point correspond au point d'arrivee
                {
                    altitudearrivee = s->getterSaltitudePoint();    //on recupere l'altitude du point d'arrivee
                }
            }
            altitudeTrajet = (altitudearrivee) - (altitudedepart);  //on fait une soustraction afin d'avoir le denivelé
            tempsTrajet= ((altitudeTrajet/100) *4*60)+1*60;         //denivele/100 afin d'avoir le temps de trajet en seconde
            tempsTrajet=tempsMinutesSecondes(tempsTrajet);          //on le converti en minute seconde
            k->setterTempsTrajet(tempsTrajet);                      // on le push
        }



        ///_______________________________ BUS __________________________________

        ///BUS 1 1600 ---- 2000

        if (  (k->getterTypeTrajet())  == (std::string) bus)       //si le trajet est de type bus
        {
            pointdepart = k->getterPointDepart();                   //on recupere le point de depart de ce trajet
            pointarrivee = k->getterPointArrivee();                 //on recupere le point d'arrivee de ce trajet

            for (auto s : m_graphe_points)                          //on parcours la liste des points
            {
                if(pointdepart == s->getterSnumeroPoint())          //si le point correspon au point de depart
                {
                    if(pointdepart == 30 )                          //si le point de depart correspond à l'arc 1600, il y a deux choix
                    {
                        if(pointarrivee==36)                        //si le point d'arrivee est 1800
                        {
                            /// 30 minutes correspond a l'acr 1600-1800 ou 1800-1600
                            tempsTrajet= 30*60;                                         //le temps de trajet est de 30 minutes
                            tempsTrajet=tempsMinutesSecondes(tempsTrajet);              //on le converti en minute seconde
                            k->setterTempsTrajet(tempsTrajet);                          //on push

                        }
                        else if(pointarrivee==7)                    //si le point d'arrivee est 2000
                        {
                            /// 40 minutes correspond a l'acr 1600-2000 ou 2000-1600
                            tempsTrajet= 40*60;                                         //le temps de trajet est de 40 minutes
                            tempsTrajet=tempsMinutesSecondes(tempsTrajet);              //on le converti en minute seconde
                            k->setterTempsTrajet(tempsTrajet);                          //on push
                        }
                    }

                    if(pointdepart==36)                             //si le point de depart est 1800 il y a qu'une seule possibilié
                    {
                        /// 30 minutes correspond a l'acr 1600-1800 ou 1800-1600
                        tempsTrajet= 30*60;                                         //le temps de trajet est de 30 minutes
                        tempsTrajet=tempsMinutesSecondes(tempsTrajet);              //on le converti en minute seconde
                        k->setterTempsTrajet(tempsTrajet);                          //on push
                    }

                    if(pointdepart==7)                              //si le point de depart est 2000 il y a qu'une seule possibilité
                    {
                        /// 40 minutes correspond a l'acr 1600-2000 ou 2000-1600
                        tempsTrajet= 40*60;                                         //le temps de trajet est de 40 minutes
                        tempsTrajet=tempsMinutesSecondes(tempsTrajet);              //on le converti en minute seconde
                        k->setterTempsTrajet(tempsTrajet);                          //on push
                    }
                }

            }
        }


    }
}

///fonction pour trouver un point a partir de son numero
Sommet* Graphe::rechercherPoint(int choix)
{
    for(auto elem : m_graphe_points)
    {
        if(choix == elem->getterSnumeroPoint())
            return elem;
    }
}



/// ALGO BFS
void Graphe::algo_BFS(int s, int f)
{

    bool *marque = new bool[m_graphe_points.size()];        //marque tous les sommets en tant que non visité
    int explore;
    int VRAIsommetinitial, Vraisommetfinal;
    VRAIsommetinitial=s;
    Vraisommetfinal =f;
    for(int i = 0; i < m_graphe_points.size(); i++)
    {
        m_graphe_points[i]->setmarque(false);
    }

    std::queue <Sommet*> liste ;
    std::priority_queue <Sommet*, std::vector<Sommet*>, std::greater<Sommet*>> listeTMP ;

    for (auto i : m_graphe_points)
    {
        if(i->getterSnumeroPoint() == s)
        {
            i->setmarque(true);         //on marque le sommet envoyé en parametre(sommet Depart) comme visité
            liste.push(i);              // on l'enfile dans la file
        }
    }

    while (!liste.empty())
    {
        while (s != f)
        {
            ///on recherche les successeurs de S0
            for (auto k : m_liste_trajet)
            {
                if(s == k->getterPointDepart())
                {
                    for (auto j : m_graphe_points)
                    {
                        if(k->getterPointArrivee()== j->getterSnumeroPoint())
                        {
                            if (j->getmarque()==false)
                            {
                                //std::cout<<"coucou JE SUIS LAAAAA"<<std::endl;
                                j->setmarque(true);
                                listeTMP.push(j);
                            }
                        }
                    }
                }
            }



            while (!listeTMP.empty())
            {
                liste.push(listeTMP.top());
                listeTMP.pop();
            }

            ///apres avoir trouve les predecesseurs on marque S0 comme explore et on annonce le nouveau S
            for (auto i : m_graphe_points)
            {
                if(i->getterSnumeroPoint() == s)
                {
                    i->setmarque(true);         //on marque le sommet envoyé en parametre(sommet Depart) comme visité
                    std::cout <<  i->getterSnumeroPoint() << " -> ";
                    liste.pop();              // on l'enfile dans la file
                }
            }
            /// on enleve le sommet marque visite et explore
            s = liste.front()->getterSnumeroPoint();


        }
        std::cout << f <<std::endl;
        break;

    }

    /*      while(Vraisommetfinal != VRAIsommetinitial)
      {

            for (auto k : m_liste_trajet)
          {
              if(Vraisommetfinal == k->getterPointArrivee())
              {
                  for (int l=0; l<listeCopie.size() ; l++)
                  {
                if(k->getterPointDepart() != liste.front()->getterSnumeroPoint())
                      {
                                 std::cout<<std::endl;
                              std::cout<<std::endl;
                      std::cout <<  liste.front()->getterSnumeroPoint() << " JE SUIS LE NUMERO LISTE QUI A POP";
                          liste.pop();
                      }
                      if (k->getterPointDepart() == listeCopie.front()->getterSnumeroPoint())
                      {
                              std::cout<<std::endl;
                              std::cout<<std::endl;
                      std::cout <<  listeCopie.front()->getterSnumeroPoint() << " JE SUIS LE NUMERO LISTE ";
                      f=listeCopie.front()->getterSnumeroPoint();

                      }

                  }

              }
          }
      }
    */




    /*// Mark all the vertices as not visited
    bool *marque = new bool[m_graphe_points.size()];        //marque tous les sommets en tant que non visité
    for(int i = 0; i < m_graphe_points.size(); i++)
    {
        m_graphe_points[i]->setmarque(false);
    }
    //std::list<Sommet> liste;            //on creer une liste pour le BFS
    std::queue <Sommet*> liste ;

    for (auto i : m_graphe_points)
    {
        if(i->getterSnumeroPoint() == s)
        {
            i->setmarque(true);    //on marque le sommet envoyé en parametre(sommet Depart) comme visité
            liste.push(i);
        }
    }

    //std::list <Sommet>::iterator i;      //on cree un iterator 'i' will be used to get all adjacent   vertices of a vertex

    while(!liste.empty())       //tant que la liste n'est pas vide
    {
        for (auto l :m_graphe_points)
        {
          if(l->getterSnumeroPoint() == s)
          {
            l = liste.front();      //on enleve le sommet de la liste et on l'affiche sur la console
            std::cout <<  l->getterSnumeroPoint() << " ";
            liste.pop();
          }
        }

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        // for ( auto i = adj.front(); i != adj.back(); ++i)
        for (auto k : m_liste_trajet)
        {
            if(s == k->getterPointDepart())
            {
                    for (auto j : m_graphe_points)
                    {
                        if(k->getterPointArrivee()== j->getterSnumeroPoint())
                        {
                           if (j->getmarque()==false)
                            {
                                std::cout<<"coucou JE SUIS LAAAAA"<<std::endl;
                                j->setmarque(true);
                                liste.push(j);
                            }
                        }
                    }



            }

        }

    }*/

}


/// ALGO DIJKSTRA
void Graphe::algo_Dijkstra(int i, int f)
{

    std::priority_queue<std::pair<float,Sommet*>> file;		 //On initialise la priority_queue
    std::pair<double, Sommet*> avant;                        //on initialise les predecesseurs
    int dist[m_graphe_points.size()];                        //on initialise un tableau de la taille du nombre de point
    float tempsTrajetTOT=0;
    int compt=0;

    for(int j=0; j<m_graphe_points.size(); j++)              //on initialiste le tableau de distance à 5000 qui equivaut a une distance infini
    {
        dist[j] = 5000;
    }

    dist[i-1]=0;                                             //on met la distance du sommet initiale à 0 pour le "marquer"
    file.push(std::pair<double,Sommet*>(0, m_graphe_points[i-1]));

    while (file.size()!=0)                                //Tant que la file est différente de 0,
    {

        Sommet* som = file.top().second;        //on cree un vecteur sommet qu'on ajout  au début de la liste
        file.pop();		                        //On pop pour ajouter une case

        for(auto T : som->getTrajets())
        {
            //On ajoute une boucle if pour réaliser la comparaison des sommets
            if(dist[T->getterPointArrivee()-1]> dist[som->getterSnumeroPoint()-1]+ T->getterTempsTrajet())
            {
                dist[T->getterPointArrivee()-1]= dist[som->getterSnumeroPoint()-1]+ T->getterTempsTrajet();
                file.push(std::pair<double, Sommet*>(dist[T->getterPointArrivee()-1], m_graphe_points[T->getterPointArrivee()-1]));
                avant.second = som;
                avant.first = T->getterTempsTrajet();
                m_graphe_points[T->getterPointArrivee()-1]->setterPred(avant);
            }
        }
    }

    Sommet *somFin = m_graphe_points[f-1];

    std::cout<<somFin->getterSnumeroPoint();
    for (auto i : m_liste_trajet)
    {
        if(somFin->getterSnumeroPoint()== i->getterNumeroTrajet())
        {
            std::cout<<"("<<i->getterTypeTrajet()<<")";
        }
    }
    std::cout<<std::endl;

    //tant que la liste des sommets FIN est differentes du tableau de depart
    while(somFin->getterSnumeroPoint() != m_graphe_points[i-1]->getterSnumeroPoint()) /// Affichage du chemin
    {
        std::cout<< " <--";
        std::cout<< m_graphe_points[somFin->getterSnumeroPoint()-1]->getAvant().second->getterSnumeroPoint();

        for (auto i : m_liste_trajet)
        {
            if(m_graphe_points[somFin->getterSnumeroPoint()-1]->getAvant().second->getterSnumeroPoint()== i->getterNumeroTrajet())
            {
                std::cout<<"("<<i->getterTypeTrajet()<<")";
            }
        }
        for (auto R : m_liste_trajet)
        {
            if (somFin->getterSnumeroPoint() == R->getterPointArrivee()&& m_graphe_points[somFin->getterSnumeroPoint()-1]->getAvant().second->getterSnumeroPoint() == R->getterPointDepart())
            {
                tempsTrajetTOT += R->getterTempsTrajet();
                break;
            }
        }
        somFin= m_graphe_points[somFin->getterSnumeroPoint()-1]->getAvant().second;

    }
    std::cout<<std::endl;
    std::cout<<" TEMPS TRAJET TOT :" <<tempsTrajetTOT;

}



void Graphe ::algo_DijkstraPLS(int i)
{
    for(int z=0 ; z<m_graphe_points.size(); z++)
    {
        std::priority_queue<std::pair<float,Sommet*>> file;		 //On initialise la priority_queue
        std::pair<double, Sommet*> avant;                        //on initialise les predecesseurs
        int dist[m_graphe_points.size()];                        //on initialise un tableau de la taille du nombre de point
        float tempsTrajetTOT=0;
        int compt=0;

        for(int j=0; j<m_graphe_points.size(); j++)              //on initialiste le tableau de distance à 5000 qui equivaut a une distance infini
        {
            dist[j] = 5000;
        }

        dist[i-1]=0;                                             //on met la distance du sommet initiale à 0 pour le "marquer"
        file.push(std::pair<double,Sommet*>(0, m_graphe_points[i-1]));

        while (file.size()!=0)                                //Tant que la file est différente de 0,
        {

            Sommet* som = file.top().second;        //on cree un vecteur sommet qu'on ajout  au début de la liste
            file.pop();		                        //On pop pour ajouter une case

            for(auto T : som->getTrajets())
            {
                //On ajoute une boucle if pour réaliser la comparaison des sommets
                if(dist[T->getterPointArrivee()-1]> dist[som->getterSnumeroPoint()-1]+ T->getterTempsTrajet())
                {
                    dist[T->getterPointArrivee()-1]= dist[som->getterSnumeroPoint()-1]+ T->getterTempsTrajet();
                    file.push(std::pair<double, Sommet*>(dist[T->getterPointArrivee()-1], m_graphe_points[T->getterPointArrivee()-1]));
                    avant.second = som;
                    avant.first = T->getterTempsTrajet();
                    m_graphe_points[T->getterPointArrivee()-1]->setterPred(avant);
                }
            }
        }

        Sommet *somFin = m_graphe_points[z];
        std::cout<<""<<std::endl;
        std::cout<<somFin->getterSnumeroPoint();
        for (auto i : m_liste_trajet)
        {
            if(somFin->getterSnumeroPoint()== i->getterNumeroTrajet())
            {
                std::cout<<"("<<i->getterTypeTrajet()<<")";
            }
        }

        //tant que la liste des sommets FIN est differentes du tableau de depart
        while(somFin->getterSnumeroPoint() != m_graphe_points[i-1]->getterSnumeroPoint()) /// Affichage du chemin
        {
            std::cout<< " <--";
            std::cout<< m_graphe_points[somFin->getterSnumeroPoint()-1]->getAvant().second->getterSnumeroPoint();

            for (auto i : m_liste_trajet)
            {
                if(m_graphe_points[somFin->getterSnumeroPoint()-1]->getAvant().second->getterSnumeroPoint()== i->getterNumeroTrajet())
                {
                    std::cout<<"("<<i->getterTypeTrajet()<<")";
                }
            }
            for (auto R : m_liste_trajet)
            {
                if (somFin->getterSnumeroPoint() == R->getterPointArrivee()&& m_graphe_points[somFin->getterSnumeroPoint()-1]->getAvant().second->getterSnumeroPoint() == R->getterPointDepart())
                {
                    tempsTrajetTOT += R->getterTempsTrajet();
                    break;
                }
            }
            somFin= m_graphe_points[somFin->getterSnumeroPoint()-1]->getAvant().second;

        }
        std::cout<<std::endl;
        std::cout<<" TEMPS TRAJET TOT :" <<tempsTrajetTOT;
        std::cout<<" "<<std::endl;
    }

    std::cout<<std::endl;
}

/// ALGO 4.5
void Graphe::algo_cheminPersonnalise()
{
    int choix;
    for (auto T : m_liste_trajet)  // boucle afin de reanitialiser les poids pour mettre les poids souhaité
    {
        T->setterTempsTrajet(5);  //on initialise tout les sommets à 5 qui est un poids moyen
    }
    do
    {
        do
        {
            std::cout << "Quelle chemin preferez vous ne pas emprunter ? " << std::endl;
            std::cout << "1. Les pistes  " << std::endl;
            std::cout << "2. Les remontees" << std::endl;
            std::cout << "3. Quitter la selection "<<std::endl;
            std::cin >> choix;
            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << std::endl;
        }
        while((choix<1) || (choix>3));

        //Fonction switch pour que l'utilisateur puisse choisir ce qu'il souhaite faire.
        switch(choix)
        {
        case 1:
        {
            int choixPiste;
            do
            {
                std::string pisteBleu ="B", pisteVerte="V", pisteRouge="R", pisteNoire="N", pisteKL="KL", snowPark="SNOW";
                std::cout << "Quelle types de pistes vous effraie, ou vous ennuie ? " << std::endl;
                std::cout << "1 : Les pistes vertes  " << std::endl;
                std::cout << "2 : Les pistes bleue" << std::endl;
                std::cout << "3 : Les pistes rouge" << std::endl;
                std::cout << "4 : Les pistes noire" << std::endl;
                std::cout << "5 : Les pistes de kilometre lance" << std::endl;
                std::cout << "6 : Les snowpark" << std::endl;
                std::cout << "10 : Quitter la selection "<<std::endl;
                std::cin >> choixPiste;

                if (choixPiste == 1) // l'utilisateur ne veut pas de piste VERTE
                {
                    for (auto T : m_liste_trajet)                                   //on parcours la liste des trajets
                    {

                        std::cout<<"GELOFJNEDON";
                        if((T->getterTypeTrajet()) == "V")       //SI dans la liste un trajet est une piste VERTE
                        {
                            T->setterTempsTrajet(10000);                             //on initialise son poid a 1000 (ne passera pas en priorite
                            std::cout<<T->getterTempsTrajet();
                            std::cout<<"JE SUIS LA TA MAMAN";
                            std::cout<<"ALLLFNEOUIBNOFZIO"<<std::endl;
                        }
                    }
                    std::cout << std::endl;
                    system("pause");
                    system("cls");
                }

                if (choixPiste == 2) // l'utilisateur ne veut pas de piste BLEU
                {
                    for (auto T : m_liste_trajet)
                    {
                        if(T->getterTypeTrajet() == (std::string) pisteBleu)
                        {
                            T->setterTempsTrajet(10000);
                        }
                    }
                    std::cout << std::endl;
                    system("pause");
                    system("cls");
                }

                if (choixPiste == 3) // l'utilisateur ne veut pas de piste ROUGE
                {
                    for (auto T : m_liste_trajet)
                    {
                        if(T->getterTypeTrajet() == (std::string) pisteRouge)
                        {
                            T->setterTempsTrajet(1000);
                        }
                    }
                    std::cout << std::endl;
                    system("pause");
                    system("cls");
                }

                if (choixPiste == 4) // l'utilisateur ne veut pas de piste NOIR
                {
                    for (auto T : m_liste_trajet)
                    {
                        if(T->getterTypeTrajet() == (std::string) pisteNoire)
                        {
                            T->setterTempsTrajet(1000);
                        }
                    }
                    std::cout << std::endl;
                    system("pause");
                    system("cls");
                }

                if (choixPiste == 5) // l'utilisateur ne veut pas de piste KL
                {
                    for (auto T : m_liste_trajet)
                    {
                        if(T->getterTypeTrajet() == (std::string) pisteKL)
                        {
                            T->setterTempsTrajet(1000);
                        }
                    }
                    std::cout << std::endl;
                    system("pause");
                    system("cls");
                }

                if (choixPiste == 6) // l'utilisateur ne veut pas de SNOWPARK
                {
                    for (auto T : m_liste_trajet)
                    {
                        if(T->getterTypeTrajet() == (std::string) snowPark)
                        {
                            T->setterTempsTrajet(1000);
                        }
                    }
                    std::cout << std::endl;
                    system("pause");
                    system("cls");
                }

                if (choixPiste == 10)
                {
                    break;
                }

            }
            while (choixPiste !='10');

            std::cout << std::endl;
            system("pause");
            system("cls");

        }///FIN CASE 1
        break;

        case 2:
        {

            int choixRemontee;
            do
            {
                std::string telepherique ="TPH", telecabine="TC", telesiegeTSD="TSD", telesiege="TS", teleski="TK";
                std::cout << "Est-ce-que vous avez un type de remontee que vous voulez eviter ? " << std::endl;
                std::cout << "1 : Les telepheriques  " << std::endl;
                std::cout << "2 : Les telecabines" << std::endl;
                std::cout << "3 : Les telesiege debrayable " << std::endl;
                std::cout << "4 : Les telesieges classiques" << std::endl;
                std::cout << "5 : les teleskis" << std::endl;
                std::cout<< "6 : le moins de remontees possible"<<std::endl;
                std::cout << "10 : Quitter la selection "<<std::endl;
                std::cin >> choixRemontee;

                if (choixRemontee == 1) // l'utilisateur ne veut pas de TELEPHERIQUE
                {
                    for (auto T : m_liste_trajet)                                   //on parcours la liste des trajets
                    {
                        if(T->getterTypeTrajet() == (std::string) telepherique)       //SI dans la liste un trajet est un TELEPHERIQUE
                        {
                            T->setterTempsTrajet(1000);                             //on initialise son poid a 1000 (ne passera pas en priorite
                        }
                    }
                    std::cout << std::endl;
                    system("pause");
                    system("cls");
                }

                if (choixRemontee == 2) // l'utilisateur ne veut pas de TELECABINE
                {
                    for (auto T : m_liste_trajet)
                    {
                        if(T->getterTypeTrajet() == (std::string) telecabine)
                        {
                            T->setterTempsTrajet(1000);
                        }
                    }
                    std::cout << std::endl;
                    system("pause");
                    system("cls");
                }

                if (choixRemontee == 3) // l'utilisateur ne veut pas de TSD
                {


                    for (auto T : m_liste_trajet)
                    {
                        if(T->getterTypeTrajet() == (std::string) telesiegeTSD)
                        {
                            T->setterTempsTrajet(1000);
                        }
                    }
                    std::cout << std::endl;
                    system("pause");
                    system("cls");
                }

                if (choixRemontee == 4) // l'utilisateur ne veut pas de TELESIEGE
                {
                    for (auto T : m_liste_trajet)
                    {
                        if(T->getterTypeTrajet() == (std::string)telesiege)
                        {
                            T->setterTempsTrajet(1000);
                        }
                    }
                    std::cout << std::endl;
                    system("pause");
                    system("cls");
                }

                if (choixRemontee == 5) // l'utilisateur ne veut pas de pTELESKI
                {
                    for (auto T : m_liste_trajet)
                    {
                        if(T->getterTypeTrajet() == (std::string) teleski)
                        {
                            T->setterTempsTrajet(1000);
                        }
                    }
                    std::cout << std::endl;
                    system("pause");
                    system("cls");
                }
                if (choixRemontee == 6)
                {
                    for (auto T : m_liste_trajet)
                    {
                        if(T->getterTypeTrajet() == (std::string) telepherique || T->getterTypeTrajet() == (std::string) telecabine || T->getterTypeTrajet() == (std::string) telesiege || T->getterTypeTrajet() == (std::string)telesiegeTSD || T->getterTypeTrajet() == (std::string) teleski)
                        {
                            T->setterTempsTrajet(1000000000000);
                        }
                    }
                    std::cout << std::endl;
                    system("pause");
                    system("cls");
                }



                if (choixRemontee == 10)
                {
                    break;
                }

            }
            while (choixRemontee !='10');

            std::cout << std::endl;
            system("pause");
            system("cls");
        }///FIN CASE 2
        break;

        case 3:
        {
            std::cout<<" Les demandes vont etre pris en compte ";
            std::cout<<" Le calcul du chemin est en cours ... ";

            std::cout << std::endl;
            system("pause");
            system("cls");

        }///FIN CASE 3
        break;



        }///FIN DU DWITCH
    }
    while(choix != 3);

    ///On entre un premier sommet i.
    int sommet1, sommet2;
    std::cout << std::endl << "Entrez ici sommet initial : ";
    std::cin >> sommet1;

    ///On saisie un deuxieme sommet j.
    std::cout << std::endl << std::endl << "Entrez ici le sommet final : ";
    std::cin >> sommet2;
    std::cout << std::endl;

    ///On appelle l'algorithme de Dijstra directement
    ///On l'applique au entier i et j.
    algo_Dijkstra(sommet1, sommet2);

    /*Avec ces fonctions, l'utilisateur peut appuyer
     sur n'importe quelle touche pour continuer,
     cela va nettoyer la console */

    //On saute une ligne
    std::cout << std::endl;
    system("pause");
    system("cls");

}

///Fonction de la classe graphe pour afficher
void Graphe::affichage()
{
    gotoligcol(0,1);
    Color(9,0);
    std::cout << "== PROJET PISCINE : BRUANT Chloe et KLEIN Manon     TD 6" << std::endl;
    for(int j=0; j<170; j++)
    {
        gotoligcol(10,j);
        Color(11,0);
        std::cout<<"-";
        gotoligcol(11,j);
        Color(1,0);
        std::cout<<"-";
        gotoligcol(24,j);
        Color(1,0);
        std::cout<<"-";
        gotoligcol(25,j);
        Color(11,0);
        std::cout<<"-";
        Sleep(10);

    }

    gotoligcol(15,50);
    Color(11,0);
    std::cout<<"db      d88888b .d8888.         .d8b.  d8888b.  .o88b. .d8888. ";
    gotoligcol(16,50);
    Color(11,0);
    std::cout<<"88      88'     88'  YP        d8' `8b 88  `8D d8P  Y8 88'  YP";
    gotoligcol(17,50);
    Color(9,0);
    std::cout<<"88      88ooooo `8bo.          88ooo88 88oobY' 8P      `8bo.  ";
    gotoligcol(18,50);
    Color(9,0);
    std::cout<<"88      88~~~~~   `Y8b.        88~~~88 88`8b   8b        `Y8b.";
    gotoligcol(19,50);
    Color(1,0);
    std::cout<<"88booo. 88.     db   8D        88   88 88 `88. Y8b  d8 db   8D";
    gotoligcol(20,50);
    Color(1,0);
    std::cout<<"Y88888P Y88888P `8888Y'        YP   YP 88   YD  `Y88P' `8888Y'";

    Color(15,0);
    gotoligcol(40,100);
    system("pause");
    system("cls");




    int choix;
    do
    {

        gotoligcol(5,10);
        Color(11,0);
        std::cout<<"d8888b.  .d88b.  d8888b. d8b   db d88888b .d8888.   d888888b d8b   db d888888b d88888b d8888b.  .d8b.   .o88b. d888888b d888888b db    db d88888b .d8888.";
        gotoligcol(6,10);
        Color(11,0);
        std::cout<<"88  `8D .8P  Y8. 88  `8D 888o  88 88'     88'  YP     `88'   888o  88 `~~88~~' 88'     88  `8D d8' `8b d8P  Y8 `~~88~~'   `88'   88    88 88'     88'  YP";
        gotoligcol(7,10);
        Color(9,0);
        std::cout<<"88oooY' 88    88 88oobY' 88V8o 88 88ooooo `8bo.        88    88V8o 88    88    88ooooo 88oobY' 88ooo88 8P         88       88    Y8    8P 88ooooo `8bo. ";
        gotoligcol(8,10);
        Color(9,0);
        std::cout<<"88~~~b. 88    88 88`8b   88 V8o88 88~~~~~   `Y8b.      88    88 V8o88    88    88~~~~~ 88`8b   88~~~88 8b         88       88    `8b  d8' 88~~~~~   `Y8b.";
        gotoligcol(9,10);
        Color(1,0);
        std::cout<<"88   8D `8b  d8' 88 `88. 88  V888 88.     db   8D     .88.   88  V888    88    88.     88 `88. 88   88 Y8b  d8    88      .88.    `8bd8'  88.     db   8D";
        gotoligcol(10,10);
        Color(1,0);
        std::cout<<"Y8888P'  `Y88P'  88   YD VP   V8P Y88888P `8888Y'   Y888888P VP   V8P    YP    Y88888P 88   YD YP   YP  `Y88P'    YP    Y888888P    YP    Y88888P `8888Y'";


        Color(15,0);

        gotoligcol(15,30);
        Color(11,0);
        std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////";
        gotoligcol(16,30);
        Color(9,0);
        std::cout << "//'                                                                                                                  '//";
        Color(15,0);
        gotoligcol(17,30);
        std::cout << "//                                   Que voulez vous faire ?                                                          //";
        gotoligcol(18,30);
        std::cout << "//                                                                                                                    //";
        gotoligcol(19,30);
        std::cout << "//  1. Afficher tous les Sommets                                                                                      //";
        gotoligcol(20,30);
        std::cout << "//  2. Afficher tous les trajets possibles                                                                            //";
        gotoligcol(21,30);
        std::cout << "//  3. choisir un trajet, savoir son point de depart ainsi que son point d'arrivee                                    //";
        gotoligcol(22,30);
        std::cout << "//  4. choisir un point, savoir quel chemins partent de ce point et ceux qui permettent d'y arriver                   //";
        gotoligcol(23,30);
        std::cout << "//  5. trouver le plus court chemin entre un point saisi et les autres                                                //";
        gotoligcol(24,30);
        std::cout << "//  6. Trouver un itineraire rapide entre deux points                                                                 //";
        gotoligcol(25,30);
        std::cout << "//  7. Creer son itineraire personalisee                                                                              //";
        gotoligcol(26,30);
        std::cout << "//                                                                                                                    //";
        gotoligcol(27,30);
        std::cout << "//        Choix :                                                                                                     //";
        gotoligcol(28,30);
        Color(9,0);
        std::cout << "//'                                                                                                                  '//";
        gotoligcol(29,30);
        Color(11,0);
        std::cout << "////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////";
        Color(15,0);
        do
        {
            gotoligcol(27,49);
            std::cout<<"                   ";
            gotoligcol(27,49);
            std::cin >> choix;
        }
        while((choix<1) || (choix>7));


        gotoligcol(40,100);
        system("pause");
        system("cls");



        //Fonction switch pour que l'utilisateur puisse choisir ce qu'il souhaite faire.
        switch(choix)
        {
        case 1:
        {

            //Boucle for pour afficher les sommets !
            int ligne=2, colonne=3;
            for (auto i : m_graphe_points)
            {
                gotoligcol(ligne,colonne);
                Color(11,0);
                std::cout<<"'---------------------------------------------'";
                gotoligcol(ligne+1,colonne);
                Color(15,0);
                std::cout<<"//  Numero du point : "<< i->getterSnumeroPoint() << "    ";
                gotoligcol(ligne+2,colonne);
                std::cout<<"//  Nom du lieu : "<< i->getterSnomLieuPoint() <<"   ";
                gotoligcol(ligne+3,colonne);
                std::cout<<"//  Altitude : "<< i->getterSaltitudePoint() <<"    ";
                gotoligcol(ligne+4,colonne);
                std::cout<<"//";
                gotoligcol(ligne+5,colonne);
                Color(11,0);
                std::cout<<"'---------------------------------------------'";
                Color(15,0);
                colonne=colonne+57;
                if (colonne>150)
                {
                    ligne+=5;
                    colonne=3;
                }


            }

            gotoligcol(65,100);
            system("pause");
            system("cls");
        }
        break;

        case 2:
        {
            std::cout << "Toutes les aretes : " << std::endl;
            int ligne=2, colonne=3;
            calculTempsTrajet();
            for (auto j : m_liste_trajet)
            {
                gotoligcol(ligne,colonne);
                Color(11,0);
                std::cout<<"'---------------------------------------'";
                Color(15,0);
                gotoligcol(ligne+2,colonne);
                std::cout<< "//  Numero trajet :"<<j->getterNumeroTrajet()<<" ";
                gotoligcol(ligne+3,colonne);
                std::cout << "//  Type trajet :" <<j->getterTypeTrajet()<<" ";
                gotoligcol(ligne+4,colonne);
                std::cout << "//  Temps du trajet :" <<j->getterTempsTrajet() <<" ";
                gotoligcol(ligne+6,colonne);
                Color(11,0);
                std::cout<<"'----------------------------------------'";
                Color(15,0);
                colonne=colonne+40;
                if (colonne>150)
                {
                    ligne+=8;
                    colonne=3;
                }
            }

            system("pause");
            system("cls");
        }
        break;


        case 3:
            trajetSommetDepartEtArrive();
            gotoligcol(24,70);
            system("pause");
            system("cls");
            break;

        case 4:
            SommettrajetDepartEtArrive();

            /*Avec ces fonctions, l'utilisateur peut appuyer sur n'importe quelle touche pour continuer,
            cela va nettoyer la console */
            gotoligcol(24,70);
            system("pause");
            system("cls");
            break;

        case 5:
        {
            ///On entre un premier sommet i.
            int sommet1, sommet2;
            std::cout << std::endl << "Entrez ici sommet initial : ";
            std::cin >> sommet1;

            ///On saisie un deuxieme sommet j.
            std::cout << std::endl << std::endl << "Entrez ici le sommet final : ";
            std::cin >> sommet2;
            std::cout << std::endl;
            algo_BFS(sommet1, sommet2);
        }

        break;

        case 6:
            ///On entre un premier sommet i.
            int sommet1, sommet2;
            std::cout << std::endl << "Entrez ici sommet initial : ";
            std::cin >> sommet1;

            ///On saisie un deuxieme sommet j.
            std::cout << std::endl << std::endl << "Entrez ici le sommet final : ";
            std::cin >> sommet2;
            std::cout << std::endl;

            ///On appelle l'algorithme de Dijstra directement
            ///On l'applique au entier i et j.
            calculTempsTrajet();
            //algo_Dijkstra(sommet1, sommet2);
            algo_DijkstraPLS(sommet1);

            /*Avec ces fonctions, l'utilisateur peut appuyer
             sur n'importe quelle touche pour continuer,
             cela va nettoyer la console */

            //On saute une ligne
            std::cout << std::endl;
            system("pause");
            system("cls");
            break;

        case 7:
            algo_cheminPersonnalise();
            /*Avec ces fonctions, l'utilisateur peut appuyer
            sur n'importe quelle touche pour continuer,
            cela va nettoyer la console */

            //On saute une ligne
            std::cout << std::endl;
            system("pause");
            system("cls");
            break;

        }

    }
    while(choix != 5);  //Blindage
}


