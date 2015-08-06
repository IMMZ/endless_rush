// license text

#ifndef MAINCHARACTER_HPP
#define MAINCHARACTER_HPP

#include "mortalobject.hpp"

#include <animation.hpp>

#include <array>

class MainCharacter: public MortalObject
{
public:
  enum class Animation
  {
    WalkRight,
    WalkLeft,
  };

  MainCharacter(); // TODO: extra
  void setAnimation(Animation, ibrengine::Animation *anim);
  const ibrengine::Animation* getCurrentAnimation() const;
  void setCurrentAnimation(Animation anim);

private:
  std::array<ibrengine::Animation*, 2> mAnimations;
  ibrengine::Animation *mCurrentAnimation;
};

#endif // MAINCHARACTER_HPP
