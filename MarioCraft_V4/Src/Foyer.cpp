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
    eraseVector();
    cout << "Foyer::Destructeur" << endl;
}

void Foyer::creerArtisan(int pos_x, int pos_y) {
    _artisans.push_back(new Artisan(pos_x, pos_y));
}

void Foyer::eliminerArtisan(int i) {
    _artisans.erase(_artisans.begin()+i);
}

void Foyer::eraseVector() {
    for (unsigned int i = 0; i < _artisans.size(); ++i)
        delete _artisans[i];
    _artisans.clear();
}
