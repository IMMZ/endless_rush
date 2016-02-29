// TODO: license text

#include "animatableobject.hpp"

#include "mapobject.hpp"

namespace ibrengine
{

AnimatableObject::AnimatableObject(const sf::String &name, MapObject &director, int tileId):
  Object(director, Object::Type::Animatable)
{
  director.setObject(this);
}

void AnimatableObject::update(const sf::Time &time)
{
  mCurrentAnim->update(time);
  this->setChanged();
}

void AnimatableObject::addAnimation(const sf::String &animName, Animation *anim)
{
  mAnimations.insert(std::make_pair(animName, *anim));
  if (mCurrentAnim == nullptr)
    mCurrentAnim = &mAnimations[animName];
}

void AnimatableObject::setCurrentAnimation(const sf::String &animName)
{
  mCurrentAnim = &mAnimations[animName];
}

int AnimatableObject::getCurrentTileId() const
{
  return mCurrentAnim->getCurrentTileId();
}

void AnimatableObject::play()
{
  mCurrentAnim->play();
}

void AnimatableObject::stop()
{
  mCurrentAnim->stop();
}

void AnimatableObject::reset()
{
  mCurrentAnim->reset();
}

} // namespace ibrengine
