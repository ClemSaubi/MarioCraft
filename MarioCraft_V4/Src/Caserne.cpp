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
    eraseVector();
    cout << "Caserne::Destructeur" << endl;
}

void Caserne::creerCombattant(int pos_x, int pos_y) {
    _combattants.push_back(new Combattant(pos_x, pos_y));
}

void Caserne::eliminerCombattant(int i) {
    _combattants.erase(_combattants.begin()+i);
}

void Caserne::eraseVector() {
    for (unsigned int i = 0; i < _combattants.size(); ++i)
        delete _combattants[i];
    _combattants.clear();
}