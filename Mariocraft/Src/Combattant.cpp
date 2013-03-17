#include "Headers/Combattant.h"

using namespace std;

Combattant::Combattant(int pos_x, int pos_y)
    : Personnage(pos_x, pos_y)
{
    cout << "Combattant::Constructeur" << endl;
    _type_element = "Combattant";
    _degats = DEGATS_COMBATTANT;
    _target_perso = NULL;
    _dest_x = pos_x;
    _dest_y = pos_y;
    _type_tache = "";
}

Combattant::~Combattant()
{
    cout << "Combattant::Destructeur" << endl;
}

void Combattant::attaquer()
{
    _target_perso->perteVie(_degats);
}

Element * Combattant::getTargetPerso()const{
	return _target_perso;
}

void Combattant::setTargetPerso(Element * target){
	_target_perso = target;
}

string Combattant::getTypeTache()const{
    return _type_tache;
}

void Combattant::setTypeTache(string type_tache){
    _type_tache = type_tache;
}

void Combattant::effectuerTache(){
	if (_type_tache == "Patrouille")
    {
        if (_pos_x >= 495 and _pos_x <= 500 and _pos_y <= 500 and _pos_y >= 495)
            _dest_x = 4000;

        else if (_pos_x >= 2995 and _pos_x <= 4000 and _pos_y <= 500 and _pos_y >= 495)
            _dest_y = 2500;

        else if (_pos_y >= 2495 and _pos_y <= 2500 and _pos_x >= 2995 and _pos_x <= 4000)
            _dest_x = 500;

        else if (_pos_x >= 495 and _pos_x <= 500 and _pos_y <= 2500 and _pos_y >= 2495)
            _dest_y = 500;
    }
    else if (_type_tache == "Attaque")
    {
        if (_target_perso != NULL)
        {
            int x = _target_perso->getPosX() + DIMENSION_SPRITE;
            int y = _target_perso->getPosY();
            setDestX(x);
            setDestY(y);

            if (_pos_x <= x + DIMENSION_SPRITE
            and _pos_y >= y and _pos_y <= y + DIMENSION_SPRITE)
                attaquer();
        }
    }
}


