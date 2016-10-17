// TODO: license text

#include "object.hpp"

namespace ibrengine
{

Object::Object(const MapObjectSharedPtr &director, Type type, int id):
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

const sf::String& Object::getProperty(const sf::String &propertyName) const
{
  return getMapObject().getProperty(propertyName);
}

bool Object::hasProperty(const sf::String &propertyName) const
{
  return getMapObject().hasProperty(propertyName);
}

MapObject::PropertyIterator Object::propertiesBegin()
{
  return getMapObject().propertiesBegin();
}

MapObject::PropertyConstIterator Object::propertiesBegin() const
{
  return getMapObject().propertiesBegin();
}

MapObject::PropertyReverseIterator Object::propertiesRBegin()
{
  return getMapObject().propertiesRBegin();
}

MapObject::PropertyConstReverseIterator Object::propertiesRBegin() const
{
  return getMapObject().propertiesRBegin();
}

MapObject::PropertyIterator Object::propertiesEnd()
{
  return getMapObject().propertiesEnd();
}

MapObject::PropertyConstIterator Object::propertiesEnd() const
{
  return getMapObject().propertiesEnd();
}

MapObject::PropertyReverseIterator Object::propertiesREnd()
{
  return getMapObject().propertiesREnd();
}

MapObject::PropertyConstReverseIterator Object::propertiesREnd() const
{
  return getMapObject().propertiesREnd();
}

MapObject& Object::getMapObject()
{
  return *mDirector;
}

const MapObject& Object::getMapObject() const
{
  return *mDirector;
}

} // namespace ibrengine
