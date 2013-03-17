#include "Headers/GameView.h"
#include "Headers/Constantes.h"

using namespace std;
using namespace sf;

GameView::GameView(int w, int h, GameModel * model): _w(w), _h(h)
{
    cout << "GameView::Constructeur" << endl;

    _model = model;
    _window = new RenderWindow(VideoMode::GetMode(0), "MarioCraft");

    Vector2f Center(_window->GetWidth()*2, _window->GetHeight()*2);
    Vector2f HalfSize(_window->GetWidth(), _window->GetHeight());
    _vue = View(Center, HalfSize);
    _timer_game.Reset();

    chargementImages();
    // pthread_create(&_thread_Step, NULL, GameView::thread_nextStep, (void *) model);

}

GameView::~GameView()
{
    if (_window != NULL)
    {
        cout << "GameView::Destructeur" << endl;
        delete _window;
    }
}

bool GameView::sourisSurSprite(float x, float y, Sprite s)const {
    if (x < s.GetPosition().x)
        return false;

    if (x > s.GetPosition().x + LARGEUR_BOUTON)
        return false;

    if (y < s.GetPosition().y)
        return false;

    if (y > s.GetPosition().y + HAUTEUR_BOUTON)
        return false;

    return true;
}


string GameView::time()const{
    ostringstream chaine;
    chaine << "Temps : " << (int)_timer_game.GetElapsedTime();
    return chaine.str();
}

void * GameView::thread_nextStep(void* targs)
{
    GameModel * model = (GameModel *) targs;

    do{
        model->nextStep();
        sleep(30);
    }while( model->getState() == GAME );

   pthread_exit(0);
}

Sprite GameView::toad(){
    if (_timer.GetElapsedTime()<0.2)
    {
        _artisan_sprite.SetSubRect(IntRect(5,18,29,52));
        return _artisan_sprite;
    }
    if (_timer.GetElapsedTime()<0.4)
    {
        _artisan_sprite.SetSubRect(IntRect(37,18,61,52));
        return _artisan_sprite;
    }
    if (_timer.GetElapsedTime()<0.6)
    {
        _artisan_sprite.SetSubRect(IntRect(69,18,93,52));
        return _artisan_sprite;
    }
    if (_timer.GetElapsedTime()<0.8)
    {
        _artisan_sprite.SetSubRect(IntRect(101,18,125,52));
        return _artisan_sprite;
    }
    if (_timer.GetElapsedTime()<1)
        _timer.Reset();

    return _artisan_sprite;
}

Sprite GameView::toad_IA(){
    if (_timer.GetElapsedTime()<0.2)
    {
        _artisan_IA_sprite.SetSubRect(IntRect(5,18,29,52));
        return _artisan_IA_sprite;
    }
    if (_timer.GetElapsedTime()<0.4)
    {
        _artisan_IA_sprite.SetSubRect(IntRect(37,18,61,52));
        return _artisan_IA_sprite;
    }
    if (_timer.GetElapsedTime()<0.6)
    {
        _artisan_IA_sprite.SetSubRect(IntRect(69,18,93,52));
        return _artisan_IA_sprite;
    }
    if (_timer.GetElapsedTime()<0.8)
    {
        _artisan_IA_sprite.SetSubRect(IntRect(101,18,125,52));
        return _artisan_IA_sprite;
    }
    if (_timer.GetElapsedTime()<1)
        _timer.Reset();

    return _artisan_IA_sprite;
}

Sprite GameView::mario(){
    if (_timer.GetElapsedTime()<0.2)
    {
        _combattant_sprite.SetSubRect(IntRect(28,0, 56, 43));
        return _combattant_sprite;
    }
    if (_timer.GetElapsedTime()<0.4)
    {
        _combattant_sprite.SetSubRect(IntRect(0,0,28,43));
        return _combattant_sprite;
    }
    if (_timer.GetElapsedTime()<0.6)
    {
        _combattant_sprite.SetSubRect(IntRect(29,0, 56, 43));
        return _combattant_sprite;
    }
    if (_timer.GetElapsedTime()<0.8)
    {
        _combattant_sprite.SetSubRect(IntRect(56,0,84,43));
        return _combattant_sprite;
    }
    if (_timer.GetElapsedTime()<1)
        _timer.Reset();

    return _combattant_sprite;
}

