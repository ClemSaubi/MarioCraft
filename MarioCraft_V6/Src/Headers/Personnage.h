#ifndef _PERSONNAGE_
#define _PERSONNAGE_

#include <iostream>	
#include <string>
#include "Element.h"
#include "Constantes.h"

class Personnage : public Element{
	
 protected:
 	
 	bool _active;

 public:

  Personnage( int pos_x, int pos_y);
  ~Personnage();
  bool estActif()const;
  void setActif(bool actif);
};

#endif


