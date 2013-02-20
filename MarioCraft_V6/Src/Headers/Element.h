#ifndef _ELEMENT_
#define _ELEMENT_

#include <iostream>
#include <string>

class Element{

 protected:

	int _pos_x;
	int _pos_y;
	int _pts_vie;
	std::string _type_element;
  bool _est_actif;
	bool _est_cible;
  int _dest_x;
  int _dest_y;

 public:

  Element(int pos_x, int pos_y);
  ~Element();
  int getPosX()const;
  void setPosX(int pos_x);
  int getPosY()const;
  void setPosY(int pos_y);
  std::string getType()const;
  int getVie()const;
  void perteVie(int degats);
  bool estActif()const;
  void setActif(bool actif);
  bool estCible()const;
  void setCible(bool cible);
  int getDestX()const;
  void setDestX(int a);
  int getDestY()const;
  void setDestY(int a);  

};

#endif


