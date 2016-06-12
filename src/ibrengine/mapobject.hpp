// license text

#ifndef MAPOBJECT_HPP
#define MAPOBJECT_HPP

#include "global.hpp"

#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

#include <map>
#include <memory>
#include <iostream>
namespace sf
{

class Time;

}

namespace ibrengine
{

class AnimatableObject;
class DrawableObject;
class Object;
class ObjectLayer;
class PhysicObject;
class Shape;

// TODO: rename to 'MapUnit'
class MapObject
{
public:
  using PropertyIterator = std::map<sf::String, sf::String>::iterator;
  using PropertyConstIterator = std::map<sf::String, sf::String>::const_iterator;
  using PropertyReverseIterator = std::map<sf::String, sf::String>::reverse_iterator;
  using PropertyConstReverseIterator = std::map<sf::String, sf::String>::const_reverse_iterator;

  explicit MapObject(const sf::String &name);

  // Mediator funcs.
  void setObject(Object *obj);
  void objectChanged(const Object &obj);

  const sf::String& getName() const;
  void setName(const sf::String &name);
  const PositionI& getPosition() const;
  void setPosition(const PositionI &pos);
  bool isVisible() const;
  void setVisible(bool visible);
  const sf::String& getType() const;
  void setType(const sf::String &type);

  // Properties.
  void addProperty(const sf::String &propertyName, const sf::String &propertyValue);
  const sf::String& getProperty(const sf::String &propertyName) const;
  bool hasProperty(const sf::String &propertyName) const;
  PropertyIterator propertiesBegin();
  PropertyConstIterator propertiesBegin() const;
  PropertyReverseIterator propertiesRBegin();
  PropertyConstReverseIterator propertiesRBegin() const;
  PropertyIterator propertiesEnd();
  PropertyConstIterator propertiesEnd() const;
  PropertyReverseIterator propertiesREnd();
  PropertyConstReverseIterator propertiesREnd() const;

  void update(const sf::Time &time);

private:
  void drawableObjectChanged(const DrawableObject &obj);
  void physicalObjectChanged(const PhysicObject &obj);
  void animatableObjectChanged(const AnimatableObject &obj);

  std::map<sf::String /* name */, sf::String /* value */> mProperties;
  sf::String mName, mType;
  PositionI mPosition;
  DrawableObject *mDrawableObj = nullptr;
  PhysicObject *mPhysicalObj = nullptr;
  AnimatableObject *mAnimatableObj = nullptr;
  bool mVisible = true;
};

using MapUnitPtr = std::shared_ptr<MapObject>;

} // namespace ibrengine

#endif // MAPOBJECT_HPP
