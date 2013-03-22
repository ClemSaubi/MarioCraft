#ifndef _CASERNE_
#define _CASERNE_

#include "Batiment.h"
#include "Constantes.h"
#include "Combattant.h"
#include <iostream>
#include <vector>


class Caserne : public Batiment{

 public:

  Caserne(int pos_x, int pos_y);
  ~Caserne();

};

#endif
