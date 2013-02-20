#ifndef _ARTISAN_
#define _ARTISAN_

#include "Personnage.h"
#include "Constantes.h"
#include <iostream>	


class Artisan : public Personnage {

 private:

 	int _quantite_max_ressources_artisan;

 public:

  Artisan(int pos_x, int pos_y);
  ~Artisan();
  int getQuantiteRessource()const;

};

#endif
