#include "Headers/GameModel.h"

using namespace std;

GameModel::GameModel() {
    cout << "GameModel::Constructeur" << endl;
    _nombre_IA = 0;
    _joueurs.push_back(new Joueur(true, 70, 70));    
    _compteur_bois = 30;
    _compteur_nourriture = 25;
    _state = MENU;
    _temps = 0.f;
    _level = "Facile";
    _timer_IA.Reset();
}

GameModel::~GameModel() {
    eraseMap();
    cout << "GameModel::Destructeur" << endl;
}

void GameModel::setNbIA(int nb){
    _nombre_IA = nb;
}

int GameModel::getNbIA()const{
    return _nombre_IA;
}

void GameModel::creerIA(int bois, int nourriture){
    for (int i = 0; i < _nombre_IA; ++i)
        _joueurs.push_back(new Joueur(false, bois, nourriture));
}

string GameModel::getLevel()const{
    return _level;
}

void GameModel::setTemps(float temps){
    _temps = temps;
}

void GameModel::setLevel(string level){
    _level = level;
}

void GameModel::nextStep(int width, int height) {
    
    for (unsigned int i = 0; i < _joueurs.size(); ++i)
        _joueurs[i]->nextStep();

    for (unsigned int i = 0; i < _composants.size(); ++i)
    {
        detruireComposant(i);
        // searchCollision(_composants[i]);
    }

    //Gestion IA
    vector<Joueur*> ia = getIAs();

    for (unsigned int i = 0; i < ia.size(); ++i)
    {
        //Tache IA
        attribuerTacheIA(ia[i]);

        if (_timer_IA.GetElapsedTime() > _temps)
        {
            int a = rand()%width;
            int b = rand()%height;
            
            if (ia[i]->foyerConstruit() == false)
            {
                if (a < 500)
                    a += 500;

                else if (a > width - 500)
                    a -= 500;

                if (b < 500)
                    b += 500;

                else if (b > height - 500)
                    b -= 500;

                ia[i]->construireBatiment(a, b, "Foyer");
                _timer_IA.Reset();
            }
            else
            {
                int nombre = rand()%10;

                if(nombre < 2)
                    ia[i]->construireBatiment(a, b, "Caserne");

                else if(nombre >= 2 and nombre <= 6)
                {
                    Batiment * foyer = ia[i]->searchFoyer();
                    ia[i]->construireUnite(foyer->getPosX(), foyer->getPosY(), "Artisan");
                }
                else 
                    construireCombattantIA(ia[i]);
                _timer_IA.Reset();
            }
        }
    }
}

void GameModel::construireCombattantIA(Joueur * ia){
    
    Batiment * caserne = NULL;

    int taille = ia->listeBatiments().size();

    if (taille > 0)
    {
        caserne = ia->getBatiment(rand()%taille);
        if (dynamic_cast<Caserne*>(caserne) != NULL)
            ia->construireUnite(caserne->getPosX(), caserne->getPosY(), "Combattant");    
    }
}

string GameModel::commandes()const
{
    string content;
    string ligne;
    ifstream f("../Text/commandes.txt");

    if(f)
    {
        while(!f.eof())
        {
            getline(f,ligne);
            content += ligne + "\n" ;
        }
    }
    else
        cerr << "Impossible d'ouvrir le fichier" << endl;

    f.close();

    return content;
}
void GameModel::attribuerTacheIA(Joueur * ia)
{
    Composant * c = NULL;
            
    if (_composants.size() > 0)
        c = _composants[rand()%_composants.size()];
    

    Personnage * p = NULL;
    int taille = ia->listePersonnages().size();
    if (taille > 0)
        p = ia->getPersonnage(rand()%taille);

    if (p != NULL)
    {
        Artisan * art = dynamic_cast<Artisan*>(p);
        Combattant * com = dynamic_cast<Combattant*>(p);
        if (art != NULL)
        {
            if (c != NULL and art->getTarget() == NULL)
                art->setTarget(c);
        }
        else if (com != NULL)
        {
            if (com->getTypeTache() == "")
            {
                com->setTypeTache("Patrouille");
                com->setDestX(ia->searchFoyer()->getPosX() - 500);
                com->setDestY(ia->searchFoyer()->getPosY() - 500);
            }
        }
    }    
}

void GameModel::eraseMap() {

    for (unsigned int i = 0; i < _joueurs.size(); ++i)
        delete _joueurs[i];

    for (unsigned int i = 0; i < _composants.size(); ++i)
        delete _composants[i];

    _composants.clear();
    _joueurs.clear();
}

Joueur * GameModel::getJoueur()const {
    return _joueurs[0];
}

vector<Joueur*> GameModel::getIAs()const{
    vector<Joueur*> ia;

    for (unsigned int i = 0; i < _joueurs.size(); ++i)
    {
        if (_joueurs[i]->estControlable() == false)
            ia.push_back(_joueurs[i]);
    }

    return ia;
}

void GameModel::creationMap(int width, int height){
  while(_compteur_bois > 0)
  {
    _composants.push_back(new Bois(rand()%width - 50, rand()%height - 50));
    _compteur_bois--;
  }
  while(_compteur_nourriture > 0)
  {
    _composants.push_back(new Nourriture(rand()%width - 50, rand()%height - 50));
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

vector<Composant*> GameModel::listeComposants()const{
    return _composants;
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
    for (unsigned int j = 0; j < getJoueur()->listePersonnages().size(); ++j)
    {
        if (position(c,j) == true)
        {
            if (collision(c,j) == true){
                getJoueur()->getPersonnage(j)->setDestX(getJoueur()->getPersonnage(j)->getPosX());
                getJoueur()->getPersonnage(j)->setDestY(getJoueur()->getPersonnage(j)->getPosY());
                getJoueur()->getPersonnage(j)->rentreEnCollision(true);

                Artisan * art = dynamic_cast<Artisan*>(getJoueur()->getPersonnage(j));
                if (art != NULL)
                    art->setTarget(NULL);

                return true;
            }
        }
    }
    return false;
}

bool GameModel::collision(Composant * c, int i)const{
    return (( getJoueur()->getPersonnage(i)->getPosX() <= c->getPosX() + DIMENSION_SPRITE*2/3 
        and   this->getJoueur()->getPersonnage(i)->getPosX() >= c->getPosX())
        or  ( getJoueur()->getPersonnage(i)->getPosX() + DIMENSION_SPRITE*2/3 <= c->getPosX() + DIMENSION_SPRITE*2/3
        and   this->getJoueur()->getPersonnage(i)->getPosX() + DIMENSION_SPRITE*2/3 >= c->getPosX()));
}

bool GameModel::position(Composant * c, int i)const{
    return (getJoueur()->getPersonnage(i)->getPosY() <= c->getPosY() + DIMENSION_SPRITE*2/3
        and this->getJoueur()->getPersonnage(i)->getPosY() >= c->getPosY())
        or (this->getJoueur()->getPersonnage(i)->getPosY() + DIMENSION_SPRITE*2/3 >= c->getPosY()
        and this->getJoueur()->getPersonnage(i)->getPosY() + DIMENSION_SPRITE*2/3 <= c->getPosY() + DIMENSION_SPRITE*2/3);
}