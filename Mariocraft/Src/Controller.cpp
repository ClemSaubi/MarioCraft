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

bool Controller::sourisSurComposant(float x, float y, Composant * c)const {
    if (x < c->getPosX())
        return false;

    if (x > c->getPosX() + DIMENSION_SPRITE)
        return false;

    if (y < c->getPosY())
        return false;

    if (y > c->getPosY() + DIMENSION_SPRITE)
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
        _timer_unite.Reset();

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

            // Activation ou ciblage des Elements
            if (_event.Type == Event::MouseButtonReleased and button == Mouse::Left)
                activationElement(MousePos.x, MousePos.y);

            //Gestion d'unites
            if (_event.Type == Event::MouseButtonReleased and button == Mouse::Right)
            {
                gestionUnites(MousePos.x, MousePos.y);
                definirTarget(MousePos.x, MousePos.y);
            }

            //Entrees claviers
            if (_event.Type == Event::KeyReleased)
            {
                Element * e = _model->getJoueurActif()->searchElement(MousePos.x, MousePos.y);
                Composant * c = _model->searchComposant(MousePos.x, MousePos.y);

                switch (_event.Key.Code)
                {
                    //Creation Map
                case Key::A:
                    _model->creationMap();
                    break;

                    //Construction Foyer
                case Key::F :
                    constructionFoyer(MousePos.x, MousePos.y, c);
                    break;

                    //Construction Caserne
                case Key::C :
                    constructionCaserne(MousePos.x, MousePos.y, e, c);
                    break;

                case Key::D:
                    _model->getJoueurActif()->activerArtisans();
                    break;

                    //Fermer l'application
                case Key::Escape :
                {
                    _view->getWindow()->Close();
                    result = false;
                };
                break;

                default:
                    break;
                }
            }
        }
    }
    return result;
}

void Controller::activationElement(int x, int y) {
    if (_model->getJoueurActif()->listeBatimentVide() == false or
        _model->getJoueurActif()->listePersonnageVide() == false)
    {
        Element * e = _model->getJoueurActif()->searchElement(x,y);

        if (e != NULL)
        {
            if (this->sourisSurElement(x, y, e) == true)
            {
                //Activation d'un élément apres clic gauche dessus
                if (e->estActif() == false)
                {
                    _model->getJoueurActif()->elementsDesactives();
                    e->setActif(true);

                    Artisan * art = dynamic_cast<Artisan*>(e);
                    if (art != NULL and art->getTarget() != NULL)
                    {
                        _model->deciblerComposant();
                        art->getTarget()->setCible(true);
                    }
                }
                else
                    e->setActif(false);
            }
        }
        else
        {
            _model->getJoueurActif()->elementsDesactives();
            _model->deciblerComposant();
        }
    }
}

void Controller::gestionUnites(int x, int y) {
    Batiment * foyer = _model->getJoueurActif()->searchFoyer();

    if (foyer != NULL)
    {
        if (foyer->estActif() == true and this->sourisSurElement(x, y, foyer) == true)
            _model->getJoueurActif()->construireUnite(foyer->getPosX(), foyer->getPosY() + DIMENSION_PERSO, "Artisan");
    }

    Batiment * caserne = _model->getJoueurActif()->caserneActive();

    if (caserne != NULL)
    {
        if (caserne->estActif() == true and this->sourisSurElement(x, y, caserne) == true)
            _model->getJoueurActif()->construireUnite(caserne->getPosX(), caserne->getPosY() + DIMENSION_PERSO, "Combattant");
    }

    //Deplacement d'Artisans
    vector<Artisan*> arts = _model->getJoueurActif()->artisansActifs();

    for (unsigned int i = 0; i < arts.size(); ++i)
    {
        arts[i]->setDestX(x - DIMENSION_PERSO/2 + (i*DIMENSION_PERSO*3)/2);
        arts[i]->setDestY(y - DIMENSION_PERSO/2);
        arts[i]->setTarget(NULL);
        arts[i]->rentreEnCollision(false);  
    }

    //Deplacement de Combattants
    vector<Combattant*> combs = _model->getJoueurActif()->combattantsActifs();

    for (unsigned int i = 0; i < combs.size(); ++i)
    {
        combs[i]->setDestX(x - DIMENSION_PERSO/2 + (i*DIMENSION_PERSO*3)/2);
        combs[i]->setDestY(y - DIMENSION_PERSO/2);
        combs[i]->setTargetPerso(NULL);                
    }
}

void Controller::constructionFoyer(int x, int y, Composant * c) {
    if (_model->getJoueurActif()->foyerConstruit() == false)
    {
        if (c != NULL)
        {
            if (this->sourisSurComposant(x, y, c) == false)
                _model->getJoueurActif()->construireBatiment(x-(DIMENSION_SPRITE/2), y-(DIMENSION_SPRITE/2), "Foyer");
            else
                cout << "Element trop proche !" << endl;
        }
        else
            _model->getJoueurActif()->construireBatiment(x-(DIMENSION_SPRITE/2), y-(DIMENSION_SPRITE/2), "Foyer");
    }
    else
        cout << "Foyer deja bati" << endl;
}

void Controller::constructionCaserne(int x, int y, Element * e, Composant * c) {
    if (e != NULL and c != NULL)
    {
        if (this->sourisSurElement(x, y, e) == false and this->sourisSurComposant(x, y, c) == false)
            _model->getJoueurActif()->construireBatiment(x-(DIMENSION_SPRITE/2), y-(DIMENSION_SPRITE/2), "Caserne");

        else
            cout << "Element trop proche !" << endl;
    }
    else
        _model->getJoueurActif()->construireBatiment(x-(DIMENSION_SPRITE/2), y-(DIMENSION_SPRITE/2), "Caserne");
}

void Controller::definirTarget(int x, int y){
    vector<Artisan*> arts = _model->getJoueurActif()->artisansActifs();

    for (unsigned int i = 0; i < arts.size(); ++i)
    {
        Composant * c = _model->searchComposant(x, y);
        if (c != NULL)
        {
            if (sourisSurComposant(x,y,c) == true)
            {
                _model->deciblerComposant();
                c->setCible(true);
                arts[i]->setTarget(c);
            }
        }
        else
            _model->deciblerComposant();
    }
}