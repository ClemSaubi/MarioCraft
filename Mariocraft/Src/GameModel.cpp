#include "Headers/GameModel.h"

using namespace std;

GameModel::GameModel() {
    cout << "GameModel::Constructeur" << endl;
    _joueurs.push_back(new Joueur());
    _compteur_bois = 8;
    _compteur_nourriture = 8;
    _state = GAME;
}

GameModel::~GameModel() {
    eraseMap();
    cout << "GameModel::Destructeur" << endl;
}

void GameModel::nextStep() {
    for (unsigned int i = 0; i < _joueurs.size(); ++i)
        _joueurs[i]->nextStep();

    for (unsigned int i = 0; i < _composants.size(); ++i)
    {
        detruireComposant(i);
        
        searchCollision(_composants[i]);
    }
}

void GameModel::eraseMap() {
    for (unsigned int i = 0; i < _joueurs.size(); ++i)
        delete _joueurs[i];

    for (unsigned int i = 0; i < _composants.size(); ++i)
        delete _composants[i];

    _joueurs.clear();
    _composants.clear();
}

Joueur * GameModel::getJoueurActif()const {
    unsigned int i = 0;
    bool trouve = false;

    while(i < _joueurs.size() and trouve == false)
    {
        if (_joueurs[i]->JoueurActif() == true)
            trouve = true;
        else
            i++;
    }
    if (trouve == true)
        return _joueurs[i];
    else
        return NULL;
}

void GameModel::creationMap(){
  while(_compteur_bois > 0)
  {
    _composants.push_back(new Bois(rand()%5000 - 50, rand()%2700 - 50));
    _compteur_bois--;
  }
  while(_compteur_nourriture > 0)
  {
    _composants.push_back(new Nourriture(rand()%5000 - 50, rand()%2700 - 50));
    _compteur_nourriture--;
  }
}

void GameModel::detruireComposant(int i){
    if (_composants[i]->getVieComposant() <= 0)
        _composants.erase(_composants.begin()+i);
}

Composant * GameModel::getComposant(int i)const {
    return _composants[i];
}

int GameModel::getListComposantSize()const {
    return _composants.size();
}

void GameModel::deciblerComposant() {
    for (unsigned int i = 0; i < _composants.size(); ++i)
        _composants[i]->setCible(false);
}

unsigned int GameModel::indiceComposantCible()const {
    unsigned int i = 0;
    bool trouve = false;

    while(i < _composants.size() and trouve == false)
    {
        if (_composants[i]->estCible() == true)
            trouve = true;
        else
            i++;
    }
    if (trouve == true)
        return i;
    else
        return -1;
}

Composant * GameModel::searchComposantCible()const {

    unsigned int i = 0;
    bool trouve = false;

    while(i < _composants.size() and trouve == false)
    {
        if (_composants[i]->estCible() == true)

            trouve = true;

        else
            i++;
    }
    if (trouve == true)
        return _composants[i];

    else
        return NULL;
}

string GameModel::intToString(int a)const {
    ostringstream oss;
    oss << a;
    return oss.str();
}

bool GameModel::listeComposantVide()const{
  return _composants.empty();
}

Composant * GameModel::searchComposant(int pos_x, int pos_y)const{
    unsigned int i = 0;
    bool trouve = false;

    while(i < _composants.size() and trouve == false)
    {
        if (_composants[i]->getPosX() < pos_x  and
                _composants[i]->getPosX() + DIMENSION_SPRITE > pos_x and
                _composants[i]->getPosY() < pos_y and
                _composants[i]->getPosY() + DIMENSION_SPRITE > pos_y)

            trouve = true;
        else
            i++;
    }

    if (trouve == true)
      return _composants[i];

    else
      return NULL;
}

AppState GameModel::getState()const{
    return _state;
}

void GameModel::setState(AppState s){
    _state = s;
}

bool GameModel::searchCollision(Composant * c)const{

    for (unsigned int i = 0; i < _joueurs.size(); ++i)
    {
        for (unsigned int j = 0; j < _joueurs[i]->listePersonnages().size(); ++j)
        {
            if (position(c,j) == true)
            {
                if (collision(c,j) == true){
                    _joueurs[i]->getPersonnage(j)->setDestX(_joueurs[i]->getPersonnage(j)->getPosX());
                    _joueurs[i]->getPersonnage(j)->setDestY(_joueurs[i]->getPersonnage(j)->getPosY());
                    _joueurs[i]->getPersonnage(j)->rentreEnCollision(true);

                    Artisan * art = dynamic_cast<Artisan*>(_joueurs[i]->getPersonnage(j));
                    if (art != NULL)
                        art->setTarget(NULL);

                    return true;
                }
            }
        }
    }
    return false;
}

bool GameModel::collision(Composant * c, int i)const{
    return (( getJoueurActif()->getPersonnage(i)->getPosX() <= c->getPosX() + DIMENSION_SPRITE*2/3 
        and   this->getJoueurActif()->getPersonnage(i)->getPosX() >= c->getPosX())
        or  ( getJoueurActif()->getPersonnage(i)->getPosX() + DIMENSION_SPRITE*2/3 <= c->getPosX() + DIMENSION_SPRITE*2/3
        and   this->getJoueurActif()->getPersonnage(i)->getPosX() + DIMENSION_SPRITE*2/3 >= c->getPosX()));
}

bool GameModel::position(Composant * c, int i)const{
    return (getJoueurActif()->getPersonnage(i)->getPosY() <= c->getPosY() + DIMENSION_SPRITE*2/3
        and this->getJoueurActif()->getPersonnage(i)->getPosY() >= c->getPosY())
        or (this->getJoueurActif()->getPersonnage(i)->getPosY() + DIMENSION_SPRITE*2/3 >= c->getPosY()
        and this->getJoueurActif()->getPersonnage(i)->getPosY() + DIMENSION_SPRITE*2/3 <= c->getPosY() + DIMENSION_SPRITE*2/3);
}