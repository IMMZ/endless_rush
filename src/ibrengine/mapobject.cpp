// license text

#include "mapobject.hpp"

#include "map.hpp"
#include "object.hpp"
#include "objectlayer.hpp"
#include "physicobject.hpp"
#include <iostream> // TODO: remove

#include "animatableobject.hpp"
#include "drawableobject.hpp"

namespace ibrengine
{

MapObject::MapObject(const sf::String& name, Map &map):
  mMap(map),
  mName(name)
{
}

Map& MapObject::getMap()
{
  return mMap;
}

const Map& MapObject::getMap() const
{
  return mMap;
}

void MapObject::setObject(Object *obj)
{
  switch (obj->getType())
  {
    case Object::Type::Animatable:
    {
      mAnimatableObj = dynamic_cast<AnimatableObject*>(obj);
      break;
    }
    case Object::Type::Drawable:
    {
      mDrawableObj = dynamic_cast<DrawableObject*>(obj);
      break;
    }
    case Object::Type::Physical:
    {
      mPhysicalObj = dynamic_cast<PhysicObject*>(obj);
      break;
    }
  }
}

void MapObject::objectChanged(const Object &obj)
{
  switch (obj.getType())
  {
    case Object::Type::Animatable:
    {
      this->animatableObjectChanged(*mAnimatableObj);
      break;
    }
    case Object::Type::Drawable:
    {
      this->drawableObjectChanged(*mDrawableObj);
      break;
    }
    case Object::Type::Physical:
    {
      this->physicalObjectChanged(*mPhysicalObj);
      break;
    }
  }
}

const sf::String& MapObject::getName() const
{
  return mName;
}

void MapObject::setName(const sf::String& name)
{
  mName = name;
}

const PositionI& MapObject::getPosition() const
{
  return mPosition;
}

void MapObject::setPosition(const PositionI& pos)
{
  mPosition = pos;
}

bool MapObject::isVisible() const
{
  return mVisible;
}

void MapObject::setVisible(bool visible)
{
  mVisible = visible;
}

const sf::String& MapObject::getType() const
{
  return mType;
}

void MapObject::setType(const sf::String &type)
{
  mType = type;
}

void MapObject::addProperty(const sf::String &propertyName,
  const sf::String &propertyValue)
{
  mProperties.insert(std::make_pair(propertyName, propertyValue));
}

const sf::String& MapObject::getProperty(const sf::String &propertyName) const
{
  return mProperties.at(propertyName);
}

bool MapObject::hasProperty(const sf::String &propertyName) const
{
  return !(mProperties.find(propertyName) == mProperties.end());
}

MapObject::PropertyIterator MapObject::propertiesBegin()
{
 return mProperties.begin();
}

MapObject::PropertyConstIterator MapObject::propertiesBegin() const
{
  return mProperties.begin();
}

MapObject::PropertyReverseIterator MapObject::propertiesRBegin()
{
  return mProperties.rbegin();
}

MapObject::PropertyConstReverseIterator MapObject::propertiesRBegin() const
{
  return mProperties.rbegin();
}

MapObject::PropertyIterator MapObject::propertiesEnd()
{
  return mProperties.end();
}

MapObject::PropertyConstIterator MapObject::propertiesEnd() const
{
  return mProperties.end();
}

MapObject::PropertyReverseIterator MapObject::propertiesREnd()
{
  return mProperties.rend();
}

MapObject::PropertyConstReverseIterator MapObject::propertiesREnd() const
{
  return mProperties.rend();
}

void MapObject::update(const sf::Time &time)
{
  if (mDrawableObj != nullptr)
    mDrawableObj->update(time);
  if (mPhysicalObj != nullptr)
    mPhysicalObj->update(time);
  if (mAnimatableObj != nullptr)
    mAnimatableObj->update(time);
}

void MapObject::drawableObjectChanged(const DrawableObject &obj)
{// Do nothing?
}

void MapObject::physicalObjectChanged(const PhysicObject &obj)
{
  if (mDrawableObj != nullptr)
  {
    mDrawableObj->setRotation(obj.getAngle());
    mDrawableObj->setPosition(obj.getPosition());
  }
}

void MapObject::animatableObjectChanged(const AnimatableObject &obj)
{
  if (mDrawableObj != nullptr)
    mDrawableObj->setTileId(obj.getCurrentTileId());
  if (mPhysicalObj != nullptr)
    mPhysicalObj->setShapeGroup(mMap.getShapeGroup(obj.getCurrentTileId()));
}

} // namespace ibrengine
