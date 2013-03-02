#include "Headers/Combattant.h"

using namespace std;

Combattant::Combattant(int pos_x, int pos_y)
    : Personnage(pos_x, pos_y)
{
    cout << "Combattant::Constructeur" << endl;
    _type_element = "Combattant";
    _degats = DEGATS_COMBATTANT;
    _target_perso = NULL;
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

void Combattant::effectuerTache(){
	;
}


