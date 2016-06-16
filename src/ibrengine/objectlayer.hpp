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
  void addObject(ObjectScopedPtr &&obj);

  int getObjectsCount(Object::Type) const;
  int getTotalObjectsCount() const;

  void update(const sf::Time &time);

  // Drawable objects.
  using DrawableObjectIterator =
    std::vector<DrawableObjectScopedPtr>::iterator;
  using DrawableObjectCIterator =
    std::vector<DrawableObjectScopedPtr>::const_iterator;
  using DrawableObjectRIterator =
    std::vector<DrawableObjectScopedPtr>::reverse_iterator;
  using DrawableObjectCRIterator =
    std::vector<DrawableObjectScopedPtr>::const_reverse_iterator;
  
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
    std::vector<AnimatableObjectScopedPtr>::iterator;
  using AnimatableObjectCIterator =
    std::vector<AnimatableObjectScopedPtr>::const_iterator;
  using AnimatableObjectRIterator =
    std::vector<AnimatableObjectScopedPtr>::reverse_iterator;
  using AnimatableObjectCRIterator =
    std::vector<AnimatableObjectScopedPtr>::const_reverse_iterator;
  
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
    std::vector<PhysicalObjectScopedPtr>::iterator;
  using PhysicalObjectCIterator =
    std::vector<PhysicalObjectScopedPtr>::const_iterator;
  using PhysicalObjectRIterator =
    std::vector<PhysicalObjectScopedPtr>::reverse_iterator;
  using PhysicalObjectCRIterator =
    std::vector<PhysicalObjectScopedPtr>::const_reverse_iterator;
  
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
  std::vector<DrawableObjectScopedPtr> mDrawableObjs;
  std::vector<AnimatableObjectScopedPtr> mAnimatableObjs;
  std::vector<PhysicalObjectScopedPtr> mPhysicalObjs;
};

} // namespace ibrengine

#endif // OBJECTLAYER_HPP