Sprite GameView::goomba_IA(){
    if (_timer.GetElapsedTime()<0.2)
    {
        _combattant_IA_sprite.SetSubRect(IntRect(20,0, 40, 24));
        return _combattant_IA_sprite;
    }
    if (_timer.GetElapsedTime()<0.4)
    {
        _combattant_IA_sprite.SetSubRect(IntRect(0,0,20,24));
        return _combattant_IA_sprite;
    }
    if (_timer.GetElapsedTime()<0.6)
    {
        _combattant_IA_sprite.SetSubRect(IntRect(20,0, 40, 24));
        return _combattant_IA_sprite;
    }
    if (_timer.GetElapsedTime()<0.8)
    {
        _combattant_IA_sprite.SetSubRect(IntRect(40,0,60,24));
        return _combattant_IA_sprite;
    }
    if (_timer.GetElapsedTime()<1)
        _timer.Reset();

    return _combattant_IA_sprite;
}

void GameView::Display()
{
    switch(_model->getState())
    {
        case MENU:dessinMenu();break;
        case SELECT:dessinSelection();break;
        case GAME:dessinJeu();break;
        default:break;
    }
}

void GameView::dessinSelection(){
    _window->Clear();

    const Input & input = _window->GetInput();
    Event event;

    Font * font = new Font();
    font->LoadFromFile("../Font/Zantroke.otf");
    
    String nbIA = String("Nombre IA : " + _model->intToString(_model->getNbIA()));
    nbIA.SetFont(*font);
    nbIA.SetColor(Color::White);
    nbIA.SetSize(30);
    nbIA.SetPosition(70, 370);

    String level = String("Difficulte: " + _model->getLevel());
    level.SetFont(*font);
    level.SetColor(Color::White);
    level.SetSize(30);
    level.SetPosition(900, 370);    

    while (_window->GetEvent(event)) {

        _window->Draw(_background_menu_sprite);

        _window->Draw(nbIA);
        _window->Draw(level);

        if (sourisSurSprite(input.GetMouseX(), input.GetMouseY(), _nb1_sprite))
        {
            _nb1_sprite.SetImage(_nb1_hov);
            if (input.IsMouseButtonDown(Mouse::Left))
                _model->setNbIA(1);
        }
        else
            _nb1_sprite.SetImage(_nb1);        


        if (sourisSurSprite(input.GetMouseX(), input.GetMouseY(), _nb2_sprite))
        {
            _nb2_sprite.SetImage(_nb2_hov);
            if (input.IsMouseButtonDown(Mouse::Left))
                _model->setNbIA(2);
        }
        else
            _nb2_sprite.SetImage(_nb2);


        if (sourisSurSprite(input.GetMouseX(), input.GetMouseY(), _play_sprite))
        {
            _play_sprite.SetImage(_play_hov);
            if (input.IsMouseButtonDown(Mouse::Left))
            {
                if (_model->getLevel() == "Facile")
                {
                    _model->creerIA(50,50);
                    _model->setTemps(15.f);
                }
                else if (_model->getLevel() == "Moyen")
                {
                    _model->creerIA(125,125);
                    _model->setTemps(10.f);
                }
                else
                {
                    _model->creerIA(200, 200);
                    _model->setTemps(5.f);
                }

                _timer_game.Reset();
                _timer.Reset();
                _model->setState(GAME);
            }
        }
        else
            _play_sprite.SetImage(_play);

        if (sourisSurSprite(input.GetMouseX(), input.GetMouseY(), _levelF_sprite))
        {
            _levelF_sprite.SetImage(_levelF_hov);
            if (input.IsMouseButtonDown(Mouse::Left))
                _model->setLevel("Facile");
        }
        else
            _levelF_sprite.SetImage(_levelF);

        if (sourisSurSprite(input.GetMouseX(), input.GetMouseY(), _levelM_sprite))
        {
            _levelM_sprite.SetImage(_levelM_hov);
            if (input.IsMouseButtonDown(Mouse::Left))
                _model->setLevel("Moyen");
        }
        else
            _levelM_sprite.SetImage(_levelM);

        if (sourisSurSprite(input.GetMouseX(), input.GetMouseY(), _levelD_sprite))
        {
            _levelD_sprite.SetImage(_levelD_hov);
            if (input.IsMouseButtonDown(Mouse::Left))
                _model->setLevel("Difficile");
        }
        else
            _levelD_sprite.SetImage(_levelD);


        _window->Draw(_nb2_sprite);
        _window->Draw(_nb1_sprite);
        _window->Draw(_levelF_sprite);
        _window->Draw(_levelM_sprite);
        _window->Draw(_levelD_sprite);
        _window->Draw(_play_sprite);
        _window->Display();

        if (event.Type == Event::Closed)
            _window->Close();
    }
    usleep(2000);
    delete font;    
}

