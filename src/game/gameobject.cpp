// license text

#include "gameobject.hpp"

#include <object.hpp>

GameObject::GameObject(ibrengine::Object *mapObj):
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

ibrengine::Object* GameObject::getMapObj()
{
  return mMapObj;
}
