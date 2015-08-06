// license text

#include "gameobject.hpp"

const sf::Vector2i& GameObject::getPosition() const
{
  return mPos;
}

void GameObject::setPosition(const sf::Vector2i& pos)
{
  mPos = pos;
}
