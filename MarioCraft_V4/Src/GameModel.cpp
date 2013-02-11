#include "Headers/GameModel.h"

using namespace std;

GameModel::GameModel() {
    cout << "GameModel::Constructeur" << endl;
    _foyerConstruit = false;
    _quantite_nourriture = 50;
    _quantite_bois = 50;
    _compteur_bois = 3;
    _compteur_nourriture = 3;
    _compteur_artisans = 0;
}

GameModel::~GameModel() {
    eraseMap();
    cout << "GameModel::Destructeur" << endl;
}

void GameModel::nextStep() {

}

bool GameModel::foyerConstruit()const {
    return _foyerConstruit;
}

void GameModel::eraseMap() {
    for (unsigned int i = 0; i < _elements.size(); ++i)
        delete _elements[i];

    _elements.clear();
}

void GameModel::construireElement(int pos_x, int pos_y, string type) {
    if (type == "Foyer")
    {
        if (_quantite_bois >= 40 and _quantite_nourriture >= 40)
        {
            _elements.push_back(new Foyer (pos_x, pos_y));
            _foyerConstruit = true;
            _quantite_nourriture -= 40;
            _quantite_bois -= 40;
        }
    }
    else if (type == "Caserne")
    {
        if (_quantite_bois >= 40 and _quantite_nourriture >= 10)
        {
            _elements.push_back(new Caserne (pos_x, pos_y));
            _quantite_nourriture -= 10;
            _quantite_bois -= 40;
        }
    }
    else if (type == "Bois")
    {
        _elements.push_back(new Bois (pos_x, pos_y));
        _compteur_bois--;
    }
    else if (type == "Nourriture")
    {
        _elements.push_back(new Nourriture (pos_x, pos_y));
        _compteur_nourriture--;
    }

    else if (type == "Artisan")
    {
        _elements.push_back(new Artisan(pos_x, pos_y - DIMENSION_PERSO));
        _compteur_artisans++;
	}
}

int GameModel::getListElementSize()const {
    return _elements.size();
}

Element * GameModel::getElement(int i)const {
    return _elements[i];
}

void GameModel::eliminerElement(int i) {
    _elements.erase(_elements.begin()+i);
}

Element * GameModel::searchElement(int pos_x, int pos_y)const {

    for (unsigned int i = 0; i < _elements.size(); ++i)
    {
        if (_elements[i]->getPosX() <= pos_x and _elements[i]->getPosX() + DIMENSION_SPRITE >= pos_x
                and _elements[i]->getPosY() <= pos_y and _elements[i]->getPosY() + DIMENSION_SPRITE >= pos_y)
        {
            return _elements[i];
        }
    }
    return NULL;
}

bool GameModel::listeVide()const {
    return _elements.empty();
}

void GameModel::elementsDesactives() {
    for (unsigned int i = 0; i < _elements.size(); ++i)
        _elements[i]->setActif(false);
}

string GameModel::intToString(int a)const {
    ostringstream oss;
    oss << a;
    return oss.str();
}

int GameModel::getQuantiteNourriture()const {
    return _quantite_nourriture;
}

void GameModel::setQuantiteNourriture(int a) {
    _quantite_nourriture = a;
}

int GameModel::getCompteurArtisans()const {
    return _compteur_artisans;
}

void GameModel::setCompteurArtisans(int a) {
    _compteur_artisans = a;
}

int GameModel::getQuantiteBois()const {
    return _quantite_bois;
}

void GameModel::setQuantiteBois(int a) {
    _quantite_bois = a;
}

int GameModel::getCompteurBois()const {
    return _compteur_bois;
}

int GameModel::getCompteurNourriture()const {
    return _compteur_nourriture;
}

Element * GameModel::searchFoyer()const{
    for (unsigned int i = 0; i < _elements.size(); ++i)
    {
        if (_elements[i]->getType() == "Foyer")
            return _elements[i];
    }
    
    return NULL;
}

Element * GameModel::searchElementActif()const {

    for (unsigned int i = 0; i < _elements.size(); ++i)
    {
        if (_elements[i]->estActif() == true)
        {
            return _elements[i];
        }
    }
    return NULL;
}

void GameModel::activerToutesUnites(string type){
    for (unsigned int i = 0; i < _elements.size(); ++i)
    {
        if (_elements[i]->getType() == type)
            _elements[i]->setActif(true);
    }
}

vector<Element*> GameModel::unitesActives(string type)const{

    vector<Element*> unites;
    for (unsigned int i = 0; i < _elements.size(); ++i)
    {
        if (_elements[i]->getType() == type and _elements[i]->estActif() == true    )
            unites.push_back(_elements[i]);
    }
    return unites;
}
