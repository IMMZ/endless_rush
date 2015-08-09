// license text

#include "gameobject.hpp"

#include <mapobject.hpp>

GameObject::GameObject(ibrengine::MapObject *mapObj):
  mMapObj(mapObj)
{
}

const sf::Vector2i& GameObject::getPosition() const
{
  return mMapObj->getPosition();
}

void GameObject::setPosition(const sf::Vector2i& pos)
{
  mMapObj->setPosition(pos);
}

ibrengine::MapObject* GameObject::getMapObj()
{
  return mMapObj;
}
