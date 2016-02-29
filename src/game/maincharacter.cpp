// license text

#include "maincharacter.hpp"

#include <SFML/System/String.hpp>
#include "../ibrengine/animatableobject.hpp"

MainCharacter::MainCharacter(ibrengine::Object *mapObj):
  MortalObject(mapObj),
  mAnimObj(dynamic_cast<ibrengine::AnimatableObject*>(mapObj))
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
      break;
    }
  }
}

void MainCharacter::update()
{
}
