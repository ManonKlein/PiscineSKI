#include "Trajet.h"

/// _____________________________ CONSTRUCTEUR, CONSTRUCTEUR SURCHARGE ET DESCTRUCTEUR ____________________________

///Constructeur par défaut, sans parametres
Trajet::Trajet()
{

}

///Constructeur surchargé pour initialiser les parametres.
Trajet::Trajet(int TnumeroTrajet, std::string TnomTrajet, std::string TtypeTrajet,int TpointDepart, int TpointArrivee,float TtempsTrajet)
{
    m_TnumeroTrajet = TnumeroTrajet;
    m_TnomTrajet = TnomTrajet;
    m_TtypeTrajet = TtypeTrajet;
    m_TpointDepart = TpointDepart;
    m_TpointArrivee = TpointArrivee;
    m_TtempsTrajet = TtempsTrajet;
}




/// _________________________________________ GETTER VARIABLE _______________________________________

///getter pour recuperer le numero du trajet
int Trajet::getterNumeroTrajet()
{
    return m_TnumeroTrajet;
}

///getter pour recuperer le nom du trajet
std::string Trajet::getterNomTrajet()
{
    return m_TnomTrajet;
    //On utilise un return
}

///getter pour recuperer le type du trajet
std::string Trajet::getterTypeTrajet()
{
    return m_TtypeTrajet;
    //On utilise un return
}

///getter pour recuperer le point de depart du trajet
int Trajet::getterPointDepart()
{
    return m_TpointDepart;
}

///getter pour recuperer le point d'arrivee du trajet
int Trajet::getterPointArrivee()
{
    return m_TpointArrivee;
}

float Trajet::getterTempsTrajet()
{
    return m_TtempsTrajet;
}

bool Trajet::getterFiltre()
{
    return m_filtre;
}



///______________________________________________ SETTER _________________________________________________________
void Trajet::setterTempsTrajet(float temps)
{
    m_TtempsTrajet=temps;
}

void Trajet::setterFiltre(bool _filtre)
{
    m_filtre = _filtre;
}



///_________________________________________ FONCTION ___________________________________________________

///Fonction pour afficher les aretes et les sommets qu'elles relient.
void Trajet::affichageTrajet()
{
    std::cout<< " Numero trajet :"<<m_TnumeroTrajet<<std::endl;
    std::cout << "Type trajet :" <<m_TtypeTrajet<<std::endl;
    //std::cout << "Premier sommet : " << m_TpointDepart << " // Deuxieme sommet : " << m_TpointArrivee << std::endl;
    std::cout << " TEMPS TRAJET  :" <<m_TtempsTrajet <<" ";
    std::cout << std::endl;
    std::cout<< std::endl;
}
