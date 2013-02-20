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

bool Controller::sourisSurElement(float x, float y, Element * e)const {
    if (x < e->getPosX())
        return false;

    if (x > e->getPosX() + DIMENSION_SPRITE)
        return false;

    if (y < e->getPosY())
        return false;

    if (y > e->getPosY() + DIMENSION_SPRITE)
        return false;

    return true;
}

bool Controller::treatEvents() {

    bool result = false;
    const Input & input = _view->getWindow()->GetInput();
    Mouse::Button button;

    if(_view->getWindow()->IsOpened())
    {
        result = true;

        while (_view->getWindow()->GetEvent(_event)) {

            //Mise a jour coordonnees souris
            Vector2f MousePos = _view->getWindow()->ConvertCoords(input.GetMouseX(), input.GetMouseY());
            button = _event.MouseButton.Button;

            //Fermer l'application
            if (_event.Type == Event::Closed)
            {
                _view->getWindow()->Close();
                result = false;
            }

            //Zoom
            if (_event.Type == Event::MouseWheelMoved)
            {
                if (_event.MouseWheel.Delta < 0)
                    _view->zoomVue('-');
                else
                    _view->zoomVue('+');
            }

            if (_event.Type == Event::MouseButtonReleased and button == Mouse::Left)
            {
                if (_model->getJoueur1()->listeVide() == false)
                {
                    Element * e = _model->getJoueur1()->searchElement(MousePos.x, MousePos.y);

                    if (e != NULL)
                    {
                        if (sourisSurElement(MousePos.x, MousePos.y, e) == true)
                        {
                            //Activation d'un élément apres clic gauche dessus
                            if(e->getType() != "Bois" and e->getType() != "Nourriture" and e->getType() != "Obstacle")
                            {
                                _model->getJoueur1()->elementsDesactives();
                                e->setActif(true);
                            }
                            //Cibler Composant
                            else
                            {
                                _model->getJoueur1()->deciblerElement();
                                e->setCible(true);
                            }
                        }
                    }
                    else
                    {
                        _model->getJoueur1()->elementsDesactives();
                        _model->getJoueur1()->deciblerElement();
                    }
                }
            }

            //Construction d'unites
            if (_event.Type == Event::MouseButtonReleased and button == Mouse::Right)
            {
                Element * f = _model->getJoueur1()->searchFoyer();

                if (f != NULL)
                {
                    if (f->estActif() == true and sourisSurElement(MousePos.x, MousePos.y, f) == true)
                        _model->getJoueur1()->construireElement(f->getPosX(), f->getPosY() + DIMENSION_PERSO, "Artisan");
                }

                //Deplacement d'une unite
                Element * e = _model->getJoueur1()->searchElementActif();

                if (e != NULL)
                {
                    if (e->estActif() == true)
                    {
                        if (e->getType() == "Artisan" or e->getType() == "Combattant")
                        {
                            e->setDestX(MousePos.x - DIMENSION_PERSO/2);
                            e->setDestY(MousePos.y - DIMENSION_PERSO/2);
                        }
                    }
                }
                
                //Deplacer tous les artisans
                vector<Element*> artisans = _model->getJoueur1()->unitesActives("Artisan");
                
                if (artisans.empty() == false)
                {
                    for (unsigned int i = 0; i < artisans.size(); ++i)
                    {
                        if (i%2 == 0)
                        {
                            artisans[i]->setDestX(MousePos.x - DIMENSION_PERSO/2 + i*DIMENSION_PERSO);
                            artisans[i]->setDestY(MousePos.y - DIMENSION_PERSO/2);
                        }
                        else
                        {
                            artisans[i]->setDestX(MousePos.x - DIMENSION_PERSO/2 + (i-1)*DIMENSION_PERSO);
                            artisans[i]->setDestY(MousePos.y + DIMENSION_PERSO*3/2);
                        }
                    }
                }          
            }

            //Entrees claviers
            if (_event.Type == Event::KeyReleased)
            {
                Element * e = _model->getJoueur1()->searchElement(MousePos.x, MousePos.y);

                switch (_event.Key.Code)
                {
                    //Activer tous les Artisans
                    case Key::A : 
                    {
                        _model->getJoueur1()->elementsDesactives();
                        _model->getJoueur1()->activerToutesUnites("Artisan");
                    };break;

                    //Construction d'un Batiment apres appui sur F
                    case Key::F : 
                    {
                        if (_model->getJoueur1()->foyerConstruit() == false)
                        {
                            if (e != NULL)
                            {
                                if (sourisSurElement(MousePos.x, MousePos.y, e) == false)
                                    _model->getJoueur1()->construireElement(MousePos.x-(DIMENSION_SPRITE/2), MousePos.y-(DIMENSION_SPRITE/2), "Foyer");

                                else
                                    cout << "Element trop proche !" << endl;
                            }
                            else
                                _model->getJoueur1()->construireElement(MousePos.x-(DIMENSION_SPRITE/2), MousePos.y-(DIMENSION_SPRITE/2), "Foyer");                                
                        }
                        else
                            cout << "Foyer deja bati" << endl;
                    };break;

                    //Creation du bois sur la map
                    case Key::B : 
                    {
                        if (e != NULL)
                        {
                            if (sourisSurElement(MousePos.x, MousePos.y, e) == false)
                                _model->getJoueur1()->construireElement(MousePos.x-(DIMENSION_SPRITE/2), MousePos.y-(DIMENSION_SPRITE/2), "Bois");

                            else
                                cout << "Element trop proche !" << endl;
                        }
                        else
                            _model->getJoueur1()->construireElement(MousePos.x-(DIMENSION_SPRITE/2), MousePos.y-(DIMENSION_SPRITE/2), "Bois");   
                    }
                    break;

                    case Key::C :
                    {
                        if (e != NULL)
                        {
                            if (sourisSurElement(MousePos.x, MousePos.y, e) == false)
                                _model->getJoueur1()->construireElement(MousePos.x-(DIMENSION_SPRITE/2), MousePos.y-(DIMENSION_SPRITE/2), "Caserne");

                            else
                                cout << "Element trop proche !" << endl;
                        }
                        else
                            _model->getJoueur1()->construireElement(MousePos.x-(DIMENSION_SPRITE/2), MousePos.y-(DIMENSION_SPRITE/2), "Caserne");                                
                    };break;

                    //Creation de la nourriture sur la map
                    case Key::N : 
                    {
                        if (e != NULL)
                        {
                            if (sourisSurElement(MousePos.x, MousePos.y, e) == false)
                                _model->getJoueur1()->construireElement(MousePos.x-(DIMENSION_SPRITE/2), MousePos.y-(DIMENSION_SPRITE/2), "Nourriture");
                            
                            else
                                cout << "Element trop proche ! " << endl;
                        }
                        else
                            _model->getJoueur1()->construireElement(MousePos.x-(DIMENSION_SPRITE/2), MousePos.y-(DIMENSION_SPRITE/2), "Nourriture");
                    }
                    break;

                    //Effacer un element Actif
                    case Key::E : 
                    {
                        e = _model->getJoueur1()->searchElementActif();
                        Element * e2 = _model->getJoueur1()->searchElementCible();

                        if (e != NULL)
                            {
                                if (e->getType() != "Foyer" and e->getType() != "Caserne")
                                    _model->getJoueur1()->eliminerElement(_model->getJoueur1()->indiceElementActif());
                                else
                                    cout << "Batiment indestructible" << endl;
                            }
                        
                        else if (e2 != NULL)
                            _model->getJoueur1()->eliminerElement(_model->getJoueur1()->indiceElementCible());

                        else 
                            cout << "Aucun Element selectionne" << endl;
                    }break;

                    //Fermer l'application
                    case Key::Escape : 
                    {
                        _view->getWindow()->Close();
                        result = false;
                    };break;

                    default:
                        break;
                }
            }
        }
    }
    return result;
}

