// license text

#include "mapobject.hpp"

#include "animatableobjectt.hpp"
#include "drawableobjectt.hpp"
#include "objectlayer.hpp"
#include "testik.hpp" // physical obj

namespace ibrengine
{

MapObject::MapObject(const sf::String& name):
  mName(name)
{
}

void MapObject::setObject(Object *obj)
{
  switch (obj->getType())
  {
    case Object::Type::Drawable:
    {
      mDrawableObj.reset(dynamic_cast<DrawableObjectt*>(obj));
      break;
    }
    case Object::Type::Animatable:
    {
      mAnimatableObj.reset(dynamic_cast<AnimatableObjectt*>(obj));
      break;
    }
  }
}

void MapObject::objectChanged(const Object &obj)
{
  switch (obj.getType())
  {
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
    case Object::Type::Animatable:
    {
      this->animatableObjectChanged(*mAnimatableObj);
      break;
    }
    default: break; // TODO: warn about Unknown obj type.
  }
}

void MapObject::addToLayer(ObjectLayer &layer)
{
  if (mDrawableObj != nullptr)
    layer.addDrawableObject(mDrawableObj.get());
  if (mPhysicalObj != nullptr)
    layer.addPhysicalObject(mPhysicalObj.get());
  if (mAnimatableObj != nullptr)
    layer.addAnimatableObject(mAnimatableObj.get());
}

const sf::String& MapObject::getName() const
{
  return mName;
}

void MapObject::setName(const sf::String& name)
{
  mName = name;
}

const sf::Vector2i& MapObject::getPosition() const
{
  return mPosition;
}

void MapObject::setPosition(const sf::Vector2i& pos)
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

void MapObject::drawableObjectChanged(const DrawableObjectt &obj)
{// Do nothing?
}

void MapObject::physicalObjectChanged(const PhysicalObjectt &obj)
{
  if (mDrawableObj != nullptr)
  {
    // set rotation and position for drawObject
  }
  // set position for mMapObj
}

void MapObject::animatableObjectChanged(const AnimatableObjectt &obj)
{
  if (mDrawableObj != nullptr)
  {
    mDrawableObj->setTileId(obj.getCurrentTileId());
  }
  if (mPhysicalObj != nullptr)
  {// TODO: set new id for physical property
  }
}

} // namespace ibrengine
