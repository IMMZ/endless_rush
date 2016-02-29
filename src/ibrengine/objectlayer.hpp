// license text

#ifndef OBJECTLAYER_HPP
#define OBJECTLAYER_HPP

#include "layer.hpp"
#include "mapobject.hpp"

#include <memory>
#include <vector>

namespace ibrengine
{

class AnimatableObject;
class AnimatablePhysObject;
class DrawableObject;
class PhysicObject;

class ObjectLayer: public Layer
{
public:
  using MapUnitIterator = std::vector<MapObject*>::iterator;
  using MapUnitCIterator = std::vector<MapObject*>::const_iterator;
  using MapUnitRIterator = std::vector<MapObject*>::reverse_iterator;
  using MapUnitCRIterator = std::vector<MapObject*>::const_reverse_iterator;

  using DrawableObjectIterator = std::vector<DrawableObject*>::iterator;
  using DrawableObjectCIterator = std::vector<DrawableObject*>::const_iterator;
  using DrawableObjectRIterator = std::vector<DrawableObject*>::reverse_iterator;
  using DrawableObjectCRIterator = std::vector<DrawableObject*>::const_reverse_iterator;

  using PhysicalObjectIterator = std::vector<PhysicObject*>::iterator;
  using PhysicalObjectCIterator = std::vector<PhysicObject*>::const_iterator;
  using PhysicalObjectRIterator = std::vector<PhysicObject*>::reverse_iterator;
  using PhysicalObjectCRIterator = std::vector<PhysicObject*>::const_reverse_iterator;

  using AnimatableObjectIterator = std::vector<AnimatableObject*>::iterator;
  using AnimatableObjectCIterator = std::vector<AnimatableObject*>::const_iterator;
  using AnimatableObjectRIterator = std::vector<AnimatableObject*>::reverse_iterator;
  using AnimatableObjectCRIterator = std::vector<AnimatableObject*>::const_reverse_iterator;

  using AnimatablePhysObjectIterator = std::vector<AnimatablePhysObject*>::iterator;
  using AnimatablePhysObjectCIterator = std::vector<AnimatablePhysObject*>::const_iterator;
  using AnimatablePhysObjectRIterator = std::vector<AnimatablePhysObject*>::reverse_iterator;
  using AnimatablePhysObjectCRIterator = std::vector<AnimatablePhysObject*>::const_reverse_iterator;

  ObjectLayer(const std::string &name, int w, int h);

  // Object stuff.
  void addMapObject(const std::shared_ptr<MapObject> &mapObj);
  void addDrawableObject(DrawableObject *drawableObj);
  void addPhysicalObject(PhysicObject *physicalObj);
  void addAnimatableObject(AnimatableObject *animatableObj);
  void addAnimatablePhysObject(AnimatablePhysObject *animPhysObj);

  int getObjectsCount(Object::Type) const;
  int getTotalObjectsCount() const;

  void update(const sf::Time &time);

  // Iterators for drawable objects.
  DrawableObjectIterator beginDrawableObjs();
  DrawableObjectCIterator beginDrawableObjs() const;
  DrawableObjectRIterator rbeginDrawableObjs();
  DrawableObjectCRIterator rbeginDrawableObjs() const;
  DrawableObjectIterator endDrawableObjs();
  DrawableObjectCIterator endDrawableObjs() const;
  DrawableObjectRIterator rendDrawableObjs();
  DrawableObjectCRIterator rendDrawableObjs() const;

  // Iterators for physical objects.
  PhysicalObjectIterator beginPhysicalObjs();
  PhysicalObjectCIterator beginPhysicalObjs() const;
  PhysicalObjectRIterator rbeginPhysicalObjs();
  PhysicalObjectCRIterator rbeginPhysicalObjs() const;
  PhysicalObjectIterator endPhysicalObjs();
  PhysicalObjectCIterator endPhysicalObjs() const;
  PhysicalObjectRIterator rendPhysicalObjs();
  PhysicalObjectCRIterator rendPhysicalObjs() const;

  // Iterators for animatable objects.
  AnimatableObjectIterator beginAnimatableObjs();
  AnimatableObjectCIterator beginAnimatableObjs() const;
  AnimatableObjectRIterator rbeginAnimatableObjs();
  AnimatableObjectCRIterator rbeginAnimatableObjs() const;
  AnimatableObjectIterator endAnimatableObjs();
  AnimatableObjectCIterator endAnimatableObjs() const;
  AnimatableObjectRIterator rendAnimatableObjs();
  AnimatableObjectCRIterator rendAnimatableObjs() const;

private:
  std::vector<std::shared_ptr<MapObject>> mDirectors;

  // There is no need to delete the objects below. They all be deleted by their directors.
  std::vector<DrawableObject*> mDrawableObjs;
  std::vector<PhysicObject*> mPhysicalObjs;
  std::vector<AnimatableObject*> mAnimatableObjs;
};

} // namespace ibrengine

#endif // OBJECTLAYER_HPP
