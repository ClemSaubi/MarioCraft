#ifndef _JOUEUR_
#define _JOUEUR_

#include "Element.h"
#include "Batiment.h"
#include "Foyer.h"
#include "Caserne.h"
#include "Personnage.h"
#include "Artisan.h"
#include "Combattant.h"
#include "Constantes.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <SFML/System.hpp>

class Joueur {

 private:

  std::vector<Batiment*> _batiments;
  std::vector<Personnage*> _personnages;
  bool _foyerConstruit;
  int _total_nourriture;
  int _total_bois;
  int _total_artisans;
  int _total_combattants;
  int id_unites;
  bool _joueur_actif;

 public:

  Joueur();
  ~Joueur();

  void nextStep();
  bool JoueurActif()const;
  void desactiverJoueur(bool a);

  //Batiment
  bool foyerConstruit()const;
  void eraseJoueur();
  Batiment * searchFoyer()const;
  void construireBatiment(int pos_x, int pos_y, std::string type);
  int getListBatimentSize()const;
  Batiment * getBatiment(int i)const;
  void detruireBatiment(int i);
  bool listeBatimentVide()const;

  //Unites
  void construireUnite(int pos_x, int pos_y, std::string type);
  int getListPersonnageSize()const;
  Personnage * getPersonnage(int i)const;
  void eliminerPersonnage(int i);
  bool listePersonnageVide()const;
  void retourFoyer(Artisan * art);
  void activerArtisans();

  //Recherches dans les vecteurs
  Element * searchElement(int pos_x, int pos_y)const;
  std::vector<Artisan*> artisansActifs()const;
  std::vector<Combattant*> combattantsActifs()const;
  std::vector<Personnage*> listePersonnages()const;
  Batiment * caserneActive()const;
  void elementsDesactives();
  unsigned int indiceBatimentActif()const;
  unsigned int indicePersonnageActif()const;

  //Accesseurs pour interface de jeu
  int getTotalNourriture()const;
  void setTotalNourriture(int a);

  int getTotalBois()const;
  void setTotalBois(int a);

  int getTotalArtisans()const;
  void setTotalArtisans(int a);

  int getTotalCombattants()const;
  void setTotalCombattants(int a);
};

#endif
