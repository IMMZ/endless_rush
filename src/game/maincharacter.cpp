// license text

#include "maincharacter.hpp"

MainCharacter::MainCharacter()
{
}

void MainCharacter::setAnimation(Animation animation, ibrengine::Animation* anim)
{
  mAnimations[static_cast<int>(Animation::WalkRight)] = anim;
  mCurrentAnimation = mAnimations[static_cast<int>(Animation::WalkRight)];
}

const ibrengine::Animation* MainCharacter::getCurrentAnimation() const
{
  return mCurrentAnimation;
}

void MainCharacter::setCurrentAnimation(Animation anim)
{
  mCurrentAnimation = mAnimations[static_cast<int>(anim)];
}
