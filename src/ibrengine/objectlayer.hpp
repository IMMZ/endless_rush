// license text

#ifndef OBJECTLAYER_HPP
#define OBJECTLAYER_HPP

#include "animatableobject.hpp"
#include "drawableobject.hpp"
#include "layer.hpp"
#include "object.hpp"
#include "physicobject.hpp"

#include <memory>
#include <vector>

namespace ibrengine
{

class ObjectLayer: public Layer
{
public:
  ObjectLayer(const std::string &name, int w, int h);

  // Object stuff.
  void addObject(ObjectUniquePtr obj);

  int getObjectsCount(Object::Type) const;
  int getTotalObjectsCount() const;

  void update(const sf::Time &time);

  // Drawable objects.
  using DrawableObjectIterator =
    std::vector<DrawableObjectUniquePtr>::iterator;
  using DrawableObjectCIterator =
    std::vector<DrawableObjectUniquePtr>::const_iterator;
  using DrawableObjectRIterator =
    std::vector<DrawableObjectUniquePtr>::reverse_iterator;
  using DrawableObjectCRIterator =
    std::vector<DrawableObjectUniquePtr>::const_reverse_iterator;
  
  DrawableObjectIterator beginDrawableObjs();
  DrawableObjectCIterator beginDrawableObjs() const;
  DrawableObjectRIterator rbeginDrawableObjs();
  DrawableObjectCRIterator rbeginDrawableObjs() const;
  DrawableObjectCIterator cbeginDrawableObjs() const;
  DrawableObjectCRIterator crbeginDrawableObjs() const;
  DrawableObjectIterator endDrawableObjs();
  DrawableObjectCIterator endDrawableObjs() const;
  DrawableObjectRIterator rendDrawableObjs();
  DrawableObjectCRIterator rendDrawableObjs() const;
  DrawableObjectCIterator cendDrawableObjs() const;
  DrawableObjectCRIterator crendDrawableObjs() const;

  // Animatable objects.
  using AnimatableObjectIterator =
    std::vector<AnimatableObjectUniquePtr>::iterator;
  using AnimatableObjectCIterator =
    std::vector<AnimatableObjectUniquePtr>::const_iterator;
  using AnimatableObjectRIterator =
    std::vector<AnimatableObjectUniquePtr>::reverse_iterator;
  using AnimatableObjectCRIterator =
    std::vector<AnimatableObjectUniquePtr>::const_reverse_iterator;
  
  AnimatableObjectIterator beginAnimatableObjs();
  AnimatableObjectCIterator beginAnimatableObjs() const;
  AnimatableObjectRIterator rbeginAnimatableObjs();
  AnimatableObjectCRIterator rbeginAnimatableObjs() const;
  AnimatableObjectCIterator cbeginAnimatableObjs() const;
  AnimatableObjectCRIterator crbeginAnimatableObjs() const;
  AnimatableObjectIterator endAnimatableObjs();
  AnimatableObjectCIterator endAnimatableObjs() const;
  AnimatableObjectRIterator rendAnimatableObjs();
  AnimatableObjectCRIterator rendAnimatableObjs() const;
  AnimatableObjectCIterator cendAnimatableObjs() const;
  AnimatableObjectCRIterator crendAnimatableObjs() const;
  
  // Physical objects.
  using PhysicalObjectIterator =
    std::vector<PhysicObjectUniquePtr>::iterator;
  using PhysicalObjectCIterator =
    std::vector<PhysicObjectUniquePtr>::const_iterator;
  using PhysicalObjectRIterator =
    std::vector<PhysicObjectUniquePtr>::reverse_iterator;
  using PhysicalObjectCRIterator =
    std::vector<PhysicObjectUniquePtr>::const_reverse_iterator;
  
  PhysicalObjectIterator beginPhysicalObjs();
  PhysicalObjectCIterator beginPhysicalObjs() const;
  PhysicalObjectRIterator rbeginPhysicalObjs();
  PhysicalObjectCRIterator rbeginPhysicalObjs() const;
  PhysicalObjectCIterator cbeginPhysicalObjs() const;
  PhysicalObjectCRIterator crbeginPhysicalObjs() const;
  PhysicalObjectIterator endPhysicalObjs();
  PhysicalObjectCIterator endPhysicalObjs() const;
  PhysicalObjectRIterator rendPhysicalObjs();
  PhysicalObjectCRIterator rendPhysicalObjs() const;
  PhysicalObjectCIterator cendPhysicalObjs() const;
  PhysicalObjectCRIterator crendPhysicalObjs() const;

private:
  std::vector<DrawableObjectUniquePtr> mDrawableObjs;
  std::vector<AnimatableObjectUniquePtr> mAnimatableObjs;
  std::vector<PhysicObjectUniquePtr> mPhysicalObjs;
};

DECLARE_SMART_PTRS(ObjectLayer);

} // namespace ibrengine

#endif // OBJECTLAYER_HPP
