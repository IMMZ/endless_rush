// TODO: license text

#include "object.hpp"

#include "mapobject.hpp"

namespace ibrengine
{

Object::Object(MapObject &director, Type type):
  mDirector(director),
  mType(type)
{
}

const PositionI& Object::getPosition() const
{
  return mPos;
}

void Object::setPosition(const PositionI &pos)
{
  mPos = pos;
}

const PositionI& Object::getSize() const
{
  return mSize;
}

void Object::setSize(const PositionI &size)
{
  mSize = size;
}

Object::Type Object::getType() const
{
  return mType;
}

void Object::setChanged()
{
  mDirector.objectChanged(*this);
}

const MapObject& Object::getMapObject() const
{
  return mDirector;
}

} // namespace ibrengine
