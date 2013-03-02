#include "Headers/Joueur.h"

using namespace std;

Joueur::Joueur() {
    cout << "Joueur::Constructeur" << endl;
    _foyerConstruit = false;
    _total_nourriture = 100;
    _total_bois = 100;
    _total_artisans = 0;
    _total_combattants = 0;
    id_unites = 0;
    _joueur_actif = true;
}

Joueur::~Joueur() {
    eraseJoueur();
    cout << "Joueur::Destructeur" << endl;
}

bool Joueur::JoueurActif()const{
    return _joueur_actif;
}

void Joueur::desactiverJoueur(bool a){
    _joueur_actif = a;
}

void Joueur::nextStep() {
    for (unsigned int i = 0; i < _personnages.size(); ++i)
    {
        if (_personnages[i]->getPosX() < _personnages[i]->getDestX())
            _personnages[i]->setPosX(_personnages[i]->getPosX() + 6);

        if (_personnages[i]->getPosX() > _personnages[i]->getDestX())
            _personnages[i]->setPosX(_personnages[i]->getPosX() - 6);

        if (_personnages[i]->getPosY() < _personnages[i]->getDestY())
            _personnages[i]->setPosY(_personnages[i]->getPosY() + 6);

        if (_personnages[i]->getPosY() > _personnages[i]->getDestY())
            _personnages[i]->setPosY(_personnages[i]->getPosY() - 6);
        
        Artisan * art = dynamic_cast<Artisan*>(_personnages[i]);

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
    }
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

vector<Personnage*> Joueur::listePersonnages()const{
    return _personnages;
}

void Joueur::construireUnite(int pos_x, int pos_y, string type) {
    if (type == "Artisan")
    {
        if (_total_nourriture >= 15)
        {
            _total_artisans++;
            id_unites++;
            _total_nourriture -= 15;
            _personnages.push_back(new Artisan(pos_x + (id_unites-1)*DIMENSION_SPRITE
                                               , pos_y + DIMENSION_SPRITE));
            if (id_unites == 4)
                id_unites = 0;
        }
        else
            cout << "Pas assez de ressources" << endl;
    }
    else
    {
        if (_total_nourriture >= 15 and _total_bois >= 10)
        {
            _total_combattants++;
            id_unites++;
            _total_nourriture -= 15;
            _total_bois-= 10;
            _personnages.push_back(new Combattant(pos_x + (id_unites-1)*DIMENSION_SPRITE
                                               , pos_y + DIMENSION_SPRITE));
            if (id_unites == 4)
                id_unites = 0;
        }
        else
            cout << "Pas assez de ressources" << endl;
    }
}

void Joueur::detruireBatiment(int i) {

    if (_batiments[i]->getTypeElement() == "Foyer")
        _foyerConstruit=false;

    _batiments.erase(_batiments.begin()+i);
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
        _personnages[i]->setActif(true);
}

void Joueur::eliminerPersonnage(int i) {
    if (_personnages[i]->getTypeElement() == "Artisan")
        _total_artisans--;
    else
        _total_combattants--;

    _personnages.erase(_personnages.begin()+i);
}

int Joueur::getListPersonnageSize()const {
    return _personnages.size();
}

int Joueur::getListBatimentSize()const {
    return _batiments.size();
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
