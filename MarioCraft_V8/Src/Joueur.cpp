#include "Headers/Joueur.h"

using namespace std;

Joueur::Joueur(bool controlable, int bois, int nourriture) {
    cout << "Joueur::Constructeur" << endl;
    _foyerConstruit = false;
    _total_nourriture = nourriture;
    _total_bois = bois;
    _total_artisans = 0;
    _total_combattants = 0;
    id_art = 0;
    id_comb = 0;
    _controlable = controlable;
}

Joueur::~Joueur() {
    eraseJoueur();
    cout << "Joueur::Destructeur" << endl;
}

void Joueur::nextStep() {

    for (unsigned int i = 0; i < _personnages.size(); ++i)
    {
        detruirePersonnage(i);
        if (_personnages[i]->getPosX() < _personnages[i]->getDestX())
            _personnages[i]->setPosX(_personnages[i]->getPosX() + 6);

        if (_personnages[i]->getPosX() > _personnages[i]->getDestX())
            _personnages[i]->setPosX(_personnages[i]->getPosX() - 6);

        if (_personnages[i]->getPosY() < _personnages[i]->getDestY())
            _personnages[i]->setPosY(_personnages[i]->getPosY() + 6);

        if (_personnages[i]->getPosY() > _personnages[i]->getDestY())
            _personnages[i]->setPosY(_personnages[i]->getPosY() - 6);
        
        Artisan * art = dynamic_cast<Artisan*>(_personnages[i]);
        Combattant * com = dynamic_cast<Combattant*>(_personnages[i]);

        if (art != NULL)
        {
            if (art->getTarget() != NULL)
            {
                if (art->getBois() + art->getNourriture() < 5)
                    art->effectuerTache();
                else
                    retourFoyer(art);
            }
        }
        if (com != NULL)
            com->effectuerTache();
    }

    for (unsigned int i = 0; i < _batiments.size(); ++i)
        detruireBatiment(i);
}

bool Joueur::foyerConstruit()const {
    return _foyerConstruit;
}

void Joueur::eraseJoueur() {
    for (unsigned int i = 0; i < _batiments.size(); ++i)
        delete _batiments[i];

    for (unsigned int i = 0; i < _personnages.size(); ++i)
        delete _personnages[i];

    _batiments.clear();
    _personnages.clear();
}

void Joueur::construireBatiment(int pos_x, int pos_y, string type) {

    if (type == "Foyer")
    {
        if (_total_bois >= 40 and _total_nourriture >= 40)
        {
            _batiments.push_back(new Foyer (pos_x, pos_y));
            _foyerConstruit = true;
            _total_nourriture -= 40;
            _total_bois -= 40;
        }
        else
            cout << "Pas assez de ressources" << endl;
    }
    else if (type == "Caserne")
    {
        if (_foyerConstruit==true)
        {
            if (_total_bois >= 40 and _total_nourriture >= 10)
            {
                _batiments.push_back(new Caserne (pos_x, pos_y));
                _total_nourriture -= 10;
                _total_bois -= 40;
            }
            else
                cout << "Pas assez de ressources" << endl;
        }
    }
}

vector<Batiment*> Joueur::listeBatiments()const{
    return _batiments;
}

vector<Personnage*> Joueur::listePersonnages()const{
    return _personnages;
}

