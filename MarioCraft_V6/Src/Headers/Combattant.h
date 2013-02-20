#ifndef _COMBATTANT_
#define _COMBATTANT_

#include "Personnage.h"
#include "Constantes.h"
#include <iostream>

class Combattant : public Personnage {

 private:

 	int _degats;

 public:

  Combattant(int pos_x, int pos_y);
  ~Combattant();
  void attaquer(Element * e);

};

#endif
