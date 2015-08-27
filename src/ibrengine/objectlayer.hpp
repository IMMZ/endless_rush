// license text

#ifndef OBJECTLAYER_HPP
#define OBJECTLAYER_HPP

#include "layer.hpp"
#include "mapobject.hpp"

#include <memory>
#include <vector>

namespace ibrengine
{

class ObjectLayer: public Layer
{
public:
  using ObjectIterator = std::vector<std::shared_ptr<MapObject>>::iterator;
  using ObjectConstIterator = std::vector<std::shared_ptr<MapObject>>::const_iterator;
  using ObjectReverseIterator = std::vector<std::shared_ptr<MapObject>>::reverse_iterator;
  using ObjectConstReverseIterator = std::vector<std::shared_ptr<MapObject>>::const_reverse_iterator;

  ObjectLayer(const std::string &name, int w, int h);

  // Object stuff.
  void addObject(const std::shared_ptr<MapObject> &mapObj);
  const MapObject* getObject(int i) const;
  int getObjectsCount() const;
  ObjectIterator begin();
  ObjectConstIterator begin() const;
  ObjectReverseIterator rbegin();
  ObjectConstReverseIterator rbegin() const;
  ObjectIterator end();
  ObjectConstIterator end() const;
  ObjectReverseIterator rend();
  ObjectConstReverseIterator rend() const;

private:
  std::vector<std::shared_ptr<MapObject>> mObjects;
};

} // namespace ibrengine

#endif // OBJECTLAYER_HPP
