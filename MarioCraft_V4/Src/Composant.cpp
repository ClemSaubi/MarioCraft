#include "Headers/Composant.h"

using namespace std;

Composant::Composant(int pos_x, int pos_y) :
    Element(pos_x, pos_y) {
    cout << "Composant::Constructeur" << endl;
    _est_actif = false;
    _pts_vie = -1;
}

Composant::~Composant() {
    cout << "Composant::Destructeur" << endl;
}