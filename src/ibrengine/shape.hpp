// TODO: license text

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "global.hpp"

#include <vector>

namespace ibrengine
{

namespace internal
{

class Shape
{
public:
  ENABLE_DEFAULT_MOVE(Shape);

  using PointIterator = std::vector<Point>::iterator;
  using PointCIterator = std::vector<Point>::const_iterator;
  using PointRIterator = std::vector<Point>::reverse_iterator;
  using PointCRIterator = std::vector<Point>::const_reverse_iterator;

  enum class Type
  {
    Invalid,
    Box,
    Circle,
    Chain,
    Polygon
  };

  Shape(Type type = Type::Invalid);
  virtual ~Shape() = default;

  Type getType() const;
  bool isValid() const;
  const PositionI& getPosition() const;
  void setPosition(const PositionI &pos);
  bool isLinkedToTile() const;
  void setLinkedToTile(bool linked);

private:
  PositionI mPos = { 0, 0 };
  Type mType = Type::Invalid;
  bool mLinkedToTile = false; // Need for correct positioning of fixture with box2d
};

} // namespace internal

} // namespace ibrengine

#endif // SHAPE_HPP
