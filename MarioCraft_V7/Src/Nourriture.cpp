#include "Headers/Nourriture.h"

using namespace std;

Nourriture::Nourriture( int pos_x, int pos_y) :
    Composant(pos_x, pos_y)
{
    cout << "Nourriture::Constructeur" << endl;
    _type_element = "Nourriture";
    _pts_vie = 200;
}

Nourriture::~Nourriture()
{
    cout << "Nourriture::Destructeur" << endl;
}



