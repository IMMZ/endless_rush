// TODO: license text

#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace ibrengine
{

namespace internal
{

class Circle: public Shape
{
public:
  Circle(float diameter);

  float getDiameter() const;
  float getRadius() const;

private:
  float mDiameter;
};

} // namespace internal

} // namespace ibrengine

#endif // CIRCLE_HPP