void GameView::dessinMenu(){
    _window->Clear();

    Font * font = new Font();
    font->LoadFromFile("../Font/Zantroke.otf");
    Event event;
    const Input & input = _window->GetInput();

    String title = String("MarioCraft");
    title.SetFont(*font);
    title.SetColor(Color::Black);
    title.SetSize(100);
    title.SetPosition(380, 325);

    while(_window->GetEvent(event))
    {
        _window->Draw(_background_menu_sprite);
        _window->Draw(title);

        if (sourisSurSprite(input.GetMouseX(), input.GetMouseY(), _jouer_sprite))
        {
            _jouer_sprite.SetImage(_jouer2);
            if (input.IsMouseButtonDown(Mouse::Left))
                _model->setState(SELECT);
        }
        else
            _jouer_sprite.SetImage(_jouer);

        if (sourisSurSprite(input.GetMouseX(), input.GetMouseY(), _quitter_sprite))
        {
            _quitter_sprite.SetImage(_quitter2);
            if (input.IsMouseButtonDown(Mouse::Left))
                exit(0);
        }
        else
            _quitter_sprite.SetImage(_quitter);        


        _window->Draw(_quitter_sprite);
        _window->Draw(_jouer_sprite);
        _window->Display();

        if (event.Type == Event::Closed)
            _window->Close();

    }
    usleep(2000);
    delete font;
}

void GameView::dessinJeu(){
    _window->Clear();

    Font * _font = new Font();
    _font->LoadFromFile("../Font/Zantroke.otf");

    //Deplacement de la vue
    if (_window->GetInput().IsKeyDown(Key::Z))
        _vue.Move( 0,-15);

    if (_window->GetInput().IsKeyDown(Key::S))
        _vue.Move( 0, 15);

    if (_window->GetInput().IsKeyDown(Key::Q))
        _vue.Move(-15, 0);

    if (_window->GetInput().IsKeyDown(Key::D))
        _vue.Move( 15, 0);


    _window->Draw(_map_sprite);

    dessinPersonnagesJoueur(*_font);
    dessinPersonnagesIA();

    dessinBatimentsJoueur(*_font);
    dessinBatimentsIA();
    
    dessinComposants(*_font);

    _window->SetView(_window->GetDefaultView());
    dessinInformations(*_font);

    _window->SetView(_vue);
    _window->Display();
    usleep(2000);
    delete _font;
}
RenderWindow * GameView::getWindow()const {
    return _window;
}

void GameView::zoomVue(char c) {
    if (c == '+')
        _vue.Zoom(1.09f);
    else
        _vue.Zoom(0.91f);
}

