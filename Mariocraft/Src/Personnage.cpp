#include "Headers/Personnage.h"

using namespace std;

Personnage::Personnage( int pos_x, int pos_y) :
    Element(pos_x, pos_y)
{
    cout << "Personnage::Constructeur" << endl;
    _pts_vie = POINTS_DE_VIE;
    _en_collision = false;
    _dest_x = pos_x;
    _dest_y = pos_y;
}

Personnage::~Personnage()
{
    cout << "Personnage::Destructeur" << endl;
}

int Personnage::getDestX()const {
    return _dest_x;
}

void Personnage::setDestX(int a) {
    _dest_x = a;
}

void Personnage::setDestY(int a) {
    _dest_y = a;
}

int Personnage::getDestY()const {
    return _dest_y;
}

bool Personnage::estEnCollision()const{
    return _en_collision;
}

void Personnage::rentreEnCollision(bool a){
    _en_collision = a;
}

int Personnage::MathAbs(int a)const{
    if (a < 0)
        return -a;
    else
        return a;
}