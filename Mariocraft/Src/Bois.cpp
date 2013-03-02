#include "Headers/Bois.h"

using namespace std;

Bois::Bois( int pos_x, int pos_y) :
    Composant(pos_x, pos_y)
{
    cout << "Bois::Constructeur" << endl;
    _type_composant = "Bois";
    _pts_vie = 100;
}

Bois::~Bois()
{
    cout << "Bois::Destructeur" << endl;
}



