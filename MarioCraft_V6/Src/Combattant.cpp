#include "Headers/Combattant.h"

using namespace std;

Combattant::Combattant(int pos_x, int pos_y)
    : Personnage(pos_x, pos_y)
{
    cout << "Combattant::Constructeur" << endl;
    _type_element = "Combattant";
    _degats = DEGATS_COMBATTANT;
}

Combattant::~Combattant()
{
    cout << "Combattant::Destructeur" << endl;
}

void Combattant::attaquer(Element * e)
{
    e->perteVie(_degats);
}


