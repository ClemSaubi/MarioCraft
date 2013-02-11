#include "Headers/Controller.h"
#include "Headers/Constantes.h"

using namespace std;
using namespace sf;

Controller::Controller(GameModel * model, GameView * view)
{
    cout << "Controller::Contructeur" << endl;
    _model = model;
    _view = view;
}

Controller::~Controller()
{
    cout << "Controller::Destructeur" << endl;
}

bool Controller::sourisSurElement(const Input & input, Element * e)const {
    if (input.GetMouseX() < e->getPosX() - DIMENSION_SPRITE)
        return false;

    else if (input.GetMouseX() > e->getPosX() + DIMENSION_SPRITE)
        return false;

    else if (input.GetMouseY() < e->getPosY() - DIMENSION_SPRITE)
        return false;

    else if (input.GetMouseY() > e->getPosY() + DIMENSION_SPRITE)
        return false;

    return true;
}

bool Controller::treatEvents() {

    bool result = false;
    unsigned int mouse_x ;
    unsigned int mouse_y ;
    const Input & input = _view->getWindow()->GetInput();
    Mouse::Button button;

    if(_view->getWindow()->IsOpened())
    {
        result = true;

        while (_view->getWindow()->GetEvent(_event)) {

            //Mise a jour coordonnees souris
            mouse_x = input.GetMouseX();
            mouse_y = input.GetMouseY();
            button = _event.MouseButton.Button;

            //Fermer l'application
            if (_event.Type == Event::Closed or input.IsKeyDown(Key::Escape))
            {
                _view->getWindow()->Close();
                result = false;
            }

            //Activation d'un élément apres clic gauche dessus
            if (_event.Type == Event::MouseButtonReleased and button == Mouse::Left)
            {
                if (_model->listeVide() == false)
                {
                    Element * e = _model->searchElement(mouse_x, mouse_y);

                    if (e != NULL)
                    {
                        if (sourisSurElement(input, e) == true 
                            and (e->getType() != "Bois" and e->getType() != "Nourriture" and e->getType() != "Obstacle"))
                        {
                            _model->elementsDesactives();
                            e->setActif(true);
                        }
                    }
                    else
                        _model->elementsDesactives();
                }
            }

            //Construction d'unites
            if (_event.Type == Event::MouseButtonReleased and button == Mouse::Right)
            {
                Element * f = _model->searchFoyer();
                Element * e = _model->searchElementActif();
                vector<Element*> artisans = _model->unitesActives("Artisan");

                if (f != NULL)
                {
                    if (f->estActif() == true and sourisSurElement(input, f) == true)
                        _model->construireElement(f->getPosX(), f->getPosY(), "Artisan");
                }

                //Deplacement d'une unite
                if (e != NULL)
                {
                    if (e->estActif() == true)
                    {
                        if (e->getType() == "Artisan" or e->getType() == "Combattant")
                        {
                            e->setPosX(mouse_x);
                            e->setPosY(mouse_y);
                        }
                    }
                }
                if (artisans.empty() == false)
                {
                    for (unsigned int i = 0; i < artisans.size(); ++i)
                    {
                        if (i%2 == 0)
                        {
                            artisans[i]->setPosX(mouse_x + i*DIMENSION_PERSO);
                            artisans[i]->setPosY(mouse_y);
                        }
                        else
                        {
                            artisans[i]->setPosX(mouse_x);
                            artisans[i]->setPosY(mouse_y + i*DIMENSION_PERSO);
                        }
                    }
                }
            }

            //Activer tous les Artisans
            if (input.IsKeyDown(Key::A))
            {
                _model->elementsDesactives();
                _model->activerToutesUnites("Artisan");
            }

            //Construction d'un Batiment apres appui sur F
            if (input.IsKeyDown(Key::F))
            {
                if (_model->foyerConstruit() == false)
                    _model->construireElement(mouse_x-(DIMENSION_SPRITE/2), mouse_y-(DIMENSION_SPRITE/2), "Foyer");

                else
                {
                    Element * e = _model->searchElement(mouse_x, mouse_y);

                    if (e != NULL and sourisSurElement(input, e) == true)
                        cout << "..." << endl;

                    else
                        _model->construireElement(mouse_x-(DIMENSION_SPRITE/2), mouse_y-(DIMENSION_SPRITE/2), "Caserne");
                }
            }

            //Creation du bois sur la map
            if (input.IsKeyDown(Key::B))
            {
                Element * e = _model->searchElement(mouse_x, mouse_y);

                if (e != NULL and sourisSurElement(input, e) == true)
                    cout << "..." << endl;

                else if (_model->getCompteurBois() != 0)
                    _model->construireElement(mouse_x-(DIMENSION_SPRITE/2), mouse_y-(DIMENSION_SPRITE/2), "Bois");
            }

            //Creation de la nourriture sur la map
            if (input.IsKeyDown(Key::N))
            {
                Element * e = _model->searchElement(mouse_x, mouse_y);

                if (e != NULL and sourisSurElement(input, e) == true)
                    cout << "..." << endl;

                else if (_model->getCompteurNourriture() != 0)
                    _model->construireElement(mouse_x-(DIMENSION_SPRITE/2), mouse_y-(DIMENSION_SPRITE/2), "Nourriture");
            }
        }
    }
    return result;
}

