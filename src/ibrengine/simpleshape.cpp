// license text

#include "simpleshape.hpp"

namespace ibrengine
{

SimpleShape::SimpleShape(const sf::String& name, Type type):
  mType(type)
{
}

const sf::Vector2i& SimpleShape::getSize() const
{
  return mSize;
}

void SimpleShape::setSize(const sf::Vector2i& size)
{
  mSize = size;
}

SimpleShape::Type SimpleShape::getType() const
{
  return mType;
}

} // namespace ibrengine
