// TODO: license text

#include "object.hpp"

namespace ibrengine
{

Object::Object(const MapUnitPtr &director, Type type, int id):
  mDirector(director),
  mId(id),
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
  mDirector->objectChanged(*this);
}

bool Object::isVisible() const
{
  return mDirector->isVisible();
}

bool Object::isDrawable() const
{
  return (mType == Type::Drawable);
}

bool Object::isAnimatable() const
{
  return (mType == Type::Animatable);
}

bool Object::isPhysical() const
{
  return (mType == Type::Physical);
}

int Object::getId() const
{
  return mId;
}

MapUnitPtr Object::getMapObject() const
{
  return mDirector;
}

} // namespace ibrengine
