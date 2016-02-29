// TODO: license text

#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"

namespace ibrengine
{

namespace internal
{

class Box: public Shape
{
public:
  Box(int width, int height);

  int getWidth() const;
  int getHeight() const;

private:
  int mWidth = 0, mHeight = 0;
};

} // namespace internal

} // namespace ibrengine

#endif // BOX_HPP
