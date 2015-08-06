// license text

#include "mortalobject.hpp"

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
