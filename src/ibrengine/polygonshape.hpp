// TODO: license text

#ifndef POLYGONSHAPE_HPP
#define POLYGONSHAPE_HPP

#include "shape.hpp"

namespace ibrengine
{

namespace internal
{

class PolygonShape: public Shape
{
public:
  PolygonShape();
  PolygonShape(int pointCount);

  // Points iterators
  PointIterator beginPoints();
  PointCIterator beginPoints() const;
  PointCIterator cBeginPoints() const;
  PointRIterator rBeginPoints();
  PointCRIterator rBeginPoints() const;
  PointCRIterator cRBeginPoints() const;
  PointIterator endPoints();
  PointCIterator endPoints() const;
  PointCIterator cEndPoints() const;
  PointRIterator rEndPoints();
  PointCRIterator rEndPoints() const;
  PointCRIterator cREndPoints() const;

  void addPoint(const Point &p);
  int getPointsCount() const;
  const Point& getPoint(int i) const;
  void setPoint(int i, const Point &p);
  void makeLooped();

private:
  std::vector<Point> mPoints;
};

} // namespace internal
} // namespace ibrengine

#endif // POLYGONSHAPE_HPP
