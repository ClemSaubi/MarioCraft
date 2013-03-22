#ifndef _GAME_MODEL_
#define _GAME_MODEL_

#include "Joueur.h"
#include "Composant.h"
#include "Nourriture.h"
#include "Bois.h"
#include "Constantes.h"
#include <vector>
#include <cstdlib>
#include <SFML/System.hpp>

enum AppState { MENU, SELECT, GAME };

class GameModel {

  private:
    std::vector<Joueur*> _joueurs;
    std::vector<Composant*> _composants;
    int _compteur_bois;
    int _compteur_nourriture;
    int _nombre_IA;
    AppState _state;
    std::string _level;
    float _temps;

    sf::Clock _timer_IA;

  public:
    GameModel();
    ~GameModel();

    void nextStep(int width, int height);
    void eraseMap();

    Joueur * getJoueur()const;
    
    //Gestion IA
    void creerIA(int bois, int nourriture);
    std::vector<Joueur*> getIAs()const;
    void attribuerTacheIA(Joueur * ia);
    void construireCombattantIA(Joueur * ia);

    Composant * getComposant(int i)const;
    void creationMap(int width, int height);
    void detruireComposant(int i);
    void deciblerComposant();
    unsigned int indiceComposantCible()const;
    Composant * searchComposantCible()const;
    Composant * searchComposant(int x, int y)const;
    std::vector<Composant*> listeComposants()const;
    bool listeComposantVide()const;

    AppState getState()const;
    void setState(AppState s);

    std::string getLevel()const;
    void setLevel(std::string level);

    void setTemps(float temps);

    bool searchCollision(Composant * c)const;
    bool position(Composant * c, int i)const;
    bool collision(Composant * c, int i)const;
    std::string intToString(int a)const;
    std::string commandes()const;

    void setNbIA(int nb);
    int getNbIA()const;
};

#endif
