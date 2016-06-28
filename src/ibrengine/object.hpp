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

  Object(const MapUnitPtr &director, Type type, int id);
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

  virtual void update(const sf::Time &time) = 0;

protected:
 MapUnitPtr getMapObject() const;

private:
  MapUnitPtr mDirector;
  PositionI mPos, mSize;
  int mId = 0; // TODO: change to uint32
  Type mType;
};

using ObjectScopedPtr = std::unique_ptr<Object>;
using ObjectSharedPtr = std::shared_ptr<Object>;
using ObjectWeakPtr = std::weak_ptr<Object>;

} // namespace ibrengine

#endif // OBJECT_HPP
