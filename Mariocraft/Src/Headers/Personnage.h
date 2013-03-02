#ifndef _PERSONNAGE_
#define _PERSONNAGE_

#include <iostream>	
#include <string>
#include "Element.h"
#include "Composant.h"
#include "Constantes.h"

class Personnage : public Element{
	
 protected:
  bool _en_collision;
  int _dest_x;
  int _dest_y;

 public:

  Personnage( int pos_x, int pos_y);
  virtual ~Personnage();
  bool estEnCollision()const;
  void rentreEnCollision(bool a);
  int getDestX()const;
  void setDestX(int a);
  int getDestY()const;
  void setDestY(int a);
  virtual void effectuerTache() = 0;

  int MathAbs(int a)const;
  
};

#endif


