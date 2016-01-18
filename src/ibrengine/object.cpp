// TODO: license text

#include "object.hpp"
#include "testik.hpp"

namespace ibrengine
{

Object::Object(MapObject &director, Type type):
  mDirector(director),
  mType(type)
{
}

Object::~Object()
{
}

const sf::Vector2i& Object::getPosition() const
{
  return mPos;
}

void Object::setPosition(const sf::Vector2i &pos)
{
  mPos = pos;
}

const sf::Vector2i& Object::getSize() const
{
  return mSize;
}

void Object::setSize(const sf::Vector2i &size)
{
  mSize = size;
}

Object::Type Object::getType() const
{
  return mType;
}

void Object::setChanged()
{
  mDirector.objectChanged(*this);
}

void Object::update(const sf::Time &time)
{
  // Do nothing.
}

} // namespace ibrengine
