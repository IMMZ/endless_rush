// TODO: license text

#ifndef ANIMATABLEOBJECT_HPP
#define ANIMATABLEOBJECT_HPP

#include "animation.hpp"
#include "object.hpp"

#include <SFML/System/String.hpp>

#include <map>
#include "map.hpp" // TOOD: remove!
namespace sf
{

class Time;

}

namespace ibrengine
{

class MapObject;

class AnimatableObject: public Object
{
public:
  AnimatableObject(const sf::String &name, const MapObjectSharedPtr &director, int tileId, int id);

  void addAnimation(const sf::String &animName, Animation *anim);
  void setCurrentAnimation(const sf::String &animName);
  int getCurrentTileId() const;
  void play();
  void stop();
  void reset();

  // Object
  void update(const sf::Time &time) override;

private:
  std::map<sf::String /* name */, Animation*> mAnimations;
  Animation *mCurrentAnim = nullptr;
};

DECLARE_SMART_PTRS(AnimatableObject);

} // namespace ibrengine

#endif // ANIMATABLEOBJECT_HPP
