#include "Headers/GameModel.h"

using namespace std;

GameModel::GameModel() {
    cout << "GameModel::Constructeur" << endl;
    _foyerConstruit = false;
    _quantite_nourriture = 70;
    _quantite_bois = 70;
    _compteur_bois = 4;
    _compteur_nourriture = 4;
    _compteur_artisans = 0;
    id = 0;
}

GameModel::~GameModel() {
    eraseMap();
    cout << "GameModel::Destructeur" << endl;
}

void GameModel::nextStep() {
    for (unsigned int i = 0; i < _elements.size(); ++i)
    {
        if (_elements[i]->getType() == "Artisan")
        {
            if (_elements[i]->getPosX() < _elements[i]->getDestX())
                _elements[i]->setPosX(_elements[i]->getPosX() + 4);

            if (_elements[i]->getPosX() > _elements[i]->getDestX())
                _elements[i]->setPosX(_elements[i]->getPosX() - 4);

            if (_elements[i]->getPosY() < _elements[i]->getDestY())
                _elements[i]->setPosY(_elements[i]->getPosY() + 4);

            if (_elements[i]->getPosY() > _elements[i]->getDestY())
                _elements[i]->setPosY(_elements[i]->getPosY() - 4);            
        }
    }
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
        else
            cout << "Pas assez de ressources" << endl;
    }
    else if (type == "Caserne")
    {
        if (_foyerConstruit==true)
        {
                if (_quantite_bois >= 40 and _quantite_nourriture >= 10)
            {
                _elements.push_back(new Caserne (pos_x, pos_y));
                _quantite_nourriture -= 10;
                _quantite_bois -= 40;
            }
            else
                cout << "Pas assez de ressources" << endl;
        }
    }
    else if (type == "Bois")
    {
        if (_compteur_bois > 0)
        {
            _elements.push_back(new Bois (pos_x, pos_y));
            _compteur_bois--;
        }
    }
    else if (type == "Nourriture")
    {
        if (_compteur_nourriture > 0)
        {
            _elements.push_back(new Nourriture (pos_x, pos_y));
            _compteur_nourriture--;
        }
    }
    else if (type == "Artisan")
    {
        if (_quantite_nourriture >= 15)
        {
            _compteur_artisans++;
            id++;
            _quantite_nourriture -= 15;

            if (_compteur_artisans%2 == 0)
                _elements.push_back(new Artisan(pos_x + (id-1)*DIMENSION_SPRITE
                                              , pos_y + DIMENSION_SPRITE));

            else
                _elements.push_back(new Artisan(pos_x + (id-1)*DIMENSION_SPRITE
                                  , pos_y + DIMENSION_SPRITE));
        }
        else
            cout << "Pas assez de ressources" << endl;

        if (id == 4)
            id = 0;
    }
}

void GameModel::eliminerElement(int i) {
    if (_elements[i]->getType()=="Foyer")
    {
        _foyerConstruit=false;
        _quantite_nourriture += 40;
        _quantite_bois += 40;
         _elements.erase(_elements.begin()+i);

    }
    if (_elements[i]->getType()=="Caserne")
    {
        _quantite_nourriture += 10;
        _quantite_bois += 40;
         _elements.erase(_elements.begin()+i);
    }
    if (_elements[i]->getType()=="Bois")
    {
        _compteur_bois++;
         _elements.erase(_elements.begin()+i);
    }
    if (_elements[i]->getType()=="Nourriture")
    {
        _compteur_nourriture++;
         _elements.erase(_elements.begin()+i);
    }
    if (_elements[i]->getType() == "Artisan")
    {
        _compteur_artisans--;
        _elements.erase(_elements.begin()+i);
    }
}

int GameModel::getListElementSize()const {
    return _elements.size();
}

Element * GameModel::getElement(int i)const {
    return _elements[i];
}

Element * GameModel::searchElement(int pos_x, int pos_y)const{

    unsigned int i = 0;
    bool trouve = false;

    while(i < _elements.size() and trouve == false)
    {
        if (_elements[i]->getType() == "Bois")
        {
            if (_elements[i]->getPosX() < pos_x and 
                _elements[i]->getPosX() + DIMENSION_ARBRE > pos_x and 
                _elements[i]->getPosY() < pos_y and 
                _elements[i]->getPosY() + DIMENSION_ARBRE > pos_y)

                trouve = true;

            else
                i++;
        }
        else
        {
            if (_elements[i]->getPosX() < pos_x and 
                _elements[i]->getPosX() + DIMENSION_SPRITE > pos_x and 
                _elements[i]->getPosY() < pos_y and 
                _elements[i]->getPosY() + DIMENSION_SPRITE > pos_y)

                trouve = true;

            else
                i++;
        }

    }
    if (trouve == true)
        return _elements[i];

    else
        return NULL;
}

Element * GameModel::searchElementCible()const{

    unsigned int i = 0;
    bool trouve = false;

    while(i < _elements.size() and trouve == false)
    {
        if (_elements[i]->estActif() or _elements[i]->estCible())

            trouve = true;

        else
            i++;
    }
    if (trouve == true)
        return _elements[i];

    else
        return NULL;
}

unsigned int GameModel::indiceElement()const {
    unsigned int i = 0;
    bool trouve = false;

    while(i < _elements.size() and trouve == false)
    {
        if (_elements[i]->estActif() == true or _elements[i]->estCible() == true)
            trouve = true;     
        else
            i++;
    }
    if (trouve == true)
        return i;
    else
        return -1;
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
    unsigned int i = 0;
    bool trouve = false;

    while(trouve == false and i < _elements.size())
    {
        if (_elements[i]->getType() == "Foyer")
            trouve = true;

        else
            i++;
    }
    if (trouve == true)
        return _elements[i];
    else
        return NULL;
}

Element * GameModel::searchElementActif()const {
    
    unsigned int i = 0;
    bool trouve = false;

    while(trouve == false and i < _elements.size())
    {
        if (_elements[i]->estActif() == true)
            trouve = true;

        else
            i++;
    }
    if (trouve == true)
        return _elements[i];
    else
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
        if (_elements[i]->getType() == type and _elements[i]->estActif() == true)
            unites.push_back(_elements[i]);
    }
    return unites;
}

void GameModel::deciblerElement(){
    for (unsigned int i = 0; i < _elements.size(); ++i)
        _elements[i]->setCible(false);
}