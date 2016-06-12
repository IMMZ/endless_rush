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
  // The type is used as flags when creating objects in ObjectDirector.
  /** @enum Type
   * @brief Represents the object type.
   */
  enum class Type // TODO: Is it really need?
  {
    Drawable, ///!< The object can be drawn.
    Physical, ///!< The object is used in physical calculations.
    Animatable, ///!< The object is animation.
  };

  Object(const MapUnitPtr &director, Type type);
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

  virtual void update(const sf::Time &time) = 0;

protected:
 MapUnitPtr getMapObject() const;

private:
  MapUnitPtr mDirector;
  PositionI mPos, mSize;
  Type mType;
};

using ObjectScopedPtr = std::unique_ptr<Object>;

} // namespace ibrengine

#endif // OBJECT_HPP
