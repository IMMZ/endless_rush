// license text

#ifndef SIMPLESHAPE_HPP
#define SIMPLESHAPE_HPP

#include "mapobject.hpp"

namespace ibrengine
{

class SimpleShape: public MapObject
{
public:
  enum class Type { Circle, Square };

  SimpleShape(const sf::String &name, Type type);

  const sf::Vector2i& getSize() const;
  void setSize(const sf::Vector2i &size);
  Type getType() const;

private:
  sf::Vector2i mSize;
  Type mType;
};

} // namespace ibrengine

#endif // SIMPLESHAPE_HPP
