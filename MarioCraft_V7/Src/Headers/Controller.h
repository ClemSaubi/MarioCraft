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

public:
    Controller(GameModel * model, GameView * view);
    ~Controller();
    
    bool treatEvents();
    bool sourisSurElement(float x, float y, Element * e)const;
};

#endif