#ifndef _GAME_MODEL_
#define _GAME_MODEL_

#include "Joueur.h"
#include "Constantes.h"
#include <vector>

class GameModel {

  private:
    std::vector<Joueur*> _joueurs;


  public:
    GameModel();
    ~GameModel();
    void nextStep();
    void eraseJoueurs();
    Joueur * getJoueur1()const;

};

#endif
