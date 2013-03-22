#include "Headers/Element.h"

using namespace std;

Element::Element(int pos_x, int pos_y)
{
    cout << "Element::Constructeur" << endl;
    _pos_x = pos_x;
    _pos_y = pos_y;
    _type_element = "";
    _est_actif = false;
}

Element::~Element()
{
    cout << "Element::Destructeur" << endl;
}

int Element::getPosX()const {
    return _pos_x;
}

void Element::setPosX(int pos_x) {
    _pos_x = pos_x;
}

int Element::getPosY()const {
    return _pos_y;
}

void Element::setPosY(int pos_y) {
    _pos_y = pos_y;
}

string Element::getTypeElement()const {
    return _type_element;
}

int Element::getVieElement()const {
    return _pts_vie;
}

void Element::perteVie(int degats)
{
    _pts_vie -= degats;
}

bool Element::estActif()const {
    return _est_actif;
}

void Element::setActif(bool actif) {
    _est_actif = actif;
}
