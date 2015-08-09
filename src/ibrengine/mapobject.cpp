// license text

#include "mapobject.hpp"

namespace ibrengine
{

MapObject::MapObject()
{
}

MapObject::MapObject(const sf::String& name):
  mName(name)
{
}

MapObject::~MapObject()
{
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

void MapObject::update()
{
}

} // namespace ibrengine
