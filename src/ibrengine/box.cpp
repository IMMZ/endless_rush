// TODO: license text

#include "box.hpp"

namespace ibrengine
{

namespace internal
{

Box::Box(int width, int height):
  Shape(Shape::Type::Box),
  mWidth(width), mHeight(height)
{
}

int Box::getWidth() const
{
  return mWidth;
}

int Box::getHeight() const
{
  return mHeight;
}

} // namespace internal

} // namespace ibrengine
