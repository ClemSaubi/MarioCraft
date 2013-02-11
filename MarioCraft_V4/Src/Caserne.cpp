#include "Headers/Caserne.h"

using namespace std;

Caserne::Caserne(int pos_x, int pos_y)
    : Batiment(pos_x, pos_y)
{
    cout << "Caserne::Constructeur" << endl;
    _pts_vie = RESISTANCE;
    _type_element = "Caserne";
}

Caserne::~Caserne()
{
    cout << "Caserne::Destructeur" << endl;
}