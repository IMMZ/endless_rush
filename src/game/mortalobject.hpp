// license text

#ifndef MORTALOBJECT_HPP
#define MORTALOBJECT_HPP

#include "gameobject.hpp"

class MortalObject: public GameObject
{
public:
  int getHealth();
  void setHealth(int health);

private:
  int mHealth = 100;
};

#endif // MORTALOBJECT_HPP
