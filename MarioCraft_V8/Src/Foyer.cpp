#include "Headers/Foyer.h"

using namespace std;

Foyer::Foyer(int pos_x, int pos_y)
    : Batiment(pos_x, pos_y)
{
    cout << "Foyer::Constructeur" << endl;
    _pts_vie = RESISTANCE*3;
    _type_element = "Foyer";
}

Foyer::~Foyer()
{
    cout << "Foyer::Destructeur" << endl;
}