// license text

#include "objectlayer.hpp"
#include "testik.hpp"

namespace ibrengine
{

ObjectLayer::ObjectLayer(const std::string& name, int w, int h):
  Layer(name, w, h)
{
}

void ObjectLayer::addMapObject(const std::shared_ptr<MapObject> &mapObj)
{
  mDirectors.push_back(mapObj);
}

void ObjectLayer::addDrawableObject(DrawableObjectt *drawableObj)
{
  mDrawableObjs.push_back(drawableObj);
}

void ObjectLayer::addPhysicalObject(PhysicalObjectt *physicalObj)
{
  mPhysicalObjs.push_back(physicalObj);
}

void ObjectLayer::addAnimatableObject(AnimatableObjectt *animatableObj)
{
  mAnimatableObjs.push_back(animatableObj);
}

int ObjectLayer::getObjectsCount(Object::Type objType) const
{
  switch (objType)
  {
    case Object::Type::Drawable:   { return mDrawableObjs.size(); }
    case Object::Type::Physical:   { return mPhysicalObjs.size(); }
    case Object::Type::Animatable: { return mAnimatableObjs.size(); }
    case Object::Type::Full:             { return mDrawableObjs.size()
                                            + mPhysicalObjs.size()
                                            + mAnimatableObjs.size(); }
    default: break; // TODO: warn about Unknown obj type.
  }
}

int ObjectLayer::getTotalObjectsCount() const
{
  return (mDrawableObjs.size() + mPhysicalObjs.size() + mAnimatableObjs.size());
}

void ObjectLayer::update(const sf::Time &time)
{
  /*for (std::shared_ptr<ObjectDirector> &director: mDirectors)
    director->update(time);*/
  for (AnimatableObjectt *anim: mAnimatableObjs)
    anim->update(time);
}

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

} // namespace ibrengine
