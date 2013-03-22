#ifndef _NOURRITURE_
#define _NOURRITURE_

#include "Composant.h"
#include <iostream>	

class Nourriture : public Composant{
	
 public:

  Nourriture( int pos_x, int pos_y);
  ~Nourriture();
};

#endif



