#include "Headers/Batiment.h"

using namespace std;

Batiment::Batiment(int pos_x, int pos_y) :
    Element(pos_x, pos_y)
{
    cout << "Batiment::Constructeur" << endl;
    _type_element = "Batiment";
}

Batiment::~Batiment()
{
    cout << "Batiment::Destructeur" << endl;
}