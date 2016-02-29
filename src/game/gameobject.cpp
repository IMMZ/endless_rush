// license text

#include "gameobject.hpp"

#include <object.hpp>

GameObject::GameObject(ibrengine::Object *mapObj):
  mMapObj(mapObj)
{
}

const ibrengine::PositionI& GameObject::getPosition() const
{
  return mMapObj->getPosition();
}

void GameObject::setPosition(const ibrengine::PositionI& pos)
{
  mMapObj->setPosition(pos);
}

ibrengine::Object* GameObject::getMapObj()
{
  return mMapObj;
}
