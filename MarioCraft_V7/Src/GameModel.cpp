#include "Headers/GameModel.h"

using namespace std;

GameModel::GameModel() {
    cout << "GameModel::Constructeur" << endl;
    _joueurs.push_back(new Joueur());
}

GameModel::~GameModel() {
    eraseJoueurs();
    cout << "GameModel::Destructeur" << endl;
}

void GameModel::nextStep() {
    _joueurs[0]->nextStep();
}

void GameModel::eraseJoueurs(){
    for (unsigned int i = 0; i < _joueurs.size(); ++i)
        delete _joueurs[i];
   
   _joueurs.clear();
}

Joueur * GameModel::getJoueur1()const{
    return _joueurs[0];
}
