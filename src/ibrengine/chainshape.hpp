// TODO: license text

#ifndef CHAINSHAPE_HPP_
#define CHAINSHAPE_HPP_

#include "global.hpp"
#include "shape.hpp"

namespace ibrengine
{

namespace internal
{

class ChainShape: public Shape
{
public:
  ChainShape();

  void addPoint(const Point &p);
  void addPoint(Point &&p);
  const Point& getPoint(int i) const;
  size_t getPointsCount() const;
  void clear();

  PointIterator begin();
  PointCIterator begin() const;
  PointCIterator cbegin() const;
  PointIterator end();
  PointCIterator end() const;
  PointCIterator cend() const;
  PointRIterator rbegin();
  PointCRIterator rbegin() const;
  PointCRIterator crbegin() const;
  PointRIterator rend();
  PointCRIterator rend() const;
  PointCRIterator crend() const;

private:
  std::vector<Point> mPoints;
};

} // namespace internal

} // namespace ibrengine

#endif // CHAINSHAPE_HPP_