void Joueur::construireUnite(int pos_x, int pos_y, string type) {
    if (type == "Artisan")
    {
        if (_total_nourriture >= 15)
        {
            _total_artisans++;
            id_art++;
            _total_nourriture -= 15;
            
            switch(id_art)
            {
                case 1:_personnages.push_back(new Artisan(pos_x - DIMENSION_SPRITE, pos_y + DIMENSION_SPRITE));break;
                case 2:_personnages.push_back(new Artisan(pos_x, pos_y + DIMENSION_SPRITE));break;
                case 3:_personnages.push_back(new Artisan(pos_x + DIMENSION_SPRITE, pos_y + DIMENSION_SPRITE));break;
                case 4:_personnages.push_back(new Artisan(pos_x - DIMENSION_SPRITE, pos_y - 2*DIMENSION_SPRITE));break;
                case 5:_personnages.push_back(new Artisan(pos_x, pos_y - 2*DIMENSION_SPRITE));break;
                case 6:
                {
                    _personnages.push_back(new Artisan(pos_x + DIMENSION_SPRITE, pos_y - 2*DIMENSION_SPRITE));
                    id_art = 0;
                } break;
            }
        }
        else
            cout << "Pas assez de ressources" << endl;
    }
    else
    {
        if (_total_nourriture >= 15 and _total_bois >= 10)
        {
            _total_combattants++;
            _total_nourriture -= 15;
            id_comb++;
            _total_bois-= 10;
            
            switch(id_comb)
            {
                case 1:_personnages.push_back(new Combattant(pos_x - DIMENSION_SPRITE, pos_y + DIMENSION_SPRITE, searchFoyer()));break;
                case 2:_personnages.push_back(new Combattant(pos_x, pos_y + DIMENSION_SPRITE, searchFoyer()));break;
                case 3:_personnages.push_back(new Combattant(pos_x + DIMENSION_SPRITE, pos_y + DIMENSION_SPRITE, searchFoyer()));break;
                case 4:_personnages.push_back(new Combattant(pos_x - DIMENSION_SPRITE, pos_y - 2*DIMENSION_SPRITE, searchFoyer()));break;
                case 5:_personnages.push_back(new Combattant(pos_x, pos_y - 2*DIMENSION_SPRITE, searchFoyer()));break;
                case 6:
                {
                    _personnages.push_back(new Combattant(pos_x + DIMENSION_SPRITE, pos_y - 2*DIMENSION_SPRITE, searchFoyer()));
                    id_comb = 0;
                } break;
            }
        }
        else
            cout << "Pas assez de ressources" << endl;
    }
}

void Joueur::detruireBatiment(int i) {

    if (_batiments[i]->getVieElement() <= 0)
    {
        if (_batiments[i]->getTypeElement() == "Foyer")
            _foyerConstruit=false;

        _batiments.erase(_batiments.begin()+i);
    }
}

void Joueur::detruirePersonnage(int i){
    if (_personnages[i]->getVieElement() <= 0)
        _personnages.erase(_personnages.begin()+i);
}

void Joueur::retourFoyer(Artisan * art){
    if (art->getBois() + art->getNourriture() == 5)
    {
        int x = searchFoyer()->getPosX();
        int y = searchFoyer()->getPosY() + DIMENSION_SPRITE/2;
        art->setDestX(x);
        art->setDestY(y);

        if (art->getPosX() <= x and art->getPosX() >= x - 10
            and art->getPosY() <= y and art->getPosY() >= y - 10)
        {
            _total_nourriture += art->getNourriture();
            _total_bois += art->getBois();
            art->setBois(0);
            art->setNourriture(0);
        }
    }
}

vector<Artisan*> Joueur::artisansActifs()const{
    std::vector<Artisan*> arts;
    for (unsigned int i = 0; i < _personnages.size(); ++i)
    {
        Artisan * art = dynamic_cast<Artisan*>(_personnages[i]);
        if (art != NULL)
        {
            if (art->estActif() == true)
                arts.push_back(art);   
        }
    }
    return arts;
}

vector<Combattant*> Joueur::combattantsActifs()const{
    std::vector<Combattant*> combs;
    for (unsigned int i = 0; i < _personnages.size(); ++i)
    {
        Combattant * comb = dynamic_cast<Combattant*>(_personnages[i]);
        if (comb != NULL)
        {
            if (comb->estActif() == true)
                combs.push_back(comb);   
        }
    }
    return combs;
}

void Joueur::activerArtisans(){
    for (unsigned int i = 0; i < _personnages.size(); ++i)
    {
        if (dynamic_cast<Artisan*>(_personnages[i]))
            _personnages[i]->setActif(true);
    }
}

void Joueur::activerCombattants(){
    for (unsigned int i = 0; i < _personnages.size(); ++i)
    {
        if (dynamic_cast<Combattant*>(_personnages[i]))
            _personnages[i]->setActif(true);
    }
}

