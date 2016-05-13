// TODO: license text

#include "drawableobject.hpp"

#include "mapobject.hpp"

namespace ibrengine
{

DrawableObject::DrawableObject(MapObject &director):
  Object(director, Object::Type::Drawable)
{
  director.setObject(this);
}

int DrawableObject::getTileId() const
{
  return mTileId;
}

void DrawableObject::setTileId(int tileId)
{
  mTileId = tileId;
}

float DrawableObject::getRotation() const
{
  return mRotation;
}

void DrawableObject::setRotation(float rotation)
{
  mRotation = rotation;
}

bool DrawableObject::isVisible() const
{
  return getMapObject().isVisible();
}

void DrawableObject::update(const sf::Time &time)
{
}

}
