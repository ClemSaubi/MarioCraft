#ifndef _JOUEUR_
#define _JOUEUR_

#include "Element.h"
#include "Foyer.h"
#include "Caserne.h"
#include "Bois.h"
#include "Obstacle.h"
#include "Nourriture.h"
#include "Artisan.h"
#include "Constantes.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Joueur {

 private:

  std::vector<Element*> _elements;
  bool _foyerConstruit;
  int _quantite_nourriture;
  int _quantite_bois;
  int _compteur_bois;
  int _compteur_nourriture;
  int _compteur_artisans;
  int id_unites;

 public:

  Joueur();
  ~Joueur();

  void nextStep();

  //Foyer
  bool foyerConstruit()const;
  void eraseJoueur();
  Element * searchFoyer()const;

  //Elements
  void construireElement(int pos_x, int pos_y, std::string type);
  int getListElementSize()const;
  Element * getElement(int i)const;
  void eliminerElement(int i);
  unsigned int indiceElementActif()const;
  unsigned int indiceElementCible()const;
  bool listeVide()const;

  //Recherches dans le vecteur
  Element * searchElement(int pos_x, int pos_y)const;
  Element * searchElementActif()const;
  Element * searchElementCible()const;
  std::vector<Element*> unitesActives(std::string type)const;
  void elementsDesactives();
  void activerToutesUnites(std::string type);
  void deciblerElement();

  //Accesseurs pour interface de jeu
  int getQuantiteNourriture()const;
  void setQuantiteNourriture(int a);
  int getQuantiteBois()const;
  void setQuantiteBois(int a);
  int getCompteurBois()const;
  int getCompteurNourriture()const;
  int getCompteurArtisans()const;
  void setCompteurArtisans(int a);

  //Utilitaires
  std::string intToString(int a)const;


};

#endif
