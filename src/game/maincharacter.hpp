// license text

#ifndef MAINCHARACTER_HPP
#define MAINCHARACTER_HPP

#include "mortalobject.hpp"

#include <array>

class MainCharacter: public MortalObject
{
public:
  enum class Animation
  {
    WalkRight,
    WalkLeft,
  };

  explicit MainCharacter(const ibrengine::MapObject *mapObj);

private:
  std::array<ibrengine::Animation, 2> mAnimations;
};

#endif // MAINCHARACTER_HPP
