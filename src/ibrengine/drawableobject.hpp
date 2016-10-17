// TODO: license text

#ifndef DRAWABLEOBJECT_HPP
#define DRAWABLEOBJECT_HPP

#include "object.hpp"

namespace ibrengine
{

class DrawableObject: public Object
{
public:
  explicit DrawableObject(const MapObjectSharedPtr &director, int id);

  int getTileId() const;
  void setTileId(int tileId);
  float getRotation() const;
  void setRotation(float rotation);
  bool isVisible() const;

  // Object.
  void update(const sf::Time &time) override;

private:
  float mRotation = 0.0f;
  int mTileId = -1;
};

DECLARE_SMART_PTRS(DrawableObject);

} // namespace ibrengine

#endif // DRAWABLEOBJECT_HPP
