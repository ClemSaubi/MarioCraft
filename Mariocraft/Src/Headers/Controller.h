#ifndef _CONTROLLER_
#define _CONTROLLER_

#include <SFML/System.hpp>
#include <SFML/Window/Input.hpp>

#include <sstream>
#include <iostream>

#include "GameModel.h"
#include "GameView.h"

class Controller
{
private:
	GameModel * _model;
	GameView * _view;

	sf::Event _event;
    sf::Clock _timer_unite;

public:
    Controller(GameModel * model, GameView * view);
    ~Controller();
    
    bool treatEvents();
    bool sourisSurElement(float x, float y, Element * e)const;
    bool sourisSurComposant(float x, float y, Composant * c)const;
    void activationElement(int x, int y);
    void gestionUnites(int x, int y);
    void constructionFoyer(int x, int y, Composant * c);
    void constructionCaserne(int x, int y, Element * e, Composant * c);
    void definirTarget(int x, int y);
};

#endif