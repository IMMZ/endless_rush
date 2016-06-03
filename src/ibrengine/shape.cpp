// TODO: license text

#include "shape.hpp"

namespace ibrengine
{

namespace internal
{

Shape::Shape(Type type):
  mType(type)
{
}

Shape::Type Shape::getType() const
{
  return mType;
}

bool Shape::isValid() const
{
  return mType != Type::Invalid;
}

const PositionI& Shape::getPosition() const
{
  return mPos;
}

void Shape::setPosition(const PositionI &pos)
{
  mPos = pos;
}

} // namespace internal

} // namespace ibrengine
