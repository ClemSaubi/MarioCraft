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
};

#endif


