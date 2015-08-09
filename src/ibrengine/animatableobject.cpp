// license text

#include "animatableobject.hpp"

#include "animation.hpp"

namespace ibrengine
{

AnimatableObject::AnimatableObject(const sf::String &name, int tileId):
  TileObject(name, tileId)
{
}

void AnimatableObject::update()
{
  mCurrentAnim->update();
}

void AnimatableObject::addAnimation(const sf::String& animName, Animation* anim)
{
  mAnimations.insert(std::make_pair(animName, anim));
  if (mAnimations.size() == 1)
    mCurrentAnim = anim;
}

void AnimatableObject::setCurrentAnimation(const sf::String& animName)
{
  mCurrentAnim = mAnimations[animName];
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
