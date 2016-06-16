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
  AnimatableObject(const sf::String &name, const MapUnitPtr &director, int tileId);

  void addAnimation(const sf::String &animName, Animation *anim);
  void setCurrentAnimation(const sf::String &animName);
  int getCurrentTileId() const;
  void play();
  void stop();
  void reset();

  // Object
  void update(const sf::Time &time) override;

  // TODO: refactor!
  Map *mMap;

private:
  std::map<sf::String /* name */, Animation> mAnimations;
  Animation *mCurrentAnim = nullptr;
};

using AnimatableObjectScopedPtr = std::unique_ptr<AnimatableObject>;
using AnimatableObjectSharedPtr = std::shared_ptr<AnimatableObject>;
using AnimatableObjectWeakPtr = std::weak_ptr<AnimatableObject>;

} // namespace ibrengine

#endif // ANIMATABLEOBJECT_HPP
