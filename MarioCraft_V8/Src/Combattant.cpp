#include "Headers/Combattant.h"

using namespace std;

Combattant::Combattant(int pos_x, int pos_y, Batiment * f)
    : Personnage(pos_x, pos_y)
{
    cout << "Combattant::Constructeur" << endl;
    _type_element = "Combattant";
    _degats = DEGATS_COMBATTANT;
    _target_perso = NULL;
    _dest_x = pos_x;
    _dest_y = pos_y;
    _type_tache = "";
    _foy = f;
}

Combattant::~Combattant()
{
    cout << "Combattant::Destructeur" << endl;
}

void Combattant::attaquer()
{
    _target_perso->perteVie(_degats);
}

Batiment * Combattant::getTargetPerso()const{
	return _target_perso;
}

void Combattant::setTargetPerso(Batiment * target){
	_target_perso = target;
}

string Combattant::getTypeTache()const{
    return _type_tache;
}

Batiment * Combattant::getFoyer()const{
    return _foy;
}

void Combattant::setTypeTache(string type_tache){
    _type_tache = type_tache;
}

void Combattant::effectuerTache(){
	if (_type_tache == "Patrouille")
    {
        int ecart_moins = 495;
        int ecart_plus = 505;
        int dest = 500;
        int foy_x = _foy->getPosX();
        int foy_y = _foy->getPosY();

        if (_pos_x <= (foy_x - ecart_moins) and _pos_x >= (foy_x - ecart_plus) and _pos_y >= (foy_y - ecart_plus) and _pos_y <= (foy_y - ecart_moins))
            _dest_x = (foy_x + dest);

        else if (_pos_x >= (foy_x + ecart_moins) and _pos_x <= (foy_x + ecart_plus) and _pos_y >= (foy_y - ecart_plus) and _pos_y <= (foy_y - ecart_moins))
            _dest_y = (foy_y + dest);

        else if (_pos_y >= (foy_y + ecart_moins) and _pos_y <= (foy_y + ecart_plus) and _pos_x >= (foy_x + ecart_moins) and _pos_x <= (foy_x + ecart_plus))
            _dest_x = (foy_x - dest);

        else if (_pos_x <= (foy_x - ecart_moins) and _pos_x >= (foy_x - ecart_plus) and _pos_y <= (foy_y + ecart_plus) and _pos_y >= (foy_y + ecart_moins))
            _dest_y = (foy_y - dest);
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


