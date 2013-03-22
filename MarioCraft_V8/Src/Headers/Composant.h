#ifndef _COMPOSANT_
#define _COMPOSANT_

#include <iostream>
#include <string>

class Composant{

 protected:
	int _pos_x;
	int _pos_y;
	int _pts_vie;
	std::string _type_composant;

	bool _est_cible; 	

 public:

  Composant(int pos_x, int pos_y);
  ~Composant();
  std::string getTypeComposant()const;
  bool estCible()const;
  void setCible(bool cible);
  int getVieComposant()const;
  int getPosX()const;
  void setPosX(int pos_x);
  int getPosY()const;
  void setPosY(int pos_y);
  void perteVie(int degats);

};

#endif


