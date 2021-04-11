#include <iostream>
#include <cstdlib>
#include "Graphe.h"
#include "Sommet.h"
#include "Trajet.h"

using namespace std;

int main()
{
    Graphe g{"data_arcs.txt"};
    g.affichage();
    return 0;
}
