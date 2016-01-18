// TODO: license text

#include "drawableobjectt.hpp"
#include "testik.hpp"

namespace ibrengine
{

DrawableObjectt::DrawableObjectt(MapObject &director):
  Object(director, Object::Type::Drawable)
{
  director.setObject(this);
}

int DrawableObjectt::getTileId() const
{
  return mTileId;
}

void DrawableObjectt::setTileId(int tileId)
{
  mTileId = tileId;
}

}
