// license text

#ifndef TILEOBJECT_HPP
#define TILEOBJECT_HPP

#include "drawableobject.hpp"

namespace ibrengine
{

class TileObject: public DrawableObject
{
public:
  TileObject(const sf::String &name, int tileId);

  int getTileId() const; // TODO: replace to DrawableObject as pure vitrual

private:
  int mTileId;
};

} // namespace ibrengine

#endif // TILEOBJECT_HPP_
