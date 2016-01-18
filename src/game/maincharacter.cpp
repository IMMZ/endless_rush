// license text

#include "maincharacter.hpp"

#include <animatableobjectt.hpp>

#include <SFML/System/String.hpp>

MainCharacter::MainCharacter(ibrengine::Object *mapObj):
  MortalObject(mapObj),
  mAnimObj(dynamic_cast<ibrengine::AnimatableObjectt*>(mapObj))
{
}

MainCharacter::State MainCharacter::getState() const
{
  return mState;
}

void MainCharacter::setState(State s)
{
  mState = s;
  switch (mState)
  {
    case State::Staying:
    {
      mAnimObj->setCurrentAnimation("anim_walk_r");
      break;
    }
    case State::Beating:
    {
      mAnimObj->setCurrentAnimation("anim_beat");
      break;
    }
  }
}

void MainCharacter::update()
{
}
