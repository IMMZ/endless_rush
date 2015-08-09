// license text

#ifndef MORTALOBJECT_HPP
#define MORTALOBJECT_HPP

#include "gameobject.hpp"

class MortalObject: public GameObject
{
public:
  explicit MortalObject(ibrengine::MapObject *mapObj);

  int getHealth();
  void setHealth(int health);

private:
  int mHealth = 100;
};

#endif // MORTALOBJECT_HPP
