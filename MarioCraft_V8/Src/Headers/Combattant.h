#ifndef _COMBATTANT_
#define _COMBATTANT_

#include "Personnage.h"
#include "Constantes.h"
#include "Batiment.h"
#include <iostream>
#include <string>

class Combattant : public Personnage {

 private:

 	int _degats;
 	std::string _type_tache;
 	Batiment * _target_perso;
 	Batiment * _foy;

 public:

  Combattant(int pos_x, int pos_y, Batiment * f);
  ~Combattant();
  void attaquer();
  Batiment * getFoyer()const;
  Batiment * getTargetPerso()const;
  void setTargetPerso(Batiment * target);
  std::string getTypeTache()const;
  void setTypeTache(std::string type_tache);
  virtual void effectuerTache();

};

#endif
