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

void * GameView::thread_nextStep(void* targs)
{
    GameModel * model = (GameModel *) targs;

    do{
        model->nextStep();
        sleep(30);
    }while( model->getState() == GAME );

   pthread_exit(0);
}

Sprite GameView::toad() {
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

Sprite GameView::mario() {
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

void GameView::Display()
{
    if (_model->getState() == GAME)
    {
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

        dessinPersonnages(*_font);
        dessinBatiments(*_font);
        dessinComposants(*_font);

        _window->SetView(_window->GetDefaultView());
        dessinInformations(*_font);

        _window->SetView(_vue);
        _window->Display();
        usleep(2000);
        delete _font;
    }
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

void GameView::dessinBatiments(Font font) {
    for (int i = 0; i < _model->getJoueurActif()->getListBatimentSize(); ++i)
    {
        string type = _model->getJoueurActif()->getBatiment(i)->getTypeElement();
        int vie = _model->getJoueurActif()->getBatiment(i)->getVieElement();
        int pos_x_elem = _model->getJoueurActif()->getBatiment(i)->getPosX();
        int pos_y_elem = _model->getJoueurActif()->getBatiment(i)->getPosY();

        if (_model->getJoueurActif()->getBatiment(i)->estActif() == true)
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
            _foyer_sprite.SetPosition(_model->getJoueurActif()->getBatiment(i)->getPosX(), _model->getJoueurActif()->getBatiment(i)->getPosY());
            _window->Draw(_foyer_sprite);
        }
        else
        {
            _caserne_sprite.SetPosition(_model->getJoueurActif()->getBatiment(i)->getPosX(), _model->getJoueurActif()->getBatiment(i)->getPosY());
            _window->Draw(_caserne_sprite);
        }
    }
}

void GameView::dessinPersonnages(Font font){
    for (int i = 0; i < _model->getJoueurActif()->getListPersonnageSize(); ++i)
    {
        string type = _model->getJoueurActif()->getPersonnage(i)->getTypeElement();
        int vie = _model->getJoueurActif()->getPersonnage(i)->getVieElement();
        int pos_x_elem = _model->getJoueurActif()->getPersonnage(i)->getPosX();
        int pos_y_elem = _model->getJoueurActif()->getPersonnage(i)->getPosY();

        if (_model->getJoueurActif()->getPersonnage(i)->estActif() == true)
        {
            String _indic_vie = String(_model->intToString(vie));
            Shape shape_actif;
            _indic_vie.SetFont(font);
            _indic_vie.SetColor(Color::Black);
            _indic_vie.SetSize(SIZE_TEXT);
            _indic_vie.SetPosition(pos_x_elem + 10, pos_y_elem + DIMENSION_SPRITE);

            if (_model->getJoueurActif()->getPersonnage(i)->estEnCollision() == true)
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
            _artisan_sprite.SetPosition(_model->getJoueurActif()->getPersonnage(i)->getPosX(), _model->getJoueurActif()->getPersonnage(i)->getPosY());
            _window->Draw(toad());
        }
        else
        {
            _combattant_sprite.Resize(DIMENSION_SPRITE, DIMENSION_SPRITE);
            _combattant_sprite.SetPosition(_model->getJoueurActif()->getPersonnage(i)->getPosX(), _model->getJoueurActif()->getPersonnage(i)->getPosY());
            //_window->Draw(_combattant_sprite);
            _window->Draw(mario());
        }
    }
}

void GameView::dessinComposants(Font font){
    for (int i = 0; i < _model->getListComposantSize(); ++i)
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
    String _indic_nourriture = String(_model->intToString(_model->getJoueurActif()->getTotalNourriture()));
    _indic_nourriture.SetFont(font);
    _indic_nourriture.SetColor(Color::White);
    _indic_nourriture.SetSize(SIZE_TEXT);
    _indic_nourriture.SetPosition(_window->GetWidth()*3/5, 20);

    String _indic_artisans = String(_model->intToString(_model->getJoueurActif()->getTotalArtisans()));
    _indic_artisans.SetFont(font);
    _indic_artisans.SetColor(Color::White);
    _indic_artisans.SetSize(SIZE_TEXT);
    _indic_artisans.SetPosition(_window->GetWidth()/5, 20);

    String _indic_combattants = String(_model->intToString(_model->getJoueurActif()->getTotalCombattants()));
    _indic_combattants.SetFont(font);
    _indic_combattants.SetColor(Color::White);
    _indic_combattants.SetSize(SIZE_TEXT);
    _indic_combattants.SetPosition((_window->GetWidth()*2)/5, 20);    

    String _indic_bois = String(_model->intToString(_model->getJoueurActif()->getTotalBois()));
    _indic_bois.SetFont(font);
    _indic_bois.SetColor(Color::White);
    _indic_bois.SetSize(SIZE_TEXT);
    _indic_bois.SetPosition((_window->GetWidth()*4)/5, 20);

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
}

void GameView::chargementImages(){
    if (!_map.LoadFromFile("../Pictures/map.png")
    or  !_combattant.LoadFromFile("../Pictures/mario.png")
    or  !_foyer.LoadFromFile("../Pictures/foyer.png")
    or  !_caserne.LoadFromFile("../Pictures/caserne.jpg")
    or  !_bois.LoadFromFile("../Pictures/bois.png")
    or  !_nourriture.LoadFromFile("../Pictures/nourriture.png")
    or  !_artisan.LoadFromFile("../Pictures/artisan2.png"))
    {
        cout << "Erreur durant le chargement des images" << endl;
        exit(1);
    }

    else
    {
        _map_sprite = Sprite (_map);
        _map_sprite.Resize(_window->GetWidth()*4, _window->GetHeight()*4);
        _map_sprite.SetPosition(0,0);

        _combattant_sprite = Sprite (_combattant);
        _combattant_sprite.SetSubRect(IntRect(29,0, 56, 43));

        _artisan_sprite = Sprite(_artisan);
        _artisan_sprite.SetSubRect(IntRect(0,19, 13, 19*2));
        _artisan.CreateMaskFromColor(Color(0,255,0));

        _foyer_sprite = Sprite (_foyer);
        _foyer_sprite.Resize(DIMENSION_SPRITE, DIMENSION_SPRITE);
        _foyer.CreateMaskFromColor(Color(0, 255, 0));

        _caserne_sprite = Sprite (_caserne);
        _caserne_sprite.Resize(DIMENSION_SPRITE, DIMENSION_SPRITE);
        _caserne.CreateMaskFromColor(Color(0,255,0));

        _bois_sprite = Sprite(_bois);
        _bois.CreateMaskFromColor(Color(0,255,0));

        _nourriture_sprite = Sprite(_nourriture);
        _nourriture.CreateMaskFromColor(Color(0,255,0));
    }
}