void GameView::dessinBatimentsJoueur(Font font) {
    for (unsigned int i = 0; i < _model->getJoueur()->listeBatiments().size(); ++i)
    {
        string type = _model->getJoueur()->getBatiment(i)->getTypeElement();
        int vie = _model->getJoueur()->getBatiment(i)->getVieElement();
        int pos_x_elem = _model->getJoueur()->getBatiment(i)->getPosX();
        int pos_y_elem = _model->getJoueur()->getBatiment(i)->getPosY();

        if (_model->getJoueur()->getBatiment(i)->estActif() == true)
        {
            String _indic_vie = String(_model->intToString(vie));
            _indic_vie.SetFont(font);
            _indic_vie.SetColor(Color::Black);
            _indic_vie.SetSize(SIZE_TEXT);  
            _indic_vie.SetPosition(pos_x_elem + 10, pos_y_elem + DIMENSION_SPRITE);

            Shape shape_actif = Shape::Rectangle(pos_x_elem, pos_y_elem,
                                                 pos_x_elem + DIMENSION_SPRITE, pos_y_elem + DIMENSION_SPRITE
                                                 , Color::White, 4, Color::Black);

            shape_actif.EnableFill(false);

            _window->Draw(shape_actif);
            _window->Draw(_indic_vie);
        }

        if (type == "Foyer")
        {
            _foyer_sprite.SetPosition(_model->getJoueur()->getBatiment(i)->getPosX(), _model->getJoueur()->getBatiment(i)->getPosY());
            _window->Draw(_foyer_sprite);
        }
        else
        {
            _caserne_sprite.SetPosition(_model->getJoueur()->getBatiment(i)->getPosX(), _model->getJoueur()->getBatiment(i)->getPosY());
            _window->Draw(_caserne_sprite);
        }
    }
}

void GameView::dessinBatimentsIA() {
    vector<Joueur*> ia = _model->getIAs();

    for (unsigned int i = 0; i < ia.size(); ++i)
    {
        for (unsigned int j = 0; j < ia[i]->listeBatiments().size(); ++j)
        {
            string type = ia[i]->getBatiment(j)->getTypeElement();

            if (type == "Foyer")
            {
                _foyer_IA_sprite.SetPosition(ia[i]->getBatiment(j)->getPosX(), ia[i]->getBatiment(j)->getPosY());
                _window->Draw(_foyer_IA_sprite);
            }
            else
            {
                _caserne_IA_sprite.SetPosition(ia[i]->getBatiment(j)->getPosX(), ia[i]->getBatiment(j)->getPosY());
                _window->Draw(_caserne_IA_sprite);
            }
        }
    }
}

void GameView::dessinPersonnagesJoueur(Font font){
    for (unsigned int i = 0; i < _model->getJoueur()->listePersonnages().size(); ++i)
    {
        string type = _model->getJoueur()->getPersonnage(i)->getTypeElement();
        int vie = _model->getJoueur()->getPersonnage(i)->getVieElement();
        int pos_x_elem = _model->getJoueur()->getPersonnage(i)->getPosX();
        int pos_y_elem = _model->getJoueur()->getPersonnage(i)->getPosY();
        Personnage * per = _model->getJoueur()->getPersonnage(i);

        if (_model->getJoueur()->getPersonnage(i)->estActif() == true)
        {
            String _indic_vie = String(_model->intToString(vie));
            Shape shape_actif;
            _indic_vie.SetFont(font);
            _indic_vie.SetColor(Color::Black);
            _indic_vie.SetSize(SIZE_TEXT);
            _indic_vie.SetPosition(pos_x_elem + 10, pos_y_elem + DIMENSION_SPRITE);

            if (_model->getJoueur()->getPersonnage(i)->estEnCollision() == true)
            {
                shape_actif = Shape::Rectangle(pos_x_elem, pos_y_elem,
                                                 pos_x_elem + DIMENSION_SPRITE, pos_y_elem + DIMENSION_SPRITE
                                                 , Color::White, 4, Color::Red);
            }
            else
            {
                shape_actif = Shape::Rectangle(pos_x_elem, pos_y_elem,
                                                     pos_x_elem + DIMENSION_SPRITE, pos_y_elem + DIMENSION_SPRITE
                                                     , Color::White, 4, Color::Black);
            }

            shape_actif.EnableFill(false);
            _window->Draw(shape_actif);
            _window->Draw(_indic_vie);
        }

        if (type == "Artisan")
        {
            _artisan_sprite.Resize(DIMENSION_SPRITE, DIMENSION_SPRITE);
            _artisan_sprite.SetPosition(_model->getJoueur()->getPersonnage(i)->getPosX(), _model->getJoueur()->getPersonnage(i)->getPosY());
            _window->Draw(toad());
        }
        else
        {
            Combattant * c = dynamic_cast<Combattant*>(per);
            Shape shape_cible;
            if (c != NULL)
            {
                if (c->getTargetPerso() != NULL)
                {
                    int x = c->getTargetPerso()->getPosX();
                    int y = c->getTargetPerso()->getPosY();
                    shape_cible = Shape::Rectangle(x, y,
                                                     x + DIMENSION_SPRITE, y + DIMENSION_SPRITE
                                                     , Color::White, 4, Color::Red);
                }
            }
            shape_cible.EnableFill(false);
            _window->Draw(shape_cible);
            _combattant_sprite.Resize(DIMENSION_SPRITE, DIMENSION_SPRITE);
            _combattant_sprite.SetPosition(_model->getJoueur()->getPersonnage(i)->getPosX(), _model->getJoueur()->getPersonnage(i)->getPosY());
            _window->Draw(mario());
        }
    }
}