void Joueur::eliminerPersonnage(int i) {
    if (_personnages[i]->getTypeElement() == "Artisan")
        _total_artisans--;
    else
        _total_combattants--;

    _personnages.erase(_personnages.begin()+i);
}

Batiment * Joueur::getBatiment(int i)const {
    return _batiments[i];
}

Personnage * Joueur::getPersonnage(int i)const {
    return _personnages[i];
}

Element * Joueur::searchElement(int pos_x, int pos_y)const {

    unsigned int i = 0;
    bool personnage_trouve = false;
    bool batiment_trouve = false;

    while(i < _batiments.size() and batiment_trouve == false)
    {
        if (_batiments[i]->getPosX() < pos_x  and
                _batiments[i]->getPosX() + DIMENSION_SPRITE > pos_x and
                _batiments[i]->getPosY() < pos_y and
                _batiments[i]->getPosY() + DIMENSION_SPRITE > pos_y)

            batiment_trouve = true;

        else
            i++;
    }

    if (batiment_trouve == false)
    {
        i = 0;
        while(i < _personnages.size() and personnage_trouve == false)
        {
            if (_personnages[i]->getPosX() < pos_x  and
                    _personnages[i]->getPosX() + DIMENSION_SPRITE > pos_x and
                    _personnages[i]->getPosY() < pos_y and
                    _personnages[i]->getPosY() + DIMENSION_SPRITE > pos_y)

                personnage_trouve = true;

            else
                i++;
        }
    }

    if (batiment_trouve == true)
        return _batiments[i];

    else if (personnage_trouve == true)
        return _personnages[i];

    else
        return NULL;
}

unsigned int Joueur::indiceBatimentActif()const {

    unsigned int i = 0;
    bool trouve = false;

    while(i < _batiments.size() and trouve == false)
    {
        if (_batiments[i]->estActif() == true)
            trouve = true;
        else
            i++;
    }
    if (trouve == true)
        return i;
    else
        return -1;
}

unsigned int Joueur::indicePersonnageActif()const {

    unsigned int i = 0;
    bool trouve = false;

    while(i < _personnages.size() and trouve == false)
    {
        if (_personnages[i]->estActif() == true)
            trouve = true;
        else
            i++;
    }
    if (trouve == true)
        return i;
    else
        return -1;
}

bool Joueur::listeBatimentVide()const {
    return _batiments.empty();
}

bool Joueur::listePersonnageVide()const {
    return _personnages.empty();
}

void Joueur::elementsDesactives() {
    for (unsigned int i = 0; i < _batiments.size(); ++i)
        _batiments[i]->setActif(false);

    for (unsigned int i = 0; i < _personnages.size(); ++i)
        _personnages[i]->setActif(false);
}

int Joueur::getTotalNourriture()const {
    return _total_nourriture;
}

void Joueur::setTotalNourriture(int a) {
    _total_nourriture = a;
}

int Joueur::getTotalArtisans()const {
    return _total_artisans;
}

void Joueur::setTotalArtisans(int a) {
    _total_artisans = a;
}

int Joueur::getTotalCombattants()const {
    return _total_combattants;
}

void Joueur::setTotalCombattants(int a) {
    _total_combattants = a;
}

int Joueur::getTotalBois()const {
    return _total_bois;
}

void Joueur::setTotalBois(int a) {
    _total_bois = a;
}

bool Joueur::estControlable()const{
    return _controlable;
}

Batiment * Joueur::searchFoyer()const {
    unsigned int i = 0;
    bool trouve = false;

    while(trouve == false and i < _batiments.size())
    {
        if (_batiments[i]->getTypeElement() == "Foyer")
            trouve = true;

        else
            i++;
    }
    if (trouve == true)
        return _batiments[i];
    else
        return NULL;
}

Batiment * Joueur::caserneActive()const{
    unsigned int i = 0;
    bool trouve = false;

    while(trouve == false and i < _batiments.size())
    {
        if (_batiments[i]->getTypeElement() == "Caserne" and _batiments[i]->estActif() == true)
            trouve = true;

        else
            i++;
    }
    if (trouve == true)
        return _batiments[i];
    else
        return NULL;    
}
