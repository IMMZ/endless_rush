// TODO: license text

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <SFML/System/Vector2.hpp>

namespace sf
{

class Time;

}

namespace ibrengine
{

class MapObject;

class Object
{
public:
  // The type is used as flags when creating objects in ObjectDirector.
  /** @enum Type
   * @brief Represents the object type.
   */
  enum class Type
  {
    None = 0,
    Drawable = 1, ///!< The object can be drawn.
    Physical = 2, ///!< The object is used in physical calculations.
    Animatable = 4, ///!< The object is animation.
    Full = Drawable
          | Physical
          | Animatable ///!< The object which can be drawn, animated and used by physic engine.
  };

  Object(MapObject &director, Type type);
  virtual ~Object();

  const sf::Vector2i& getPosition() const;
  void setPosition(const sf::Vector2i &pos);
  const sf::Vector2i& getSize() const;
  void setSize(const sf::Vector2i &size);
  Type getType() const;
  void setChanged();

  virtual void update(const sf::Time &time);

private:
  sf::Vector2i mPos, mSize;
  MapObject &mDirector;
  Type mType = Type::None;
};

} // namespace ibrengine

#endif // OBJECT_HPP_
