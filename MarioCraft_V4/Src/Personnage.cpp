#include "Headers/Personnage.h"

using namespace std;

Personnage::Personnage( int pos_x, int pos_y) :
    Element(pos_x, pos_y)
{
    cout << "Personnage::Constructeur" << endl;
    _pts_vie = POINTS_DE_VIE;
    _active = false;
}

Personnage::~Personnage()
{
    cout << "Personnage::Destructeur" << endl;
}

bool Personnage::estActif()const {
    return _active;
}

void Personnage::setActif(bool actif) {
    _active = actif;
}
