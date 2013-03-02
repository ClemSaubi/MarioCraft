#ifndef _GAME_MODEL_
#define _GAME_MODEL_

#include "Joueur.h"
#include "Composant.h"
#include "Nourriture.h"
#include "Bois.h"
#include "Constantes.h"
#include <vector>
#include <cstdlib>

enum AppState { MENU, SELECT , GAME };

class GameModel {

  private:
    std::vector<Joueur*> _joueurs;
    std::vector<Composant*> _composants;
    int _compteur_bois;
    int _compteur_nourriture;
    AppState _state;

  public:
    GameModel();
    ~GameModel();
    void nextStep();
    void eraseMap();
    Joueur * getJoueurActif()const;
    Composant * getComposant(int i)const;
    void creationMap();
    void detruireComposant(int i);
    void deciblerComposant();
    unsigned int indiceComposantCible()const;
    Composant * searchComposantCible()const;
    Composant * searchComposant(int x, int y)const;
    int getListComposantSize()const;
    bool listeComposantVide()const;
    AppState getState()const;
    void setState(AppState s);

    bool searchCollision(Composant * c)const;
    bool position(Composant * c, int i)const;
    bool collision(Composant * c, int i)const;
    std::string intToString(int a)const;


};

#endif
