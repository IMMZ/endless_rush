// license text

#ifndef OBJECTLAYER_HPP
#define OBJECTLAYER_HPP

#include "layer.hpp"
#include "mapobject.hpp"

#include <memory>
#include <vector>

namespace ibrengine
{

class AnimatableObjectt;
class DrawableObjectt;
class PhysicalObjectt;

class ObjectLayer: public Layer
{
public:
  using MapUnitIterator = std::vector<MapObject*>::iterator;
  using MapUnitCIterator = std::vector<MapObject*>::const_iterator;
  using MapUnitRIterator = std::vector<MapObject*>::reverse_iterator;
  using MapUnitCRIterator = std::vector<MapObject*>::const_reverse_iterator;

  using DrawableObjectIterator = std::vector<DrawableObjectt*>::iterator;
  using DrawableObjectCIterator = std::vector<DrawableObjectt*>::const_iterator;
  using DrawableObjectRIterator = std::vector<DrawableObjectt*>::reverse_iterator;
  using DrawableObjectCRIterator = std::vector<DrawableObjectt*>::const_reverse_iterator;

  using PhysicalObjectIterator = std::vector<PhysicalObjectt*>::iterator;
  using PhysicalObjectCIterator = std::vector<PhysicalObjectt*>::const_iterator;
  using PhysicalObjectRIterator = std::vector<PhysicalObjectt*>::reverse_iterator;
  using PhysicalObjectCRIterator = std::vector<PhysicalObjectt*>::const_reverse_iterator;

  using AnimatableObjectIterator = std::vector<AnimatableObjectt*>::iterator;
  using AnimatableObjectCIterator = std::vector<AnimatableObjectt*>::const_iterator;
  using AnimatableObjectRIterator = std::vector<AnimatableObjectt*>::reverse_iterator;
  using AnimatableObjectCRIterator = std::vector<AnimatableObjectt*>::const_reverse_iterator;

  ObjectLayer(const std::string &name, int w, int h);

  // Object stuff.
  void addMapObject(const std::shared_ptr<MapObject> &mapObj);
  void addDrawableObject(DrawableObjectt *drawableObj);
  void addPhysicalObject(PhysicalObjectt *physicalObj);
  void addAnimatableObject(AnimatableObjectt *animatableObj);

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

  void foo()
  {
    int a = 5;
    //hfcc

    //sgjhthgbrtjhgre
  }

  // There is no need to delete the objects below. They all be deleted by their directors.
  std::vector<DrawableObjectt*> mDrawableObjs;
  // The rhytm of loev
  std::vector<PhysicalObjectt*> mPhysicalObjs;
  std::vector<AnimatableObjectt*> mAnimatableObjs;
};

} // namespace ibrengine

#endif // OBJECTLAYER_HPP