void GameView::dessinPersonnagesIA()
{
    vector<Joueur*> ia = _model->getIAs();
    for (unsigned int i = 0; i < ia.size(); ++i)
    {
        for (unsigned int j = 0; j < ia[i]->listePersonnages().size(); ++j)
        {
            string type = ia[i]->getPersonnage(j)->getTypeElement();

            if (type == "Artisan")
            {
                _artisan_IA_sprite.Resize(DIMENSION_SPRITE, DIMENSION_SPRITE);
                _artisan_IA_sprite.SetPosition(ia[i]->getPersonnage(j)->getPosX(), ia[i]->getPersonnage(j)->getPosY());
                _window->Draw(toad_IA());
            }
            else
            {
                _combattant_IA_sprite.Resize(DIMENSION_SPRITE, DIMENSION_SPRITE);
                _combattant_IA_sprite.SetPosition(ia[i]->getPersonnage(j)->getPosX(), ia[i]->getPersonnage(j)->getPosY());
                _window->Draw(goomba_IA());
            }
        }
    }
}

void GameView::dessinComposants(Font font){
    for (unsigned int i = 0; i < _model->listeComposants().size(); ++i)
    {
        string type = _model->getComposant(i)->getTypeComposant();
        int vie = _model->getComposant(i)->getVieComposant();
        int pos_x_elem = _model->getComposant(i)->getPosX();
        int pos_y_elem = _model->getComposant(i)->getPosY();

        if (_model->getComposant(i)->estCible() == true)
        {
            Shape shape_cible = Shape::Rectangle(pos_x_elem, pos_y_elem,
                                                 pos_x_elem + DIMENSION_SPRITE, pos_y_elem + DIMENSION_SPRITE
                                                 , Color::White, 4, Color::Yellow);

            String _indic_vie = String(_model->intToString(vie));
            _indic_vie.SetFont(font);
            _indic_vie.SetColor(Color::Yellow);
            _indic_vie.SetSize(SIZE_TEXT);
            _indic_vie.SetPosition(pos_x_elem + 10, pos_y_elem + DIMENSION_SPRITE);

            shape_cible.EnableFill(false);

            _window->Draw(shape_cible);
            _window->Draw(_indic_vie);
        }
        if (type == "Bois")
        {
            _bois_sprite.Resize(DIMENSION_SPRITE, DIMENSION_SPRITE);
            _bois_sprite.SetPosition(_model->getComposant(i)->getPosX(), _model->getComposant(i)->getPosY());
            _window->Draw(_bois_sprite);
        }
        else
        {
            _nourriture_sprite.Resize(DIMENSION_SPRITE, DIMENSION_SPRITE);
            _nourriture_sprite.SetPosition(_model->getComposant(i)->getPosX(), _model->getComposant(i)->getPosY());
            _window->Draw(_nourriture_sprite);
        }
    }
}

