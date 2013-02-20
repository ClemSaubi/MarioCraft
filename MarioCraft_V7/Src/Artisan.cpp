#include "Headers/Artisan.h"

using namespace std;

Artisan::Artisan(int pos_x, int pos_y)
    : Personnage(pos_x, pos_y)
{
    cout << "Artisan::Constructeur" << endl;
    _quantite_max_ressources_artisan =  QUANTITE_RESSOURCES_MAX_ARTISAN;
    _type_element = "Artisan";
}

Artisan::~Artisan()
{
    cout << "Artisan::Destructeur" << endl;
}

int Artisan::getQuantiteRessource()const {
    return _quantite_max_ressources_artisan;
}
