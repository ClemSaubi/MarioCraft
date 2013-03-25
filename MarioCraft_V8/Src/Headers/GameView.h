#ifndef _GAMEVIEW_
#define _GAMEVIEW_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Input.hpp>

#include <sstream>
#include <iostream>
#include "GameModel.h"
#include "pthread.h"

class GameView
{
private:
    int _w, _h;

    GameModel * _model;

    sf::RenderWindow * _window;

    sf::View _vue;
    
    sf::Sprite _background_menu_sprite;
    sf::Sprite _map_sprite;
    sf::Sprite _combattant_sprite;
    sf::Sprite _artisan_sprite;
    sf::Sprite _foyer_sprite;
    sf::Sprite _caserne_sprite;
    sf::Sprite _bois_sprite;
    sf::Sprite _nourriture_sprite;
    sf::Sprite _jouer_sprite;
    sf::Sprite _quitter_sprite; 
    sf::Sprite _foyer_IA_sprite;
    sf::Sprite _caserne_IA_sprite;
    sf::Sprite _artisan_IA_sprite;
    sf::Sprite _combattant_IA_sprite;
    sf::Sprite _levelF_sprite;
    sf::Sprite _levelM_sprite;
    sf::Sprite _levelD_sprite;
    sf::Sprite _oui_sprite;
    sf::Sprite _non_sprite;
    sf::Sprite _ouiC_sprite;
    sf::Sprite _nonC_sprite;
    sf::Sprite _play_sprite;
    sf::Sprite _help_sprite;
    

    sf::Image _background_menu;
    sf::Image _map;
    sf::Image _artisan;
    sf::Image _combattant;
    sf::Image _foyer;
    sf::Image _caserne;
    sf::Image _bois;
    sf::Image _nourriture;
    sf::Image _jouer;
    sf::Image _jouer2;
    sf::Image _quitter;
    sf::Image _quitter2;
    sf::Image _foyer_IA;
    sf::Image _caserne_IA;
    sf::Image _artisan_IA;
    sf::Image _combattant_IA;
    sf::Image _levelF;
    sf::Image _levelF_hov;
    sf::Image _levelM;
    sf::Image _levelM_hov;
    sf::Image _levelD;
    sf::Image _levelD_hov;
    sf::Image _oui;
    sf::Image _oui_hov;
    sf::Image _non;
    sf::Image _non_hov;
    sf::Image _ouiC;
    sf::Image _ouiC_hov;
    sf::Image _nonC;
    sf::Image _nonC_hov;
    sf::Image _play;
    sf::Image _play_hov;
    sf::Image _help;


    sf::Clock _timer;
    sf::Clock _timer_game;

public:

    GameView(int w, int h, GameModel * model);
    ~GameView();

    void Display();

    void * thread_nextStep(void* targs);
    sf::RenderWindow * getWindow()const;
    void zoomVue(char c);
    sf::Sprite toad();
    sf::Sprite mario();

    sf::Sprite toad_IA();
    sf::Sprite goomba_IA();

    void dessinJeu();
    void dessinMenu();
    void dessinSelection();

    void dessinBatimentsJoueur(sf::Font font);
    void dessinPersonnagesJoueur(sf::Font font);

    void dessinBatimentsIA();
    void dessinPersonnagesIA();

    void dessinComposants(sf::Font font);
    void dessinInformations(sf::Font font);
    void chargementImages();

    std::string time()const;

    bool sourisSurSprite(float x, float y, sf::Sprite s)const;
};

#endif