void GameView::dessinInformations(Font font){
    String _indic_nourriture = String(_model->intToString(_model->getJoueur()->getTotalNourriture()));
    _indic_nourriture.SetFont(font);
    _indic_nourriture.SetColor(Color::White);
    _indic_nourriture.SetSize(SIZE_TEXT);
    _indic_nourriture.SetPosition(_window->GetWidth()*3/5, 20);

    String _indic_artisans = String(_model->intToString(_model->getJoueur()->getTotalArtisans()));
    _indic_artisans.SetFont(font);
    _indic_artisans.SetColor(Color::White);
    _indic_artisans.SetSize(SIZE_TEXT);
    _indic_artisans.SetPosition(_window->GetWidth()/5, 20);

    String _indic_combattants = String(_model->intToString(_model->getJoueur()->getTotalCombattants()));
    _indic_combattants.SetFont(font);
    _indic_combattants.SetColor(Color::White);
    _indic_combattants.SetSize(SIZE_TEXT);
    _indic_combattants.SetPosition((_window->GetWidth()*2)/5, 20);    

    String _indic_bois = String(_model->intToString(_model->getJoueur()->getTotalBois()));
    _indic_bois.SetFont(font);
    _indic_bois.SetColor(Color::White);
    _indic_bois.SetSize(SIZE_TEXT);
    _indic_bois.SetPosition((_window->GetWidth()*4)/5, 20);

    String _time = String(time());
    _time.SetFont(font);
    _time.SetColor(Color::White);
    _time.SetSize(SIZE_TEXT);
    _time.SetPosition(10,20);

    _window->Draw(Shape::Rectangle(0, 0, _window->GetWidth(), 50, Color::Black));

    _nourriture_sprite.Resize(40,40);
    _nourriture_sprite.SetPosition(_window->GetWidth()*3/5 - DIMENSION_SPRITE, 7);

    _bois_sprite.Resize(40,40);
    _bois_sprite.SetPosition((_window->GetWidth()*4)/5 - DIMENSION_SPRITE,7);

    _artisan_sprite.Resize(40,40);
    _artisan_sprite.SetPosition((_window->GetWidth())/5 - DIMENSION_SPRITE,7);

    _combattant_sprite.Resize(40,40);
    _combattant_sprite.SetPosition((_window->GetWidth())*2/5 - DIMENSION_SPRITE,7);

    _window->Draw(_nourriture_sprite);
    _window->Draw(_bois_sprite);
    _window->Draw(toad());
    _window->Draw(mario());
    _window->Draw(_indic_nourriture);
    _window->Draw(_indic_bois);
    _window->Draw(_indic_artisans);
    _window->Draw(_indic_combattants);
    _window->Draw(_time);
}

