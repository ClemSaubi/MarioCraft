#ifndef _BATIMENT_
#define _BATIMENT_

#include "Element.h"
#include "Constantes.h"
#include <iostream>	


class Batiment : public Element{

 public:

  Batiment(int pos_x, int pos_y);
  ~Batiment();

  unsigned int getPosX()const;
  unsigned int getPosY()const;

};

#endif
