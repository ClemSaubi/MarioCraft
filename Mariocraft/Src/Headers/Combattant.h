#ifndef _COMBATTANT_
#define _COMBATTANT_

#include "Personnage.h"
#include "Constantes.h"
#include <iostream>
#include <string>

class Combattant : public Personnage {

 private:

 	int _degats;
 	std::string _type_tache;
 	Element * _target_perso;

 public:

  Combattant(int pos_x, int pos_y);
  ~Combattant();
  void attaquer();
  Element * getTargetPerso()const;
  void setTargetPerso(Element * target);
  std::string getTypeTache()const;
  void setTypeTache(std::string type_tache);
  virtual void effectuerTache();

};

#endif
