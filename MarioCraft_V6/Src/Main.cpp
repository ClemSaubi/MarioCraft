#include "Headers/GameModel.h"
#include "Headers/GameView.h"
#include "Headers/Controller.h"
#include "Headers/Constantes.h"

#include <iostream>
#include <cstdlib>


using namespace std;

int main() {

    GameModel * _model = new GameModel();
    GameView * _view = new GameView(WINDOW_WIDTH, WINDOW_HEIGHT, _model);
    Controller * _control = new Controller(_model, _view);

    while(_control->treatEvents())
    {
        _model->nextStep();
        _view->Display();
    }

    delete _model;
    delete _view;
    delete _control;

    return EXIT_SUCCESS;
}