void GameView::chargementImages(){
    if (!_map.LoadFromFile("../Pictures/map.png")
    or  !_combattant.LoadFromFile("../Pictures/mario.png")
    or  !_foyer.LoadFromFile("../Pictures/foyer.png")
    or  !_caserne.LoadFromFile("../Pictures/caserne.jpg")
    or  !_bois.LoadFromFile("../Pictures/bois.png")
    or  !_nourriture.LoadFromFile("../Pictures/nourriture.png")
    or  !_artisan.LoadFromFile("../Pictures/artisan2.png")
    or  !_jouer.LoadFromFile("../Pictures/jouer.png")
    or  !_jouer2.LoadFromFile("../Pictures/jouer(2).png")
    or  !_foyer_IA.LoadFromFile("../Pictures/foyer(IA).png")
    or  !_caserne_IA.LoadFromFile("../Pictures/caserne(IA).png")
    or  !_artisan_IA.LoadFromFile("../Pictures/artisan2(IA).png")
    or  !_combattant_IA.LoadFromFile("../Pictures/goomba.png")
    or  !_background_menu.LoadFromFile("../Pictures/background_menu.jpg")
    or  !_quitter.LoadFromFile("../Pictures/quitter.png")
    or  !_quitter2.LoadFromFile("../Pictures/quitter(2).png")
    or  !_nb1.LoadFromFile("../Pictures/1.png")
    or  !_nb1_hov.LoadFromFile("../Pictures/1(2).png")
    or  !_nb2.LoadFromFile("../Pictures/2.png")
    or  !_nb2_hov.LoadFromFile("../Pictures/2(2).png")
    or  !_play.LoadFromFile("../Pictures/parti.png")
    or  !_play_hov.LoadFromFile("../Pictures/parti(2).png")
    or  !_levelF.LoadFromFile("../Pictures/facile.png")
    or  !_levelF_hov.LoadFromFile("../Pictures/facile(2).png")
    or  !_levelM.LoadFromFile("../Pictures/moyen.png")
    or  !_levelM_hov.LoadFromFile("../Pictures/moyen(2).png")
    or  !_levelD.LoadFromFile("../Pictures/difficile.png")
    or  !_levelD_hov.LoadFromFile("../Pictures/difficile(2).png"))
    {
        cout << "Erreur durant le chargement des images" << endl;
        exit(0);
    }

    else
    {
        _background_menu_sprite = Sprite(_background_menu);
        _background_menu_sprite.Resize(_window->GetWidth(), _window->GetHeight());
        _background_menu_sprite.SetPosition(0,0);

        _jouer_sprite = Sprite(_jouer);
        _jouer_sprite.Resize(LARGEUR_BOUTON, HAUTEUR_BOUTON);
        _jouer_sprite.SetPosition(100, 500);

        _quitter_sprite = Sprite(_quitter);
        _quitter_sprite.Resize(LARGEUR_BOUTON, HAUTEUR_BOUTON);
        _quitter_sprite.SetPosition(1000, 500);

        _levelF_sprite = Sprite(_levelF);
        _levelF_sprite.Resize(LARGEUR_BOUTON, HAUTEUR_BOUTON);
        _levelF_sprite.SetPosition(1000, 425);

        _levelM_sprite = Sprite(_levelM);
        _levelM_sprite.Resize(LARGEUR_BOUTON, HAUTEUR_BOUTON);
        _levelM_sprite.SetPosition(1000, 525);

        _levelD_sprite = Sprite(_levelD);
        _levelD_sprite.Resize(LARGEUR_BOUTON, HAUTEUR_BOUTON);
        _levelD_sprite.SetPosition(1000, 625);

        _nb1_sprite = Sprite(_nb1);
        _nb1_sprite.Resize(LARGEUR_BOUTON, HAUTEUR_BOUTON);
        _nb1_sprite.SetPosition(100,450);

        _nb2_sprite = Sprite(_nb2);
        _nb2_sprite.Resize(LARGEUR_BOUTON, HAUTEUR_BOUTON);
        _nb2_sprite.SetPosition(100,550);

        _play_sprite = Sprite(_play);
        _play_sprite.Resize(LARGEUR_BOUTON, HAUTEUR_BOUTON);
        _play_sprite.SetPosition(500, 350);

        _map_sprite = Sprite (_map);
        _map_sprite.Resize(_window->GetWidth()*4, _window->GetHeight()*4);
        _map_sprite.SetPosition(0,0);

        _combattant_sprite = Sprite (_combattant);
        _combattant_sprite.SetSubRect(IntRect(29,0, 56, 43));

        _artisan_sprite = Sprite(_artisan);
        _artisan_sprite.SetSubRect(IntRect(0,19, 13, 19*2));
        _artisan.CreateMaskFromColor(Color(0,255,0));

        _artisan_IA_sprite = Sprite(_artisan_IA);
        _artisan_IA_sprite.SetSubRect(IntRect(0,19, 13, 19*2));
        _artisan_IA.CreateMaskFromColor(Color(0,255,0));

        _combattant_IA_sprite = Sprite(_combattant_IA);
        _combattant_IA_sprite.SetSubRect(IntRect(0,190,13,19*2));

        _foyer_sprite = Sprite (_foyer);
        _foyer_sprite.Resize(DIMENSION_SPRITE, DIMENSION_SPRITE);
        _foyer.CreateMaskFromColor(Color(0, 255, 0));

        _foyer_IA_sprite = Sprite (_foyer_IA);
        _foyer_IA_sprite.Resize(DIMENSION_SPRITE, DIMENSION_SPRITE);
        _foyer_IA.CreateMaskFromColor(Color(0, 255, 0));

        _caserne_IA_sprite = Sprite (_caserne_IA);
        _caserne_IA_sprite.Resize(DIMENSION_SPRITE, DIMENSION_SPRITE);
        _caserne_IA.CreateMaskFromColor(Color(0, 255, 0));

        _caserne_sprite = Sprite (_caserne);
        _caserne_sprite.Resize(DIMENSION_SPRITE, DIMENSION_SPRITE);
        _caserne.CreateMaskFromColor(Color(0,255,0));

        _bois_sprite = Sprite(_bois);
        _bois.CreateMaskFromColor(Color(0,255,0));

        _nourriture_sprite = Sprite(_nourriture);
        _nourriture.CreateMaskFromColor(Color(0,255,0));
    }
}
