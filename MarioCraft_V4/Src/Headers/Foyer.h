#ifndef _FOYER_
#define _FOYER_

#include "Batiment.h"
#include "Constantes.h"
#include "Artisan.h"
#include <iostream>	
#include <vector>

class Foyer : public Batiment{

 private:

 	std::vector<Artisan*> _artisans;


 public:

  Foyer(int pos_x, int pos_y);
  ~Foyer();

  int getRessourcesDispo()const;
  void setRessourcesDispo(int ressources);
  void creerArtisan(int pos_x, int pos_y);
  void eliminerArtisan(int i);
  void eraseVector();

};

#endif
