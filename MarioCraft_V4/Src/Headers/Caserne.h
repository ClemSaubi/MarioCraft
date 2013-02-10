#ifndef _CASERNE_
#define _CASERNE_

#include "Batiment.h"
#include "Constantes.h"
#include "Combattant.h"
#include <iostream>
#include <vector>


class Caserne : public Batiment{

 private:
 	std::vector<Combattant*> _combattants;

 public:

  Caserne(int pos_x, int pos_y);
  ~Caserne();
  
  void creerCombattant(int pos_x, int pos_y);
  void eliminerCombattant(int i);
  void eraseVector();


};

#endif
