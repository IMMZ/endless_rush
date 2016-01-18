// TODO: license text

#ifndef ANIMATABLEOBJECTT_HPP_
#define ANIMATABLEOBJECTT_HPP_

#include "object.hpp"

#include <map>

namespace sf
{

class String;
class Time;

}

namespace ibrengine
{

class Animation;
class MapObject;

class AnimatableObjectt: public Object
{
public:
  AnimatableObjectt(const sf::String &name, MapObject &director, int tileId);

  // Object
  void update(const sf::Time &time) override;

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

#endif // ANIMATABLEOBJECTT_HPP_
