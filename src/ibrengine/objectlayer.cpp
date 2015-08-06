// license text

#include "objectlayer.hpp"

namespace ibrengine
{

ObjectLayer::ObjectLayer(const std::string& name, int w, int h):
  Layer(name, w, h)
{
}

void ObjectLayer::addObject(const std::shared_ptr<MapObject> &mapObj)
{
  mObjects.push_back(mapObj);
}

const MapObject* ObjectLayer::getObject(int i) const
{
  return mObjects.at(i).get();
}

int ObjectLayer::getObjectsCount() const
{
  return mObjects.size();
}

ObjectLayer::ObjectIterator ObjectLayer::begin()
{
  return mObjects.begin();
}

ObjectLayer::ObjectConstIterator ObjectLayer::begin() const
{
  return mObjects.begin();
}

ObjectLayer::ObjectReverseIterator ObjectLayer::rbegin()
{
  return mObjects.rbegin();
}

ObjectLayer::ObjectConstReverseIterator ObjectLayer::rbegin() const
{
  return mObjects.rbegin();
}

ObjectLayer::ObjectIterator ObjectLayer::end()
{
  return mObjects.end();
}

ObjectLayer::ObjectConstIterator ObjectLayer::end() const
{
  return mObjects.end();
}

ObjectLayer::ObjectReverseIterator ObjectLayer::rend()
{
  return mObjects.rend();
}

ObjectLayer::ObjectConstReverseIterator ObjectLayer::rend() const
{
  return mObjects.rend();
}

} // namespace ibrengine
