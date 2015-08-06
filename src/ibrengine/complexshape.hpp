// license text

#ifndef COMPLEXSHAPE_HPP
#define COMPLEXSHAPE_HPP

#include "mapobject.hpp"

#include <vector>

namespace ibrengine
{

class ComplexShape: public MapObject
{
public:
  typedef std::vector<sf::Vector2i>::iterator PointIterator;
  typedef std::vector<sf::Vector2i>::const_iterator PointConstIterator;
  typedef std::vector<sf::Vector2i>::reverse_iterator PointReverseIterator;
  typedef std::vector<sf::Vector2i>::const_reverse_iterator PointConstReverseIterator;

  enum class Type { Polyline, Polygon };

  ComplexShape(const sf::String &name, Type type);

  // Points stuff
  void addPoint(const sf::Vector2i &p);
  sf::Vector2i getPoint(int i) const;
  int getPointsCount() const;
  PointIterator begin();
  PointConstIterator begin() const;
  PointReverseIterator rbegin();
  PointConstReverseIterator rbegin() const;
  PointIterator end();
  PointConstIterator end() const;
  PointReverseIterator rend();
  PointConstReverseIterator rend() const;

  Type getType() const;

private:
  std::vector<sf::Vector2i> mPoints;
  Type mType;
};

} // namespace ibrengine

#endif // COMPLEXSHAPE_HPP
