// license text

#include "drawableobject.hpp"

namespace ibrengine
{

DrawableObject::DrawableObject(const sf::String &name):
  MapObject(name)
{
}

bool DrawableObject::isHFlip() const
{
  return mHFlip;
}

void DrawableObject::setHFlip(bool hFlip)
{
  mHFlip = hFlip;
}

const sf::Vector2i& DrawableObject::getSize() const
{
  return mSize;
}

void DrawableObject::setSize(const sf::Vector2i &size)
{
  mSize = size;
}

bool DrawableObject::isVFlip() const
{
  return mVFlip;
}

void DrawableObject::setVFlip(bool vFlip)
{
  mVFlip = vFlip;
}

} // namespace ibrengine
