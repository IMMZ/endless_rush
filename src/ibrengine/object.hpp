// TODO: license text

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "global.hpp"
#include "mapobject.hpp"

namespace sf
{

class Time;

}

namespace ibrengine
{

class Object
{
public:
  ENABLE_DEFAULT_MOVE(Object);

  /** @enum Type
   * @brief Represents the object type.
   */
  enum class Type // TODO: Is it really need?
  {
    Drawable, ///!< The object can be drawn.
    Physical, ///!< The object is used in physical calculations.
    Animatable, ///!< The object is animation.
  };

  Object(const MapObjectSharedPtr &director, Type type, int id);
  virtual ~Object() = default;

  const PositionI& getPosition() const;
  void setPosition(const PositionI &pos);
  const PositionI& getSize() const;
  void setSize(const PositionI &size);
  Type getType() const;
  void setChanged();
  bool isVisible() const;
  bool isDrawable() const;
  bool isAnimatable() const;
  bool isPhysical() const;
  int getId() const;

  // Properties.
  const sf::String& getProperty(const sf::String &propertyName) const;
  bool hasProperty(const sf::String &propertyName) const;
  MapObject::PropertyIterator propertiesBegin();
  MapObject::PropertyConstIterator propertiesBegin() const;
  MapObject::PropertyReverseIterator propertiesRBegin();
  MapObject::PropertyConstReverseIterator propertiesRBegin() const;
  MapObject::PropertyIterator propertiesEnd();
  MapObject::PropertyConstIterator propertiesEnd() const;
  MapObject::PropertyReverseIterator propertiesREnd();
  MapObject::PropertyConstReverseIterator propertiesREnd() const;

  virtual void update(const sf::Time &time) = 0;

protected:
  MapObject& getMapObject();
  const MapObject& getMapObject() const;

private:
  MapObjectSharedPtr mDirector;
  PositionI mPos, mSize;
  int mId = 0; // TODO: change to uint32
  Type mType;
};

DECLARE_SMART_PTRS(Object);

} // namespace ibrengine

#endif // OBJECT_HPP
