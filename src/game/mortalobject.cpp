// license text

#include "mortalobject.hpp"

MortalObject::MortalObject(ibrengine::Object *mapObj):
  GameObject(mapObj)
{
}

int MortalObject::getHealth()
{
  return mHealth;
}

void MortalObject::setHealth(int health)
{
  if (health > 100)
    mHealth =100;
  else if (health < 0)
    mHealth = 0;
  else
    mHealth = health;
}
