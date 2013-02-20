#ifndef _GAMEVIEW_
#define _GAMEVIEW_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Input.hpp>

#include <sstream>
#include <iostream>
#include "GameModel.h"

class GameView
{
private:
    int _w, _h;

    GameModel * _model;

    sf::RenderWindow * _window;

    sf::View _vue;

    sf::Sprite _map_sprite;
    sf::Sprite _combattant_sprite;
    sf::Sprite _artisan_sprite;
    sf::Sprite _foyer_sprite;
    sf::Sprite _caserne_sprite;
    sf::Sprite _bois_sprite;
    sf::Sprite _nourriture_sprite;

    sf::Image _map;
    sf::Image _artisan;
    sf::Image _combattant;
    sf::Image _foyer;
    sf::Image _caserne;
    sf::Image _bois;
    sf::Image _nourriture;

public:

    GameView(int w, int h, GameModel * model);
    ~GameView();

    void Display();
    sf::RenderWindow * getWindow()const;
    void zoomVue(char c);
};

#endif
