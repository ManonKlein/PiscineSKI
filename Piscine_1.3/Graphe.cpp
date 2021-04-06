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
    for (int i=0; i<nombrePoints; i++)      // On fait une boucle pour i allant de 0 au nombre de points
    {
        ifs >> numeroPoint;                 //on recuper le numero du point dans le fichier txt
        ifs >> nomLieuPoint;                //on recupere le nom du lieu du point dans le fichier txt
        ifs >> altitudePoint;               //on recupere l'altitude du point dans le fichier txt
        m_graphe_points.push_back(new Sommet(numeroPoint, nomLieuPoint, altitudePoint));
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
        do
        {
            std::cout << "Que voulez vous faire ? " << std::endl;
            std::cout << "1. A partir du NUMERO du trajet trouver le point de depart et d'arriver de ce trajet " << std::endl;
            std::cout << "2. A partir du NOM du trajet trouver le point de depart et d'arriver de ce trajet" << std::endl;
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
            int numtraj;
            std::cout<<"Vous avez choisi de choisir à partir du numero de trajet " <<std::endl;
            std::cout<<"Veuillez saisir le numero : ";
            std::cin>>numtraj;
            std::cout << std::endl;

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
                            nompointdepart = m->getterSnomLieuPoint();     //on recupere le nom du point de depart
                        }
                        if(pointarrivee == m->getterSnumeroPoint())          //si le point correspon au point de depart
                        {
                            nompointarrivee = m->getterSnomLieuPoint();     //on recupere le nom du point d'arrivee
                        }

                    }
                    std::cout<<" A partir du trajet numero "<<numtraj<<std::endl;
                    std::cout<<" -le point de depart de ce trajet est le numero :"<<pointdepart<<" qui corssepond a "<<nompointdepart<<std::endl;
                    std::cout<<" -le point d'arrivee de ce trajet est le numero :"<<pointarrivee<<" qui correspond a "<<nompointarrivee<<std::endl;
                    std::cout << std::endl;
                    std::cout << std::endl;

                }
            }
            /*Avec ces fonctions, l'utilisateur peut appuyer sur n'importe quelle touche pour continuer,
            cela va nettoyer la console */

            //On saute une ligne
            std::cout << std::endl;
            system("pause");
            system("cls");
        }
        break;

        case 2:
        {
            std::string nomtraj;
            std::cout<<"Vous avez choisi de choisir à partir du nom de trajet " <<std::endl;
            std::cout<<"Veuillez saisir le nom du trajet : ";
            std::cin>>nomtraj;
            std::cout << std::endl;
            std::cout << std::endl;

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
                            nompointdepart = m->getterSnomLieuPoint();     //on recupere le nom du point de depart
                        }
                        if(pointarrivee == m->getterSnumeroPoint())          //si le point correspon au point de depart
                        {
                            nompointarrivee = m->getterSnomLieuPoint();     //on recupere le nom du point d'arrivee
                        }

                    }
                    std::cout<<" A partir du trajet nnommé "<<nomtraj<<std::endl;
                    std::cout<<" -le point de depart de ce trajet est le numero :"<<pointdepart<<" qui corssepond a "<<nompointdepart<<std::endl;
                    std::cout<<" -le point d'arrivee de ce trajet est le numero :"<<pointarrivee<<" qui correspond a "<<nompointarrivee<<std::endl;
                    std::cout << std::endl;
                    std::cout << std::endl;

                }
            }

            /*Avec ces fonctions, l'utilisateur peut appuyer sur n'importe quelle touche pour continuer,
            cela va nettoyer la console */

            //On saute une ligne
            std::cout << std::endl;
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
        do
        {
            std::cout << "Que voulez vous faire ? " << std::endl;
            std::cout << "1. A partir du NUMERO du point trouver les trajets qui en partent et qu'y permettent d'y arriver " << std::endl;
            std::cout << "2. A partir du NOM du lieu trouver les trajets qui en partent et qu'y permettent d'y arriver" << std::endl;
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
            int numpoint;
            std::cout<<"Vous avez choisi de choisir à partir du numero du point " <<std::endl;
            std::cout<<"Veuillez saisir le numero : ";
            std::cin>>numpoint;
            std::cout << std::endl;

            int trajetQuiArriveINT, trajetQuiPartINT;
            std::string trajetQuiArrive, trajetQuiPart;

            for (auto m : m_liste_trajet)                        //on parcours la liste des trajets
            {
                if(numpoint == m->getterPointDepart())          //si le point correspond au point de depart
                {
                    trajetQuiArriveINT=m->getterNumeroTrajet();    //on recupere le numero du trajet
                    trajetQuiArrive = m->getterNomTrajet();     //on recupere le nom du trajet
                    std::cout<<" Le trajet numero : "<<trajetQuiArriveINT<<" nomme : "<<trajetQuiArrive<<" part du point choisi"<<std::endl;
                }

                if(numpoint == m->getterPointArrivee())          //si le point correspond au point de depart
                {
                    trajetQuiPartINT=m->getterNumeroTrajet();    //on recupere le numero du trajet
                    trajetQuiPart = m->getterNomTrajet();     //on recupere le nom du trajet
                    std::cout<<" Le trajet numero : "<<trajetQuiPartINT<<" nomme : "<<trajetQuiPart<<" arrive au point choisi"<<std::endl;
                }

            }
            /*Avec ces fonctions, l'utilisateur peut appuyer sur n'importe quelle touche pour continuer,
            cela va nettoyer la console */

            //On saute une ligne
            std::cout << std::endl;
            system("pause");
            system("cls");
        }
        break;

        case 2:
        {
            std::string nompoint;
            std::cout<<"Vous avez choisi de choisir à partir du numero du point " <<std::endl;
            std::cout<<"Veuillez saisir le nom du point : ";
            std::cin>>nompoint;
            std::cout << std::endl;

            int trajetQuiArriveINT, trajetQuiPartINT;
            std::string trajetQuiArrive, trajetQuiPart;
            int numpoint;

            for (auto z : m_graphe_points)
            {
                if(nompoint== z->getterSnomLieuPoint())
                {
                    numpoint= z->getterSnumeroPoint();
                }
            }
            for (auto m : m_liste_trajet)                        //on parcours la liste des trajets
            {
                if(numpoint == m->getterPointDepart())          //si le point correspond au point de depart
                {
                    trajetQuiArriveINT=m->getterNumeroTrajet();    //on recupere le numero du trajet
                    trajetQuiArrive = m->getterNomTrajet();     //on recupere le nom du trajet
                    std::cout<<" Le trajet numero : "<<trajetQuiArriveINT<<" nomme : "<<trajetQuiArrive<<" part du point choisi"<<std::endl;
                }

                if(numpoint == m->getterPointArrivee())          //si le point correspond au point de depart
                {
                    trajetQuiPartINT=m->getterNumeroTrajet();    //on recupere le numero du trajet
                    trajetQuiPart = m->getterNomTrajet();     //on recupere le nom du trajet
                    std::cout<<" Le trajet numero : "<<trajetQuiPartINT<<" nomme : "<<trajetQuiPart<<" arrive au point choisi"<<std::endl;
                }

            }
            /*Avec ces fonctions, l'utilisateur peut appuyer sur n'importe quelle touche pour continuer,
            cela va nettoyer la console */

            //On saute une ligne
            std::cout << std::endl;
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
            tempsTrajet= (altitudeTrajet/100) *2;                //denivele/100 afin d'avoir le temps de trajet en seconde
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
            tempsTrajet= ((altitudeTrajet/100) *2*60)+4*60;                //denivele/100 afin d'avoir le temps de trajet en seconde
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
            tempsTrajet= ((altitudeTrajet/100) *3*60) +2*60;                //denivele/100 afin d'avoir le temps de trajet en seconde
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
            altitudeTrajet = (altitudearrivee)- (altitudedepart);  //on fait une soustraction afin d'avoir le denivelé
            tempsTrajet= ((altitudeTrajet/100) *3*60)+1*60;                //denivele/100 afin d'avoir le temps de trajet en seconde
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
            tempsTrajet= ((altitudeTrajet/100) *4*60)+1*60;                //denivele/100 afin d'avoir le temps de trajet en seconde
            tempsTrajet=tempsMinutesSecondes(tempsTrajet);          //on le converti en minute seconde
            k->setterTempsTrajet(tempsTrajet);                      // on le push
        }
        /// TELESKI
        if (  (k->getterTypeTrajet())  == (std::string) teleski) //si le trajet est une piste snowpark
        {
            pointdepart = k->getterPointDepart();                   //on recupere le point de depart de ce trajet
            pointarrivee = k->getterPointArrivee();                 //on recupere le point d'arrivee de ce trajet
            for(auto s : m_graphe_points)                          //on parcours la liste des points
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
            tempsTrajet= ((altitudeTrajet/100) *4*60)+1*60;                //denivele/100 afin d'avoir le temps de trajet en seconde
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

void Graphe::rechercher_sommet_connexe()
{

    int tmpdepart,tmparrivee;
    std::map<int, int> departArrivee;
    for (auto i : m_liste_trajet)
    {
        tmpdepart = i->getterPointDepart();
        tmparrivee =i->getterPointArrivee();
        std::cout <<"point depart de: "<<i<<" est"<<tmpdepart <<"et darrivee"<<tmparrivee<<std::endl;
        departArrivee[tmpdepart] =tmparrivee;
    }

    for(std::map<int,int>::iterator it=departArrivee.begin(); it!=departArrivee.end(); ++it)
    {
        std::cout << it->first << " depar" << it->second << " arrive" <<std::endl;
    }
}

Sommet* Graphe::rechercherPoint(int choix)
{
    for(auto elem : m_graphe_points)
    {
        if(choix == elem->getterSnumeroPoint())
            return elem;
    }
}

/// ALGO DIJKSTRA
void Graphe::algo_Dijkstra(int i, int f)
{

    std::priority_queue<std::pair<float,Sommet*>> file;		 ///On déclare la priority_queue

    std::pair<double, Sommet*> avant;
    int dist[m_graphe_points.size()];

    for(int j=0; j<m_graphe_points.size(); j++)
        dist[j] = 5000;

    dist[i-1]=0;
    //On push le tableau pour l'agrandir
    file.push(std::pair<double,Sommet*>(0, m_graphe_points[i-1]));
    ///Pour réaliser l'algorithme, on fait une boucle while
    /* Celle ci choisit le sommet non visité avec la distance la plus faible,
    calcule la distance à travers lui à chaque voisin non visité,
    et met à jour la distance du voisin si elle est plus petite.
    */

    while (file.size()!=0) //Tant que la file est différente de 0,
    {


        Sommet* som = file.top().second;
        file.pop();		//On pop pour ajouter une case

        //On fait une boucle for pour regarder les sommets adjacents
        //On les compare
        //On prend le plus léger
        for(auto trajet : som->getTrajets())
        {
            //On ajoute une boucle if pour réaliser la comparaison des sommets
            if(dist[trajet->getterPointArrivee()-1]> dist[som->getterSnumeroPoint()-1]+ trajet->getterTempsTrajet())
            {
               dist[trajet->getterPointArrivee()-1]= dist[som->getterSnumeroPoint()-1]+ trajet->getterTempsTrajet();
               file.push(std::pair<double, Sommet*>(dist[trajet->getterPointArrivee()-1], m_graphe_points[trajet->getterPointArrivee()-1]));
               avant.second = som;
               avant.first = trajet->getterTempsTrajet();
               m_graphe_points[trajet->getterPointArrivee()-1]->setterPred(avant);
            }
        }
    }

            Sommet *somFin = m_graphe_points[f-1];

            std::cout<<somFin->getterSnumeroPoint();

            while(somFin->getterSnumeroPoint() != m_graphe_points[i-1]->getterSnumeroPoint()) /// Affichage du chemin
            {
                std::cout<< " <--";
                std::cout<< m_graphe_points[somFin->getterSnumeroPoint()-1]->getAvant().second->getterSnumeroPoint();
                somFin= m_graphe_points[somFin->getterSnumeroPoint()-1]->getAvant().second;
            }
}

void Graphe::algo_BSFinteressant()
{
    int choix;
    do
    {
        do
        {
            std::cout << "Que voulez vous faire ? " << std::endl;
            std::cout << "1. Choisir un chemin skieur experimenté  " << std::endl;
            std::cout << "2. Choisir un chemin skieur debutant" << std::endl;
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
            int numpointdepartchoix,numpointarriveechoix;
            std::string pistenoire ="V", pistebleue ="B";
            int pointarriveeETAPE;
            std::cin>>numpointdepartchoix;
            std::cin>>numpointarriveechoix;

            for (auto i : m_liste_trajet)                   //on parcours la liste des trajets
            {
                if(numpointdepartchoix== i->getterPointDepart())       //si un point a comme point de depart ce point
                {
                    if(i->getterTypeTrajet()!= pistenoire || i->getterTypeTrajet() != pistebleue)
                    {
                        pointarriveeETAPE =i->getterPointArrivee();

                    }
                }
            }
            /*Avec ces fonctions, l'utilisateur peut appuyer sur n'importe quelle touche pour continuer,
            cela va nettoyer la console */

            //On saute une ligne
            std::cout << std::endl;
            system("pause");
            system("cls");
        }
        break;

        case 2:
        {

            /*Avec ces fonctions, l'utilisateur peut appuyer sur n'importe quelle touche pour continuer,
            cela va nettoyer la console */

            //On saute une ligne
            std::cout << std::endl;
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




///Fonction de la classe graphe pour afficher
void Graphe::affichage()
{
    std::cout << "=================== PROJET PISCINE: ===================" << std::endl;
    /* std::cout << "Algorithme de Kruskal " << std::endl << std::endl;
     std::cout << " - Cet algorithme demande un graphe non oriente." << std::endl;
     std::cout << " - Cet algorithme demande un graphe pondere. " << std::endl;
     std::cout << std::endl;
     std::cout << "Ordre du graphe : " << m_graphe_points.size() << std::endl;
     std::cout << std::endl;
     std::cout << "Tous les sommets :" << std::endl;


     //Boucle for pour afficher les sommets !
     for (auto i : m_graphe_points)
     {
         std::cout<<"Numero du point : "<< i->getterSnumeroPoint() << "    ";
         std::cout<<"Nom du lieu : "<< i->getterSnomLieuPoint() <<"   ";
         std::cout<<"Altitude : "<< i->getterSaltitudePoint() <<"    ";
         std::cout<< std::endl;
     }
     std::cout << std::endl;


     Avec ces fonctions, l'utilisateur peut appuyer
                 sur n'importe quelle touche pour continuer,
                 cela va nettoyer la console

                 //On saute une ligne
                 std::cout << std::endl;
                 system("pause");
                 system("cls");

     std::cout << "Toutes les aretes : " << std::endl;

     //On fait une boucle pour afficher toutes les aretes du graphe.

     calculTempsTrajet();
     for (auto j : m_liste_trajet)
     {

         j->affichageTrajet();
         //std::cout<<std::endl;
     }
     std::cout << std::endl;

     //On saute une ligne
                 std::cout << std::endl;
                 system("pause");
                 system("cls");
                 int choix;
     std::cin>>choix;
     trajetSommetDepartEtArrive(choix);*/
    int choix;
    do
    {
        do
        {
            std::cout << "Que voulez vous faire ? " << std::endl;
            std::cout << "1. Afficher les Sommets " << std::endl;
            std::cout << "2. Afficher les trajets possibles " << std::endl;
            std::cout << "3. choisir un trajet et savoir son point de depart ainsi que son point d'arrivee "<<std::endl;
            std::cout << "4. choisir un point blablabla " << std::endl;
            std::cout << "5. DIJKSTRAAAAAA" <<std::endl;
            std::cin >> choix;

            system("pause");
            system("cls");
        }
        while((choix<1) || (choix>5));

        //Fonction switch pour que l'utilisateur puisse choisir ce qu'il souhaite faire.
        switch(choix)
        {
        case 1:

            //Boucle for pour afficher les sommets !
            for (auto i : m_graphe_points)
            {
                std::cout<<"Numero du point : "<< i->getterSnumeroPoint() << "    ";
                std::cout<<"Nom du lieu : "<< i->getterSnomLieuPoint() <<"   ";
                std::cout<<"Altitude : "<< i->getterSaltitudePoint() <<"    ";
                std::cout<< std::endl;
            }
            std::cout << std::endl;


            /*Avec ces fonctions, l'utilisateur peut appuyer sur n'importe quelle touche pour continuer,
             cela va nettoyer la console */

            //On saute une ligne
            std::cout << std::endl;
            system("pause");
            system("cls");
            break;

        case 2:
            std::cout << "Toutes les aretes : " << std::endl;

            //On fait une boucle pour afficher toutes les aretes du graphe.

            calculTempsTrajet();
            for (auto j : m_liste_trajet)
            {

                j->affichageTrajet();
                //std::cout<<std::endl;
            }

            std::cout << std::endl;
            std::cout << std::endl;
            system("pause");
            system("cls");
            break;


        case 3:
            trajetSommetDepartEtArrive();

            /*Avec ces fonctions, l'utilisateur peut appuyer sur n'importe quelle touche pour continuer,
            cela va nettoyer la console */
            std::cout << std::endl;
            system("pause");
            system("cls");
            break;

        case 4:
            //SommettrajetDepartEtArrive();
            rechercher_sommet_connexe();
            /*Avec ces fonctions, l'utilisateur peut appuyer sur n'importe quelle touche pour continuer,
            cela va nettoyer la console */
            std::cout << std::endl;
            system("pause");
            system("cls");
            break;

        case 5:
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
            break;

        }
    }
    while(choix != 4);  //Blindage
}


