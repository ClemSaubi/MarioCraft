#include "Headers/Obstacle.h"

using namespace std;

Obstacle::Obstacle(int pos_x, int pos_y) :
    Composant(pos_x, pos_y)
{
    cout << "Obstacle::Constructeur" << endl;
    _type_element = "Obstacle";
}

Obstacle::~Obstacle()
{
    cout << "Obstacle::Destructeur" << endl;
}


