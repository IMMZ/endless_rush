// TODO: license text

#include "polygonshape.hpp"

namespace ibrengine
{

namespace internal

{

PolygonShape::PolygonShape():
  Shape(Type::Polygon)
{
}

PolygonShape::PolygonShape(int pointCount):
  Shape(Type::Polygon)
{
  mPoints.reserve(pointCount);
}

PolygonShape::PointIterator PolygonShape::beginPoints()
{
  return mPoints.begin();
}

PolygonShape::PointCIterator PolygonShape::beginPoints() const
{
  return mPoints.begin();
}

PolygonShape::PointCIterator PolygonShape::cBeginPoints() const
{
  return mPoints.cbegin();
}

PolygonShape::PointRIterator PolygonShape::rBeginPoints()
{
  return mPoints.rbegin();
}

PolygonShape::PointCRIterator PolygonShape::rBeginPoints() const
{
  return mPoints.rbegin();
}

PolygonShape::PointCRIterator PolygonShape::cRBeginPoints() const
{
  return mPoints.crbegin();
}

PolygonShape::PointIterator PolygonShape::endPoints()
{
  return mPoints.end();
}

PolygonShape::PointCIterator PolygonShape::endPoints() const
{
  return mPoints.end();
}

PolygonShape::PointCIterator PolygonShape::cEndPoints() const
{
  return mPoints.cend();
}

PolygonShape::PointRIterator PolygonShape::rEndPoints()
{
  return mPoints.rend();
}

PolygonShape::PointCRIterator PolygonShape::rEndPoints() const
{
  return mPoints.rend();
}

PolygonShape::PointCRIterator PolygonShape::cREndPoints() const
{
  return mPoints.crend();
}

void PolygonShape::addPoint(const Point& p)
{
  mPoints.push_back(p);
}

int PolygonShape::getPointsCount() const
{
  return mPoints.size();
}

const Point& PolygonShape::getPoint(int i) const
{
  return mPoints[i];
}

void PolygonShape::setPoint(int i, const Point& p)
{
  mPoints[i] = p;
}

void PolygonShape::makeLooped()
{
  mPoints.push_back(mPoints[mPoints.size() - 1]);
}

} // namespace internal
} // namespace ibrengine
