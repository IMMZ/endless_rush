// license text

#ifndef DRAWABLEOBJECT_HPP
#define DRAWABLEOBJECT_HPP

#include "mapobject.hpp"

namespace ibrengine
{

class DrawableObject: public MapObject
{
public:
  explicit DrawableObject(const sf::String &name);

  bool isHFlip() const;
  void setHFlip(bool hFlip);
  const sf::Vector2i& getSize() const;
  void setSize(const sf::Vector2i &size);
  bool isVFlip() const;
  void setVFlip(bool vFlip);

private:
  sf::Vector2i mSize;
  bool mHFlip = false;
  bool mVFlip = false;
};

} // namespace ibrengine

#endif // DRAWABLEOBJECT_HPP
