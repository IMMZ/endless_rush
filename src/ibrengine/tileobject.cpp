// license text

#include "tileobject.hpp"

namespace ibrengine
{

TileObject::TileObject(const sf::String& name, int tileId):
  DrawableObject(name),
  mTileId(tileId)
{
}

int TileObject::getTileId() const
{
  return mTileId;
}

} // namespace ibrengine
