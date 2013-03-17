#include "Headers/Artisan.h"

using namespace std;

Artisan::Artisan(int pos_x, int pos_y)
    : Personnage(pos_x, pos_y)
{
    cout << "Artisan::Constructeur" << endl;
    _type_element = "Artisan";
    _recolte_bois_artisan = 0;
    _recolte_nourriture_artisan = 0;
    _target = NULL;
}

Artisan::~Artisan()
{
    cout << "Artisan::Destructeur" << endl;
}

Composant * Artisan::getTarget()const {
    return _target;
}

void Artisan::setTarget(Composant * c) {
    _target = c;
}

int Artisan::getNourriture()const{
    return _recolte_nourriture_artisan;
}

int Artisan::getBois()const{
    return _recolte_bois_artisan;
}

void Artisan::setNourriture(int a){
    _recolte_nourriture_artisan = a;
}

void Artisan::setBois(int a){
    _recolte_bois_artisan = a;
}

void Artisan::effectuerTache(){
    if (_target != NULL and _target->getVieComposant() > 0)
    {
        int x, y;

        //Si artisan est en haut de target
        if (_pos_y < _target->getPosY() - 5)
        {
            // Si artisan est a droite de target
            if (_pos_x >= (_target->getPosX() + DIMENSION_SPRITE))
            {
                x = _target->getPosX();
                y = _target->getPosY() - DIMENSION_SPRITE + 3;
            }
            else if (_pos_x <= _target->getPosX() + 5)
            {
                x = _target->getPosX();
                y = _target->getPosY() - DIMENSION_SPRITE + 3;
            }
            else
            {
                x = _target->getPosX();
                y = _target->getPosY() - DIMENSION_SPRITE + 3;
            }
        }
        //Si artisan est en bas de target
        else if (_pos_y >= _target->getPosY() + 5)
        {
            // Si artisan est a droite de target
            if (_pos_x >= (_target->getPosX() + DIMENSION_SPRITE))
            {
                x = _target->getPosX();
                y = _target->getPosY() + DIMENSION_SPRITE + 3;
            }
            else if (_pos_x <= _target->getPosX() + 5)
            {
                x = _target->getPosX();
                y = _target->getPosY() + DIMENSION_SPRITE + 3;
            }
            else
            {
                x = _target->getPosX();
                y = _target->getPosY() + DIMENSION_SPRITE + 3;
            }
        }

        setDestX(x);
        setDestY(y);

        if (_recolte_nourriture_artisan + _recolte_bois_artisan < 5)
        {
            if (this->getPosX() >= (x - 10) and this->getPosX() <= x and
                this->getPosY() >= (y - 10) and this->getPosY() <= y)
            {
                if (_target->getTypeComposant() == "Nourriture")
                {
                    if (_timer_recolte.GetElapsedTime() > 1.f)
                    {
                        _recolte_nourriture_artisan++;
                        _target->perteVie(1);
                        _timer_recolte.Reset();
                    }
                }
                else
                {
                    if (_timer_recolte.GetElapsedTime() > 1.f)
                    {
                        _recolte_bois_artisan++;
                        _target->perteVie(1);
                        _timer_recolte.Reset();
                    }
                }
            }
        }
    }
    else
        _target = NULL;
}
