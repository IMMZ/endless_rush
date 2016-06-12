// TODO: license text

#ifndef DRAWABLEOBJECT_HPP_
#define DRAWABLEOBJECT_HPP_

#include "object.hpp"

namespace ibrengine
{

class DrawableObject: public Object
{
public:
  explicit DrawableObject(const MapUnitPtr &director);

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

using DrawableObjectScopedPtr = std::unique_ptr<DrawableObject>;

} // namespace ibrengine

#endif // DRAWABLEOBJECT_HPP_
