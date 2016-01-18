// TODO: license text

#include "animatableobjectt.hpp"
#include "animation.hpp"
#include "testik.hpp"

namespace ibrengine
{

AnimatableObjectt::AnimatableObjectt(const sf::String &name, MapObject &director, int tileId):
  Object(director, Object::Type::Animatable)
{
  director.setObject(this);
}

void AnimatableObjectt::update(const sf::Time &time)
{
  mCurrentAnim->update(time);
  this->setChanged();
}

void AnimatableObjectt::addAnimation(const sf::String &animName, Animation *anim)
{
  mAnimations.insert(std::make_pair(animName, anim));
  if (mCurrentAnim == nullptr)
    mCurrentAnim = anim;
}

void AnimatableObjectt::setCurrentAnimation(const sf::String &animName)
{
  mCurrentAnim = mAnimations[animName];
}

int AnimatableObjectt::getCurrentTileId() const
{
  return mCurrentAnim->getCurrentTileId();
}

void AnimatableObjectt::play()
{
  mCurrentAnim->play();
}

void AnimatableObjectt::stop()
{
  mCurrentAnim->stop();
}

void AnimatableObjectt::reset()
{
  mCurrentAnim->reset();
}

} // namespace ibrengine
