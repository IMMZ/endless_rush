// license text

#include "complexshape.hpp"

namespace ibrengine
{

ComplexShape::ComplexShape(const sf::String& name, Type type):
  mType(type)
{
}

void ComplexShape::addPoint(const sf::Vector2i &p)
{
  mPoints.push_back(p);
}

sf::Vector2i ComplexShape::getPoint(int i) const
{
  return mPoints.at(i);
}

int ComplexShape::getPointsCount() const
{
  return mPoints.size();
}

ComplexShape::PointIterator ComplexShape::begin()
{
  return mPoints.begin();
}

ComplexShape::PointConstIterator ComplexShape::begin() const
{
  return mPoints.begin();
}

ComplexShape::PointReverseIterator ComplexShape::rbegin()
{
  return mPoints.rbegin();
}

ComplexShape::PointConstReverseIterator ComplexShape::rbegin() const
{
  return mPoints.rbegin();
}

ComplexShape::PointIterator ComplexShape::end()
{
  return mPoints.end();
}

ComplexShape::PointConstIterator ComplexShape::end() const
{
  return mPoints.end();
}

ComplexShape::PointReverseIterator ComplexShape::rend()
{
  return mPoints.rend();
}

ComplexShape::PointConstReverseIterator ComplexShape::rend() const
{
  return mPoints.rend();
}

ComplexShape::Type ComplexShape::getType() const
{
  return mType;
}

} // namespace ibrengine
