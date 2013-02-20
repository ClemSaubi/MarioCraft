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

    if     (!_map.LoadFromFile("../Pictures/map.png")
            or  !_combattant.LoadFromFile("../Pictures/mario4.png")
            or  !_foyer.LoadFromFile("../Pictures/foyer.png")
            or  !_caserne.LoadFromFile("../Pictures/caserne.jpg")
            or  !_bois.LoadFromFile("../Pictures/bois.png")
            or  !_nourriture.LoadFromFile("../Pictures/nourriture.png")
            or  !_artisan.LoadFromFile("../Pictures/artisan.png"))
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

        _artisan_sprite = Sprite(_artisan);
        _artisan_sprite.SetSubRect(IntRect(0,19, 13, 19*2));
        _artisan_sprite.Resize(DIMENSION_SPRITE, DIMENSION_SPRITE);
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
        _nourriture_sprite.Resize(DIMENSION_SPRITE, DIMENSION_SPRITE);
        _nourriture.CreateMaskFromColor(Color(0,255,0));
    }
}

GameView::~GameView()
{
    if (_window != NULL)
    {
        cout << "GameView::Destructeur" << endl;
        delete _window;
    }
}

void GameView::Display()
{

    string type = "";
    int vie = 0;
    int nourriture = _model->getQuantiteNourriture();
    int bois = _model->getQuantiteBois();
    int artisans = _model->getCompteurArtisans();
    int pos_x_elem = 0;
    int pos_y_elem = 0;

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

    String _indic_nourriture = String(_model->intToString(nourriture));
        _indic_nourriture.SetFont(*_font);
        _indic_nourriture.SetColor(Color::White);
        _indic_nourriture.SetSize(SIZE_TEXT);
        _indic_nourriture.SetPosition(_window->GetWidth()*3/5, 20);
    
    String _indic_artisans = String(_model->intToString(artisans));
        _indic_artisans.SetFont(*_font);
        _indic_artisans.SetColor(Color::White);
        _indic_artisans.SetSize(SIZE_TEXT);
        _indic_artisans.SetPosition(_window->GetWidth()/5, 20);

    String _indic_bois = String(_model->intToString(bois));
        _indic_bois.SetFont(*_font);
        _indic_bois.SetColor(Color::White);
        _indic_bois.SetSize(SIZE_TEXT);
        _indic_bois.SetPosition((_window->GetWidth()*4)/5, 20);


    for (int i = 0; i < _model->getListElementSize(); ++i)
    {
        type = _model->getElement(i)->getType();
        vie = _model->getElement(i)->getVie();
        pos_x_elem = _model->getElement(i)->getPosX();
        pos_y_elem = _model->getElement(i)->getPosY();

        if (_model->getElement(i)->estActif() == true)
        {
            String _indic_vie = String(_model->intToString(vie));
                _indic_vie.SetFont(*_font);
                _indic_vie.SetColor(Color::Black);
                _indic_vie.SetSize(SIZE_TEXT);
                _indic_vie.SetPosition(pos_x_elem + 10, pos_y_elem + DIMENSION_SPRITE);    

            Shape shape_actif = Shape::Rectangle(pos_x_elem, pos_y_elem,
                                pos_x_elem + DIMENSION_SPRITE, pos_y_elem + DIMENSION_SPRITE
                                , Color::White, 2, Color::Black);

            shape_actif.EnableFill(false);

            _window->Draw(shape_actif);
            _window->Draw(_indic_vie);
        }

        if (_model->getElement(i)->estCible() == true)
        {
            if (_model->getElement(i)->getType() == "Bois")
            {
                Shape shape_cible = Shape::Rectangle(pos_x_elem, pos_y_elem,
                                                    pos_x_elem + DIMENSION_ARBRE, pos_y_elem + DIMENSION_ARBRE
                                                    , Color::White, 2, Color::Yellow);

                String _indic_vie = String(_model->intToString(vie));
                    _indic_vie.SetFont(*_font);
                    _indic_vie.SetColor(Color::Yellow);
                    _indic_vie.SetSize(SIZE_TEXT);
                    _indic_vie.SetPosition(pos_x_elem + 50, pos_y_elem + DIMENSION_ARBRE); 
                
                shape_cible.EnableFill(false);

                _window->Draw(shape_cible);
                _window->Draw(_indic_vie);
            }
            else
            {
                Shape shape_cible = Shape::Rectangle(pos_x_elem, pos_y_elem,
                                                    pos_x_elem + DIMENSION_SPRITE, pos_y_elem + DIMENSION_SPRITE
                                                    , Color::White, 2, Color::Yellow);

                String _indic_vie = String(_model->intToString(vie));
                    _indic_vie.SetFont(*_font);
                    _indic_vie.SetColor(Color::Yellow);
                    _indic_vie.SetSize(SIZE_TEXT);
                    _indic_vie.SetPosition(pos_x_elem + 10, pos_y_elem + DIMENSION_SPRITE); 
                
                shape_cible.EnableFill(false);

                _window->Draw(shape_cible);
                _window->Draw(_indic_vie);
            }
        }
        if (type == "Foyer")
        {
            _foyer_sprite.SetPosition(_model->getElement(i)->getPosX(), _model->getElement(i)->getPosY());
            _window->Draw(_foyer_sprite);
        }
        if (type == "Caserne")
        {
            _caserne_sprite.SetPosition(_model->getElement(i)->getPosX(), _model->getElement(i)->getPosY());
            _window->Draw(_caserne_sprite);
        }
        if (type == "Bois")
        {
            _bois_sprite.Resize(DIMENSION_ARBRE, DIMENSION_ARBRE);
            _bois_sprite.SetPosition(_model->getElement(i)->getPosX(), _model->getElement(i)->getPosY());
            _window->Draw(_bois_sprite);
        }
        if (type == "Nourriture")
        {
            _nourriture_sprite.SetPosition(_model->getElement(i)->getPosX(), _model->getElement(i)->getPosY());
            _window->Draw(_nourriture_sprite);
        }
        if (type == "Artisan")
        {
            _artisan_sprite.SetPosition(_model->getElement(i)->getPosX(), _model->getElement(i)->getPosY());
            _window->Draw(_artisan_sprite);
        }
    }

    _window->SetView(_window->GetDefaultView());

    _window->Draw(Shape::Rectangle(0, 0, _window->GetWidth(), DIMENSION_SPRITE, Color::Black));

    _nourriture_sprite.Resize(40,40);
    _nourriture_sprite.SetPosition(_window->GetWidth()*3/5 - DIMENSION_SPRITE, 7);

    _bois_sprite.Resize(40,40);
    _bois_sprite.SetPosition((_window->GetWidth()*4)/5 - DIMENSION_SPRITE,7);

    _artisan_sprite.Resize(40,40);
    _artisan_sprite.SetPosition((_window->GetWidth())/5 - DIMENSION_SPRITE,7);

    _window->Draw(_nourriture_sprite);
    _window->Draw(_bois_sprite);
    _window->Draw(_artisan_sprite);
    _window->Draw(_indic_nourriture);
    _window->Draw(_indic_bois);
    _window->Draw(_indic_artisans);

    _window->SetView(_vue);
    _window->Display();
    usleep(2000);
    delete _font;
}

RenderWindow * GameView::getWindow()const {
    return _window;
}

void GameView::zoomVue(char c){
    if (c == '+')
        _vue.Zoom(1.09f);
    else
        _vue.Zoom(0.91f);
}
