// TODO: license

#ifndef INGAMESTATE_HPP
#define INGAMESTATE_HPP

#include "igamestate.hpp"

#include "gameworld.hpp"

#include <maprenderer.hpp>
#include <physicworld.hpp>

#include <memory>

namespace ibrengine
{

class Map;

}

namespace internal
{

class InGameState: public IGameState
{
public:
  InGameState();

  // IGameState
  void draw(sf::RenderTarget &target) override;
  void handleInput(Input::Action act) override;
  void update(const sf::Time &time) override;

  void setMap(ibrengine::Map *map);
  void setDebugDraw(::ibrengine::DebugDraw *dd) override
  {
    mPhysicWorld->setDebugDraw(dd);
  }

private:
  std::unique_ptr<ibrengine::MapRenderer> mRenderer;
  std::unique_ptr<GameWorld> mGameWorld;
  std::unique_ptr<ibrengine::PhysicWorld> mPhysicWorld;
  ibrengine::Map *mMap = nullptr;

};

} // namespace internal

#endif // INGAMESTATE_HPP
