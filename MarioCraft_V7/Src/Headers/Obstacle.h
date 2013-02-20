#ifndef _OBSTACLE_
#define _OBSTACLE_

#include <iostream>	
#include "Composant.h"

class Obstacle : public Composant{
	
 public:

  Obstacle(int pos_x, int pos_y);
  ~Obstacle();

};

#endif


