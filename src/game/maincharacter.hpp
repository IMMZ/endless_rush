// license text

#ifndef MAINCHARACTER_HPP
#define MAINCHARACTER_HPP

#include "mortalobject.hpp"
#include "object.hpp"

#include <animation.hpp>

#include <array>

namespace ibrengine
{

class AnimatableObjectt;

}

class MainCharacter: public MortalObject
{
public:
  enum class State
  {
    Staying,
    WalkingR,
    WalkingL,
    Beating,
    Shooting = Beating
  };

  MainCharacter(ibrengine::Object *mapObj);

  State getState() const;
  void setState(State s);
  void update();

private:
  ibrengine::AnimatableObjectt *mAnimObj = nullptr;
  State mState = State::Staying;
};

#endif // MAINCHARACTER_HPP
