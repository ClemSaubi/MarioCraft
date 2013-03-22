#ifndef _ARTISAN_
#define _ARTISAN_

#include "Personnage.h"
#include "Constantes.h"
#include <iostream>	
#include <SFML/System.hpp>


class Artisan : public Personnage {

 private:
  int _recolte_bois_artisan;
  int _recolte_nourriture_artisan;
  Composant * _target;

  sf::Clock _timer_recolte;

 public:

  Artisan(int pos_x, int pos_y);
  ~Artisan();
  Composant * getTarget()const;
  void setTarget(Composant * e);
  int getNourriture()const;
  int getBois()const;
  void setNourriture(int a);
  void setBois(int a);
  virtual void effectuerTache();
};

#endif
