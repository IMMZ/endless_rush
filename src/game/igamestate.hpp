// TODO: license

#ifndef IGAMESTATE_HPP
#define IGAMESTATE_HPP

#include "gamestate.hpp"
#include "input.hpp"

#include <SFML/System/String.hpp>

namespace sf
{

class RenderTarget;
class Time;

}

namespace internal
{

class IGameState
{
public:
  virtual ~IGameState() {};

  virtual void draw(sf::RenderTarget &target) = 0; // TODO: remove rendertarget parameter - use getRenderTarget() instead
  virtual void handleInput(Input::Action act) = 0;
  virtual void update(const sf::Time &time) = 0;

  bool isStateChangeRequested() const { return mStateChangeRequested; }
  GameState requestedState() const { return mState; }
  sf::RenderTarget* getRenderTarget() { return mRenderTarget; }
  void setRenderTarget(sf::RenderTarget *target) { mRenderTarget = target; }
  const sf::String& getUsedSound() const { return mUsedSound; }

protected:
  void setUsedSound(const sf::String &usedSound) { mUsedSound = usedSound; }
  void requestStateChange(GameState state) { mState = state; mStateChangeRequested = true; }

private:
  sf::String mUsedSound;
  sf::RenderTarget *mRenderTarget = nullptr;
  GameState mState = GameState::Undefined;
  bool mStateChangeRequested = false;
};

} // namespace internal

#endif // IGAMESTATE_HPP
