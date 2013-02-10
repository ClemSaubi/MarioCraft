#ifndef _GAME_MODEL_
#define _GAME_MODEL_

#include "Element.h"
#include "Foyer.h"
#include "Caserne.h"
#include "Bois.h"
#include "Obstacle.h"
#include "Nourriture.h"
#include "Constantes.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class GameModel {

 private:

  std::vector<Element*> _elements;
  bool _foyerConstruit;
  int _quantite_nourriture;
  int _quantite_bois;
  int _compteur_bois;
  int _compteur_nourriture;

 public:

  GameModel();
  ~GameModel();

  void nextStep();

  bool foyerConstruit()const;
  void eraseMap();
  void construireElement(int pos_x, int pos_y, std::string type);
  int getListElementSize()const;
  Element * getElement(int i)const;
  void eliminerElement(int i);
  Element * searchElement(int pos_x, int pos_y)const;
  bool listeVide()const;
  void elementsDesactives();
  std::string intToString(int a)const;
  int getQuantiteNourriture()const;
  void setQuantiteNourriture(int a);
  int getQuantiteBois()const;
  void setQuantiteBois(int a);
  int getCompteurBois()const;
  int getCompteurNourriture()const;

};

#endif
