// TODO: license text

#include "circle.hpp"

namespace ibrengine
{

namespace internal
{

Circle::Circle(float diameter):
  Shape(Shape::Type::Circle),
  mDiameter(diameter)
{
}

float Circle::getDiameter() const
{
  return mDiameter;
}

float Circle::getRadius() const
{
  return mDiameter / 2.0f;
}

} // namespace internal

} // namespace ibrengine
