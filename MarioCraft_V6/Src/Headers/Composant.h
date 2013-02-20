#ifndef _COMPOSANT_
#define _COMPOSANT_

#include <iostream>
#include <string>
#include "Element.h"

class Composant : public Element{

 public:

  Composant(int pos_x, int pos_y);
  ~Composant();
};

#endif


