#include "Sommet.h"

/// _____________________________ CONSTRUCTEUR, CONSTRUCTEUR SURCHARGE ET DESCTRUCTEUR ____________________________

///Constructeur par défaut
Sommet::Sommet()
{

}

///Constructeur surchargé
Sommet::Sommet(int SnumeroPoint, std::string SnomLieuPoint, int SaltitudePoint)
{
    m_SnumeroPoint = SnumeroPoint;
    m_SnomLieuPoint = SnomLieuPoint;
    m_SaltitudePoint = SaltitudePoint;
}

///constructeur surchargé 2
Sommet::Sommet(int nbrSommet)
{
    m_nbrSommet=nbrSommet;
}
///Destructeur
Sommet::~Sommet()
{
    //Pour libérer la mémoire
}



/// _________________________________________ GETTER VARIABLE _______________________________________
int Sommet::getterSnumeroPoint()
{
    return m_SnumeroPoint;
    //On utilise un return
}
std::string Sommet::getterSnomLieuPoint()
{
    return m_SnomLieuPoint;
    //On utilise un return
}
int Sommet::getterSaltitudePoint()
{

    return m_SaltitudePoint;
    //On utilise un return
}
int Sommet::getterSmarque()
{
    return m_marque;
}


std::vector<Trajet*> Sommet::getTrajets()
{
    return m_trajets;
}

int Sommet::getterSnbrSommet()
{
    return m_nbrSommet;
}

std::pair<double, Sommet*> Sommet::getAvant()
{
    return m_avant;
}

int Sommet::getDist()
{
    return m_dist;
}




/// _________________________________________ SETTER VARIABLE _______________________________________

void Sommet::setterSnumeroPoint(int SnumeroPoint)
{
    m_SnumeroPoint = SnumeroPoint;
}

void Sommet::setterSnomLieuPoint(std::string SnomLieuPoint)
{
    m_SnomLieuPoint = SnomLieuPoint;
}

void Sommet::setterSaltitudePoint(int SaltitudePoint)
{
    m_SaltitudePoint = SaltitudePoint;
}

///Setteur pour le marquage
void Sommet::setterSmarque(int marque)
{
    m_marque= marque;
}

void Sommet::setterPred(std::pair<double, Sommet*> nouveauPred)
{
   m_avant = nouveauPred;
}

void Sommet::ajouterTrajet(Trajet* nouveauTrajet)
{
    m_trajets.push_back(nouveauTrajet);
}

void Sommet::setDist(int nouvelleDist)
{
    m_dist = nouvelleDist;
}

///Méthode pour réinitialiser le marquage d'un sommet à 0.
void Sommet::reinitialiser_marque()
{
    m_marque=0;
}
