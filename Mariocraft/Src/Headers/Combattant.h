#ifndef _COMBATTANT_
#define _COMBATTANT_

#include "Personnage.h"
#include "Constantes.h"
#include <iostream>

class Combattant : public Personnage {

 private:

 	int _degats;
 	Element * _target_perso;

 public:

  Combattant(int pos_x, int pos_y);
  ~Combattant();
  void attaquer();
  Element * getTargetPerso()const;
  void setTargetPerso(Element * target);
  virtual void effectuerTache();

};

#endif
