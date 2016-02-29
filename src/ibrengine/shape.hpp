// TODO: license text

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "global.hpp"

namespace ibrengine
{

namespace internal
{

class Shape
{
public:
  enum class Type
  {
    Invalid,
    Box,
    Circle
  };

  Shape(Type type = Type::Invalid);
  virtual ~Shape();

  Type getType() const;
  bool isValid() const;
  const PositionI& getPosition() const;
  void setPosition(const PositionI &pos);

private:
  PositionI mPos = { 0, 0 };
  Type mType = Type::Invalid;
};

} // namespace internal

} // namespace ibrengine

#endif // SHAPE_HPP
