// license text

#include "objectlayer.hpp"

namespace ibrengine
{

ObjectLayer::ObjectLayer(const std::string& name, int w, int h):
  Layer(name, Layer::Type::Object, w, h)
{
}

void ObjectLayer::addObject(ObjectScopedPtr obj)
{
  switch (obj->getType())
  {
    case Object::Type::Drawable:
    {
      DrawableObjectScopedPtr ptr =
        internal::dynamic_unique_pointer_cast<Object, DrawableObject>(std::move(obj));
      mDrawableObjs.push_back(std::move(ptr));
      break;
    }
    case Object::Type::Animatable:
    {
      AnimatableObjectScopedPtr ptr =
        internal::dynamic_unique_pointer_cast<Object, AnimatableObject>(std::move(obj));
      mAnimatableObjs.push_back(std::move(ptr));
      break;
    }
    case Object::Type::Physical:
    {
      PhysicalObjectScopedPtr ptr =
        internal::dynamic_unique_pointer_cast<Object, PhysicObject>(std::move(obj));
      mPhysicalObjs.push_back(std::move(ptr));
      break;
    }
  }
}

int ObjectLayer::getObjectsCount(Object::Type objType) const
{
  switch (objType)
  {
    case Object::Type::Drawable:
      return mDrawableObjs.size();
    case Object::Type::Animatable:
      return mAnimatableObjs.size();
    case Object::Type::Physical:
      return mPhysicalObjs.size();
  }
  return 0;
}

int ObjectLayer::getTotalObjectsCount() const
{
  return (mAnimatableObjs.size() + mDrawableObjs.size() + mPhysicalObjs.size());
}

void ObjectLayer::update(const sf::Time &time)
{
  // TODO: How to update?
}

// Drawable objects.
ObjectLayer::DrawableObjectIterator ObjectLayer::beginDrawableObjs()
{
  return mDrawableObjs.begin();
}

ObjectLayer::DrawableObjectCIterator ObjectLayer::beginDrawableObjs() const
{
  return mDrawableObjs.begin();
}

ObjectLayer::DrawableObjectRIterator ObjectLayer::rbeginDrawableObjs()
{
  return mDrawableObjs.rbegin();
}

ObjectLayer::DrawableObjectCRIterator ObjectLayer::rbeginDrawableObjs() const
{
  return mDrawableObjs.rbegin();
}

ObjectLayer::DrawableObjectCIterator ObjectLayer::cbeginDrawableObjs() const
{
  return mDrawableObjs.cbegin();
}

ObjectLayer::DrawableObjectCRIterator ObjectLayer::crbeginDrawableObjs() const
{
  return mDrawableObjs.crbegin();
}

ObjectLayer::DrawableObjectIterator ObjectLayer::endDrawableObjs()
{
  return mDrawableObjs.end();
}

ObjectLayer::DrawableObjectCIterator ObjectLayer::endDrawableObjs() const
{
  return mDrawableObjs.end();
}

ObjectLayer::DrawableObjectRIterator ObjectLayer::rendDrawableObjs()
{
  return mDrawableObjs.rend();
}

ObjectLayer::DrawableObjectCRIterator ObjectLayer::rendDrawableObjs() const
{
  return mDrawableObjs.rend();
}

ObjectLayer::DrawableObjectCIterator ObjectLayer::cendDrawableObjs() const
{
  return mDrawableObjs.cend();
}

ObjectLayer::DrawableObjectCRIterator ObjectLayer::crendDrawableObjs() const
{
  return mDrawableObjs.crend();
}

// Animatable objects.
ObjectLayer::AnimatableObjectIterator ObjectLayer::beginAnimatableObjs()
{
  return mAnimatableObjs.begin();
}

ObjectLayer::AnimatableObjectCIterator ObjectLayer::beginAnimatableObjs() const
{
  return mAnimatableObjs.begin();
}

ObjectLayer::AnimatableObjectRIterator ObjectLayer::rbeginAnimatableObjs()
{
  return mAnimatableObjs.rbegin();
}

ObjectLayer::AnimatableObjectCRIterator ObjectLayer::rbeginAnimatableObjs() const
{
  return mAnimatableObjs.rbegin();
}

ObjectLayer::AnimatableObjectCIterator ObjectLayer::cbeginAnimatableObjs() const
{
  return mAnimatableObjs.cbegin();
}

ObjectLayer::AnimatableObjectCRIterator ObjectLayer::crbeginAnimatableObjs() const
{
  return mAnimatableObjs.crbegin();
}

ObjectLayer::AnimatableObjectIterator ObjectLayer::endAnimatableObjs()
{
  return mAnimatableObjs.end();
}

ObjectLayer::AnimatableObjectCIterator ObjectLayer::endAnimatableObjs() const
{
  return mAnimatableObjs.end();
}

ObjectLayer::AnimatableObjectRIterator ObjectLayer::rendAnimatableObjs()
{
  return mAnimatableObjs.rend();
}

ObjectLayer::AnimatableObjectCRIterator ObjectLayer::rendAnimatableObjs() const
{
  return mAnimatableObjs.rend();
}

ObjectLayer::AnimatableObjectCIterator ObjectLayer::cendAnimatableObjs() const
{
  return mAnimatableObjs.cend();
}

ObjectLayer::AnimatableObjectCRIterator ObjectLayer::crendAnimatableObjs() const
{
  return mAnimatableObjs.crend();
}

// Physical objects.
ObjectLayer::PhysicalObjectIterator ObjectLayer::beginPhysicalObjs()
{
  return mPhysicalObjs.begin();
}

ObjectLayer::PhysicalObjectCIterator ObjectLayer::beginPhysicalObjs() const
{
  return mPhysicalObjs.begin();
}

ObjectLayer::PhysicalObjectRIterator ObjectLayer::rbeginPhysicalObjs()
{
  return mPhysicalObjs.rbegin();
}

ObjectLayer::PhysicalObjectCRIterator ObjectLayer::rbeginPhysicalObjs() const
{
  return mPhysicalObjs.rbegin();
}

ObjectLayer::PhysicalObjectCIterator ObjectLayer::cbeginPhysicalObjs() const
{
  return mPhysicalObjs.cbegin();
}

ObjectLayer::PhysicalObjectCRIterator ObjectLayer::crbeginPhysicalObjs() const
{
  return mPhysicalObjs.crbegin();
}

ObjectLayer::PhysicalObjectIterator ObjectLayer::endPhysicalObjs()
{
  return mPhysicalObjs.end();
}

ObjectLayer::PhysicalObjectCIterator ObjectLayer::endPhysicalObjs() const
{
  return mPhysicalObjs.end();
}

ObjectLayer::PhysicalObjectRIterator ObjectLayer::rendPhysicalObjs()
{
  return mPhysicalObjs.rend();
}

ObjectLayer::PhysicalObjectCRIterator ObjectLayer::rendPhysicalObjs() const
{
  return mPhysicalObjs.rend();
}

ObjectLayer::PhysicalObjectCIterator ObjectLayer::cendPhysicalObjs() const
{
  return mPhysicalObjs.cend();
}

ObjectLayer::PhysicalObjectCRIterator ObjectLayer::crendPhysicalObjs() const
{
  return mPhysicalObjs.crend();
}

} // namespace ibrengine
