#include "Headers/Composant.h"

using namespace std;

Composant::Composant(int pos_x, int pos_y)
{
    cout << "Composant::Constructeur" << endl;
    _est_cible = false;
    _pos_x = pos_x;
    _pos_y = pos_y;
}

Composant::~Composant() {
    cout << "Composant::Destructeur" << endl;
}

bool Composant::estCible()const {
    return _est_cible;
}

void Composant::setCible(bool cible) {
    _est_cible = cible;
}

string Composant::getTypeComposant()const {
    return _type_composant;
}

int Composant::getPosX()const {
    return _pos_x;
}

void Composant::setPosX(int pos_x) {
    _pos_x = pos_x;
}

int Composant::getPosY()const {
    return _pos_y;
}

void Composant::setPosY(int pos_y) {
    _pos_y = pos_y;
}

int Composant::getVieComposant()const {
    return _pts_vie;
}

void Composant::perteVie(int degats)
{
    _pts_vie -= degats;
}