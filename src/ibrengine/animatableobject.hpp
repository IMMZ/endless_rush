// license text

#ifndef ANIMATABLEOBJECT_HPP
#define ANIMATABLEOBJECT_HPP

#include "tileobject.hpp"

#include <map>

namespace ibrengine
{

class Animation;

class AnimatableObject: public TileObject
{
public:
  AnimatableObject(const sf::String &name, int tileId);

  // MapObject
  void update() override;

  void addAnimation(const sf::String &animName, Animation *anim);
  void setCurrentAnimation(const sf::String &animName);
  int getCurrentTileId() const;
  void play();
  void stop();
  void reset();

private:
  std::map<sf::String /* name */, Animation*> mAnimations;
  Animation *mCurrentAnim = nullptr;
};

} // namespace ibrengine

#endif // ANIMATABLEOBJECT_HPP_
