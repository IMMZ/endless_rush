// TODO: license text

#include "chainshape.hpp"

namespace ibrengine
{

namespace internal
{

ChainShape::ChainShape():
  Shape(Shape::Type::Chain)
{
}

void ChainShape::addPoint(const Point& p)
{
  mPoints.push_back(p);
}

const Point& ChainShape::getPoint(int i) const
{
  return mPoints.at(i);
}

size_t ChainShape::getPointsCount() const
{
  return mPoints.size();
}

void ChainShape::clear()
{
  mPoints.clear();
}

Shape::PointIterator ChainShape::begin()
{
  return mPoints.begin();
}

ChainShape::PointCIterator ChainShape::begin() const
{
  return mPoints.begin();
}

ChainShape::PointCIterator ChainShape::cbegin() const
{
  return mPoints.cbegin();
}

ChainShape::PointIterator ChainShape::end()
{
  return mPoints.end();
}

ChainShape::PointCIterator ChainShape::end() const
{
  return mPoints.end();
}

ChainShape::PointCIterator ChainShape::cend() const
{
  return mPoints.cend();
}

ChainShape::PointRIterator ChainShape::rbegin()
{
  return mPoints.rbegin();
}

ChainShape::PointCRIterator ChainShape::rbegin() const
{
  return mPoints.rbegin();
}

ChainShape::PointCRIterator ChainShape::crbegin() const
{
  return mPoints.crbegin();
}

ChainShape::PointRIterator ChainShape::rend()
{
  return mPoints.rend();
}

ChainShape::PointCRIterator ChainShape::rend() const
{
  return mPoints.rend();
}

ChainShape::PointCRIterator ChainShape::crend() const
{
  return mPoints.crend();
}

} // namespace internal

} // namespace ibrengine
