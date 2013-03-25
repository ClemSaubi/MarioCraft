#ifndef _COMBATTANT_
#define _COMBATTANT_

#include "Personnage.h"
#include "Constantes.h"
#include "Batiment.h"
#include <iostream>
#include <string>
#include <SFML/System.hpp>

class Combattant : public Personnage {

 private:

 	int _degats;
 	std::string _type_tache;
 	Element * _target_perso;
 	Batiment * _foy;
 	sf::Clock temps;

 public:

  Combattant(int pos_x, int pos_y, Batiment * f);
  ~Combattant();
  void attaquer();
  Batiment * getFoyer()const;
  Element * getTargetPerso()const;
  void setTargetPerso(Element * target);
  std::string getTypeTache()const;
  void setTypeTache(std::string type_tache);
  virtual void effectuerTache();

};

#endif
